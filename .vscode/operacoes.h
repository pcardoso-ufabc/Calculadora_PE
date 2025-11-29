typedef struct Node {
    int digito;
    struct Node* prox;
} Node;

Node* criar_no(int dado) {
    Node* novo = (Node*)malloc(sizeof(Node));
    if (novo == NULL) exit(1);
    novo->digito = dado;
    novo->prox = NULL;
    return novo;
}

void ler_numero(char num[], int A[], int *tam, int *negativo);
int soma(int A[], int tamA, int B[], int tamB, int S[]);
int subtracao(int A[], int tamA, int B[], int tamB, int S[], int *neg);
int multiplicacao(int A[], int tamA, int B[], int tamB, int S[]);
int maior_ou_igual(int A[], int tamA, int B[], int tamB);
int divisao(int A[], int tamA, int B[], int tamB, int Q[], int R[], int *tamR);
void imprime_resultado(int S[], int digitos, int negativo);
void imprimir_recursivo_aux(Node* no);
void liberar_lista_aux(Node* head);
void fatorial(int n);
