from analisadorLexico import lex
from arvore import Node

# inicializa variaveis globais
cadeia, proxToken, head, row, col = '', '', 0, 1, 0
mainNode = Node('S')

n_terminais = [
               'tipo', 'relop', 'artop', 'funcao', 'comando', 'bloco', 
               'sequencia_id', 'declaracao_var', 'atribuicao', 'term', 
               'exp', 'exp_op', 'cond','selecao', 'else', 'while', 'do-while'
               ]

terminais = {
             'atribuicao': ':=',
             'virgula': ',',
             'ponto_virgula': ';',
             'abre_bloco': '{',
             'fecha_bloco': '}',
             'abre_comentario': '[*',
             'fecha_comentario': '*]',
             'abre_parenteses': '(',
             'fecha_parenteses': ')',
             'id': 'id',
             'numero': 'numero',
             'tipo_int': 'int',
             'tipo_char': 'char',
             'tipo_real': 'real',
             'artop_+': '+',
             'artop_-': '-',
             'artop_*': '*',
             'artop_/': '/',
             'relop_>': '>',
             'relop_<': '<',
             'relop_>=': '>=',
             'relop_<=': '<=',
             'relop_<>': '<>',
             'relop_==': '==',
             'programa': 'programa',
             'se': 'se',
             'entao': 'entao',
             'senao': 'senao',
             'enquanto': 'enquanto',
             'faca': 'faca'
            }

glc = {
    'bloco': [['{','comando','}']],
    'term': [['id'],['numero']],
    'artop': [['+'], ['-'], ['*'], ['/']],
    'relop': [['<'], ['<='], ['>'], ['>='], ['<>'], ['==']],
    'tipo': [['int'], ['char'], ['real']],
    'selecao': [['se', '(', 'cond', ')', 'entao', 'bloco', 'else']],
    'else': [['senao', 'bloco'], ['&']],
    'comentario': [['[*', 'string', '*]']],
    'while': [['enquanto', '(', 'cond', ')', 'bloco']],
    'do-while':[['faca', 'bloco', 'enquanto', '(', 'cond', ')']],
    'funcao': [['programa', 'id', 'bloco']],
    'exp': [['term', 'exp_op']],
    'exp_op': [['artop', 'exp'], ['&']],
    'sequencia_id': [[ ',','id','sequencia_id' ], ['&']],
    'declaracao_var': [['tipo', 'id', 'sequencia_id']],
    'atribuicao': [['id', ':=', 'exp']],
    'cond': [['exp', 'relop', 'exp']],
    'comando': [['declaracao_var', 'comando'], ['atribuicao', 'comando'], ['selecao', 'comando'], ['while', 'comando' ], ['do-while', 'comando'], ['comentario', 'comando'], ['&']]           
}

first = {
    'bloco': ['{'],
    'term': ['id', 'numero'],
    'artop': ['+', '-', '*', '/'],
    'relop': ['<', '<=', '>', '>=', '<>', '=='],
    'tipo': ['int', 'char','real'],
    'selecao': ['se'],
    'else': ['senao', '&'],
    'comentario': ['[*'],
    'while': ['enquanto'],
    'do-while': ['faca'],
    'funcao': ['programa'],
    'exp': ['id', 'numero'],
    'exp_op': ['+', '-', '/', '*', '&'],
    'sequencia_id': [',', '&'],
    'declaracao_var': ['int', 'char', 'real'],
    'atribuicao': ['id', 'numero'],
    'cond': ['id', 'numero'],
    'comando': ['int', 'char', 'real', 'id', 'numero', 'se', 'enquanto', 'faca', '[*', '&'],
    '+' : ['+'],
    '==' : ['=='],
    '-' : ['-'],
    '/' : ['/'],
    '*' : ['*'],
    '<>' : ['<>'],
    '>=' : ['>='],
    '<=' : ['<='],
    '&' : ['&'],
    '>' : ['>'],
    '<' : ['<'],
    ',' : [','],
    ';' : [';'],
    '{' : ['{'],
    '}' : ['}'],
    ':=': [':='],
    '(' : ['('],
    ')' : [')'],
    'string' : ['string'],
    'faca' : ['faca'],
    'int' : ['int'],
    'char' : ['char'],
    'real' : ['real'],
    'id' : ['id'],
    'programa' : ['programa'],
    'entao' : ['entao'],
    'se' : ['se'],
    'senao' : ['senao'],
    'enquanto': ['enquanto'],
    'numero' : ['numero']
}

def producao(token, glcValor):
    for i in range(len(glcValor)):
        findFirst = False
        firstValor = first[glcValor[i][0]]

        for firstElem in firstValor:
            if firstElem == token:
                findFirst = True

        if findFirst:
            break

    return glcValor[i]


def getToken():
    global head, row, col, mainNode
    token_list = ['space']
    
    while token_list[0] == 'space' or token_list[0] == 'new_line':
        try:
            token_list = lex(cadeia, head, col, row)
            if not token_list:
                print("Cadeia Aceita!")
                mainNode.printaArvore()
                quit()
            if token_list[0] == 'abre_comentario':
                token_list = comentario()
        except Exception as e:
            print(e)
            quit()

        head = token_list[-1]
        row = token_list[2]
        col = token_list[-2]

    return terminais[token_list[0]]

def comentario():
    global cadeia, head, col, row

    while not (cadeia[head] == '*' and cadeia[head+1] == ']'):
        head += 1
        col += 1
        if cadeia[head] == '\n':
            row += 1
    head += 2
    col += 2
    token_list = lex(cadeia, head, col, row)

    return token_list

def sintatico(node, glcValor=[['programa', 'id', 'bloco']]):
    global head, row, col, proxToken

    Xs = producao(proxToken, glcValor)
    
    for x in Xs:
        xNode = Node(x)
        node.addChild(xNode)
       
        if x in n_terminais:
            sintatico(xNode, glc[x])
        elif x == proxToken:
            proxToken = getToken()
        elif x == '&':
            pass
        else:
            print(f'proxToken {proxToken} - x {x} -- Deu ruim mané, row {row} col {col}')
            quit()
     

def run(fita):
    global cadeia, proxToken, mainNode
    cadeia = fita
    proxToken = getToken()
    sintatico(mainNode)
    
