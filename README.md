## What this is
An openFrameworks addon that converts PDF files into vector paths for drawing and manipulation within the openFrameworks framework. It parses PDF graphics operators and converts geometric primitives (lines, curves, fills) into `ofPath` objects that can be rendered and transformed by the graphics framework.

### Stack
- **Language:** C++
- **Framework / runtime:** openFrameworks (creative coding framework)
- **Notable libraries:** 
  - **PoDoFo** — PDF parsing and manipulation library (GPLv2)
  - **ofxClipper** — polygon clipping addon (appears to be integrated but currently disabled in code)

## How it's organized

```
src/
  ofxPoDoFo.h        Main public API: Document & Page classes for loading/drawing
  ofxPoDoFo.cpp      Document::load() implementation with page iteration
  ofxPoDoFoParse.h   Parser and Extractor base class for PDF operator handling
  ofxPoDoFoParse.cpp ~400 lines parsing PDF content operators (moveTo, lineTo, bezierTo, 
                       colors, fills, strokes, etc.) into ofPath commands
  
example/            Standard openFrameworks example project structure
  src/ofApp.h       ofxPoDoFo type alias and Document instance
  src/ofApp.cpp     Trivial example: load("tiger.pdf") in setup(), draw() in render loop
  
addon_config.mk     Addon metadata + dependency declaration (requires ofxClipper)
license.md          Dual licensed: MIT (addon code) + GPLv2 (PoDoFo library)
```

**How it fits together:**  
The example app calls `Document::load()` with a PDF path. This loads the PoDoFo `PdfMemDocument`, iterates pages, and creates a `Parser::Context` for each. The `Parser::parse()` method reads the PDF content stream using `PdfContentStreamReader`, extracts operators (like `m` for moveTo, `c` for cubic Bezier), and dispatches them through an inheritance hierarchy of `Extractor` subclasses (`MoveTo`, `BezierTo`, `StrokeColor`, etc.). Each applies transformations and builds `ofPath` objects. The populated paths are stored in `Document::page_[]` and rendered via `Document::draw()`, which calls `ofPath::draw()` on each path.

## How to run it

This is an openFrameworks addon, not a standalone executable. To use it:

1. Clone into your openFrameworks `addons/` directory:
   ```bash
   git clone https://github.com/danoli3/ofxPoDoFo.git addons/ofxPoDoFo
   ```

2. Ensure `ofxClipper` addon is also installed (declared in `addon_config.mk`).

3. Generate an example project using the openFrameworks Project Generator, add `ofxPoDoFo` as an addon, and build:
   ```bash
   # With the example provided in the repo
   cd example
   make
   ```

4. Place a PDF file (e.g., `tiger.pdf`) in the example's `bin/data/` directory and run the resulting executable.

## Try asking
- What PDF drawing commands does the parser currently handle, and which ones are stubbed as "ignore" or "should handle"?
- Why is the ofxClipper integration commented out in `Parser::Context::getClippedPath()`, and what was the clipping feature supposed to do?
- How would you extend the parser to support text rendering from PDF embedded fonts?
