#include <Scintilla.h>
#include <gtk/gtk.h>
#include <ScintillaWidget.h>
#include <v8.h>

static ScintillaObject* getSciFromArgs(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Local<v8::External> ext = v8::Local<v8::External>::Cast(args.Data());
	ScintillaObject* sci = (ScintillaObject*) (ext->Value());
	return sci;
}
