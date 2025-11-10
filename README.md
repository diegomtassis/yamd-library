# YaMDl - Yet another MegaDrive library

Sega Mega Drive utility library written by diegomtassis as an extension to SGDK.

It's currently, and will always be, work in progress.

Utilities here have been created when needed for games development, and they are generic enough to be extracted to a multipurpose library.

Feel free to use whatever you need for your game.
Pull requests are welcome.

https://github.com/diegomtassis/yamd-library


## Utilities

Code is located under the fwk folder. As of now there are utilities covering more or less deeply the following concerns:

| Utility | Description | Docs status |
|---------|-------------|-------------|
| [2D simple physics](#2d-simple-physics) | AABB collision & relative position helpers | Pending detailed docs |
| [Spatial partitioning](#spatial-partitioning) | Prototype spatial grid indexing (broad-phase) | Proof of concept |
| [Data structures](#data-structures) | Fixed-size array list; doubly linked list | Brief summary |
| [Display printer](#display-printer) | In-ROM text console (wrap, scroll, typewriter, cursor) | Documented |
| [Countdown](#countdown) | Timer-based countdown utility | Pending detailed docs |


### 2D simple physics

* Support for Axis Aligned Bounding Box paradigm (AABB).
* Overlap between AABBs.
* Position of individual pixels regarding AABBs.
* Relative position between AABBs, including offsets.

Code yet to be documented.


### Spatial partitioning

* Spatial partitioning proof of concept.


### Data structures

* Array fixed list. Uses a fixed size array as back storage. Size is set when the list is initialized.
* Doubly linked list.


### Display printer

Provides an in-ROM text console with a blinking cursor, automatic word–wrapping / scrolling and a typewriter effect (per‑character delay).

Key features:
* Typewriter effect (fixed per‑character delay of `WAIT_50`).
* Simple word wrapping with minimal hyphenation (adds '-' when breaking inside a word at last column).
* Vertical auto‑scroll when reaching bottom; keeps writing while smoothly pushing previous lines up.
* Blinking cursor sprite (visibility toggled by the `blinker` utility) to indicate input focus / pacing pauses.
* Ignored leading spaces of a new line to avoid ragged left padding.

Screen geometry:
* Columns: 38 for 320px wide mode, else 30.
* Rows: 28 for 240px high mode, else 26.
The printer internally works in tile coordinates; conversion helpers keep the cursor sprite aligned with text tiles.

Public API (in `inc/fwk/printer.h`):
```c
void initPrinter();        // Reset internal state; call once early.
void turnPrinterOn();      // Allocate cursor, clear text plane, show console.
void turnPrinterOff();     // Free resources and hide console.
void clearScreen();        // Clear text plane & reset cursor to top-left.

void print(const char *text);   // Type out a string (no implicit newline).
void println(const char *text); // print(text) + ensure an empty line after.

void printerWait(u32 ms);  // Blink cursor while delaying for pacing.

// Timing helper constants (milliseconds) for punctuation pacing:
#define WAIT_50            50
#define COMMA_WAIT         500
#define MIDDLE_DOT_WAIT    900
#define PARAGRAPH_DOT_WAIT 1250
#define FULL_STOP_WAIT     3000
```

Usage example:
```c
initPrinter();
turnPrinterOn();

print("Hello, Mega Drive");
printerWait(COMMA_WAIT);      // brief pause after comma / phrase
println("! This is a demo paragraph that will wrap and scroll if long enough.");
printerWait(FULL_STOP_WAIT);  // longer pause at end of paragraph

println("Second paragraph starts after an empty line.");

turnPrinterOff();
```

Behavior notes:
* Wrapping: when the last column is reached, if the next character continues the current word and the previous character was not a space, a hyphen is printed before line break; if starting a word at last column, it moves the whole word to the next line (no hyphen).
* Scrolling: once the cursor passes the last visible row, vertical scroll is advanced and the newly exposed bottom line cleared.
* Cursor: `printerWait` keeps blinking active so longer waits still feel alive.
* println adds one mandatory blank line after the printed text (effectively a paragraph break); if the cursor is mid‑line it first completes that line, then adds an extra empty line.


### Countdown

* Simple countdown support using timers.

Code yet to be documented.


## Test suite

This project includes a test suite which can be compiled into a rom and executed either in real hardware or an emulator. The suite offers several executable scenarios which test the utilities under different circumstances, but serve as well as examples showcasing how to use the library.


## SGDK

SGDK is a development kit for Sega Mega Drive created by Stephane Dallongeville

https://stephane-d.github.io/SGDK/

GitHub page: https://github.com/Stephane-D/SGDK

Wiki page: https://github.com/Stephane-D/SGDK/wiki
