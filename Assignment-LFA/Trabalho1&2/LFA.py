from Funcoes import *
from Write import *

def main():
    er = input("Digite sua expressão regular: ")
    aut = automato(er)
    alf = alfabeto(er)
    escrevendo(aut,alf)

def alfabeto(er):
    expReg,alf,semiAlf = [],[],[]

    for i in range(len(er)):#transf a string numa lista
        expReg.append(er[i])
    
    for i in range(len(expReg)):#tiro o '(' ')' '.' '+' '*' 'e' da lista
        if expReg[i] != '(' and expReg[i] != 'e' and expReg[i] != ')' and expReg[i] != '.' and expReg[i] != '*' and expReg[i] != '+':
            semiAlf.append(expReg[i])
    
    for i in range(len(semiAlf)):#tira as repetições
        if not (semiAlf[i] in alf):
            alf.append(semiAlf[i])

    return alf

def automato(er):
    ok = []
    for i in range(len(er)):#transf string numa lista
        ok.append(er[i])
    cont,i = 0,0
    visitados = []
    while 1:#faz o com parentese
        while i<len(ok):
            if ok[i] == "+" and ok[i-2] == "(":
                cont += 6
                ok[i+2] = uniao(ok[i-1],ok[i+1],cont-6,cont)
                for i in range(i-2,i+2):
                    visitados.append(i)
                i = i+2
            elif ok[i] == "." and ok[i-2] == "(":
                cont += 4
                ok[i+2] = conca(ok[i-1],ok[i+1],cont-4,cont)
                for i in range(i-2,i+2):
                    visitados.append(i)
                i = i+2
            else:
                i += 1

        ok = arrumaVetor(visitados,ok)
        visitados,i = [],0
        if not('(' in ok):
            break

    while i<len(ok):#faz o fechamento
        if ok[i] == "*":
            cont += 4
            ok[i] = fecha(ok[i-1],cont-4,cont)
            visitados.append(i-1)
        i += 1

    ok = arrumaVetor(visitados,ok)
    visitados,i = [],0

    while i<len(ok):#faz os OU e E sem parentese
        if ok[i] == "+":
            cont += 6
            ok[i+1] = uniao(ok[i-1],ok[i+1],cont-6,cont)
            i += 2
        elif ok[i] == ".":
            cont += 4
            ok[i+1] = conca(ok[i-1],ok[i+1],cont-4,cont)
            i += 2
        else:
            i += 1
    
    return ok[-1]

main()