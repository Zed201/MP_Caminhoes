#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
        char Placa[6];
}Caminhao;

typedef struct 
{
        int codigo;
        float loc_x, loc_y;
        Caminhao *frota;
        int n_caminhao;
} Sede;

typedef struct 
{
        float origem_x, origem_y;
        float destino_x, destino_y;
} produto;


void remover_caminhao(Sede *filiais, int codigo_filial, int qtd_filiais){
        int aux = 0;
        // Achar o codigo correspondente
        for (int i = 0; i < qtd_filiais; i++)
                if (filiais[i].codigo == codigo_filial)
                        aux = i;
        filiais[aux].frota = realloc(filiais[aux].frota, sizeof(Caminhao) *(filiais[aux].n_caminhao - 1));
        filiais[aux].n_caminhao--;
        printf("\nRemoveu um caminhao da sede de codigo %d\n", codigo_filial);
}
// Serve para alocar uma sede nova
Sede *cadastar_filial(Sede *filais, int *n_linhas){
        // fazer lógica de colocar null no final da matriz
        filais = realloc(filais, sizeof(Sede) * (*(n_linhas) + 1));
        if (filais == NULL)
        {
                printf("Nao deu para alocar");
                exit(1);
        }
        printf("Digite as coordenadas da nova filial:\n");
        scanf("%f %f", &filais[*(n_linhas)].loc_x, &filais[*(n_linhas)].loc_y);
        printf("\nDigite o codigo dela:\n");
        filais[*n_linhas].codigo = 0;
        filais[*n_linhas].frota = NULL;
        scanf(" %d", &filais[*(n_linhas)].codigo);
        filais[*n_linhas].n_caminhao = 0;
        *(n_linhas) += 1;
        printf("Mais uma filial cadrastada\n");
        return filais;
}

void cadrastar_caminhao(Sede *filiais, Caminhao Caminhao, int codigo_filial, int qtd_filiais){
        // A duvida é se eu pego o caminhao antes ou depois
        int aux = -1;
        // Usar o null no final para traquear o final da matriz
        // zerar para não ter lixo de memória
        for (int i = 0; i < qtd_filiais; i++){
     
                if (filiais[i].codigo == codigo_filial){
                    aux = i;  
                }
        }
        if (aux == -1)
        {
                printf("nao foi possibel achar esse codigo");
                exit(1);
        }
        // Nao ta conseguindo alocar memoria de forma alguma
        filiais[aux].frota = realloc(filiais[aux].frota, sizeof(Caminhao) * (filiais[aux].n_caminhao + 1));
        if (filiais[aux].frota == NULL)
        {
                printf("nao conseguiu");
                exit(1);
        }
        strcpy(filiais[aux].frota[filiais[aux].n_caminhao].Placa, Caminhao.Placa);
        filiais[aux].n_caminhao++;
        printf("%d-", filiais[aux].n_caminhao);
        printf("Novo caminhao cadrastado\n");
}

void realizar_entrega(Sede *filiais, produto produto, int n_filiais);

void imprimir_filiais(Sede *filiais, int n_filiais){
        for (int i = 0; i < n_filiais; i++)
        {
                printf(" Filial de codigo %d na cord x %.2f e y %.2f| caminhoes\n", filiais[i].codigo, filiais[i].loc_x, filiais[i].loc_y);
                for (int z = 0; z < filiais[i].n_caminhao; z++)
                {
                    printf(" Placa %s\n", filiais[i].frota[z].Placa);
                }
        }
}

int main(){
        Sede* Filiais = NULL;
        int qtd_filiais = 0;
        Filiais = cadastar_filial(Filiais, &qtd_filiais);
        Caminhao n_caranga;
        Filiais = cadastar_filial(Filiais, &qtd_filiais);
        Filiais = cadastar_filial(Filiais, &qtd_filiais);
        strcpy(n_caranga.Placa, "c1\0");
        int x = 0;
        printf("Digite o codigo da filial que deseja adicionar caminhoes\n");
        scanf("%d", &x);
        cadrastar_caminhao(Filiais, n_caranga, x, qtd_filiais);
        printf("Digite o codigo da filial que deseja adicionar caminhoes\n");
        scanf("%d", &x);
        strcpy(n_caranga.Placa, "c2\0");
        cadrastar_caminhao(Filiais, n_caranga, x, qtd_filiais);
        printf("Diga o codigo da filial para tirar o ultimo caminhao");
        int y = 0;
        scanf("%d", &y);
        remover_caminhao(Filiais, y, qtd_filiais);
        imprimir_filiais(Filiais, qtd_filiais);
        
        return 0;
}