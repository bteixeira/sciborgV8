
ScintillaObject *sci;

/******************************************************************************/

/* TODO DONT KNOW HOW TO IMPLEMENT THIS */
static v8::Handle<v8::Value> SEND_SCI_GETTEXT(const v8::Arguments& args) {
    v8::Handle<v8::String> val = v8::String::New("NOT WORKING -- NEEDS ALLOCATION");
    //v8::String lol;
    return val;
}

void SEND_SCI_SETTEXT(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::String::AsciiValue text(args[0]);
	//printf("setting text to %s\n", *text);
	scintilla_send_message(sci, SCI_SETTEXT, 0, (long int) *text);
}

/******************************************************************************/

static void SEND_SCI_STYLECLEARALL(const v8::FunctionCallbackInfo<v8::Value>& args) {
	scintilla_send_message(sci, SCI_STYLECLEARALL, 0, 0);
}

static void SEND_SCI_STYLESETBACK(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::Handle<v8::Value> style = args[0];
	v8::Handle<v8::Value> color = args[1];
	scintilla_send_message(sci, SCI_STYLESETBACK, style->Int32Value(), color->Int32Value());
}

static void SEND_SCI_STYLESETFORE(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Handle<v8::Value> style = args[0];
	v8::Handle<v8::Value> color = args[1];
	scintilla_send_message(sci, SCI_STYLESETFORE, style->Int32Value(), color->Int32Value());
}

static void SEND_SCI_STYLESETFONT(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Handle<v8::Value> style = args[0];
	v8::String::AsciiValue font(args[1]);
	scintilla_send_message(sci, SCI_STYLESETFONT, style->Int32Value(), (sptr_t) *font);
}

/******************************************************************************/

static v8::Handle<v8::Value> SEND_SCI_SETLEXER(const v8::Arguments& args) {
    int lexer = args[0]->Int32Value();
    printf("setting lexer %d\n", lexer);
	scintilla_send_message(sci, SCI_SETLEXER, lexer, 0);
}

/* TODO DOES NOT SEEM TO WORK IF THE TEXT IS EMPTY */
static v8::Handle<v8::Value> SEND_SCI_SETKEYWORDS(const v8::Arguments& args) {
    v8::String::AsciiValue keywords(args[0]);
    printf("setting keywords [%s]\n", *keywords);
	scintilla_send_message(sci, SCI_SETKEYWORDS, 0, (long int) *keywords);
}

/******************************************************************************/

/*

SCI_SETREADONLY(bool readOnly)

*/

/*

SCI_SETCARETLINEVISIBLE(bool show)
SCI_SETCARETLINEBACK(int colour)
SCI_SETCARETLINEBACKALPHA(int alpha)

SCI_SETCARETPERIOD(int milliseconds)
SCI_SETCARETSTYLE(int style)
SCI_SETCARETWIDTH(int pixels)

*/

static v8::Handle<v8::Value> SEND_SCI_SETCARETFORE(const v8::Arguments& args) {
    int color = args[0]->Int32Value();
	scintilla_send_message(sci, SCI_SETCARETFORE, color, 0);
}

static v8::Handle<v8::Value> SEND_SCI_SETCARETSTYLE(const v8::Arguments& args) {
    int style = args[0]->Int32Value();
	scintilla_send_message(sci, SCI_SETCARETSTYLE, style, 0);
}

/******************************************************************************/

static void makeFunsAvailable(v8::Handle<v8::ObjectTemplate> context) {
	context->Set(v8::String::New("setText"), v8::FunctionTemplate::New(SEND_SCI_SETTEXT));
	context->Set(v8::String::New("getText"), v8::FunctionTemplate::New(SEND_SCI_GETTEXT));

	context->Set(v8::String::New("styleClearAll"), v8::FunctionTemplate::New(SEND_SCI_STYLECLEARALL));
	context->Set(v8::String::New("styleSetBack"), v8::FunctionTemplate::New(SEND_SCI_STYLESETBACK));
	context->Set(v8::String::New("styleSetFore"), v8::FunctionTemplate::New(SEND_SCI_STYLESETFORE));
	context->Set(v8::String::New("styleSetFont"), v8::FunctionTemplate::New(SEND_SCI_STYLESETFONT));

//	context->Set(v8::String::New("SCI_SETCARETFORE"), v8::FunctionTemplate::New(SEND_SCI_SETCARETFORE));

	context->Set(v8::String::New("setCaretFore"), v8::FunctionTemplate::New(SEND_SCI_SETCARETFORE));
//	context->Set(v8::String::New("SCI_SETCARETFORE"), v8::FunctionTemplate::New(SEND_SCI_SETCARETFORE));
//	context->Set(v8::String::New("SCI_SETCARETFORE"), v8::FunctionTemplate::New(SEND_SCI_SETCARETFORE));
//	context->Set(v8::String::New("SCI_SETCARETFORE"), v8::FunctionTemplate::New(SEND_SCI_SETCARETFORE));
//	context->Set(v8::String::New("SCI_SETCARETFORE"), v8::FunctionTemplate::New(SEND_SCI_SETCARETFORE));
	context->Set(v8::String::New("setCaretStyle"), v8::FunctionTemplate::New(SEND_SCI_SETCARETSTYLE));
//	context->Set(v8::String::New("SCI_SETCARETFORE"), v8::FunctionTemplate::New(SEND_SCI_SETCARETFORE));

	context->Set(v8::String::New("setLexer"), v8::FunctionTemplate::New(SEND_SCI_SETLEXER));
	context->Set(v8::String::New("setKeywords"), v8::FunctionTemplate::New(SEND_SCI_SETKEYWORDS));
}
