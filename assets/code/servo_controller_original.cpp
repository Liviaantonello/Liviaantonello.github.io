#include <iostream>
#include <fstream>
#include <string>
#include <pigpio.h>
#include <unistd.h>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;

// ---------- Servo Parameters ----------
static const int SERVO_GPIO = 18;
static const int SERVO_MIN_US = 1000;
static const int SERVO_MAX_US = 2000;

// Deadband to reduce jitter (in degrees)
static const double ANGLE_TOL = 0.6;

// ---------- Utilities ----------
bool readSatelliteData(const string& filename, double& az, double& el) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    if (!getline(file, line)) return false;

    size_t commaPos = line.find(',');
    if (commaPos == string::npos) return false;

    try {
        az = stod(line.substr(0, commaPos));
        el = stod(line.substr(commaPos + 1));
    } catch (...) {
        return false;
    }
    return true;
}

// Converts degrees [0..180] -> microseconds for pigpio
int angleToPulseWidth(double angleDeg) {
    if (angleDeg < 0)   angleDeg = 0;
    if (angleDeg > 180) angleDeg = 180;
    double ratio = angleDeg / 180.0;
    int us = static_cast<int>(SERVO_MIN_US + ratio * (SERVO_MAX_US - SERVO_MIN_US));
    return us;
}

// Normalizes azimuth 0..360 and maps to 0..180 (servo half-turn).
double mapAzToServo180(double azDeg) {
    // constrain to [0,360)
    double a = fmod(azDeg, 360.0);
    if (a < 0) a += 360.0;

    // map to [0,180]: 0..180 -> same angle; 180..360 -> angle-180 (wrap)
    if (a <= 180.0) return a;
    return a - 180.0;
}

int main() {
    if (gpioInitialise() < 0) {
        cerr << "pigpio initialization failed.\n";
        return 1;
    }

    const string filename = "last_command.txt";

    // Set servo to neutral position (90°) at startup
    gpioServo(SERVO_GPIO, angleToPulseWidth(90.0));

    double az = 0.0, el = 0.0;
    double lastCmdAngle = -1.0; // invalid to force first set

    while (true) {
        if (!readSatelliteData(filename, az, el)) {
            // If read fails, maintain current position
            this_thread::sleep_for(chrono::milliseconds(200));
            continue;
        }

        // Direct follow using half-turn mapping
        double targetAngle = mapAzToServo180(az);

        // Filter small variations (jitter)
        if (lastCmdAngle < 0 || fabs(targetAngle - lastCmdAngle) > ANGLE_TOL) {
            int pw = angleToPulseWidth(targetAngle);
            gpioServo(SERVO_GPIO, pw);

            cout << "AZ target: " << az
                 << " -> servoAngle: " << targetAngle
                 << " -> pulse: " << pw << " us" << endl;

            lastCmdAngle = targetAngle;
        }

        this_thread::sleep_for(chrono::milliseconds(100));
    }

    gpioTerminate();
    return 0;
}