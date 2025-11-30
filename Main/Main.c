#include <stdio.h>
#include <string.h>
#include "operacoes.h"

#define MAX 101

int main() {
    
    char num_1 [MAX], num_2 [MAX];
    int A[MAX], B[MAX], S[2 * MAX];
    int ope = 0, negA = 0, negB = 0, digitos = 0, negativo = 0, tamA, tamB;
    
    printf("Digite dois valores inteiros: ");
    scanf("%100s %100s", num_1, num_2);
    
    ler_numero(num_1, A, &tamA, &negA);
    ler_numero(num_2, B, &tamB, &negB);
    
    while (ope != 6) {
        printf("Digite uma opcao entre 1 e 6:\n"
               " Opcao 1 Soma\n"
               " Opcao 2 Subtracao\n"
               " Opcao 3 Multiplicao\n"
               " Opcao 4 Divisao\n"
               " Opcao 5 Fatorial (operacao personalizada)\n"
               " Opcao 6 Sair\n");
        scanf("%d", &ope);

        for (int i = 0; i < 2 * MAX; i++)
            S[i] = 0;
        
        if (ope == 1){
            printf("Soma e ");
            
            if(negA == negB){
                digitos = soma(A, tamA, B, tamB, S);
                negativo = negA;
            } else {
                digitos = subtracao(A, tamA, B, tamB, S, &negativo);
                if (maior_ou_igual(A, tamA, B, tamB))
                    negativo = negA;
                else
                    negativo = negB;
            }
            
            imprime_resultado(S, digitos, negativo);
            
        } else if(ope == 2){
            printf("Subtracao e ");
            
            if (negA != negB) {
                digitos = soma(A, tamA, B, tamB, S);
                negativo = negA;
            } else {
                digitos = subtracao(A, tamA, B, tamB, S, &negativo);
                if (!maior_ou_igual(A, tamA, B, tamB))
                    negativo = !negA;
                else
                    negativo = negA;
            }
            
            imprime_resultado(S, digitos, negativo);
            
        } else if(ope == 3){
            printf("Multiplicacao e ");
            digitos = multiplicacao(A, tamA, B, tamB, S);
            negativo = (negA != negB) ? 1 : 0;
            imprime_resultado(S, digitos, negativo);            
            
        } else if(ope == 4){
            int Q[MAX], R[MAX];
            int tamR = 0;
            
            digitos = divisao(A, tamA, B, tamB, Q, R, &tamR);
            
            if (digitos == -1) {
                printf("Erro: Divisao por zero\n");
            } else {
                negativo = (negA != negB) ? 1 : 0;
                printf("Divisao e ");
                imprime_resultado(Q, digitos, negativo);
            }

        } else if (ope == 5) {
            int n;
            printf("Digite um valor inteiro (pequeno) para o fatorial: ");
            scanf("%d", &n);
            printf("Fatorial e ");
            fatorial(n);

        } else if(ope == 6) {
            printf("Operacao encerrada\n");
        } else {
            printf("Operacao invalida\n");
        }
    }
    
    return 0;
}
