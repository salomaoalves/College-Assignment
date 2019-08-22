from ReadLFA3P1 import *
from ClasseLFA3P1 import *
from FuncoesLFA3P1 import *
from PilhaLFA3P1 import *

def main():
    pi = criaPilha()
    antPi = criaPilha()
    word = input("Escreva a palavra: ")
    #url = input("URL do arquivo: ")
    word = converteWord(word)
    url = "Automato.docx"
    aut = lendo(url)
    if verificaAlf(word,aut.alfA):
        print("A palavra não pertence ao Alfabeto")
        return
    if len(aut.fim) == 2:#caso seja automato pot pilha vazia
        aut.est = str(aut.est[:len(aut.est)-1]) + ",w]"
        aut.fim = "[w]"
        if aut.saida[-1][5] == "Z":
            aut.dest[-1] = "(w,Z)"
    estAtual = aut.ini
    estFin = aut.fim
    j = 0
    done = transicoes(estAtual,estFin,word,aut,pi,antPi,j)
    if done == 1:
        print("Palavra pertence ao automato")
    else:
        print("Palavra NAO pertence ao automato")
        


main()