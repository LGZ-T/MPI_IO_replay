import ply.lex as lex

tokens = (
	'NUMBER',
	'PLUS',
)

t_PLUS = r'\+'

t_ignore = ' \t'

def t_NUMBER(t):
	r'\d+'
	t.value = int(t.value)
	return t

def t_newline(t):
	r'\n+'
	t.lexer.lineno += len(t.value)

def t_error(t):
	print "Illegal charater '%s'" % t.value[0]
	t.lexer.skip(1)

lexer = lex.lex()

data = '''
3 + 4
5+6

7
'''

lexer.input(data)

while True:
	tok = lexer.token()
	if not tok: break
	print tok.type, tok.value, tok.lineno, tok.lexpos
