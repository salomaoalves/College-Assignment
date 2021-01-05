Para executar o código é bem simples, basta ir executando cada célula e depois carregar um arquivo csv utilizando a função pd.read_csv(PATH), na CELULA 4, onde PATH será o caminho onde deverá ser encontrado o data set. Abaixo, irei explicar, de forma resumida, a lógica de cada célula.

CELULA 01:
Importa a biblioteca pandas, numpy e math, além de conectar com o Google Drive (opcional, utilizamos o drive para fazermos todos juntos).

CELULA 02:
Célula das funções, há 4. A primeira, write() recebe uma lista dos cluster e gera um arquivo txt. A euclidiana() calcula a distância euclediana entre dois vector. A calcula_dist() calcula a matriz de distância entre os exemplos do data frame passado, apenas a parte triangular superior. Por último, a recalcula() recalcula a matriz de distância, após o agrupamento.

CELULA 03:
A função principal, main(), ela recebe uma matriz de distância inicial e por meio de um loop while, acha o menor valor, faz o agrupamento, salva o agrupamento e recalcula a matriz de distância. Esse loop irá acabar quando tiver apenas um grupo. Após o loop, ele escreve os agrupamentos formados.

CELULA 04:
Lê o data set, calcula a matriz de distância usando a calcula_dist() e chama o main().

CELULA 05:
Executamos um exemplo passado na sala de aula.
