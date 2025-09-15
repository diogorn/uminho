#include <iostream>
#include <fstream>
#include <vector>
#include "figuras/Triangles.h"
#include "ficheiro3d/Ficheiro.h"
#include <map>
#include <utility>
#include "engine/groups.h"

using namespace std;

//Escrever uma figura em ficheiro texto
bool escreverBinario(const string nome_ficheiro, const ModelSkeletonGenerator& lista) {

    ofstream f (nome_ficheiro, ios::binary);

    //Verifica se correu tudo bem
    if (!f) {
        cerr << "Erro ao criar o ficheiro " << nome_ficheiro << endl;
        return false;
    }

    /* ##############################
                    VERTICES
       ##############################*/

    //Escreve a quantidade de vertices
    int vertices_quant = lista.vertices.size();
    f.write(reinterpret_cast<const char*>(&vertices_quant), sizeof(int));

    //Escreve as coordenadas dos vertices
    for (Ponto p : lista.vertices) {
        //std::cout << "Ponto: (" << p.x << ", " << p.y << ", " << p.z << ")\n";
        f.write(reinterpret_cast<const char*>(&p.x), sizeof(double));
        f.write(reinterpret_cast<const char*>(&p.y), sizeof(double));
        f.write(reinterpret_cast<const char*>(&p.z), sizeof(double));
    }

    /* ##############################
                    NORMAIS
       ##############################*/

    //Escreve a quantidade de normais
    int normais_quant = lista.normais.size();
    f.write(reinterpret_cast<const char*>(&normais_quant), sizeof(int));

    //Escreve as coordenadas das normais
    for (VetorNormal n : lista.normais) {
        //std::cout << "Ponto: (" << p.x << ", " << p.y << ", " << p.z << ")\n";
        f.write(reinterpret_cast<const char*>(&n.x), sizeof(double));
        f.write(reinterpret_cast<const char*>(&n.y), sizeof(double));
        f.write(reinterpret_cast<const char*>(&n.z), sizeof(double));
    }

    /* ##############################
                    TEXTURAS
       ##############################*/

    //Escreve a quantidade de coordenadas de textura
    int texturas_quant = lista.texturas.size();
    f.write(reinterpret_cast<const char*>(&texturas_quant), sizeof(int));

    //Escreve as coordenadas de textura
    for (Textura t : lista.texturas) {
        //std::cout << "Ponto: (" << p.x << ", " << p.y << ", " << p.z << ")\n";
        f.write(reinterpret_cast<const char*>(&t.x), sizeof(double));
        f.write(reinterpret_cast<const char*>(&t.y), sizeof(double));
    }

    f.close();
    return true;

}

//Ler Ficheiros .3d
ModelSkeletonEngine* lerBinario(const string nome_ficheiro) {

    ifstream f(nome_ficheiro, ios::binary);

    //Verifica se correu tudo bem
    if (!f) {
        cerr << "Erro ao abrir o arquivo " << nome_ficheiro << endl;
        return nullptr;
    }

    /* #######################
                VERTICES
       #######################*/

    vector<double> vertices = vector<double>();

    //Ler quantidade de vertices a ler
    int vertices_quant;
    f.read(reinterpret_cast<char*>(&vertices_quant), sizeof(int));

    //Ler as vertices
    for (int i = 0; i < vertices_quant; i++) {

        double x, y, z;
        f.read(reinterpret_cast<char*>(&x), sizeof(double));
        f.read(reinterpret_cast<char*>(&y), sizeof(double));
        f.read(reinterpret_cast<char*>(&z), sizeof(double));

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
    }

    /* #######################
                NORMAIS
       #######################*/

    vector<double> normais = vector<double>();

    //Ler quantidade de normais a ler
    int normais_quant;
    f.read(reinterpret_cast<char*>(&normais_quant), sizeof(int));
   
    //Ler as normais
    for (int i = 0; i < normais_quant; i++) {
   
        double x, y, z;
        f.read(reinterpret_cast<char*>(&x), sizeof(double));
        f.read(reinterpret_cast<char*>(&y), sizeof(double));
        f.read(reinterpret_cast<char*>(&z), sizeof(double));

        normais.push_back(x);
        normais.push_back(y);
        normais.push_back(z);
    }

    /* #######################
                TEXTURAS
       #######################*/

    vector<double> texturas = vector<double>();

    //Ler quantidade de texturas a ler
    int texturas_quant;
    f.read(reinterpret_cast<char*>(&texturas_quant), sizeof(int));

    //Ler as texturas
    for (int i = 0; i < texturas_quant; i++) {

        double x, y;
        f.read(reinterpret_cast<char*>(&x), sizeof(double));
        f.read(reinterpret_cast<char*>(&y), sizeof(double));

        texturas.push_back(x);
        texturas.push_back(y);
    }

    f.close();

    ModelSkeletonEngine* res = new ModelSkeletonEngine(vertices,normais,texturas);

    return res;
}

//Ficheiro .3d para texto
int ficheiroParaTexto(const string nome_ficheiro, const string output) {

    ifstream f(nome_ficheiro, ios::binary);
    ofstream out(output, ios::binary);

    //Verifica se correu tudo bem
    if (!f || !out) {
        return 0;
    }

    /* #######################
                VERTICES
       #######################*/

    //Ler quantidade de vertices a ler
    int vertices_quant;
    f.read(reinterpret_cast<char*>(&vertices_quant), sizeof(int));
    out << "#############\n";
    out << "VERTICES\n";
    out << "#############\n\n";

    out << "Vertices (Pontos - " << vertices_quant << "):\n\n";
    //Ler as vertices
    for (int i = 0; i < vertices_quant; i++) {

        double x, y, z;
        f.read(reinterpret_cast<char*>(&x), sizeof(double));
        f.read(reinterpret_cast<char*>(&y), sizeof(double));
        f.read(reinterpret_cast<char*>(&z), sizeof(double));

        out << x << " " << y << " " << z << "\n";
    }

    /* #######################
                NORMAIS
       #######################*/

    //Ler quantidade de normais a ler
    int normais_quant;
    f.read(reinterpret_cast<char*>(&normais_quant), sizeof(int));
    out << "\n\n#############\n";
    out << "NORMAIS\n";
    out << "#############\n\n";

    out << "Normais (Vetores - " << normais_quant << "):\n\n";

    //Ler as normais
    for (int i = 0; i < normais_quant; i++) {
   
        double x, y, z;
        f.read(reinterpret_cast<char*>(&x), sizeof(double));
        f.read(reinterpret_cast<char*>(&y), sizeof(double));
        f.read(reinterpret_cast<char*>(&z), sizeof(double));

        out << x << " " << y << " " << z << "\n";
    }
   
    /* #######################
                TEXTURAS
       #######################*/

    //Ler quantidade de texturas a ler
    int texturas_quant;
    f.read(reinterpret_cast<char*>(&texturas_quant), sizeof(int));
    out << "\n\n#############\n";
    out << "TEXTURAS\n";
    out << "#############\n\n";

    out << "Texturas (Coordenadas - " << texturas_quant << "):\n\n";

    //Ler as texturas
    for (int i = 0; i < texturas_quant; i++) {

        double x, y;
        f.read(reinterpret_cast<char*>(&x), sizeof(double));
        f.read(reinterpret_cast<char*>(&y), sizeof(double));

        out << x << " " << y << "\n";

    }

    f.close();
    out.close();

    return 1;
}