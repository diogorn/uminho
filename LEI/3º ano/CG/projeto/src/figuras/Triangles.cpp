#include "figuras/Triangles.h"
#include "iostream"
#include <vector>
#include <cstring>
#include <cmath>

//Classe para Ponto
Ponto::Ponto() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Ponto::Ponto(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

bool Ponto::operator<(const Ponto& other) const {

    if (x != other.x) 
        return x < other.x;
    
    if (y != other.y)
        return y < other.y;
    
    return z < other.z;

}

// Classe para VetorNormal
VetorNormal::VetorNormal() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

VetorNormal::VetorNormal(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

bool VetorNormal::operator<(const VetorNormal& other) const {

    if (x != other.x) 
        return x < other.x;
    
    if (y != other.y)
        return y < other.y;
    
    return z < other.z;

}

void VetorNormal::normalize() {
    double len = sqrt(x*x + y*y + z*z);
    if (len > 0) {
        x /= len;
        y /= len;
        z /= len;
    }
}

// Classe para Textura
Textura::Textura() {
    this->x = 0;
    this->y = 0;
}

Textura::Textura(double x, double y) {
    this->x = x;
    this->y = y;
}

bool Textura::operator<(const Textura& other) const {

    if (x != other.x) 
        return x < other.x;
    
    return y < other.y;

}

//Classe do Modelo - Generator
ModelSkeletonGenerator::ModelSkeletonGenerator(std::vector<Ponto> vertices, std::vector<VetorNormal> normais, std::vector<Textura> texturas) {

    this->vertices = vertices;
    this->normais = normais;
    this->texturas = texturas;

}

//Classe do Modelo - Engine
ModelSkeletonEngine::ModelSkeletonEngine(std::vector<double> vertices,std::vector<double> normais,std::vector<double> texturas) {

    // Guardar os tamanhos
    this->vertices_N = vertices.size();
    this->normais_N = normais.size();
    this->texturas_N = texturas.size();

    this->vertices = new double[vertices_N];
    for (int i = 0 ; i < this->vertices_N ; i++)
        this->vertices[i] = vertices.at(i);

    this->normais = new double[normais_N];
    for (int i = 0 ; i < this->normais_N ; i++)
        this->normais[i] = normais.at(i);

    this->texturas = new double[texturas_N];
    for (int i = 0 ; i < this->texturas_N ; i++)
        this->texturas[i] = texturas.at(i);

}

    

