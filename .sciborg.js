//var dictionary = ['Amanda', 'asymptotic', 'babe', 'beautiful', 'butter', 'butterfly'];
var dictionary = [
    'break',
    'case',
    'catch',
    'continue',
    'debugger',
    'default',
    'delete',
    'do',
    'else',
    'finally',
    'for',
    'function',
    'if',
    'in',
    'instanceof',
    'new',
    'return',
    'switch',
    'this',
    'throw',
    'try',
    'typeof',
    'var',
    'void',
    'while',
    'with'
];

var log = BORG.log;

function isLetter(char) {
	return (char >= 'A' && char <= 'Z') || (char >= 'a' && char <= 'z');
}

var soFar = '';
var possible = []

function checkPossible(prefix) {
	var i;
	possible = [];
	for (i = 0 ; i < dictionary.length ; i++) {
		if (dictionary[i].indexOf(prefix) === 0) {
			possible.push(dictionary[i]);
		}
	}
}

function openAutoC() {
	BORG.editor.autoCShow(soFar.length, possible.join(' '));
}

function doAutoC() {
	if (soFar && soFar.length > 0) {
		checkPossible(soFar);
	} else {
		possible = [];
	}
	if (possible.length > 0) {
		openAutoC();
	}
}

BORG.editor.on('charAdded', function(code) {
	char = String.fromCharCode(code);
//	BORG.log(char + ' (' + soFar + ')');
	
	if (isLetter(char)) {
		soFar += char;
		
	//	BORG.log('calling autoc with ' + soFar.length + ',"' + dictionary + '"');
		//BORG.editor.autoCShow(soFar.length, dictionary);
	} else {
		soFar = '';
	//	BORG.log('so far reset');
	}
	
	log('so far:' + soFar);
	
	doAutoC();
	
});

BORG.editor.on('key', function(key, mod) {
	BORG.log('key: ' + key);
	//BORG.log('mod: ' + mod);
	if (key === 83 && mod === 2) {
		BORG.save();
	}
	/*
	if (key === 81 && mod === 2) {
		var pos = BORG.editor.getCurrentPos();
		BORG.editor.insertText(pos, '-');
	}
	*/
});

BORG.editor.on('autoCCharDeleted', function() {
//	BORG.log('autoCCharDeleted !!!');
	soFar = soFar.substr(0, soFar.length - 1);
	log('so far:' + soFar);
	doAutoC();
});

BORG.editor.on('autoCCancelled', function() {
	/**/
	soFar = '';
	log('so far:' + soFar);
	/**/
});

BORG.editor.on('autoCSelection', function() {
	soFar = '';
	log('ACCEPTED! so far:' + soFar);
	//BORG.editor.addText('D');
	var pos = BORG.editor.getCurrentPos();
	BORG.editor.insertText(8, ' ');
	BORG.editor.setCurrentPos(pos + 1);
	log('POS:' + pos);
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
BORG.editor.setCaretStyle(1);
BORG.editor.setCaretWidth(2);
BORG.editor.setCaretPeriod(0);
/**/

BORG.infoPane.styleSetBack(32, 0xDDDDDD);
BORG.consolePane.styleSetBack(32, 0x333333);

BORG.consolePane.setReadOnly(true);

//BORG.editor.autoCShow(1, 'aaa aab aac');


BORG.editor.setKeywords(dictionary.join(' '));

