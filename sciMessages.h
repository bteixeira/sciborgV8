
static ScintillaObject* getSciFromArgs(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Local<v8::External> ext = v8::Local<v8::External>::Cast(args.Data());
	ScintillaObject* sci = (ScintillaObject*) (ext->Value());
	return sci;
}

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
	ScintillaObject* sci = getSciFromArgs(args);
	scintilla_send_message(sci, SCI_SETTEXT, 0, (long int) *text);
}

/******************************************************************************/

static void SEND_SCI_STYLECLEARALL(const v8::FunctionCallbackInfo<v8::Value>& args) {
    ScintillaObject* sci = getSciFromArgs(args);
	scintilla_send_message(sci, SCI_STYLECLEARALL, 0, 0);
}

static void SEND_SCI_STYLESETBACK(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::Handle<v8::Value> style = args[0];
	v8::Handle<v8::Value> color = args[1];

	ScintillaObject* sci = getSciFromArgs(args);

	scintilla_send_message(sci, SCI_STYLESETBACK, style->Int32Value(), color->Int32Value());
}

static void SEND_SCI_STYLESETFORE(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Handle<v8::Value> style = args[0];
	v8::Handle<v8::Value> color = args[1];
	ScintillaObject* sci = getSciFromArgs(args);
	scintilla_send_message(sci, SCI_STYLESETFORE, style->Int32Value(), color->Int32Value());
}

static void SEND_SCI_STYLESETFONT(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Handle<v8::Value> style = args[0];
	v8::String::AsciiValue font(args[1]);
	//printf("setting font for editor %p\n", sci);
	ScintillaObject* sci = getSciFromArgs(args);
	scintilla_send_message(sci, SCI_STYLESETFONT, style->Int32Value(), (sptr_t) *font);
}

/******************************************************************************/



/* TODO DOES NOT SEEM TO WORK IF THE TEXT IS EMPTY */
static v8::Handle<v8::Value> SEND_SCI_SETKEYWORDS(const v8::Arguments& args) {
    v8::String::AsciiValue keywords(args[0]);
    printf("setting keywords [%s]\n", *keywords);
    ScintillaObject* sci = getSciFromArgs(args);
	scintilla_send_message(sci, SCI_SETKEYWORDS, 0, (long int) *keywords);
}

/******************************************************************************/

static v8::Handle<v8::Value> SEND_SCI_SETREADONLY(const v8::Arguments& args) {
    bool readOnly = args[0]->BooleanValue();
    //std::cout << "setting RO " << readOnly << "\n";
    ScintillaObject* sci = getSciFromArgs(args);
    //std::cout << "got sci " << sci << "\n";
	scintilla_send_message(sci, SCI_SETREADONLY, readOnly, 0);
	std::cout << "sent message" << "\n";
}

/*

SCI_GETREADONLY
SCI_FINDTEXT(int flags, Sci_TextToFind *ttf)
SCI_SEARCHNEXT(int searchFlags, const char *text)
SCI_GETTEXTLENGTH
SCI_GETLENGTH
SCI_GETLINECOUNT
SCI_GETMODIFY
SCI_SETVIEWWS(int wsMode)
SCI_SETMARGINTYPEN(int margin, int iType)
SCI_SETMARGINWIDTHN(int margin, int pixelWidth)
SCI_SETMARGINMASKN(int margin, int mask)
SCI_MARGINSETTEXT(int line, char *text)
SCI_MARGINSETSTYLE(int line, int style)
SCI_ANNOTATIONSETTEXT(int line, char *text)
SCI_ANNOTATIONSETSTYLE(int line, int style)
SCI_ANNOTATIONSETVISIBLE(int visible)
SCI_SETFOCUS(bool focus)
SCI_BRACEHIGHLIGHT(int pos1, int pos2)
SCI_BRACEBADLIGHT(int pos1)
SCI_BRACEHIGHLIGHTINDICATOR(bool useBraceHighlightIndicator, int indicatorNumber)
SCI_BRACEBADLIGHTINDICATOR(bool useBraceBadLightIndicator, int indicatorNumber)
SCI_BRACEMATCH(int position, int maxReStyle)
SCI_SETINDENTATIONGUIDES(int indentView)
SCI_MARKERDEFINE(int markerNumber, int markerSymbols)
SCI_MARKERADD(int line, int markerNumber)
SCI_MARKERDELETE(int line, int markerNumber)
SCI_INDICSETSTYLE(int indicatorNumber, int indicatorStyle)
SCI_INDICATORFILLRANGE(int position, int fillLength)
SCI_INDICATORCLEARRANGE(int position, int clearLength)

SCI_AUTOCCANCEL
SCI_AUTOCCOMPLETE
SCI_CALLTIPSHOW(int posStart, const char *definition)
SCI_SETWRAPMODE(int wrapMode)
SCI_SETWRAPVISUALFLAGS(int wrapVisualFlags)
SCI_SETEDGEMODE(int mode)
SCI_SETEDGECOLUMN(int column)

SCI_SETCARETLINEVISIBLE(bool show)
SCI_SETCARETLINEBACK(int colour)
SCI_SETCARETLINEBACKALPHA(int alpha)
SCI_SETCARETWIDTH(int pixels)

*/

static v8::Handle<v8::Value> SEND_SCI_AUTOCSHOW(const v8::Arguments& args) {
    int len = args[0]->Int32Value();
    v8::String::AsciiValue list(args[1]);
    ScintillaObject* sci = getSciFromArgs(args);
    scintilla_send_message(sci, SCI_AUTOCSHOW, len, (sptr_t) *list);
}

static v8::Handle<v8::Value> SEND_SCI_SETCARETFORE(const v8::Arguments& args) {
    int color = args[0]->Int32Value();
    ScintillaObject* sci = getSciFromArgs(args);
	scintilla_send_message(sci, SCI_SETCARETFORE, color, 0);
}

static v8::Handle<v8::Value> SEND_SCI_SETCARETSTYLE(const v8::Arguments& args) {
    int style = args[0]->Int32Value();
    ScintillaObject* sci = getSciFromArgs(args);
	scintilla_send_message(sci, SCI_SETCARETSTYLE, style, 0);
}

static v8::Handle<v8::Value> SEND_SCI_SETCARETPERIOD(const v8::Arguments& args) {
    int millis = args[0]->Int32Value();
    ScintillaObject* sci = getSciFromArgs(args);
	scintilla_send_message(sci, SCI_SETCARETPERIOD, millis, 0);
}

static v8::Handle<v8::Value> SEND_SCI_SETLEXER(const v8::Arguments& args) {
    int lexer = args[0]->Int32Value();
	v8::Local<v8::External> ext = v8::Local<v8::External>::Cast(args.Data());
	ScintillaObject* sci = (ScintillaObject*) (ext->Value());
	scintilla_send_message(sci, SCI_SETLEXER, lexer, 0);
}

/******************************************************************************/

static void makeFunsAvailable(v8::Handle<v8::ObjectTemplate> context, ScintillaObject* sci) {
    v8::Handle<v8::External> ext = v8::External::New(sci);

    std::cout << sci << "\n";

	context->Set(v8::String::New("setText"), v8::FunctionTemplate::New(SEND_SCI_SETTEXT, ext));
	//context->Set(v8::String::New("getText"), v8::FunctionTemplate::New(SEND_SCI_GETTEXT, ext));

	context->Set(v8::String::New("styleClearAll"), v8::FunctionTemplate::New(SEND_SCI_STYLECLEARALL, ext));
	context->Set(v8::String::New("styleSetBack"), v8::FunctionTemplate::New(SEND_SCI_STYLESETBACK, ext));
	context->Set(v8::String::New("styleSetFore"), v8::FunctionTemplate::New(SEND_SCI_STYLESETFORE, ext));

	context->Set(v8::String::New("styleSetFont"), v8::FunctionTemplate::New(SEND_SCI_STYLESETFONT, ext));

	context->Set(v8::String::New("setCaretFore"), v8::FunctionTemplate::New(SEND_SCI_SETCARETFORE, ext));
	context->Set(v8::String::New("setCaretPeriod"), v8::FunctionTemplate::New(SEND_SCI_SETCARETPERIOD, ext));
	context->Set(v8::String::New("setCaretStyle"), v8::FunctionTemplate::New(SEND_SCI_SETCARETSTYLE, ext));

	context->Set(v8::String::New("setLexer"), v8::FunctionTemplate::New(SEND_SCI_SETLEXER, ext));
	context->Set(v8::String::New("setKeywords"), v8::FunctionTemplate::New(SEND_SCI_SETKEYWORDS, ext));

	context->Set(v8::String::New("setReadOnly"), v8::FunctionTemplate::New(SEND_SCI_SETREADONLY, ext));

	context->Set(v8::String::New("autoCShow"), v8::FunctionTemplate::New(SEND_SCI_AUTOCSHOW, ext));

}
