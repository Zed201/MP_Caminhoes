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
// Serve para alocar mais um caminhão facilmente na frota


void remover_caminhao(Sede *filiais, int codigo_filial);
// Serve para alocar uma sede nova
Sede *cadastar_filial(Sede *filais, int *n_linhas){
        filais = realloc(filais, (sizeof(Sede) * *(n_linhas)) + 1);
        printf("Digite as coordenadas da nova filial:\n");
        scanf("%f %f", &filais[*(n_linhas)].loc_x, &filais[*(n_linhas)].loc_y);
        // Adiciona mais uma na variavel de controle da quantidade de filiais
        printf("\n digite o código dela:\n");
        scanf("%d", &filais[*(n_linhas)].codigo);
        *n_linhas += 1;
        return filais;
}

void cadrastar_caminhao(Sede *filiais, Caminhao Caminhao, int codigo_filial, int qtd_filiais){
        // A duvida é se eu pego o caminhao antes ou depois
        int aux = 0;
        // zerar para não ter lixo de memória
        filiais[aux].n_caminhao = 0;
        for (int i = 0; i < qtd_filiais; i++)
                if (filiais[i].codigo == codigo_filial)
                    aux = i;    
        filiais[aux].frota = realloc(filiais[aux].frota, (sizeof(Sede) * filiais[aux].n_caminhao) + 1);
        strcpy(filiais[aux].frota[filiais[aux].n_caminhao].Placa, Caminhao.Placa);
        filiais[aux].n_caminhao++;
}

void realizar_entrega(Sede *filiais, produto produto, int n_filiais);

void imprimir_filiais(Sede *filiais, int n_filiais);

int main(){
        Sede* Filiais = NULL;
        int qtd_filiais = 0;
        Filiais = cadastar_filial(Filiais, &qtd_filiais);
        Caminhao n_caranga;
        strcpy(n_caranga.Placa, "cwcfw");
        int x = 0;
        printf("Digite o codigo da filial que deseja adicionar caminhoes\n");
        scanf("%d", &x);
        cadrastar_caminhao(Filiais, n_caranga, x, 3);
        printf("%f %f de código %d\n", Filiais[0].loc_x, Filiais[0].loc_y, Filiais[0].codigo);
        printf(" placa - %s", Filiais[0].frota[0].Placa);
        return 0;
}