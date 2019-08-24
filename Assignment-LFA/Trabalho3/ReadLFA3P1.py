from ClasseLFA3P1 import *

def lendo(url):
    est, alfA, alfP, fim, trans, saida, dest, ini = [],[],[],[],[],[],[],[]
    with open(url,'r') as arq:
        text = arq.readlines()
    for i in range(len(text)):
        if i == 0:
            aux = text[i].split()
            est = aux[2]
        if i == 1:
            aux = text[i].split()
            alfA = aux[2]
        if i == 2:
            aux = text[i].split()
            alfP = aux[2]
        if i == 3:
            aux = text[i].split()
            fim = aux[2]
        if i == 4:
            aux = text[i].split()
            ini = aux[2]
        if i > 4:
            trans.append(text[i].split("->"))
    for i in range(len(trans)):
        saida.append(trans[i][0])
        dest.append(trans[i][1][:5])
    aut = Automato(est,alfA,alfP,fim,ini,saida,dest)
    return aut