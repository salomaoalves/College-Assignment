def criaPilha():
    pilha = ["Z"]
    return pilha

def inserePilha(pilha,ele):
    pilha.append(ele)
    
def removePilha(pilha):
    pilha.pop()

def vaziaPilha(pilha):
    if len(pilha) == 0:
        return True
    else:
        return False