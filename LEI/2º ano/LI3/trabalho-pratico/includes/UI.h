#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// ANSI color code

// Cor
#define BLACK        "\x1b[30m"
#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define YELLOW       "\x1b[33m"
#define BLUE         "\x1b[34m"
#define MAGENTA      "\x1b[35m"
#define CYAN         "\x1b[36m"
// Bold
#define RED_BOLD     "\x1b[1;31m"
#define GREEN_BOLD   "\x1b[2;32m"
#define YELLOW_BOLD   "\x1b[1;33m"
#define BLUE_BOLD    "\x1b[1;34m"
#define MAGENTA_BOLD "\x1b[1;35m"
#define CYAN_BOLD    "\x1b[1;36m"
#define WHITE_BOLD   "\x1b[1;37m" 
// Default
#define RESET_COR   "\x1b[0m"

//
void cleanPage();
void menuPrincipal(bool fileIsLoaded);
void UIloadFiles();
void UIPreLoadedFiles();
void UIFilePath();

void infoFilesMenu();
void invalidInputUI();
void loadingMenu();
void resultsMenu();

void closedProgramUI();