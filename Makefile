
.PHONY: all clean clean-scintilla clean-v8

.SUFFIXES: .cpp .o .h .a

INCLUDEDIRS=-Iscintilla/include -Iv8/include
CXXFLAGS= -DGTK -DSCI_LEXER -W -Wall
LEXEROBJS=$(wildcard scintilla/gtk/Lex*.o)
V8_OUTPUT=v8/out/x64.debug/obj.target/tools/gyp/libv8_base.x64.a v8/out/x64.debug/obj.target/tools/gyp/libv8_snapshot.a

CXX=g++

all: sciborg

.cpp.o:
	$(CXX) `pkg-config --cflags gtk+-2.0` $(INCLUDEDIRS) $(CXXFLAGS) -c $< -o $@
sciborg: sciborg.o $(LEXEROBJS) scintilla/bin/scintilla.a $(V8_OUTPUT)
	$(CXX) -DGTK $^ -o $@ -lpthread -lstdc++ `pkg-config --libs gtk+-2.0 gthread-2.0`
clean: clean-scintilla clean-v8
	rm -f sciborg *.o

scintilla/bin/scintilla.a:
	make -C scintilla/gtk

clean-scintilla:
	make clean -C scintilla/gtk

clean-v8:
	make clean -C v8

$(V8_OUTPUT): v8/build/gyp
	make x64.debug -C v8

v8/build/gyp:
	make dependencies -C v8

