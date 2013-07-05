
ScintillaObject *sci;

static void SEND_SCI_STYLESETBACK(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::Handle<v8::Value> arg = args[0];
	scintilla_send_message(sci, SCI_STYLESETBACK, 0, arg->Int32Value());
}

static void SEND_SCI_STYLESETFORE(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::Handle<v8::Value> arg = args[0];
	scintilla_send_message(sci, SCI_STYLESETFORE, 0, arg->Int32Value());
}

/*
//Text retrieval and modification

SCI_GETTEXT(int length, char *text)
*/
static v8::Handle<v8::Value> SEND_SCI_GETTEXT(const v8::Arguments& args) {
    v8::Handle<v8::String> val = v8::String::New("NOT WORKING -- NEEDS ALLOCATION");
    //v8::String lol;
    return val;
}

/*
SCI_SETTEXT(<unused>, const char *text)
*/
void SEND_SCI_SETTEXT(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::String::AsciiValue text(args[0]);
	//printf("setting text to %s\n", *text);
	scintilla_send_message(sci, SCI_SETTEXT, 0, (long int) *text);
}

/*
SCI_SETSAVEPOINT
SCI_GETLINE(int line, char *text)
SCI_REPLACESEL(<unused>, const char *text)
SCI_SETREADONLY(bool readOnly)
SCI_GETREADONLY
SCI_GETTEXTRANGE(<unused>, Sci_TextRange *tr)
SCI_ALLOCATE(int bytes, <unused>)
SCI_ADDTEXT(int length, const char *s)
SCI_ADDSTYLEDTEXT(int length, cell *s)
SCI_APPENDTEXT(int length, const char *s)
SCI_INSERTTEXT(int pos, const char *text)
SCI_CLEARALL
SCI_DELETERANGE(int pos, int deleteLength)
SCI_CLEARDOCUMENTSTYLE
SCI_GETCHARAT(int position)
SCI_GETSTYLEAT(int position)
SCI_GETSTYLEDTEXT(<unused>, Sci_TextRange *tr)
SCI_SETSTYLEBITS(int bits)
SCI_GETSTYLEBITS
SCI_RELEASEALLEXTENDEDSTYLES
SCI_ALLOCATEEXTENDEDSTYLES(int numberStyles)
SCI_TARGETASUTF8(<unused>, char *s)
SCI_ENCODEDFROMUTF8(const char *utf8, char *encoded)
SCI_SETLENGTHFORENCODE(int bytes)
*/

static void makeFunsAvailable(v8::Handle<v8::ObjectTemplate> context) {
	context->Set(v8::String::New("setText"), v8::FunctionTemplate::New(SEND_SCI_SETTEXT));
	context->Set(v8::String::New("getText"), v8::FunctionTemplate::New(SEND_SCI_GETTEXT));

	context->Set(v8::String::New("styleSetBack"), v8::FunctionTemplate::New(SEND_SCI_STYLESETBACK));
	context->Set(v8::String::New("styleSetFore"), v8::FunctionTemplate::New(SEND_SCI_STYLESETFORE));
}
