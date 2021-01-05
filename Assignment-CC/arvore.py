class Node():
    def __init__(self, data):
        self.data = data
        self.children = []

    def addChild(self, obj):
        self.children.append(obj)

    def printaArvore(self, counter=0):
        """ 
            Como o terminal não possui espaço suficiente, é aconselhável:
            - Diminuir a fonte do terminal;
            - ou colar a saída num arquivo .txt para melhor visualização;
        """
        tab="      "*counter
        if(counter == 0):
            print(" ", self.data)
        if (len(self.children) != 0):
            print(tab," |")
        
        for idx, child in enumerate(self.children):
            print(tab," |-> ", child.data)
            child.printaArvore(counter + 1)
        