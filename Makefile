
.SUFFIXES: .cpp .o .h .a

INCLUDEDIRS=-Iscintilla/include -Iv8/include
CXXFLAGS= -DGTK -DSCI_LEXER -W -Wall
LEXEROBJS=$(wildcard scintilla/gtk/Lex*.o)

all: sciborg

.cpp.o:
	g++ `pkg-config --cflags gtk+-2.0` $(INCLUDEDIRS) $(CXXFLAGS) -c $< -o $@
sciborg: sciborg.o $(LEXEROBJS) scintilla/bin/scintilla.a
	g++ -DGTK $^ -o $@ v8/out/native/obj.target/tools/gyp/libv8_base.x64.a v8/out/native/obj.target/tools/gyp/libv8_snapshot.a -lpthread -lstdc++ `pkg-config --libs gtk+-2.0 gthread-2.0`
clean: clean-scintilla clean-v8
	rm -rf sciborg *.o

build-scintilla:
	make -C scintilla/gtk

clean-scintilla:
	make clean -C scintilla/gtk

get-v8:
	git clone git://github.com/v8/v8.git v8

build-v8: v8
	make dependencies -C v8
	make native -C v8

clean-v8:
	make clean -C v8

