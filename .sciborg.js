
/**/
SCI.on('charAdded', function(char) {
	//SCI.setText('HACKED');
	//SCI.setText(SCI.getText() + SCI.getText());
	Util.log(char);
});

SCI.on('key', function(key, mod) {
	//SCI.setText('HACKED');
	//SCI.setText(SCI.getText() + SCI.getText());
	Util.log("key: " + key);
	Util.log("mod: " + mod);
	if (key === 83 && mod === 2) {
		Util.save();
	}
});
/**/
/**/
SCI.setLexer(3);
//SCI.setText('a');

SCI.styleSetFont(32, 'monospace');
SCI.styleSetFore(32, 0xFFFFFF);
SCI.styleSetBack(32, 0x444444);
SCI.styleClearAll();
//SCI.setKeywords('var function if while do throw for');
SCI.styleSetFore(5, 0xFF66FF);
SCI.styleSetFont(0, 'monospace');
SCI.styleSetFont(5, 'monospace');
SCI.styleSetFont(11, 'monospace');
//SCI.setText('function() {\n\tvar x;\n\treturn 0;\n}\n');

SCI.setCaretFore(0x00FF00);
SCI.setCaretStyle(2);
SCI.setCaretPeriod(0);
/**/
