Para executar o código é bem simples, basta carregar um arquivo csv utilizando a função pd.read_csv(PATH), onde PATH será o caminho onde deverá ser encontrado o data set. Após isso, é só ir executando as células que a inserção nos valores nulos vão acontecendo de forma automática. Abaixo, irei explicar, de forma resumida, a lógica de cada célula.

CELULA 01:
Importa a biblioteca panda e conecta com o Google Drive (opcional, utilizamos o drive para fazermos todos juntos).

CELULA 02:
Lê o arquivo csv e imprimi as 5 primeiras linhas. Detalhe, nos data sets que usamos, não vinha os cabeçalhos, por isso usamos o parâmetro header=None, caso o arquivo csv já venha com o cabeçalho, tem que pagar esse parâmetro.

CELULA 03:
Algumas variáveis úteis durantes o código.

CELULA 04:
Pecorremos todo o data set para buscarmos as colunas que possuem valor null (no caso, os data sets que usamos representava os valores null como '?'), assim, calculamos a moda só das colunas necessarias.

CELULA 05:
Essa célula irá pecorrer cada coluna que possuem valor null (o primeiro for), fazendo a contagem de cada elemento (segundo for), guardando a quantidade de vezes que esse elemento aparece e o próprio elemento no dicionário moda_col. Após pecorrer cada coluna, pegamos o valor mais frequente (moda) e guardamos no dicionário moda, o qual irá conter a moda de cada coluna.

CELULA 06:
Pecorremos cada coluna com valores null (o for), em cada intereção, usamos o slice do pandas para substituir todos os valores nulos pela moda correspondente.

CELULA 07:
Chamamos a função .to_csv(PATH) para exportar o data frame. Note, o PATH é o local que o data set será baixado.
