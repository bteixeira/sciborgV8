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

char* filename;

v8::Handle<v8::Script> readFromFile(char* filename);

v8::Isolate* isolate;
v8::Handle<v8::Context> context;

static int exit_app(GtkWidget*w, GdkEventAny*e, gpointer p) {
   gtk_main_quit();
   return w||e||p||1;	// Avoid warnings
}

static void log(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::String::AsciiValue what(args[0]);
	std::cout << ">>> " << *what << "\n";
}

std::map<std::string, v8::Persistent<v8::Function> > handlers;

static void setHandler(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::String::AsciiValue ascii2(args[0]);
	printf("setting handler for: %s\n", *ascii2);
	v8::Persistent<v8::Function> charAddedHandler = v8::Persistent<v8::Function>::New(v8::Handle<v8::Function>::Cast(args[1]));
	handlers[*ascii2] = charAddedHandler;
}

static void saveIt(const v8::FunctionCallbackInfo<v8::Value>& args) {
    if (filename != NULL) {
        std::cout << "this should save the file to " << filename << " ...\n";

        int n = scintilla_send_message(sci, SCI_GETLENGTH, 0, 0);
        std::cout << "text length should be " << n << "\n";

        char* contents = (char*) malloc(n + 1);
        scintilla_send_message(sci, SCI_GETTEXT, n + 1, (sptr_t) contents);
        std::cout << "text contents should be " << contents << "\n";

        std::ofstream myfile;
        myfile.open (filename);
        myfile << contents;
        myfile.close();
        free(contents);
    } else {
        std::cout << "tried to save but there is no filename\n";
    }
}

static std::map<int, std::string> signals;

static void handleSCISignal(GtkWidget *, gint /*wParam*/, SCNotification *notification, void *data) {
	int code = notification->nmhdr.code;
	std::string signal = signals[code];
    if (!signal.empty()) {
        std::cout << "Calling handler for " << signal << "! (if any)\n";
        v8::Persistent<v8::Function> handler = handlers.at(signal);
        v8::Local<v8::Object> global = context->Global();
        v8::Handle<v8::Value> args[2];
        args[0] = v8::Number::New(notification->ch);
        args[1] = v8::Number::New(notification->modifiers);
        handler->Call(global, 2, args);
    }
}

int main(int argc, char **argv) {

    /* TODO Take this out of here */
    signals[SCN_CHARADDED] = "charAdded";
    signals[SCN_KEY] = "key";

	GtkWidget *app;
	GtkWidget *editor;

	gtk_init(&argc, &argv);
	app = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	editor = scintilla_new();
	sci = SCINTILLA(editor);

    GtkWidget* layout = gtk_fixed_new();

	gtk_container_add(GTK_CONTAINER(app), layout);
	gtk_fixed_put(GTK_FIXED(layout), editor, 0, 20);

	gtk_signal_connect(GTK_OBJECT(app), "delete_event", GTK_SIGNAL_FUNC(exit_app), 0);

	scintilla_set_id(sci, 0);
	gtk_widget_set_usize(editor, 500, 300);

	/***************/
	/* Try adding a new editor pane to the same window */

    GtkWidget *pane;
    pane = scintilla_new();
	ScintillaObject *sci2 = SCINTILLA(pane);
	gtk_fixed_put(GTK_FIXED(layout), pane, 0, 0);
	scintilla_set_id(sci2, 1);

	scintilla_send_message(sci2, SCI_SETWRAPMODE, 2, 0);

    scintilla_send_message(sci2, SCI_STYLECLEARALL, 0, 0);

    scintilla_send_message(sci2, SCI_STYLESETFONT, 0, (sptr_t) "monospace");
    scintilla_send_message(sci2, SCI_STYLESETSIZE, 0, 10);

	gtk_widget_set_usize(pane, 500, 20);

	/***************/
	/* Try reading a file */
	if (argc > 1) {
	    filename = argv[1];

	    std::cout << "Will read file '" << filename << "'\n";

	    FILE *f = fopen(filename, "r");
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        char *string = (char*) malloc(fsize + 1);
        fread(string, fsize, 1, f);
        fclose(f);

        string[fsize] = 0;
        scintilla_send_message(sci, SCI_INSERTTEXT, 0, (sptr_t) string);
        scintilla_send_message(sci2, SCI_INSERTTEXT, 0, (sptr_t) filename);
	} else {
	    std::cout << "No filename passed\n";
	    scintilla_send_message(sci2, SCI_INSERTTEXT, 0, (sptr_t) "[new file]");
	}

	scintilla_send_message(sci2, SCI_SETREADONLY, 1, 0);
	/***************/

	isolate = v8::Isolate::GetCurrent();
	v8::HandleScope handle_scope(isolate);

	v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();

	v8::Handle<v8::ObjectTemplate> sciObj = v8::ObjectTemplate::New();

	global->Set(v8::String::New("SCI"), sciObj);
	makeFunsAvailable(sciObj);
	sciObj->Set(v8::String::New("on"), v8::FunctionTemplate::New(setHandler));

	v8::Handle<v8::ObjectTemplate> utilObj = v8::ObjectTemplate::New();
	global->Set(v8::String::New("Util"), utilObj);
	utilObj->Set(v8::String::New("save"), v8::FunctionTemplate::New(saveIt));
	utilObj->Set(v8::String::New("log"), v8::FunctionTemplate::New(log));

	g_signal_connect(editor, SCINTILLA_NOTIFY, G_CALLBACK(handleSCISignal), NULL);

	context = v8::Context::New(isolate, NULL, global);
	v8::Context::Scope context_scope(context);

	v8::Handle<v8::Script> script = readFromFile("./.sciborg.js");
	v8::Handle<v8::Value> result = script->Run();

	gtk_widget_show_all(app);
	gtk_widget_grab_focus(GTK_WIDGET(editor));
	gtk_main();

	return 0;
}

v8::Handle<v8::Script> readFromFile(char* filename) {
	// PARSING JS FILE
	FILE *f = fopen(filename, "r");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *string = (char*) malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);

	string[fsize] = 0;
	//printf("contents: %s\n", string);
	v8::Handle<v8::String> source = v8::String::New(string);
	return v8::Script::Compile(source);
}

