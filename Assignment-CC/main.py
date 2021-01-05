import analisadorSintatico
import os

def read(arq_fonte):
    fita = []
    if os.path.exists(arq_fonte):
        arq_fonte = open(arq_fonte, 'r')
        for line in arq_fonte:
            for j in range(len(line)):
                fita.append(line[j])
        fita.append('\n')
        
    else:
        print("Arquivo inexistente, digite novamente.")
        exit()
    return fita

fita = read('./fonte.txt')
print(fita)
analisadorSintatico.run(fita)
