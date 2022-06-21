/*mais sofisticado*/
/*melhor caso: O(N log N)
  pior caso: O(N log N)*/
/*est�vel: n altera a ordem de dados iguais*/
/*desvantagem: � recursivo e usa um vetor aux, obtendo um gasto extra de memoria*/

void mergeSort(int *v, int ini, int fim){//v � o vetor, ini/fim � o inicio/fim do vetor(as pos)
    int meio;
    if(ini<fim){//o floor arredonda
        meio = floor((inicio+fim)/2);//calcula o meio
        mergeSort(v,inicio,meio);/*chama a fun��o para as duas metades,*/
        mergeSort(v,meio+1,fim); /*divindo elas novamente, at� sobra um elemento*/
        merge(v,ini,meio,fim);//chama outra fun��o para combinar os dados
    }
}

void merge(int *v, int ini, int meio, int fim){
    int *temp, p1, p2, tam, i, j, k;
    int fim1=0, fim2=0;
    tam = fim-ini+1;//calcula o tamanho dele
    p1 = ini;    /*cria dois*/
    p2 = meio+1; /*vetores*/
    temp = (int *) malloc(tam*sizeof(int));//aloca o vetor temp
    if(temp != NULL){//cria��o correta
        for(i=0 ; i<tam ; i++){//pecorre o vetor temp
            if(!fim1 && !fim2){//quando tem os dois vetores
                if(v[p1] < v[p2])//v� quem q poe no vetor temp, o menor
                    temp[i] = v[p1++];
                else
                    temp[i] = v[p2++];
                //quando um dos vetores acabarem
                if(p1>meio)
                    fim1=1;
                if(p2>meio)
                    fim2=1;
            }else{//quando um acabar, copia o outro pro temp
                if(!fim1)
                    temp[i] = v[p1++];
                else
                    temp[i] = v[p2++];
            }
        }
        for(j=0,k=ini ; j<tan ; j++,k++)//passa o dados do vetor aux pro vetor v
            v[k] = temp[j];
    }
    free(temp);
}
