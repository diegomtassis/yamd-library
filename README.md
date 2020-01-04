# YaMDl - Yet another MegaDrive library

Sega Mega Drive utility library written by diegomtassis as an extension to SGDK.

It's currently, and will always be, work in progress.

Utilities here have been created when needed for games development, and they are generic enough to be extracted to a multipurpose library.

Feel free to use whatever you need for your game.
Pull requests are welcome.

https://github.com/diegomtassis/yamd-library


## Utilities

Code is located under the fwk folder. As of now there are utilities covering more or less deeply the following concerns:

### 2D simple physics

* Support for Axis Aligned Bounding Box paradigm (AABB).
* Overlap between AABBs.
* Position of individual pixels regarding AABBs.
* Relative position between AABBs, including offsets.

Code yet to be documented.


### Data structures

* Array fixed list. Uses a fixed size array as back storage. Size is set when the list is initialized.
* Doubly linked list.


### Display printer

* Supports typewriter effect.

Code yet to be documented.


### Countdown

* Simple countdown support using timers.

Code yet to be documented.


## Yet to be implemented

* Spatial grid indexing.
* ...


## Test suite

This project includes a test suite which can be compiled into a rom and executed either in real hardware or an emulator. The suite offers several executable scenarios which test the utilities under different circumstances, but serve as well as examples showcasing how to use the library.


## SGDK

SGDK is a development kit for Sega Mega Drive created by Stephane Dallongeville

https://stephane-d.github.io/SGDK/

GitHub page: https://github.com/Stephane-D/SGDK

Wiki page: https://github.com/Stephane-D/SGDK/wiki
