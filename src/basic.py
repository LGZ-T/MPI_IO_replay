import ply.lex as lex

tokens = (
	'NUMBER',
	'LETTER'
	'C_IDENTIFIER',
	'C_FUNCTION',
	'POINTER',
	'DELIMITER',
	'LPAREN',
	'RPAREN',
	'STRING',
	'POINT',
)

t_LETTER = r'a-zA-Z'
t_C_IDENTIFIER = 	???
t_POINTER = r'\*'
t_DELIMITER = ' \t\n,'
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_STRING = r'".*"'	???
t_POINT = r'\.'

def t_NUMBER(t):
	r'\d+'
	t.value = int(t.value)
	return t

def t_C_FUNCTION(t):	???
	pass
