
.SUFFIXES: .c .o .h .a

INCLUDEDIRS=-I../scintilla/include -I../../v8/include
CXXFLAGS= -DGTK -DSCI_LEXER -W -Wall
LEXEROBJS=$(wildcard ../scintilla/gtk/Lex*.o)

all: bait

.c.o:
	g++ `pkg-config --cflags gtk+-2.0` $(INCLUDEDIRS) $(CXXFLAGS) -c $< -o $@
bait: bait.o $(LEXEROBJS) ../scintilla/bin/scintilla.a
	g++ -DGTK $^ -o $@ ../../v8/out/x64.release/obj.target/tools/gyp/libv8_base.x64.a ../../v8/out/x64.release/obj.target/tools/gyp/libv8_snapshot.a -lpthread -lstdc++ `pkg-config --libs gtk+-2.0 gthread-2.0`
clean:
	rm -rf bait *.o
