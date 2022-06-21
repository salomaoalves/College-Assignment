/*melhor caso: O(N^2)
  pior caso: O(N^2)*/
/*n � est�vel: altera a ordem de dados iguais*/
/*ineficiente para grandes conjs de dados ou se precisar ser rapido*/
/*melhor do q o BubbleSort*/

void selectionSort(int *v, int n){//v � o vetor e o n � o tam do vetor
    int i, j, menor, troca;
    for(i=0 ; i<n-1 ; i++){//pecorre td o vetor
        menor = i;//considera o i como menor valor
        for(j=i+1 ; j<n ; j++){//vai do i at� o final do vetor, procurando o menor elemento
            if(v[j]<v[menor])//verifica se � menor do q o i
                menor = j;//se for, atualiza o menor
        }
        if(i != menor){//realiza a troca do elemento, ou seja, o i troca de pos cm o menor
            troca = v[i];
            v[i] = v[menor];
            v[menor] = troca;
        }
    }
}
