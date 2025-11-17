#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.

#include <stdbool.h>

#include <time.h>


#define MAX_ITENS 10


typedef enum { NOME, TIPO, PRIORIDADE } CriterioOrdenacao;



typedef struct {

    char nome[30];

    char tipo[20];

    int quantidade;

    int prioridade;

} Componente;



bool estaOrdenada = false;

CriterioOrdenacao ultimoCriterio;



// ================================

// Pausa

// ================================

void pausar() {

    printf("\nPressione ENTER para continuar...");

    getchar(); getchar();

}



// ================================

// Medir tempo real de execução

// ================================

double medirTempo(void (*funcao)(void*, void*, void*, void*),

                  void *arg1, void *arg2, void *arg3, void *arg4) {

    clock_t inicio = clock();

    funcao(arg1, arg2, arg3, arg4);

    clock_t fim = clock();

    return (double)(fim - inicio) / CLOCKS_PER_SEC;

}



// ================================

// Inserir item

// ================================

void inserirItem(Componente mochila[], int *qtd) {

    if (*qtd >= MAX_ITENS) {

        printf("\n Mochila cheia! Não é possível adicionar mais itens.\n");

        pausar();

        return;

    }



    Componente novo;

    printf("\n--- Cadastro de Item ---\n");

    printf("Nome: "); scanf(" %[^\n]", novo.nome);

    printf("Tipo: "); scanf(" %[^\n]", novo.tipo);

    printf("Quantidade: "); scanf("%d", &novo.quantidade);

    printf("Prioridade (1 a 5): "); scanf("%d", &novo.prioridade);



    for (int i = 0; i < *qtd; i++) {

        if (strcmp(mochila[i].nome, novo.nome) == 0) {

            mochila[i].quantidade += novo.quantidade;

            printf("\n Item existente! Quantidade atualizada para %d.\n", mochila[i].quantidade);

            pausar();

            return;

        }

    }



    mochila[*qtd] = novo;

    (*qtd)++;

    estaOrdenada = false;

    printf("\n Item adicionado com sucesso!\n");

}



// ================================

// Remover item

// ================================

void removerItem(Componente mochila[], int *qtd) {

    if (*qtd == 0) {

        printf("\n Mochila vazia!\n");

        pausar();

        return;

    }



    char nomeRemover[30];

    printf("\n--- Remover Item ---\n");

    printf("Digite o nome do item: ");

    scanf(" %[^\n]", nomeRemover);



    for (int i = 0; i < *qtd; i++) {

        if (strcmp(mochila[i].nome, nomeRemover) == 0) {

            mochila[i] = mochila[*qtd - 1];

            (*qtd)--;

            printf("\n Item '%s' removido!\n", nomeRemover);

            pausar();

            estaOrdenada = false;

            return;

        }

    }

    printf("\n Item não encontrado.\n");

    pausar();

}



// ================================

// Mostrar itens

// ================================

void mostrarComponentes(void *m, void *qtd, void *a, void *b) {

    Componente *mochila = (Componente *)m;

    int quantidade = *(int *)qtd;



    if (quantidade == 0) {

        printf("\n Mochila vazia.\n");

        return;

    }



    printf("\n--- Itens na Mochila %d/%d ---\n", quantidade, MAX_ITENS);

    printf("------------------------------------------------------------\n");

    printf("%-20s| %-20s| %-10s| %-10s\n", "NOME", "TIPO", "QTD", "PRIORIDADE");

    printf("------------------------------------------------------------\n");

    for (int i = 0; i < quantidade; i++)

        printf("%-20s| %-20s| %-10d| %-10d\n",

               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);

    printf("------------------------------------------------------------\n");

}



// ================================

// Insertion Sort por tipo

// ================================

void insertionSortTipo(Componente arr[], int n) {

    for (int i = 1; i < n; i++) {

        Componente chave = arr[i];

        int j = i - 1;

        while (j >= 0 && strcmp(arr[j].tipo, chave.tipo) > 0) {

            arr[j + 1] = arr[j];

            j--;

        }

        arr[j + 1] = chave;

    }

}



// ================================

// Selection Sort por prioridade

// ================================

void selectionSortPrioridade(Componente arr[], int n) {

    for (int i = 0; i < n - 1; i++) {

        int min = i;

        for (int j = i + 1; j < n; j++)

            if (arr[j].prioridade < arr[min].prioridade)

                min = j;

        if (min != i) {

            Componente temp = arr[i];

            arr[i] = arr[min];

            arr[min] = temp;

        }

    }

}



// ================================

// Ordenar mochila

// ================================

void ordenarMochilaFunc(void *m, void *qtd, void *crit, void *nulo) {

    Componente *mochila = (Componente *)m;

    int quantidade = *(int *)qtd;

    CriterioOrdenacao criterio = *(CriterioOrdenacao *)crit;



    if (criterio == NOME) {

        for (int i = 1; i < quantidade; i++) {

            Componente chave = mochila[i];

            int j = i - 1;

            while (j >= 0 && strcmp(mochila[j].nome, chave.nome) > 0) {

                mochila[j + 1] = mochila[j];

                j--;

            }

            mochila[j + 1] = chave;

        }

    } else if (criterio == TIPO) {

        insertionSortTipo(mochila, quantidade);

    } else {

        selectionSortPrioridade(mochila, quantidade);

    }



    estaOrdenada = true;

    ultimoCriterio = criterio;

}



// ================================

// Busca Binária (nome, tipo ou prioridade)

// ================================

void buscaBinariaFunc(void *m, void *qtd, void *crit, void *nulo) {

    Componente *mochila = (Componente *)m;

    int quantidade = *(int *)qtd;

    CriterioOrdenacao criterio = *(CriterioOrdenacao *)crit;



    if (!estaOrdenada) {

        printf("\n A mochila precisa estar ordenada para busca binária!\n");

        return;

    }



    int inicio = 0, fim = quantidade - 1, meio;

    bool achou = false;

    long comparacoes = 0;



    if (criterio == PRIORIDADE) {

        int chave;

        printf("Digite a prioridade: ");

        scanf("%d", &chave);

        while (inicio <= fim) {

            meio = (inicio + fim) / 2;

            comparacoes++;

            if (mochila[meio].prioridade == chave) {

                printf("\nItens com prioridade %d:\n", chave);

                for (int i = meio; i < quantidade; i++)

                    if (mochila[i].prioridade == chave)

                        printf("- %s (%s)\n", mochila[i].nome, mochila[i].tipo);

                achou = true;

                break;

            } else if (chave < mochila[meio].prioridade)

                fim = meio - 1;

            else

                inicio = meio + 1;

        }

    } else {

        char chave[30];

        printf("Digite o %s: ", criterio == NOME ? "nome" : "tipo");

        scanf(" %[^\n]", chave);

        while (inicio <= fim) {

            meio = (inicio + fim) / 2;

            int cmp = (criterio == NOME)

                        ? strcmp(chave, mochila[meio].nome)

                        : strcmp(chave, mochila[meio].tipo);

            comparacoes++;

            if (cmp == 0) {

                printf("\nItem encontrado: %s (%s), Qtd: %d, Prioridade: %d\n",

                       mochila[meio].nome, mochila[meio].tipo,

                       mochila[meio].quantidade, mochila[meio].prioridade);

                achou = true;

                break;

            } else if (cmp < 0)

                fim = meio - 1;

            else

                inicio = meio + 1;

        }

    }



    if (!achou)

        printf("\n Item não encontrado.\n");

    printf("🔎 Comparações: %ld\n", comparacoes);

}



// ================================

// Utilitário para texto do critério

// ================================

const char* criterioToString(CriterioOrdenacao c) {

    switch (c) {

        case NOME: return "Nome";

        case TIPO: return "Tipo";

        case PRIORIDADE: return "Prioridade";

        default: return "Desconhecido";

    }

}



// ================================

// Menu

// ================================

void exibirMenu(int qtd) {

    printf("\n=================================================\n");

    printf("    MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA\n");

    printf("=================================================\n");

    printf(" Itens na mochila: %d/%d\n", qtd, MAX_ITENS);

    if (estaOrdenada)

        printf(" Status: ORDENADA por %s\n\n", criterioToString(ultimoCriterio));

    else

        printf(" Status: NÃO ORDENADA\n\n");

    printf("1. Inserir item\n");

    printf("2. Remover item\n");

    printf("3. Listar itens\n");

    printf("4. Buscar item (sequencial)\n");

    printf("5. Ordenar mochila\n");

    printf("6. Buscar item (busca binária)\n");

    printf("0. Sair\n");

    printf("-------------------------------------------------\n");

    printf("Escolha uma opção: ");

}



// ================================

// Principal

// ================================

