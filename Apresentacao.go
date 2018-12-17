Ela é uma linguagem de alto nível, muito mais que C.
É compilada e gera executável nativo.
Originalmente foi concebida para ser uma linguagem para desenvolvimento de sistemas 
	e não tanto para aplicativos, mas isto não ocorreu de fato, então é de multipropósito 
	e é usada em muitas coisas para web, embora possa ser usada para qualquer coisa.
Ela é do paradigma imperativo, essencialmente. 
É modular, possui encapsulamento e polimorfismo, mas não há mecanismo de herança.
	Ela evita recursos que a torne multiparadigma. Ela prefere os mecanismos mais básicos.
Ponteiros são expostos embora não possa usá-los livremente como ocorre em C. São mais como referências.
A sintaxe é sucinta como em Python, por isso atrai programadores desta que desejam mais performance.
Possui coletor de lixo então não precisa se preocupar muito com o gerenciamento de memória. 
Ela é rápida

//BIBLIOTECAS
import(
	"lib1",
	"lib2",
	...,
	"libn"
)
lib1.Function() //assim que se utiliza uma função de uma biblioteca

//OPERADORES ARITMETICOS & COMPARAÇÃO & LÓGICOS
Soma 		  | + | Igual  	       | == | OU   | || |
Subtração 	  | - | Diferente  	   | != | E    | && |
Multiplicação | * | Maior que  	   | >  |
Divisão		  | / | Menor que	   | <  |
Restao        | % | Maior ou igual | >= |
					Menor ou igual | <= |

//DECREMENTO & INCREMENTO
var += N //soma N na variável var; vale para tds as outras operações
var -= N //subtrai N na variável var; vale para tds as outras operações

//CRIANDO FUNÇÃO
func nome(par1 type, ..., parN type) type/*este pe pra caso a função retorne algo*/{
	CODIGO
	return ALGO //caso precise retorna algo
}

//DECLARANDO CONSTANSTES
const (
	constante = VALOR
)

//DECLARANDO VARIÁVEL
var NOME type = Valor //a variável é do tipo type
var NOME = Valor //a variável é do mesmo tipo do Valor
NOME := Valor //a variável é do mesmo tipo do Valor

//BIBLIOTECA fmt
fmt.Print(ALGO) //printa o ALGO e NÃO pula linha
fmt.Println(ALGO) //printa o ALGO E pula linha
fmt.Scan(&Variavel) //leitura do teclado

//BIBLIOTECA strings
strings.ToUpper(ALGO) //deixa ALGO em letra maiuscula
strings.ToLower(ALGO) //deixa ALGO em letra minuscula

//ARRAYS
var NOME[SIZE] type
NOME := [] type {ELEMENTOS} 

//ARRAYS MULTIDIMENSIONAIS
var NOME = [n_l][n_c] type {ELEMENTOS}

//STRUCT
type estrutura struct{
	ATRIBUTOS //ex: id int
}
func (nome estrutura) metodoNome(){ //cria um metodo para a estrutura
	CODIGO
}
var := estrutura{Valores dos atributos} //a var recebe a struct
var.metodoNome() //chama o metodo
var.Atr = Valor //atribui Valor ao atributo Atr

//DICIONARIO
var dic = map[type]/*da chave*/type/*dos valores*/{ CHAVE:VALOR}
dic[chave] = Valor //atualiza a chave
delete(dic,chave) //deleta a chave
dic = make(map[type]type) //apaga o dic, na vdd, ele atribui um dic vazio

//IF ELSE
if COMPARACAO {
	CODIGO
}else{
	CODIGO
}

//SWITCH
switch EXPRESSION {
	case CONDICAO:
		CODIGO
	default:
		CODIGO
	}

//FOR
for INDICE:=VALOR; COMPARACAO COM O INDICE; DEC/INC COM O INDICE{
	CODIGO
}
for indice/*indice do array*/,elemento/*elementos do array;opcional*/ := range Array{
	CODIGO
}
for CONDICAO/*executa ate a condicao for false*/{
	CODIGO
}

//BREAK & CONTINUE
break //da fim a um loop
continue //ignora o resto e volta pro loop

//READ & WRITE EM ARQUIVOS(usa a lib os)
var caminho = "URL do arq"
var status = os.Stat(caminho) //devolve o status do arq(T p/ ele existe e F p/ ele n existe)
os.IsNotExist(status) //diz se existe(F) ou não(V)
var arq,erro = os.Open(caminho,os.O_WRONLY,0644) //abre para escrita
var arq,erro = os.Open(caminho) //abre para escrita
var arq,erro = os.Open(caminho,os.O_RDONLY,0644) //abre para leitura
var arq,erro = os.Create(caminho) //abre para leitura e cria (caso ele n exista)
defer arq.Close() //fecha o arq
arq.WriteString(ALGO) //escreve no arq
escritor := bufio.NewWriter(arq); fmt.Fprintln(escritor, linha) //escreve no arquivo
arq.Read(var) //ler o arq e guarda em var
scanner := bufio.NewScanner(arq); linhas = append(linhas, scanner.Text()) //le no arquivo
arq.Sync() //sincroniza o arq