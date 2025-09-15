#ifndef FICHEIRO_HEADER
#define FICHEIRO_HEADER

#include <vector>
#include <string>
#include "engine/groups.h"
#include "figuras/Triangles.h"

using namespace std;

bool escreverBinario(const string nome_ficheiro, const ModelSkeletonGenerator& lista);
ModelSkeletonEngine* lerBinario(const string nome_ficheiro);
int ficheiroParaTexto(const string nome_ficheiro, const string output);

#endif