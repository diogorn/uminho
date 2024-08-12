#include "UI.h"
#include <unistd.h>

void cleanPage() {
    system("clear");
}

void menuPrincipal(bool fileIsLoaded){
    cleanPage();
    puts(RED_BOLD "\n##########################################\n########## Aplicação de Viagens ##########\n##########################################\n" RESET_COR);
    puts("\t0 - Carregar ficheiros.\n");

    printf(WHITE_BOLD"Queries\n\n");

      if (!fileIsLoaded)
    {
        puts(YELLOW_BOLD"#################### ¡WARNING! ####################\n"
             YELLOW"> Carregue ficheiros para usar as seguintes opções:\n");
    }

    printf(fileIsLoaded ? RESET_COR : RED);
    puts(
        "\t1 - Resumo do perfil\n"
        "\t2 - Condutores com maior avaliação média\n"
        "\t3 - Utilizadores com maior distância viajada\n"
        "\t4 - Preço médio das viagens numa cidade\n"
        "\t5 - Preço médio das viagens num intervalo de datas\n"
        "\t6 - Distância média percorrida numa cidade num intervalo de datas\n"
        RED_BOLD"\t7 - Melhores condutores numa determinada cidade\n"
        "\t8 - Viagens efetuadas pelo utilizador com um determinado género e idade\n"
        "\t9 - Viagens num intervalo de tempo em que o passageiro deu gorjeta\n");

    puts(RESET_COR "10 - Fechar programa\n\n"
         BLUE_BOLD "Selecione a opção pretendida\n"
         RESET_COR);


}

void UIloadFiles(){
    cleanPage();
    puts(MAGENTA_BOLD "\n########### Carregar Ficheiros ###########\n" RESET_COR);
    puts(RESET_COR "1 - Ficheiros pré-carregados\n"
                   "2 - Carregar ficheiros\n");
                   //"3 - Gerir ficheiros carregados\n\n");
    puts(RESET_COR "0 - Sair\n\n"
         BLUE_BOLD "Selecione a opção pretendida\n"
         RESET_COR);
}

void UIPreLoadedFiles (){
    cleanPage();
    puts(MAGENTA_BOLD "\n########### Carregar Ficheiros ###########\n" RESET_COR);
    puts(RESET_COR "1 - Dataset regular\n"
                   "2 - Dataset regular with invalid entries\n"
                   "3 - Dataset large\n"
                   "4 - Dataset large with invalid entries\n\n"
                   "0 - Sair\n");
    puts(BLUE_BOLD "Selecione a opção pretendida\n"
         RESET_COR);
}

void UIFilePath(){
    cleanPage();
    puts(MAGENTA_BOLD "\n########### Carregar Ficheiros ###########\n" WHITE_BOLD"0 - Sair\n");
    puts(BLUE_BOLD "Insira o path dos ficheiros\n"RESET_COR);
}



void infoFilesMenu(){
    cleanPage ();
    puts(YELLOW_BOLD "\n\t| Gerenciador de ficheiros |\n\n");
    puts(GREEN"Viagens\n\n"
        RESET_COR"\tFicheiro carragado:\n\tTotal de viagens:\n");
    puts(GREEN"Utilizadores\n\n"
         RESET_COR"\tFicheiro carragado:\n\tTotal de utilizadores:\n\tUtilizadores ativos:\n");
    puts(GREEN "Condutores\n\n"
        RESET_COR"\tFicheiro carragado:\n\tTotal de condutores:\n\tCondutores ativos:\n\n");
    puts(BLUE "ENTER para continuar \n"); // esta opção vai alterar o bool fileIsLoaded para true

}
void invalidInputUI(){
    cleanPage();
    puts(BLUE_BOLD"Insira uma opção válida"RESET_COR);
}

void loadingMenu(){
    cleanPage();
    puts(BLUE_BOLD"\n\tA carregar...\n");
}
void resultsMenu(){
    puts(GREEN "\n ------------\n| Resultados |\n ------------");

}

void closedProgramUI(){
    cleanPage();
    puts(BLUE_BOLD"\n\t> Programa encerrado <\n"RESET_COR);
}