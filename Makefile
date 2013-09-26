
.PHONY: clean

.SUFFIXES: .cpp .o .h .a

INCLUDEDIRS=-Iscintilla/include -Iv8/include
CXXFLAGS= -DGTK -DSCI_LEXER -W -Wall
LEXEROBJS=$(wildcard scintilla/gtk/Lex*.o)
V8_OUTPUT=v8/out/native/obj.target/tools/gyp/libv8_base.x64.a v8/out/native/obj.target/tools/gyp/libv8_snapshot.a

CXX=g++

all: sciborg

.cpp.o:
	$(CXX) `pkg-config --cflags gtk+-2.0` $(INCLUDEDIRS) $(CXXFLAGS) -c $< -o $@
build-sciborg: $(V8_OUTPUT) scintilla/bin/scintilla.a sciborg.o sciMessages.o $(LEXEROBJS)
	$(CXX) -DGTK $^ -o $@ -lpthread -lstdc++ `pkg-config --libs gtk+-2.0 gthread-2.0`
sciborg: v8 build-sciborg

clean: clean-scintilla clean-v8
	rm -rf sciborg *.o




scintilla/bin/scintilla.a:
	make -C scintilla/gtk

clean-scintilla:
	make clean -C scintilla/gtk

#get-v8: v8
v8:
	git clone git://github.com/v8/v8.git v8

remove-v8:
	rm -rf v8

$(V8_OUTPUT):
	make dependencies -C v8
	make native -C v8

clean-v8:
	make clean -C v8

