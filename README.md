SciborgV8
=========

An attempt to make a text editor fully scriptable and customizable through Javascript.
Makes use of the [Scintilla](http://www.scintilla.org/) text editing component and [Google's V8](https://code.google.com/p/v8/) Javascript engine.

Project Goals
-------------
0. **Minimal**: Where possible, funcionality should be left to the Javascript layer. Sciborg should provide only a set of bindings for Scintilla calls.
0. **Cross-platform**: Support the major versions of Linux, Windows and Mac _(but don't compromise development to support every single last flavour of the most exotic platform)_
0. **Lightweight**: Watch for performance. No fancy stuff needed, just text.
0. **Self-contained**: Rely on minimum of dependencies on target system. A single, small, executable file would be ideal.

Prerequisites
-------------
SciborgV8 currently builds only for **Linux/GTK**.
I plan to add support for Windows. Mac OS will be trickier, but other editors have done it before.

SciborgV8 depends on **Scintilla** and **V8**.
Scintilla 3.3.3 source code is included.
V8 is not included due to its large size.
Make will automatically download the current version of V8.
For this, you need **Git** installed.

V8 in turn requires **Gyp** to build. This is also obtained automatically.

Building
--------
To build Sciborg for GTK+ 2 (tested on Ubuntu 12.10)

0. Clone the project

        $ git clone https://github.com/bteixeira/sciborgV8.git

0. Install the `libgtk2.0-dev` package, e.g.:

        $ sudo apt-get install libgtk2.0-dev

0. Call `make` in the root directory

        $ cd sciborgV8
        $ make

Heroes Needed
-------------
I started this project because my expertise is in Javascript.


My C++ skills have been dwindling in the last few years.
If you're a *real* C++ dev and think this is a noble project, your help will be much appreciated.

While looking at the code, you will probably find lots of room for improvement in the way things are done, right down to the simplest things. Even the makefile is in desperate need of work.
