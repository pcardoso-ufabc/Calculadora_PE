//Subtracao

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

//Soma

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

//Maior ou igual

int maior_ou_igual(int A[], int tamA, int B[], int tamB){
    if (tamA != tamB)
        return tamA > tamB;
    for(int i = 0; i < tamA; i++){
        if(A[i] != B[i])
            return A[i] > B[i];
    }
    return 1;
}

//Ler numero

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

//Imprime resultado

void imprime_resultado(int S[], int digitos, int negativo) {
    if (negativo) 
        printf("-");
    int i = 0;
    while (i < digitos - 1 && S[i] == 0) i++;
    for (; i < digitos; i++)
        printf("%d", S[i]);
    printf("\n");
}

//Fatorial

void imprimir_recursivo_aux(Node* no) {
    if (no == NULL) return;
    imprimir_recursivo_aux(no->prox);
    printf("%d", no->digito);
}

void liberar_lista_aux(Node* head) {
    Node* atual = head;
    while (atual != NULL) {
        Node* temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

void fatorial(int n) {
    if (n < 0) return;
    
    Node* head = criar_no(1);
    
    for (int i = 2; i <= n; i++) {
        Node* atual = head;
        Node* anterior = NULL;
        int carry = 0;

        while (atual != NULL) {
            int produto = (atual->digito * i) + carry;
            atual->digito = produto % 10;
            carry = produto / 10;
            anterior = atual;
            atual = atual->prox;
        }

        while (carry > 0) {
            Node* novo = criar_no(carry % 10);
            anterior->prox = novo;
            anterior = novo;
            carry = carry / 10;
        }
    }

    imprimir_recursivo_aux(head);
    printf("\n");
    
    liberar_lista_aux(head);
}