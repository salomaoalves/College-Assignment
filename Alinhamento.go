package main

import (
	"fmt"
)

func main(){
	result := maxVal(1,2,3)
	fmt.Print("%d", result)

	func maxVal(x int , y int, z int )(resultado int){
	if(x > y && x > z){
		resultado =  x
	}else if(y > x && y > z){
		resultado = y
	}else{
		resultado = z
	}
	return resultado
	}
 }
	/*
	//recebe as inf
	inputUtilizador := bufio.NewReader(os.Stdin)
	fmt.Print("Digite a sequencia A:")
	seq1 := inputUtilizador.ReadeString('\n')
	fmt.Print("\nDigite a sequencia B:")
	seq2 := inputUtilizador.ReadeString('\n')
	fmt.Print("Digite o gap:")
	d := inputUtilizador.ReadeString('\n')
	size1 := len(seq1)
	size2 := len(seq2)

	//criando as matrizes
	tabela := [seq1+1][seq2+1] int

	//inicializacao

	for i:=0; i<=size1; i++{
		for j:=0; j<=size2; j++{
			F := condIni(i,j,d)
			//add F na tabela
		}
	}

	//preenchimento (scoring)
	for i:=1; i<=size1; i++{
		for j:=1; j<=size2; j++{
			F := pontuacao(i,j,d)
			//add F na tabela
		}
	}

	//alinhamento(traceback)
}

func condIni(i int, j int, d int) int{
	if i == 0 && j == 0{
		return 0
	}else{
		if j == 0{
			return -i * d
		}else{
			return -j * d
		}
	}
}

func pontuacao(i int, j int, d int) int{
	l1 := F(i-1,j-1) + s(i,j)
	l2 := F(i-1,j) - d
	l3 := F(i,j-1) - d 
	return max(l1,l2,l3)
}

func F(i int, j int) int{
	//procurar na propria matriz
}

func s(i int, j int) int{
	//procurar na matriz de merito
}

func max(l1 int, l2 int, l3 int) int{
	if l1 > l2 && l1 > l3 {
		return l1
	}else{
		if l2 > l3{
			return l2
		}else{
			return l3
		}
	}
}*/