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
    
    while(ope!=5){
        printf("Digite um opcao entre 1 e 5:\n Opcao 1 Soma\n Opcao 2 Subtracao\n Opcao 3 Multiplicao\n Opcao 4 Divisao\n Opcao 5 Sair\n");
        scanf("%d", &ope);
        for (int i = 0; i < 2 * MAX; i++)
            S[i] = 0;
        
            if (ope == 1){
                printf("Soma e ");
                
                if(negA == negB){
                    digitos = soma(A, tamA, B, tamB, S);
                    negativo = negA;
                }else{
                    digitos = subtracao(A, tamA, B, tamB, S, &negativo);
                    if (maior_ou_igual(A, tamA, B, tamB))
                        negativo = negA;
                    else
                        negativo = negB;
                    }
                
                imprime_resultado(S, digitos, negativo);
                
            }else if(ope == 2){
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
            }else if(ope == 5)
                printf("Operação encerrada\n");
            else
                printf("Operacao invalida\n");
    }
    
    return 0;
}

void ler_numero(char num[], int A[], int *tam, int *negativo){
    int inicio = 0;
    *negativo = 0;
    
    if(num[0] == '-'){
        *negativo = 1;
        inicio = 1;
    }
    
    *tam = strlen(num) - inicio;
    
    for(int i = 0; i < *tam; i++){
        A[i] = num[i + inicio] - '0';
    }
}

int soma(int A[], int tamA, int B[], int tamB, int S[]) {
 int i = tamA - 1, j = tamB - 1, k = MAX, resto = 0;
    int temp[MAX + 1] = {0};

    while (i >= 0 || j >= 0 || resto) {
        int digA = (i >= 0) ? A[i--] : 0;
        int digB = (j >= 0) ? B[j--] : 0;
        temp[k--] = (digA + digB + resto) % 10;
        resto = (digA + digB + resto) / 10;
    }

    int inicio = k + 1;
    int digitos = MAX + 1 - inicio;

    for (int x = 0; x < digitos; x++)
        S[x] = temp[inicio + x];

    return digitos;
}

int subtracao(int A[], int tamA, int B[], int tamB, int S[], int *neg) {
   int tempA[MAX], tempB[MAX];
    memcpy(tempA, A, tamA * sizeof(int));
    memcpy(tempB, B, tamB * sizeof(int));

    *neg = 0;
    if (!maior_ou_igual(tempA, tamA, tempB, tamB)) {
        int temp[MAX];
        memcpy(temp, tempA, sizeof(tempA));
        memcpy(tempA, tempB, sizeof(tempB));
        memcpy(tempB, temp, sizeof(temp));
        int t = tamA; tamA = tamB; tamB = t;
        *neg = 1;
    }

    int i = tamA - 1, j = tamB - 1, k = MAX, emprestimo = 0;
    int temp[MAX + 1] = {0};

    while (i >= 0) {
        int digA = tempA[i] - emprestimo;
        int digB = (j >= 0) ? tempB[j] : 0;

        if (digA < digB) {
            digA += 10;
            emprestimo = 1;
        } else {
            emprestimo = 0;
        }

        temp[k--] = digA - digB;
        i--; j--;
    }

    int inicio = k + 1;
    while (inicio < MAX && temp[inicio] == 0)
        inicio++;

    int digitos = MAX + 1 - inicio;
    if (digitos == 0) digitos = 1;

    for (int x = 0; x < digitos; x++)
        S[x] = temp[inicio + x];

    return digitos;
}

int multiplicacao(int A[], int tamA, int B[], int tamB, int S[]) {
    int tamanhoMax = tamA + tamB;
    
    for (int i = tamB - 1; i >= 0; i--) {
        int carry = 0;
        int deslocamento = tamB - 1 - i; 
        
        for (int j = tamA - 1; j >= 0; j--) {
            int posicao = tamanhoMax - 1 - deslocamento - (tamA - 1 - j);
            int produto = A[j] * B[i] + S[posicao] + carry;
            S[posicao] = produto % 10;
            carry = produto / 10;
        }
        
        if (carry > 0) {
            int posicao = tamanhoMax - 1 - deslocamento - tamA;
            S[posicao] += carry;
        }
    }
    
    int inicio = 0;
    while (inicio < tamanhoMax - 1 && S[inicio] == 0)
        inicio++;
    
    int digitos = tamanhoMax - inicio;

    for (int x = 0; x < digitos; x++)
        S[x] = S[inicio + x];

    return digitos;
}

int divisao(int A[], int tamA, int B[], int tamB, int Q[], int R[], int *tamR) {
    // Verifica divisão por zero
    if (tamB == 1 && B[0] == 0) {
        return -1;
    }
    
    // Se A < B, quociente = 0, resto = A
    if (!maior_ou_igual(A, tamA, B, tamB)) {
        Q[0] = 0;
        for (int i = 0; i < tamA; i++)
            R[i] = A[i];
        *tamR = tamA;
        return 1;
    }
    
    int resto[2 * MAX] = {0};
    int tamResto = 0;
    int quociente[MAX] = {0};
    int tamQuociente = 0;
    
    // Para cada dígito de A
    for (int i = 0; i < tamA; i++) {
        // Traz o próximo dígito
        resto[tamResto++] = A[i];
        
        // Remove zeros à esquerda
        int inicio = 0;
        while (inicio < tamResto - 1 && resto[inicio] == 0)
            inicio++;
        if (inicio > 0) {
            for (int j = 0; j < tamResto - inicio; j++)
                resto[j] = resto[inicio + j];
            tamResto -= inicio;
        }
        
        // Conta quantas vezes B cabe
        int digito = 0;
        while (digito < 10 && maior_ou_igual(resto, tamResto, B, tamB)) {
            int temp[2 * MAX];
            int neg = 0;
            int novoTam = subtracao(resto, tamResto, B, tamB, temp, &neg);
            
            for (int j = 0; j < novoTam; j++)
                resto[j] = temp[j];
            tamResto = novoTam;
            
            digito++;
        }
        
        quociente[tamQuociente++] = digito;
    }
    
    // Remove zeros à esquerda do quociente
    int inicio = 0;
    while (inicio < tamQuociente - 1 && quociente[inicio] == 0)
        inicio++;
    
    int tamQ = tamQuociente - inicio;
    for (int i = 0; i < tamQ; i++)
        Q[i] = quociente[inicio + i];
    
    // Copia o resto
    for (int i = 0; i < tamResto; i++)
        R[i] = resto[i];
    *tamR = tamResto;
    
    return tamQ;
}

int maior_ou_igual(int A[], int tamA, int B[], int tamB){
    if (tamA != tamB)
        return tamA > tamB;
    for(int i = 0; i < tamA; i++){
        if(A[i] != B[i])
            return A[i] > B[i];
    }
    return 1;
}

void imprime_resultado(int S[], int digitos, int negativo) {
    if (negativo) 
        printf("-");
    int i = 0;
    while (i < digitos - 1 && S[i] == 0) i++;
    for (; i < digitos; i++)
        printf("%d", S[i]);
    printf("\n");
}
