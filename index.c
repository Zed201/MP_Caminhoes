#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// Tipo de dado que é o caminhao
typedef struct
{
        char Placa[7];
}Caminhao;
// Struct das filiais/sedes
typedef struct
{
        int codigo;
        float loc_x, loc_y;
        Caminhao *frota;
        int n_caminhao;
} Sede;
// Struct dos produtos
typedef struct
{
        float origem_x, origem_y;
        float destino_x, destino_y;
} produto;

// Funcao usada para remover o ultimo caminho de uma sede indicada
void remover_caminhao(Sede *filiais, int codigo_filial, int qtd_filiais){
    // Basicamente procura a filial com o código indicado e depois realoca tirando o ultimo elemento
        int aux = 0;
        for (int i = 0; i < qtd_filiais; i++)
                if (filiais[i].codigo == codigo_filial)
                        aux = i;
        filiais[aux].frota = realloc(filiais[aux].frota, sizeof(Caminhao) *(filiais[aux].n_caminhao - 1));
        filiais[aux].n_caminhao--;
        printf("Removeu um caminhao da sede de codigo %d\n", codigo_filial);
}
// Funcao para adicionar uma filial ao vetor de filiais
Sede *cadastar_filial(Sede *filais, int *n_linhas){
    // Primeiro realoca memoria para o vetor, depois faz perguntas dos dados e vai "preenchendo"
        filais = realloc(filais, sizeof(Sede) * (*(n_linhas) + 1));
        if (filais == NULL){ printf("Nao deu para alocar");exit(1); }
        printf("Digite as coordenadas da nova filial:\n");
        scanf("%f %f", &filais[*(n_linhas)].loc_x, &filais[*(n_linhas)].loc_y);
        printf("Digite o codigo dela:\n");
        filais[*n_linhas].codigo = 0;
        filais[*n_linhas].frota = NULL;
        scanf(" %d", &filais[*(n_linhas)].codigo);
        filais[*n_linhas].n_caminhao = 0;
        *(n_linhas) += 1;
        printf("Mais uma filial cadrastada\n");
        return filais;
}
// Funcao para adicionar um caminhao a filial com o codigo indicado
void cadrastar_caminhao(Sede *filiais, Caminhao Caminhao, int codigo_filial, int qtd_filiais){
    // Primeiro vai char a filiar e depois vai alocar memoria na frota e preencher o novo caminhao com a placa digitada
        int aux = -1;
        for (int i = 0; i < qtd_filiais; i++)
                if (filiais[i].codigo == codigo_filial)
                    aux = i;
        if (aux == -1){ printf("Nao foi possivel achar esse codigo"); exit(1); }
        filiais[aux].frota = realloc(filiais[aux].frota, sizeof(Caminhao) * (filiais[aux].n_caminhao + 1));
        if (filiais[aux].frota == NULL) { printf("Nao conseguiu"); exit(1); }
        strcpy(filiais[aux].frota[filiais[aux].n_caminhao].Placa, Caminhao.Placa);
        filiais[aux].n_caminhao++;
        printf("Novo caminhao cadrastado\n");
}
// Muda o caminhao que vai entregar o produto de filial
void realizar_entrega(Sede *filiais, produto produto, int n_filiais){
        // Basicamente calcula, de forma bem básica a filial mas proxima, no caso a que tem as coordenadas mais proximas
        // O calculo deveria ser feito com pitagoras, mas nao e algo que traga tando problema
        // Quando ele ve o mais proximo da origem e o mais proximo do destino ele tira um caminhao do mais proximo da origem
        // e cadrasta ele no mais proximo do destino(o cmainhao vai para a outra filial)
        int aux_o = -1, x_arm = -1, y_amr = -1, aux_d;
       for (int i = 0; i < n_filiais; i++){
        // filiais[i].loc_x/.loc_y
                int x_aux = abs(produto.origem_x - filiais[i].loc_x), y_aux = abs(produto.origem_y - filiais[i].loc_y);
                if (x_aux < x_arm && y_aux < y_amr || i == 0)
                {
                        x_arm = x_aux;
                        y_amr = y_aux;
                        aux_o = i;
                }
                x_aux = abs(produto.destino_y - filiais[i].loc_x), y_aux = abs(produto.destino_y - filiais[i].loc_y);
                if (x_aux < x_arm && y_aux < y_amr || i == 0)
                {
                    x_arm = x_aux;
                    y_amr = y_aux;
                    aux_d = i;
                }
       }
       // Basicamente troca o caminhao de filial
        Caminhao Aux_caminhao;
        strcpy(Aux_caminhao.Placa, filiais[aux_o].frota[filiais[aux_o].n_caminhao - 1].Placa);
        cadrastar_caminhao(filiais, Aux_caminhao, filiais[aux_d].codigo, n_filiais);
        remover_caminhao(filiais, filiais[aux_o].codigo, n_filiais);
}
// Imprimi tudo normalmente
void imprimir_filiais(Sede *filiais, int n_filiais){
    // Imprimi tudo com um for normal
        printf("----------------------------------------------\n");
        for (int i = 0; i < n_filiais; i++)
        {
                printf("-Filial de codigo %d na cord x %.1f e y %.1f| caminhoes\n", filiais[i].codigo, filiais[i].loc_x, filiais[i].loc_y);
                for (int z = 0; z < filiais[i].n_caminhao; z++)
                {
                    printf(" Placa -%s-\n", filiais[i].frota[z].Placa);
                }
        }
}

int main(){
        Sede* Filiais = NULL;
        int qtd_filiais = 0;
        int controle = 0;
        char placa[7];
        int x = 0;
        // Menu para selecionar as opcoes
        do
        {
                printf("---------------------MENU---------------------\n - 1:Cadastrar Filiar - 2:Cadastrar Caminhao\n - 3:Realizar Entrega - 4:Imprimir filiais\n\t\t  - 5:Sair\n");

                scanf("%d", &controle);
                switch (controle)
                {
                        case 1:
                                Filiais = cadastar_filial(Filiais, &qtd_filiais);
                                system("clear");
                        break;
                        case 2:
                                printf("Digite o codigo da filial que deseja adicionar caminhoes\n");
                                scanf("%d", &x);
                                printf("Qual a placa deseja ser adicionada:\n");
                                scanf(" %s", placa);
                                Caminhao n_caranga;
                                strcpy(n_caranga.Placa, placa);
                                cadrastar_caminhao(Filiais, n_caranga, x, qtd_filiais);
                                system("clear");
                        break;
                        case 3:
                                produto n_produto;
                                float o_x, o_y, d_x, d_y;
                                printf("Digite os dados de origem do pacote, primeiro x depois y:\n");
                                scanf("%f %f", &n_produto.origem_x, &n_produto.origem_y);
                                printf("Digite os dados de destino do pacote, primeiro x depois y:\n");
                                scanf("%f %f", &n_produto.destino_x, &n_produto.destino_y);
                                realizar_entrega(Filiais, n_produto, qtd_filiais);
                                system("clear");
                        break;
                        case 4:
                                imprimir_filiais(Filiais, qtd_filiais);
                        break;
                        case 5:
                                printf("Saindo\n");
                        break;
                }
        } while (controle != 5);
       return 0;
}