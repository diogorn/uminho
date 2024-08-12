#include "UI_queries.h"
#include "UI.h"

#define RANKINGSIZE puts(RESET_COR"Escolha o tamanho do ranking\n");
#define INTERVALO puts(RESET_COR"Insira o intervalo de datas que pretende consultar no formato DD/MM/AAAA\n");

#define DISABLE puts(RED_BOLD"Querie inativa"RESET_COR);

// QUERIE 1
void querie1_UI(){
	cleanPage ();
	resultsMenu();
	puts(BLUE"\n\t\t> Resumo do perfil <\n\n"
		WHITE_BOLD"0 - Sair\n\n"
		RESET_COR"Introduza ID do perfil\n");
}

// QUERIE 2
void querie2_UI(){
	cleanPage();
	resultsMenu();
	puts(BLUE"\n\t\t> Condutores com maior avaliação média <\n\n"
		 WHITE_BOLD"0 - Sair\n");
	RANKINGSIZE

}

// QUERIE 3
void querie3_UI(){
	cleanPage();
	resultsMenu();
	puts(BLUE"\n\t\t> Utilizadores com maior distância viajada <\n"
	WHITE_BOLD"0 - Sair\n");
	RANKINGSIZE
}

// QUERIE 4
void querie4_UI(){
	cleanPage();
	resultsMenu();
	puts(BLUE"\n\t\t> Preço médio das viagens numa cidade <\n\n"
		WHITE_BOLD"0 - Sair\n\n"
		RESET_COR"Insira a cidade que pretende consultar\n");
}

// QUERIE 5
void querie5_UI(){
	cleanPage();
	resultsMenu();
	puts(BLUE"\n\t\t> Preço médio das viagens num intervalo de datas <\n\n"WHITE_BOLD"0 - Sair\n\n");
	INTERVALO
}

// QUERIE 6
void querie6_UI(){
	cleanPage();
	resultsMenu();
	puts(BLUE"\n\t\t> Distância média percorrida numa cidade num intervalo de datas <\n\n"WHITE_BOLD"0 - Sair\n\n"
		RESET_COR"Insira a cidade que pretende consultar seguida do intervalo de datas\n");
	
}

// QUERIE 7
void querie7_UI(){
	cleanPage();
	resultsMenu();
	DISABLE
	puts(BLUE"\n\t\t> Melhores condutores numa determinada cidade <\n\n"WHITE_BOLD"0 - Sair\n\n"
		RESET_COR"Insira o tamanho do ranking seguido da cidade que pretende consultar\n");
}

// QUERIE 8
void querie8_UI(){
	cleanPage();
	resultsMenu();
	DISABLE
	puts(BLUE"\n\t> Viagens efetuadas pelo utilizador com um determinado género e idade <\n\n"WHITE_BOLD"0 - Sair\n\n"
		RESET_COR"Insira o género (M/F) seguido da idade do utilizador\n");

}

void querie9_UI(){
	cleanPage();
	resultsMenu();
	DISABLE
	puts(BLUE"\n\t> Viagens num intervalo de tempo em que o passageiro deu gorjeta <\n"WHITE_BOLD"0 - Sair\n\n");
	INTERVALO
}

