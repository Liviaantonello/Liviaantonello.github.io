import socket

HOST = "0.0.0.0"
PORT = 4533

azimuth = 0.0
elevation = 0.0

print(f"[INFO] Rotator TCP server started on {HOST}:{PORT} (minimal rotctld protocol)")

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((HOST, PORT))
    server.listen()

    while True:
        conn, addr = server.accept()
        print(f"[INFO] Connection from {addr}")
        with conn:
            while True:
                try:
                    data = conn.recv(1024)
                    if not data:
                        break
                    command = data.decode().strip()
                    print(f"[RX] {command}")

                    if command.lower() == 'p':
                        response = f"{azimuth:.2f}\n{elevation:.2f}\n"
                        conn.sendall(response.encode())
                        print(f"[TX] {response.strip()}")

                    elif command.startswith('P '):
                        try:
                            _, az_str, el_str = command.split()
                            azimuth = float(az_str)
                            elevation = float(el_str)
                            print(f"[INFO] Tracking updated: AZ={azimuth}, EL={elevation}")

                            # Update real-time buffer for C++ backend
                            with open("last_command.txt", "w") as f:
                                f.write(f"{azimuth:.2f},{elevation:.2f}\n")
                            with open("log_commands.csv", "a") as log:
                                log.write(f"{azimuth:.2f},{elevation:.2f}\n")

                            conn.sendall(b"RPRT 0\n")
                        except Exception as e:
                            print(f"[PARSE ERROR]: {e}")
                            conn.sendall(b"RPRT -1\n")

                    elif command.upper() == 'S':
                        conn.sendall(b"RPRT 0\n")

                    elif command.lower() == 'v':
                        conn.sendall(b"rotctld LiviaPi 0.1\n")

                    elif command.lower() == 'q':
                        print("[INFO] Closure requested by client")
                        break

                    else:
                        conn.sendall(b"RPRT -1\n")
                        print(f"[IGNORED] Unknown command: {command}")

                except Exception as e:
                    print(f"[CONNECTION ERROR]: {e}")
                    break