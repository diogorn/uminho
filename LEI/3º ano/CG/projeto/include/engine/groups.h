#ifndef GROUPS_HEADER
#define GROUPS_HEADER

#include <vector>
#include <string>
#include "figuras/Triangles.h"
#include <map>
#include <utility>

using namespace std;

    // Classe para Model Element
    class ModelElement {
        public:

            ModelSkeletonEngine* modelo;
            char* textura;
            bool hasColor;

            float color_diffuse[4];
            float color_ambient[4];
            float color_specular[4];
            float color_emissive[4];

            float color_shininess;

            ModelElement(ModelSkeletonEngine* modelo,char* textura, bool hasColor, float color_diffuse_r, float color_diffuse_g, float color_diffuse_b, float color_ambient_r, float color_ambient_g, float color_ambient_b, float color_specular_r, float color_specular_g, float color_specular_b, float color_emissive_r, float color_emissive_g, float color_emissive_b, float color_shininess);
    
    };

    // Classe para Models
    class Models {
        public:
            vector<ModelElement*> modelos;

            Models();
            void addModel(ModelElement* modelo);
    };

enum TransformacoesENUM {VAZIO, TRANSLACAO, ROTACAO, ESCALA};

    // Classe para Transform
    class TransformElement {
        public:
            TransformacoesENUM tipo;
            double tempo, angulo, x, y, z;
            bool align, drawCurve;
            vector<Ponto>* pontos;

            TransformElement(TransformacoesENUM tipo, double tempo, double angulo, double x, double y, double z,bool align, bool drawCurve, vector<Ponto>* pontos);
            
        };

    // Classe para Transform
    class Transform {
        public:
            vector<TransformElement> transformacoes;

            Transform();
            void addTransform(TransformElement transformacao);
        };

    // Classe para Rose Tree
    class RoseTreeNode {
        public:
            Transform* transform;
            Models* models;
            vector<RoseTreeNode*> filhos;
            int ID;
            int ultimaTransformacao;

            RoseTreeNode(int ID, int ultimaTransformacao);
            void addTransform(Transform* t);
            void addModels(Models* models);
            void addFilho(RoseTreeNode* filho);
            Transform* getTransform();
            Models* getModels();
    };

    // Classe para Group
    class Groups {
        public:
            RoseTreeNode* arvore;

            //Parametros do iterador
            vector<int> stackIterTransformacoes;
            vector<RoseTreeNode*> stackIter;
            RoseTreeNode* iter;
            int iterPush;
            int iterPop;

            Groups();
            Groups(RoseTreeNode* arvore);

            void startIter();
            bool hasNext();
            RoseTreeNode* next();
            bool shouldPush();
            int shouldPop();
            int PopsRestantes();
    };

#endif
