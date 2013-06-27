#include <gtk/gtk.h>

#include <Scintilla.h>
#include <SciLexer.h>
#define PLAT_GTK 1
#include <ScintillaWidget.h>

#include <v8.h>
#include <stdio.h>
#include <stdlib.h>

#define SSM(m, w, l) scintilla_send_message(sci, m, w, l)

static int exit_app(GtkWidget*w, GdkEventAny*e, gpointer p) {
   gtk_main_quit();
   return w||e||p||1;	// Avoid warnings
}

static void testMe(const v8::FunctionCallbackInfo<v8::Value>& args) {
	printf("ping!\n");
}
ScintillaObject *sci;
static void SEND_SCI_STYLESETBACK(const v8::FunctionCallbackInfo<v8::Value>& args) {
	//printf("it works!\n");
	v8::Handle<v8::Value> arg = args[0];
	SSM(SCI_STYLESETBACK, 0, arg->Int32Value());
}

v8::Handle<v8::Context> context;

static void handleCA(GtkWidget *, void *object) {
	//printf("it works!!!!111\n");
	v8::Handle<v8::Value> onSignalVal = context->Global()->Get(v8::String::New("onSignal"));
	v8::Handle<v8::Function> onSignal = v8::Handle<v8::Function>::Cast(onSignalVal);
	onSignal->Call(context->Global(), 0, NULL);
}

int main(int argc, char **argv) {

   GtkWidget *app;
   GtkWidget *editor;

   gtk_init(&argc, &argv);
   app = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   editor = scintilla_new();
   sci = SCINTILLA(editor);

   gtk_container_add(GTK_CONTAINER(app), editor);
   gtk_signal_connect(GTK_OBJECT(app), "delete_event",
	   GTK_SIGNAL_FUNC(exit_app), 0);

   scintilla_set_id(sci, 0);
   gtk_widget_set_usize(editor, 500, 300);



/********************/
// PARSING JS FILE
	FILE *f = fopen("/home/bruno/projects/jstextedit/cfg.js", "r");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *string = (char*) malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);

	string[fsize] = 0;
	printf("contents: %s\n", string);
	
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope handle_scope(isolate);
	
	v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
    global->Set(v8::String::New("testMe"), v8::FunctionTemplate::New(testMe));
    global->Set(v8::String::New("SEND_SCI_STYLESETBACK"), v8::FunctionTemplate::New(SEND_SCI_STYLESETBACK));
    /*
    void Attach(GtkWidget *w, CommandHandler *object, const char *sigName="clicked") {
		g_signal_connect(G_OBJECT(w), sigName, G_CALLBACK(Function), object);
	}
	static void Function(GtkWidget *, CommandHandler *object) {
		object->PerformCommand(commandNumber);
	}
	*/
	//int total;
	//g_signal_list_ids (editor, &total);
	/* WORKS!!!!!! */
	/* WORKS!!!!!! */
	/* WORKS!!!!!! */
	/* WORKS!!!!!! */
	/* WORKS!!!!!! */
	/* WORKS!!!!!! */
	g_signal_connect(editor, SCINTILLA_NOTIFY, G_CALLBACK(handleCA), NULL);
	/* WORKS!!!!!! */
	/* WORKS!!!!!! */
	/* WORKS!!!!!! */
	/* WORKS!!!!!! */
	/* WORKS!!!!!! */
	/* WORKS!!!!!! */
	
	
	/*
	g_signal_connect(G_OBJECT(PWidget(wEditor)), SCINTILLA_NOTIFY,
	                   G_CALLBACK(NotifySignal), this);
    g_signal_connect(G_OBJECT(PWidget(wOutput)), SCINTILLA_NOTIFY,
	                   G_CALLBACK(NotifySignal), this);
	*/
	
	context = v8::Context::New(isolate, NULL, global);
	v8::Context::Scope context_scope(context);
	
	v8::Handle<v8::String> source = v8::String::New(string);
	v8::Handle<v8::Script> script = v8::Script::Compile(source);
	v8::Handle<v8::Value> result = script->Run();
	v8::Local<v8::Value> stuff = context->Global()->Get(v8::String::New("background"));
	
	
	v8::String::AsciiValue ascii2(stuff);
    printf("%s\n", *ascii2);

/*
   SSM(SCI_STYLECLEARALL, 0, 0);
   SSM(SCI_SETLEXER, SCLEX_CPP, 0);
   SSM(SCI_SETKEYWORDS, 0, (sptr_t)"int char");
   SSM(SCI_STYLESETFORE, SCE_C_COMMENT, 0x008000);
   SSM(SCI_STYLESETFORE, SCE_C_COMMENTLINE, 0x008000);
   SSM(SCI_STYLESETFORE, SCE_C_NUMBER, 0x808000);
   SSM(SCI_STYLESETFORE, SCE_C_WORD, 0x800000);
   SSM(SCI_STYLESETFORE, SCE_C_STRING, 0x800080);
   SSM(SCI_STYLESETBOLD, SCE_C_OPERATOR, 1);
   SSM(SCI_INSERTTEXT, 0, (sptr_t)
    "int main(int argc, char **argv) {\n"
    "    // Start up the gnome!\n"
    "    gnome_init(\"stest\", \"1.0\", argc, argv);\n}"
   );
   */
   //SSM(SCI_STYLESETBACK, 0, 0xDDDDDD);
   //SSM(SCI_STYLESETBACK, 0, atoi(*ascii2));

   gtk_widget_show_all(app);
   gtk_widget_grab_focus(GTK_WIDGET(editor));
   gtk_main();

   return 0;
}