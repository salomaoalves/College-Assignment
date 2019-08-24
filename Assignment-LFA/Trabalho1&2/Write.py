def escrevendo(aut,alf):
    with open("vaiDaSim.pl","w") as arq:
        arq.writelines("inicial("+str(aut.inicial)+").\n")
        arq.writelines("final("+str(aut.final)+").\n")

        eFecho = []
        for i in range(len(aut.trans)):
            if not('e' in aut.trans[i]):
                arq.writelines("trans("+str(aut.trans[i][0])+",'"+str(aut.trans[i][1])+"',"+str(aut.trans[i][2])+").\n")
            else:
                eFecho.append(i)
        
        if len(eFecho) != 0:
            for i in range(len(eFecho)):
                arq.writelines("vazia("+str(aut.trans[eFecho[i]][0])+","+str(aut.trans[eFecho[i]][2])+").\n")

        for i in range(len(aut.vazio)):
            arq.writelines("vazia(")
            for j in range(2):
                arq.writelines(str(aut.vazio[i][j]))
                if j!=1:
                    arq.writelines(",")
            arq.writelines(").\n")

        
        arq.writelines("alfabeto("+str(alf)+").")