# Livia Antonello — Engineering Portfolio

Static, responsive project website built for **GitHub Pages**.

The site contains **11 HTML files**: `index.html` plus 10 separate project pages. Every card on the homepage opens an existing project page; PDF reports, photos and demo video are stored locally in `assets/`.

## Deploy to GitHub Pages

1. Download and extract the project ZIP. **Do not upload the ZIP itself as one file**: GitHub Pages needs the extracted files.
2. Open the repository `Liviaantonello/Liviaantonello.github.io` on GitHub.
3. Upload the contents of this directory **into the repository root**, replacing files with matching names. Keep the entire `assets/` directory.
4. Commit changes to the `main` branch.
5. Under **Settings → Pages**, check that deployment uses the `main` branch and `/ (root)` (or GitHub Actions if already configured).
6. The homepage will appear at `https://liviaantonello.github.io/` after GitHub finishes publishing.

### Files to keep together

- `index.html`: homepage with filterable project cards.
- `style.css` / `site.js`: shared design and filtering behaviour.
- Existing URLs preserved: `satellite.html`, `rover_project.html`, `macchina.html`, `simulink.html`.
- Added pages: `power_systems.html`, `powertrain.html`, `tractor.html`, `electrical_lab.html`, `estun.html`, `acav.html`.
- `assets/img/`: project preview images and profile photo.
- `assets/video/`: RoverTech demonstration.
- `assets/docs/`: downloadable PDF academic reports and CV.
- `assets/code/`: archived excerpts from the original satellite HTML.

No build step, Node.js installation or external JavaScript libraries are required.

## Editing

Open any `.html` file with a code editor. Project descriptions and links are plain HTML. Update colours/fonts in `style.css`. The homepage cards are in `index.html` and filter by categories stored in `data-categories`.

To test locally (optional), from the project folder run:

```bash
python -m http.server 8000
```

Then open `http://localhost:8000`.

## Information and status notes

- **RoverTech:** extracurricular project. Simulation demo provided; final physical switch contact is still under development. Team source code is not included.
- **ACAV:** ongoing project. The page describes the learning architecture under study, not finished neural-network results.
- **ESTUN:** summary only; the original workspace or private controller code is not included, and no demonstration video is claimed.
- **Arduino car:** only the Bluetooth-controlled functionality is presented as verified; earlier HTML contained an unfinished sketch and unverified autonomous obstacle avoidance claims.
- **Satellite:** the original Python/C++ examples are retained as archival, experimental reference code, not a production-ready full-range rotator controller.
- **Research reports:** the attached original DOCX files have been converted to PDF to enable viewing in browsers; conversion may alter formatting. Review them before making public.
- The source ZIP containing about 93 MB of raw NOAA recordings was deliberately **not** included; the portfolio includes the relevant image only.

## Before publishing a public repository

Please **review the PDF reports and CV** for personal information, coauthor names, institution-specific material or data that you do not want to publish. This is a public site. Replace the CV if you have made more recent changes. Do not publish restricted RoboTech/PoliSpace or ESTUN team source files without authorization.

## Project assets provenance

Descriptions are based on the HTML, notes, PDFs, DOCX reports, images and videos provided by Livia. Preview thumbnails of some reports were rendered from those PDF files, with no external assets required.
