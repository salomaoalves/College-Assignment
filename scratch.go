package main

//Pacotes/Bibliotecas necessários
import (
	"fmt"
	"reflect"
	"runtime"
	"strings"
)
	// Constantes adotadas
	const (
		 gap = -1
		 match = 1
		 missmatch = -1
	)

func main() {

	//Usar quantos processadores estiverem disponíveis
	runtime.GOMAXPROCS(runtime.NumCPU())


	//Coletamdo os dados / retorno multiplas variáveis
	tamSeq1, tamSeq2, seq1, seq2  := coletaDados()
	// Cria a matrix segundo os dados de entrada
	matrix := criaMatrix(tamSeq1, tamSeq2)
	//Inicializa a matrix com os valores
	inicializaMatrix(matrix, tamSeq1, tamSeq2)
	//Faz os devidos calculos e monta a matrix
	preencheMatrix(matrix, seq1, seq2, tamSeq1, tamSeq2)
	//Vizualização da matrix
	//printMatrix(matrix, seq1, seq2, tamSeq1, tamSeq2)

	//Realiza o calculo do caminho
	traceback(matrix, seq1, seq2, tamSeq1, tamSeq2)
	//retorna score da sequência
	fmt.Printf("Score do alinhamento é: %d\n",matrix[tamSeq2-1][tamSeq1-1])
}

func coletaDados()(tamSeq1 int,tamSeq2 int, seq_1 string, seq_2 string ){
	var (
		sequencia_1 string;
		sequencia_2 string
	)
	//Lendo do teclado as informações
	fmt.Print("Digite a Sequencia A: ")
	fmt.Scan(&sequencia_1)
	fmt.Print("Digite a Sequencia B: ")
	fmt.Scan(&sequencia_2)

	//Obtendo tamanho da string
	tamSeq1 = len(sequencia_1) + 1
	tamSeq2 = len(sequencia_2) + 1
	seq_1 = strings.ToUpper(sequencia_1)
	seq_2 = strings.ToUpper(sequencia_2)
	return
}

func criaMatrix(tamSeq1 int, tamSeq2 int)[][]int{
	//Cria matriz
	matrix := make([][]int, tamSeq2)
	for i := 0; i < tamSeq2 ; i++ {
		matrix[i] = make([]int, tamSeq1)
	}
	return matrix
}

 func inicializaMatrix(matrix[][]int, tamSeq1 int, tamSeq2 int){

	 //Valores iniciais
	 matrix[0][0] = 0
	 for k:=0; k < tamSeq1 ; k++{
		 if(k>0){
			 matrix[0][k] = matrix[0][k-1] + gap
		 }
	 }

	 for j:=0; j < tamSeq2 ; j++{
		 if(j>0){
			 matrix[j][0] = matrix[j-1][0] + gap
		 }
	 }
 }

func printMatrix(matrix [][]int,seq1 string ,seq2 string, tamSeq1 int, tamSeq2 int){

	sequencia_1 := "-"
	sequencia_1 += seq1

	sequencia_2 := "-"
	sequencia_2 += seq2

	fmt.Printf("x")
	for i:= 0; i < tamSeq1; i++{
		fmt.Printf("%4c", sequencia_1[i])
	}
	fmt.Printf("\n")
	for i := 0; i < tamSeq2 ; i++ {
		fmt.Printf("%c",sequencia_2[i])
		for j:= 0; j < tamSeq1; j++{
			fmt.Printf("%4d", matrix[i][j])
		}
		fmt.Printf("\n")
	}
}
//Calcula o topo a esquerda e a diagonal
func calc(matrix [][]int, i int, j int, score int)(diagonal int, superior int, esquerda int){

	diagonal = retornaDiag(matrix, i , j , score)

	superior = retornaTop(matrix, i , j , score)

	esquerda = retornaLeft(matrix, i , j , score)

	return
}

func retornaDiag(matrix [][]int, i int, j int, score int)(int){
	return matrix[i-1][j-1] + score
}

func retornaLeft(matrix [][]int, i int, j int, score int)(int){
	return matrix[i][j-1] + gap
}

func retornaTop(matrix [][]int, i int, j int, score int)(int){
	return matrix[i-1][j] + gap
}


//Retorna o maior com entrada de 3 elementos
func maxZ(l1 int, l2 int, l3 int) int{
	if l1 > l2 && l1 > l3 {
		return l1
	}else{
		if l2 > l3{
			return l2
		}else{
			return l3
		}
	}
}

func preencheMatrix(matrix [][]int, seq1 string ,seq2 string, tamSeq1 int, tamSeq2 int){

	for x:=1 ; x < tamSeq2 ; x++{
		for y := 1; y < tamSeq1 ; y++{
			//Compara se as sequências são iguais
			if(verificaMatch(seq2, seq1, x , y)){
				//fmt.Printf("Igual %c e %c\n",seq2[x-1], seq1[y-1])
				//Se houver match o score eh 1
				score := match
				diagonal, topo, esquerda := calc(matrix, x, y, score)
				maX := maxZ(diagonal, topo, esquerda)
				matrix[x][y] = maX
			}else{
				//fmt.Printf("~igual %c e %c\n",seq2[x-1], seq1[y-1])
				score := missmatch
				diagonal, topo, esquerda := calc(matrix, x, y, score)
				maX := maxZ(diagonal, topo, esquerda)
				matrix[x][y] = maX
			}
		}
	}
}

func verificaMatch(seq2 string, seq1 string, x int,y int)(resultado bool){
	if(reflect.DeepEqual(seq2[x -1],seq1[y -1])){
		 return true
	}
	return false
}

func traceback(matrix [][]int, seq1 string ,seq2 string, tamSeq1 int, tamSeq2 int){
	var(
		X int = tamSeq2 - 1
		Y int = tamSeq1 - 1

	)
	sequencia_1 , sequencia_2 := "", ""
	//score := 0
	//Primeira posição sempre último elemento

	for X > 0 && Y > 0{
		score := matrix[X][Y]
		if(verificaMatch(seq2, seq1, X , Y)){
			sequencia_1 = string(seq1[Y-1]) + sequencia_1
			sequencia_2 = string(seq2[X-1]) + sequencia_2
			Y--
			X--
			//Verifica top
		}else if(score ==  retornaTop(matrix, X , Y , score)){
			sequencia_1 = "-" + sequencia_1
			sequencia_2 = string(seq2[X-1]) + sequencia_2
			X--
			//Sobrou left
		}else{
			sequencia_2 = "-" + sequencia_2
			sequencia_1 = string(seq1[Y-1]) + sequencia_1
			Y--
		}
	}
	//Se chega na parede do lado esquerdo ai tem que colocar gap
	for Y > 0{
		sequencia_2 = "-" + sequencia_2
		sequencia_1 = string(seq1[Y-1]) + sequencia_1
		Y--
	}
	//Chega no topo ai tem que colocar os gap
	for X > 0{
		sequencia_1 = "-" + sequencia_1
		sequencia_2 = string(seq2[X-1]) + sequencia_2
		X--
	}
	println(sequencia_1)
	println(sequencia_2)

}


