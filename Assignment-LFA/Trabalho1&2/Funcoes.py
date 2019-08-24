from Classes import *

def arrumaVetor(visitados,expReg):
    ok = []
    for i in range(len(expReg)):
        if not(i in visitados):
            ok.append(expReg[i])
    return ok

def uniao(er1,er2,ini,fin):
    fin -= 1
    if type(er1) == Objeto and type(er2) != Objeto:
        ini = ini
        fin = fin
        trans = [[ini+2,er2,ini+4]]
        for i in range(len(er1.trans)):
            trans.append(er1.trans[i])
        vazio = [[ini,er1.inicial],[er1.final,fin],[ini,ini+2],[ini+4,fin]]
        for i in range(len(er1.vazio)):
            vazio.append(er1.vazio[i])
        obj = Objeto(ini,fin,trans,vazio)
    
    elif type(er1) != Objeto and type(er2) == Objeto:
        ini = ini
        fin = fin
        trans = [[ini+2,er1,ini+4]]
        for i in range(len(er2.trans)):
            trans.append(er2.trans[i])
        vazio = [[ini,er2.inicial],[er2.final,fin],[ini,ini+2],[ini+4,fin]]
        for i in range(len(er1.vazio)):
            vazio.append(er1.vazio[i])
        obj = Objeto(ini,fin,trans,vazio)
    
    elif type(er1) == Objeto and type(er2) == Objeto:
        ini = ini
        fin = fin
        trans = []
        for i in range(len(er1.trans)):
            trans.append(er1.trans[i])
        for i in range(len(er2.trans)):
            trans.append(er2.trans[i])
        vazio = [[ini,er1.inicial],[er1.final,fin],[ini,er2.inicial],[er2.final,fin]]
        for i in range(len(er1.vazio)):
            vazio.append(er1.vazio[i])
        for i in range(len(er2.vazio)):
            vazio.append(er2.vazio[i])
        obj = Objeto(ini,fin,trans,vazio)

    else:
        ini = ini
        fin = fin
        trans = [[ini+1,er1,ini+3],[ini+2,er2,ini+4]]
        vazio = [[ini+0,ini+1],[ini+0,ini+2],[ini+4,fin],[ini+3,fin]]
        obj = Objeto(ini,fin,trans,vazio)   

    return obj

def conca(er1,er2,inic,fin):
    fin -= 1
    if type(er1) == Objeto and type(er2) != Objeto:
        ini = er1.inicial
        fin = inic+3
        trans = [[inic+2,er2,inic+3]]
        for i in range(len(er1.trans)):
            trans.append(er1.trans[i])
        vazio = [[er1.final,inic+2]]
        for i in range(len(er1.vazio)):
            vazio.append(er1.vazio[i])
        obj = Objeto(ini,fin,trans,vazio)
        
    elif type(er1) != Objeto and type(er2) == Objeto:
        ini = inic
        fin = er2.final
        trans = [[inic,er1,inic+1]]
        for i in range(len(er2.trans)):
            trans.append(er2.trans[i])
        vazio = [[inic+1,er2.inicial]]
        for i in range(len(er2.vazio)):
            vazio.append(er2.vazio[i])
        obj = Objeto(ini,fin,trans,vazio)

    elif type(er1) == Objeto and type(er2) == Objeto:
        ini = er1.inicial
        fin = er2.final
        trans = []
        for i in range(len(er1.trans)):
            trans.append(er1.trans[i])
        for i in range(len(er2.trans)):
            trans.append(er2.trans[i])
        vazio = [[er1.final,er2.inicial]]
        for i in range(len(er1.vazio)):
            vazio.append(er1.vazio[i])
        for i in range(len(er2.vazio)):
            vazio.append(er2.vazio[i])
        obj = Objeto(ini,fin,trans,vazio)

    else:
        ini = inic
        fin = fin
        trans = [[ini,er1,ini+1],[ini+2,er2,ini+3]]
        vazio = [[ini+1,ini+2]]
        obj = Objeto(ini,fin,trans,vazio)

    return obj

def fecha(er1,inic,fin):
    fin -= 1
    if type(er1) == Objeto:
        ini = inic
        fin = inic+3
        trans = []
        for i in range(len(er1.trans)):
            trans.append(er1.trans[i])
        vazio = [[ini,fin],[er1.final,er1.inicial],[ini,er1.inicial],[er1.final,inic+3]]
        for i in range(len(er1.vazio)):
            vazio.append(er1.vazio[i])
        obj = Objeto(ini,fin,trans,vazio)

    else:
        ini = inic
        fin = fin
        trans = [[ini+1,er1,ini+2]]
        vazio = [[ini,ini+1],[ini,fin],[ini+2,fin],[ini+2,ini+1]]
        obj = Objeto(ini,fin,trans,vazio)
    
    return obj
