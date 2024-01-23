#include <stdio.h>
#include <stdlib.h>

//Calculando o tamanho de um numero
int calculaTam(unsigned long long int num){
    int dig=0;
    while(num != 0){
        num /= 10;
        dig++;
    }
    return dig;
}

//Passando o numero do cartao para um vetor
void toVet(int tam, unsigned long long int numCartao, int *vetCartao){
    unsigned long long int cont=1;
    for(int i = tam-1; i>=0; i--){
        vetCartao[i]=(numCartao/cont) % 10;
        cont = cont * 10;
    }
}

//Verifica se o cartao é valido
int validaCartao(int tamCartao, int *vetCartao){
    //Pegando as posicoes impares e pares, e as colocando em vetores alocados dinamicamentes
    int *vetImpar, *vetPar, contImpar=0, contPar=0, tam=tamCartao;
    vetImpar = (int *)malloc(1 * sizeof(int));
    vetPar = (int *)malloc(1 * sizeof(int));
    for(int i=tam-1; i>=0; i--){
        if(tam%2==1){
            vetImpar[contImpar] = vetCartao[i];
            contImpar++;
            if(i!=0 || i!=1){
                vetImpar = realloc(vetImpar, (contImpar+1) * sizeof(int));
            }
            tam -= 1;
        }else{
            vetPar[contPar] = vetCartao[i];
            contPar++;
            if(i!=0 || i!=1){
                vetPar = realloc(vetPar, (contPar+1) * sizeof(int));
            }
            tam -= 1;
        }
    }

    int contVet;
    if(tamCartao%2 == 0){
        contVet = contImpar;
    }else{
        contVet = contPar;
    }

    //Multiplicando os numeros das devidas posições
    int contMult, vetMult[contVet];
    if(tamCartao%2 == 0){
        contMult = contImpar;
        for (int i=0; i<contImpar; i++){
            vetMult[i] = vetImpar[i] * 2;
        }
    }else{
        contMult = contPar;
        for (int i=0; i<contPar; i++){
            vetMult[i] = vetPar[i] * 2;
        }
    }

   //Pegando cada elemento e multiplicando
   int *vetElemMult, contAloc=0, j=0;
   vetElemMult = (int *)malloc(1 * sizeof(int));
   for(int i=0; i<contMult; i++){
        if(calculaTam(vetMult[i])==1 || vetMult[i]==0){
            contAloc+=1;
            vetElemMult = realloc(vetElemMult, contAloc * sizeof(int));
            vetElemMult[j] = vetMult[i];
            j++;
        }else{
            contAloc+=2;
            vetElemMult = realloc(vetElemMult, contAloc * sizeof(int));
            vetElemMult[j] = vetMult[i]/10;
            vetElemMult[j+1] = vetMult[i]%10;
            j+=2;
        }
   }

   //Somando os resultados
   int somaPar=0, somaImpar=0;
   if(tamCartao%2 == 0){
        for(int i=0; i<contAloc; i++){
            somaImpar += vetElemMult[i];
        }

        for(int i=0; i<contPar; i++){
            somaPar += vetPar[i];
        }
    }else{
        for(int i=0; i<contAloc; i++){
            somaPar += vetElemMult[i];
        }

        for(int i=0; i<contImpar; i++){
            somaImpar += vetImpar[i];
        }
    }

    free(vetImpar);    
    free(vetPar);
    free(vetElemMult);

    if((somaImpar+somaPar)%10 == 0){
        return 0; //Cartão válido
    }else{
        return 1;//Cartão inválido
    }
}

//Verifica qual o tipo do cartao
void verificaCartao(int tam, int *vetCartao, int status){
    if(status == 0){
        //Cartao valido
        if(tam==15 && (vetCartao[0]==3 && (vetCartao[1]==4 || vetCartao[1]==7))){
            printf("AMEX");
        }else if(tam==16 && (vetCartao[0]==5 && (vetCartao[1]==1 || vetCartao[1]==2 || vetCartao[1]==3 ||
                            vetCartao[1]==4 || vetCartao[1]==5))){
            printf("MASTERCARD");
        }else if((tam==13 || tam==16) && (vetCartao[0]==4)){
            printf("VISA");
        }
    }else{
        //Cartao invalido
        printf("INVALID");
    }
}

int main(){
    int tam=0;  
    unsigned long long int numCartao;

    scanf("%llu", &numCartao);
    tam = calculaTam(numCartao);
    int vetCartao[tam];
    toVet(tam, numCartao, vetCartao);
    validaCartao(tam, vetCartao);
    verificaCartao(tam, vetCartao, validaCartao(tam, vetCartao));
    return 0;
}
