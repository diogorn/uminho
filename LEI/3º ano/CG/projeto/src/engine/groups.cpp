#include "engine/groups.h"
#include <vector>
#include <string>
#include "figuras/Triangles.h"
#include <map>

using namespace std;

//Classe para Groups
Groups::Groups() {

    this->arvore = nullptr;
    this->iter = nullptr;
    this->stackIterTransformacoes = vector<int>();
    this->stackIter = vector<RoseTreeNode*>();
    this->iterPop = 0;
    this->iterPush = 0;

}

Groups::Groups(RoseTreeNode* arvore) {

    this->arvore = arvore;
    this->iter = nullptr;
    this->stackIterTransformacoes = vector<int>();
    this->stackIter = vector<RoseTreeNode*>();

}

void Groups::startIter() {

    this->iter = nullptr;
    this->stackIterTransformacoes.clear();
    this->stackIter.clear();
    this->iterPop = 0;
    this->iterPush = 0;

    if (this->arvore != nullptr) {
        this->stackIter.push_back(this->arvore);
    }

}

RoseTreeNode* Groups::next() {
    
    if (this->stackIter.size() == 0)
        this->iter = nullptr;
    else {

        this->iter = this->stackIter.back();
        this->stackIter.pop_back();

        for (int i = this->iter->filhos.size() - 1; i >= 0 ; i--) {
            this->stackIter.push_back(this->iter->filhos[i]);
        }

        this->iterPop = 0;

        while (this->stackIterTransformacoes.empty() == false && this->stackIterTransformacoes.back() != this->iter->ultimaTransformacao) {
            this->iterPop++;
            this->stackIterTransformacoes.pop_back();
        }

        this->iterPush = 0;

        if (this->iter->transform != nullptr) {
            this->iterPush = 1;
            this->stackIterTransformacoes.push_back(this->iter->ID);
        }

    }


    return this->iter;
}

bool Groups::shouldPush() {
    return this->iterPush == 1;
}

int Groups::shouldPop() {
    return this->iterPop;
}

int Groups::PopsRestantes() {

    return this->stackIterTransformacoes.size();

}

// Classe para Rose Tree
RoseTreeNode::RoseTreeNode(int ID, int ultimaTransformacao) {

    this->ID = ID;
    this->ultimaTransformacao = ultimaTransformacao;
    this->transform = nullptr;
    this->models = nullptr;
    this->filhos = vector<RoseTreeNode*>();

}

void RoseTreeNode::addTransform(Transform* t) {

    this->transform = t;

}

void RoseTreeNode::addModels(Models* models) {

    this->models = models;

}

void RoseTreeNode::addFilho(RoseTreeNode* filho) {

    this->filhos.push_back(filho);

}

Transform* RoseTreeNode::getTransform() {

    return this->transform;

}

Models* RoseTreeNode::getModels() {
    return this->models;
}

// Classe para Model Element
ModelElement::ModelElement(ModelSkeletonEngine* modelo,char* textura, bool hasColor, float color_diffuse_r, float color_diffuse_g, float color_diffuse_b, float color_ambient_r, float color_ambient_g, float color_ambient_b, float color_specular_r, float color_specular_g, float color_specular_b, float color_emissive_r, float color_emissive_g, float color_emissive_b, float color_shininess) {

    this->modelo = modelo;
    this->textura = textura;

    this->hasColor = hasColor;

    this->color_diffuse[0] = color_diffuse_r / 255.0f;
    this->color_diffuse[1] = color_diffuse_g / 255.0f;
    this->color_diffuse[2] = color_diffuse_b / 255.0f;
    this->color_diffuse[3] = 1.0f;

    this->color_ambient[0] = color_ambient_r / 255.0f;
    this->color_ambient[1] = color_ambient_g / 255.0f;
    this->color_ambient[2] = color_ambient_b / 255.0f;
    this->color_ambient[3] = 1.0f;

    this->color_specular[0] = color_specular_r / 255.0f;
    this->color_specular[1] = color_specular_g / 255.0f;
    this->color_specular[2] = color_specular_b / 255.0f;
    this->color_specular[3] = 1.0f;

    this->color_emissive[0] = color_emissive_r / 255.0f;
    this->color_emissive[1] = color_emissive_g / 255.0f;
    this->color_emissive[2] = color_emissive_b / 255.0f;
    this->color_emissive[3] = 1.0f;

    this->color_shininess = color_shininess;

}

// Classe para Models
Models::Models() {

    this->modelos = vector<ModelElement*>();

}

void Models::addModel(ModelElement* modelo) {

    this->modelos.push_back(modelo);

}

// Classe para TransformElement
TransformElement::TransformElement(TransformacoesENUM tipo, double tempo,double angulo, double x, double y, double z, bool align, bool drawCurve, vector<Ponto>* pontos) {

    this->tipo = tipo;
    this->angulo = angulo;
    this->tempo = tempo;
    this->x = x;
    this->y = y;
    this->z = z;
    this->align = align;
    this->pontos = pontos;
    this->drawCurve = drawCurve;

}

// Classe para Transform
Transform::Transform() {
    this->transformacoes = vector<TransformElement>();
}

void Transform::addTransform(TransformElement transformacao) {

    this->transformacoes.push_back(transformacao);

}