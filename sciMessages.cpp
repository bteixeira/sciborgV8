#include <gtk/gtk.h>

#include <Scintilla.h>
#include <SciLexer.h>
#define PLAT_GTK 1
#include <ScintillaWidget.h>

#include <v8.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include "sciMessages.h"

static ScintillaObject* getSciFromArgs(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Local<v8::External> ext = v8::Local<v8::External>::Cast(args.Data());
	ScintillaObject* sci = (ScintillaObject*) (ext->Value());
	return sci;
}
