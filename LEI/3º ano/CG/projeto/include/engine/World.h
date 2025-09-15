#ifndef WORLD_ENGINE_HEADER
#define WORLD_ENGINE_HEADER

#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "figuras/Triangles.h"
#include "engine/groups.h"

using namespace std;

enum LuzENUM {POINT, DIRECTIONAL, SPOTLIGHT};

    // Classe para Luz
    class Luz {
        public:
            LuzENUM tipo;
            float pos_x, pos_y, pos_z;
            float dir_x, dir_y, dir_z;
            float cutoff;

            static Luz criarLuzPoint(float x, float y, float z);
            static Luz criarLuzDirectional(float x, float y, float z);
            static Luz criarLuzSpotlight(float pos_x, float pos_y, float pos_z, float dir_x, float dir_y, float dir_z, float cutoff);
            
        private:
            Luz(LuzENUM tipo,float pos_x, float pos_y, float pos_z, float dir_x, float dir_y, float dir_z, float cutoff);

        };


    // Classe para World
    class World {
        public:
            
            //Objeto com <group>
            Groups* grupos;
            bool hasTime; //Indica se tem tempo na scene
            vector<Luz>* luzes;

            //Janela
            int height = 0;
            int width = 0;

            //Posição
            double pos_x = 0;
            double pos_y = 0;
            double pos_z = 0;

            //Vetor de visão
            double camera_x = 0;
            double camera_y = 0;
            double camera_z = 0;

            //Vetor Normal
            double normal_x = 0;
            double normal_y = 0;
            double normal_z = 0;

            //Projeção
            double fov = 0;
            double near = 0;
            double far = 0;

            //Modo debug
            bool modo_debug = false;
            int quantidade_max_triangulos = 0;

            // Camera livre
            double free_alfa = 0;
            double free_beta = 0;
            double sensitivity = 1.0f;
            bool free_disable = false;
            bool free_needClick = true;
            bool free_limitedAngle = true;
            double free_speed = 1.0f;

            World();
    };

#endif