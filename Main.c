#include <stdio.h>
#include <string.h>

#define MAX 101

void ler_numero(char num[], int A[], int *tam, int *negativo);
int soma(int A[], int tamA, int B[], int tamB, int S[]);
int subtracao(int A[], int tamA, int B[], int tamB, int S[], int *neg);
int multiplicacao(int A[], int tamA, int B[], int tamB, int S[]);
int maior_ou_igual(int A[], int tamA, int B[], int tamB);
void imprime_resultado(int S[], int digitos, int negativo);

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
        for (int i = 0; i < MAX + 1; i++)
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
            //else if(ope == 4){
                //if (num_2 != 0)
                    //printf("Divisao e %d\n", (float)num_1/num_2);
                //else 
                    //("Erro: Divisao por zero\n");
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
    
    // Para cada dígito de B (da direita para esquerda)
    for (int i = tamB - 1; i >= 0; i--) {
        int carry = 0;
        int deslocamento = tamB - 1 - i; // Quantas posições deslocar
        
        // Multiplica todo A por este dígito de B
        for (int j = tamA - 1; j >= 0; j--) {
            int posicao = tamanhoMax - 1 - deslocamento - (tamA - 1 - j);
            int produto = A[j] * B[i] + S[posicao] + carry;
            S[posicao] = produto % 10;
            carry = produto / 10;
        }
        
        // Coloca o carry restante
        if (carry > 0) {
            int posicao = tamanhoMax - 1 - deslocamento - tamA;
            S[posicao] += carry;
        }
    }
    
    // Remove zeros à esquerda
    int inicio = 0;
    while (inicio < tamanhoMax - 1 && S[inicio] == 0)
        inicio++;
    
    return tamanhoMax - inicio;
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