//
//  main.c
//  pi_miniteste5
//
//  Created by Diogo Neto
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {
  char *nome;
  int nr;
  int nota;
} Aluno;

typedef struct cel {
  Aluno aluno;
  struct cel *prox;
} *Turma;

int adicionaAluno(Turma *t, char *nome, int nr, int nota) {
  Aluno novo_aluno;
  novo_aluno.nome = malloc(sizeof(char) * (strlen(nome) + 1));
  if (novo_aluno.nome == NULL) {
    return 1;
  }
  strcpy(novo_aluno.nome, nome);
  novo_aluno.nr = nr;
  novo_aluno.nota = nota;
  struct cel *nova_cel = malloc(sizeof(struct cel));
  if (nova_cel == NULL) {
    free(novo_aluno.nome);
    return 1;
  }
  nova_cel->aluno = novo_aluno;

  while (*t != NULL && (*t)->aluno.nr < nr) {
    t = &((*t)->prox);
  }

  nova_cel->prox = *t;
  *t = nova_cel;
  return 0;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
