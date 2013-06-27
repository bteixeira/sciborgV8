SciborgV8
=========

An attempt to make a text editor fully scriptable and customizable through Javascript.
Makes use of Scintilla text editing component and Google's V8 Javascript engine.

Prerequisites
-------------
SciborgV8 currently builds only for Linux/GTK.
I plan to add support for Mac/Cocoa and Windows, although in the current state it should be easy to adapt.

SciborgV8 depends on Scintilla and V8.
Scintilla 3.3.3 source code is included.
V8 is not included due to its large size.
Make will automatically download the current version of V8.
For this, you need Git installed.

V8 in turn requires Gyp to build. This is also obtained automatically.

