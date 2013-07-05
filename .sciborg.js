//Scintilla.background =  "sdkjfn";
//testMe();
//SEND_SCI_STYLESETBACK(0xFF00FF);
var background = (true == "1" ? 0xFF00FF : 0x00FF00);
var text = "#666666";
var i = 0;
function onSignal() {
	i = (i + 1) % 256;
	//testMe();
	SEND_SCI_STYLESETBACK((i * 255 * 255) + (i * 255) + i);
};

testMe();

/**
on('charAdded', function() {
	//testMe();
	SCI.SEND_SCI_SETTEXT("HACKED");
});
/**/

/**
SCI.on('charAdded', function() {
	//SCI.setText('HACKED');
	SCI.setText(SCI.getText() + SCI.getText());
});
/**/

SCI.setLexer(3);
SCI.setText('a');
SCI.setKeywords('var function if while do throw for');
SCI.styleSetFore(5, 0x00FF00);
SCI.setText('function() {\n\tvar x;\n\treturn 0;\n}\n');

