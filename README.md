# Como compilar o arquivo

```bash
gcc -c operacoes.c -o operacoes.o
```

Aqui a gente pega o arquivo operacoes.c que tá as funções de soma, subtração, etc e transforma em operacoes.o, que é a versão compilada dele mas que não da pra executar ainda.
Assim só essa parte é compilada, quando precisar fazer alguma alteração nas operações, só esse arquivo precisa ser recompilado

```bash
gcc -c main.c -o main.o
```

Mesma coisa do passo anterior, quando precisar fazer alguma alteração na main, só esse arquivo precisa ser recompilado

```bash
gcc main.o operacoes.o -o calculadora
```

Aqui é pra linkar os dois main.o + operacoes.o e cria o executável chamado calculadora, porque os .o sozinhos não funcionam 

```bash
./calculadora
```

Depois é só rodar o código
