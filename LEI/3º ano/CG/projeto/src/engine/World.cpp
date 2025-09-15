#include "engine/World.h"

#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "figuras/Triangles.h"
#include "engine/groups.h"

using namespace std;

// Classe para Luz
Luz::Luz(LuzENUM tipo,float pos_x, float pos_y, float pos_z, float dir_x, float dir_y, float dir_z, float cutoff) {

    this->tipo = tipo;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->pos_z = pos_z;
    this->dir_x = dir_x;
    this->dir_y = dir_y;
    this->dir_z = dir_z;
    this->cutoff = cutoff;

}

Luz Luz::criarLuzPoint(float x, float y, float z) {
    return Luz(POINT,x,y,z,0,0,0,0);
}

Luz Luz::criarLuzDirectional(float x, float y, float z) {
    return Luz(DIRECTIONAL,0,0,0,x,y,z,0);
}

Luz Luz::criarLuzSpotlight(float pos_x, float pos_y, float pos_z, float dir_x, float dir_y, float dir_z, float cutoff) {
    return Luz(SPOTLIGHT,pos_x,pos_y,pos_z,dir_x,dir_y,dir_z,cutoff);  
}

//Classe para World
World::World() {

    //Grupos
    this->grupos = nullptr;
    this->hasTime = false;
    this->luzes = nullptr;

    //Janela
    this->height = 0;
    this->width = 0;

    //Posição
    this->pos_x = 0;
    this->pos_y = 0;
    this->pos_z = 0;

    //Vetor de visão
    this->camera_x = 0;
    this->camera_y = 0;
    this->camera_z = 0;

    //Vetor Normal
    this->normal_x = 0;
    this->normal_y = 0;
    this->normal_z = 0;

    //Projeção
    this->fov = 0;
    this->near = 0;
    this->far = 0;

    //Modo debug
    this->modo_debug = false;
    this->quantidade_max_triangulos = 0;

    // Camera livre
    this->free_alfa = 0;
    this->free_beta = 0;
    this->sensitivity = 0.5f;
    this->free_disable = false;
    this->free_needClick = true;
    this->free_limitedAngle = true;
    this->free_speed = 0.3f;

}