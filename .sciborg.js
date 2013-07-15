
/**/
BORG.editor.on('charAdded', function(char) {
	//BORG.editor.setText('HACKED');
	//BORG.editor.setText(BORG.editor.getText() + BORG.editor.getText());
	BORG.log(char);
});

BORG.editor.on('key', function(key, mod) {
	//BORG.editor.setText('HACKED');
	//BORG.editor.setText(BORG.editor.getText() + BORG.editor.getText());
	BORG.log("key: " + key);
	BORG.log("mod: " + mod);
	if (key === 83 && mod === 2) {
		BORG.save();
	}
});
/**/
/**/
BORG.editor.styleSetFont(32, 'monospace');
BORG.editor.setLexer(3);
//BORG.editor.setText('a');


BORG.editor.styleSetFore(32, 0xFFFFFF);
BORG.editor.styleSetBack(32, 0x444444);
BORG.editor.styleClearAll();
//BORG.editor.setKeywords('var function if while do throw for');
BORG.editor.styleSetFore(5, 0xFF66FF);
BORG.editor.styleSetFont(0, 'monospace');
BORG.editor.styleSetFont(5, 'monospace');
BORG.editor.styleSetFont(11, 'monospace');
//BORG.editor.setText('function() {\n\tvar x;\n\treturn 0;\n}\n');

BORG.editor.setCaretFore(0x00FF00);
BORG.editor.setCaretStyle(2);
BORG.editor.setCaretPeriod(0);
/**/
