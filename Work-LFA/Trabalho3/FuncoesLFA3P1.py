from PilhaLFA3P1 import *

def verificaAlf(word,alf):#verifica se a palavra so contem caracter do alfabeto
    for i in range(len(word)-1):
        if not word[i] in alf:
            return 1
    return 0

def converteWord(word):#transf a palavra numa lista
    w = []
    for i in range(len(word)):
        w.append(word[i])
    w.append("E")#quando chegar nele, a palavre é vazia
    return w

def trans(estAtual,w,aut,pi,pos):
    if aut.saida[pos][5] == pi[len(pi)-1] or aut.saida[pos][5] == "E":
        if aut.dest[pos][3] != "E":
            inserePilha(pi,aut.dest[pos][3])
        if aut.dest[pos][3] == "E":
            removePilha(pi)
        estAtual = aut.dest[pos][1]    
    return estAtual,pi

def transicoes(estAtual,estFin,word,aut,pi,antPi,j):
    for i in range(len(aut.saida)):
        if not j == len(word) and (estAtual in aut.saida[i] and (word[j] in aut.saida[i] or aut.saida[i][3] == "E") and (aut.saida[i][5] == pi[-1] or aut.saida[i][5] == "E")):
            antPi = pi[:]
            estAtual,pi = trans(estAtual,word[j],aut,pi,i)
            j += 1
            done = transicoes(estAtual,estFin,word,aut,pi,antPi,j)
            if done == 1:
                return 1
            else:
                pi = antPi
                j -= 1
    if len(pi) == 1 and estAtual in estFin and word[j] == "E":
        return 1
    else:
        return -1
