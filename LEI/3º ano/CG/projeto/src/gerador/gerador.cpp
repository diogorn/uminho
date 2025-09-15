#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "figuras/Triangles.h"
#include "ficheiro3d/Ficheiro.h"
#include <math.h>
#include <sstream>
#include <string> 

using namespace std;

VetorNormal vetorEntreDoisPontos(Ponto p1, Ponto p2) {

    VetorNormal n = VetorNormal(p2.x - p1.x , p2.y - p1.y , p2.z - p1.z);
    n.normalize();
    return n;

}

ModelSkeletonGenerator geraEsfera(double radius, double slices, double stacks) {

    vector<Ponto> vertices;
    vector<VetorNormal> normais;
    vector<Textura> texturas;

    Ponto centro = Ponto(0,0,0);

    for (int i = 0; i < stacks; ++i) {

        float alpha1 = M_PI * i / stacks;
        float alpha2 = M_PI * (i + 1) / stacks;

        for (int j = 0; j < slices; ++j) {
            float beta1 = -2.0f * M_PI * j / slices;
            float beta2 = -2.0f * M_PI * (j + 1) / slices;

            float x1 = radius * sin(alpha1) * sin(beta1);
            float y1 = radius * cos(alpha1);
            float z1 = radius * sin(alpha1) * cos(beta1);

            float x2 = radius * sin(alpha2) * sin(beta1);
            float y2 = radius * cos(alpha2);
            float z2 = radius * sin(alpha2) * cos(beta1);

            float x3 = radius * sin(alpha1) * sin(beta2);
            float y3 = radius * cos(alpha1);
            float z3 = radius * sin(alpha1) * cos(beta2);

            float x4 = radius * sin(alpha2) * sin(beta2);
            float y4 = radius * cos(alpha2);
            float z4 = radius * sin(alpha2) * cos(beta2);

            Ponto p1 = Ponto(x1,y1,z1);
            Ponto p2 = Ponto(x2,y2,z2);
            Ponto p3 = Ponto(x3,y3,z3);
            Ponto p4 = Ponto(x4,y4,z4);

            vertices.push_back(p2); normais.push_back(vetorEntreDoisPontos(centro,p2));
            vertices.push_back(p1); normais.push_back(vetorEntreDoisPontos(centro,p1));
            vertices.push_back(p3); normais.push_back(vetorEntreDoisPontos(centro,p3));

            vertices.push_back(p2); normais.push_back(vetorEntreDoisPontos(centro,p2));
            vertices.push_back(p3); normais.push_back(vetorEntreDoisPontos(centro,p3));
            vertices.push_back(p4); normais.push_back(vetorEntreDoisPontos(centro,p4));

        }
    }

    return ModelSkeletonGenerator(vertices,normais,texturas);

}

ModelSkeletonGenerator geraCaixa(double length, double divisions) {
    if (divisions <= 0) {
        throw invalid_argument("divisions must be greater than zero");
    }

    vector<Ponto> vertices;
    vector<VetorNormal> normais;
    vector<Textura> texturas;

    double step = length / divisions;
    double half = length / 2.0;

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            double x1 = -half + i * step;
            double x2 = x1 + step;
            double y1 = -half + j * step;
            double y2 = y1 + step;

            // Para as texturas
            double ti = (double)i / divisions;
            double tip = (double)(i + 1) / divisions;
            double tj = (double)j / divisions;
            double tjp = (double)(j + 1) / divisions;

            // Face inferior (y = -half)
            VetorNormal nBottom(0, -1, 0);
            vertices.push_back(Ponto(x1, -half, y1)); normais.push_back(nBottom); texturas.push_back(Textura(ti, tj));
            vertices.push_back(Ponto(x2, -half, y1)); normais.push_back(nBottom); texturas.push_back(Textura(tip, tj));
            vertices.push_back(Ponto(x1, -half, y2)); normais.push_back(nBottom); texturas.push_back(Textura(ti, tjp));
            vertices.push_back(Ponto(x2, -half, y1)); normais.push_back(nBottom); texturas.push_back(Textura(tip, tj));
            vertices.push_back(Ponto(x2, -half, y2)); normais.push_back(nBottom); texturas.push_back(Textura(tip, tjp));
            vertices.push_back(Ponto(x1, -half, y2)); normais.push_back(nBottom); texturas.push_back(Textura(ti, tjp));

            // Face superior (y = +half)
            VetorNormal nTop(0, 1, 0);
            vertices.push_back(Ponto(x1, half, y1)); normais.push_back(nTop); texturas.push_back(Textura(ti, tj));
            vertices.push_back(Ponto(x1, half, y2)); normais.push_back(nTop); texturas.push_back(Textura(ti, tjp));
            vertices.push_back(Ponto(x2, half, y1)); normais.push_back(nTop); texturas.push_back(Textura(tip, tj));
            vertices.push_back(Ponto(x2, half, y1)); normais.push_back(nTop); texturas.push_back(Textura(tip, tj));
            vertices.push_back(Ponto(x1, half, y2)); normais.push_back(nTop); texturas.push_back(Textura(ti, tjp));
            vertices.push_back(Ponto(x2, half, y2)); normais.push_back(nTop); texturas.push_back(Textura(tip, tjp));

            // Face frontal (z = +half)
            VetorNormal nFront(0, 0, 1);
            vertices.push_back(Ponto(x1, y1, half)); normais.push_back(nFront); texturas.push_back(Textura(ti, tj));
            vertices.push_back(Ponto(x2, y1, half)); normais.push_back(nFront); texturas.push_back(Textura(tip, tj));
            vertices.push_back(Ponto(x1, y2, half)); normais.push_back(nFront); texturas.push_back(Textura(ti, tjp));
            vertices.push_back(Ponto(x2, y1, half)); normais.push_back(nFront); texturas.push_back(Textura(tip, tj));
            vertices.push_back(Ponto(x2, y2, half)); normais.push_back(nFront); texturas.push_back(Textura(tip, tjp));
            vertices.push_back(Ponto(x1, y2, half)); normais.push_back(nFront); texturas.push_back(Textura(ti, tjp));

            // Face traseira (z = -half)
            VetorNormal nBack(0, 0, -1);
            vertices.push_back(Ponto(x1, y1, -half)); normais.push_back(nBack); texturas.push_back(Textura(ti, tj));
            vertices.push_back(Ponto(x1, y2, -half)); normais.push_back(nBack); texturas.push_back(Textura(ti, tjp));
            vertices.push_back(Ponto(x2, y1, -half)); normais.push_back(nBack); texturas.push_back(Textura(tip, tj));
            vertices.push_back(Ponto(x2, y1, -half)); normais.push_back(nBack); texturas.push_back(Textura(tip, tj));
            vertices.push_back(Ponto(x1, y2, -half)); normais.push_back(nBack); texturas.push_back(Textura(ti, tjp));
            vertices.push_back(Ponto(x2, y2, -half)); normais.push_back(nBack); texturas.push_back(Textura(tip, tjp));

            // Face esquerda (x = -half)
            VetorNormal nLeft(-1, 0, 0);
            vertices.push_back(Ponto(-half, y1, x1)); normais.push_back(nLeft); texturas.push_back(Textura(ti, tj));
            vertices.push_back(Ponto(-half, y1, x2)); normais.push_back(nLeft); texturas.push_back(Textura(tip, tj));
            vertices.push_back(Ponto(-half, y2, x1)); normais.push_back(nLeft); texturas.push_back(Textura(ti, tjp));
            vertices.push_back(Ponto(-half, y2, x1)); normais.push_back(nLeft); texturas.push_back(Textura(ti, tjp));
            vertices.push_back(Ponto(-half, y1, x2)); normais.push_back(nLeft); texturas.push_back(Textura(tip, tj));
            vertices.push_back(Ponto(-half, y2, x2)); normais.push_back(nLeft); texturas.push_back(Textura(tip, tjp));

            // Face direita (x = +half)
            VetorNormal nRight(1, 0, 0);
            vertices.push_back(Ponto(half, y1, x1)); normais.push_back(nRight); texturas.push_back(Textura(ti, tj));
            vertices.push_back(Ponto(half, y2, x1)); normais.push_back(nRight); texturas.push_back(Textura(ti, tjp));
            vertices.push_back(Ponto(half, y1, x2)); normais.push_back(nRight); texturas.push_back(Textura(tip, tj));
            vertices.push_back(Ponto(half, y2, x1)); normais.push_back(nRight); texturas.push_back(Textura(ti, tjp));
            vertices.push_back(Ponto(half, y2, x2)); normais.push_back(nRight); texturas.push_back(Textura(tip, tjp));
            vertices.push_back(Ponto(half, y1, x2)); normais.push_back(nRight); texturas.push_back(Textura(tip, tj));
        }
    }

    return ModelSkeletonGenerator(vertices,normais,texturas);
}

ModelSkeletonGenerator geraCone(double radius, double height, int slices, int stacks) {
    
    vector<Ponto> vertices;
    vector<VetorNormal> normais;
    vector<Textura> texturas;

    //Base do cone
    for (int i = 0; i < slices; i++) {

        double alfa1 = ((2.0f * M_PI)/slices) * i;
        double alfa2 = ((2.0f * M_PI)/slices) * (i+1);

        Ponto origem = Ponto(0,0,0);
        Ponto p1 = Ponto(radius*sin(alfa1),0,radius*cos(alfa1));
        Ponto p2 = Ponto(radius*sin(alfa2),0,radius*cos(alfa2));

        vertices.push_back(origem);
        vertices.push_back(p2);
        vertices.push_back(p1);
    }

    //Corpo do cone
    double delta_h = height/stacks;
    double h = 0;
    for (int i = 0; i < stacks; i++) {

        double h2 = h + delta_h; //Altura da circunferência de cima
        double raio1 = radius * ((height - h) / height); //Raio da circunferencia de baixo
        double raio2 = radius * ((height - h2) / height); //Raio da circunferencia de cima

        for (int j = 0; j < slices; j++) {

            double alfa1 = (2.0f * M_PI)/slices * j;
            double alfa2 = (2.0f * M_PI)/slices * (j+1);

            Ponto p1 = Ponto(raio2*sin(alfa1),h2,raio2*cos(alfa1));
            Ponto p2 = Ponto(raio2*sin(alfa2),h2,raio2*cos(alfa2));
            Ponto p3 = Ponto(raio1*sin(alfa1),h,raio1*cos(alfa1));
            Ponto p4 = Ponto(raio1*sin(alfa2),h,raio1*cos(alfa2));

            vertices.push_back(p3);
            vertices.push_back(p4);
            vertices.push_back(p1);
            vertices.push_back(p1);
            vertices.push_back(p4);
            vertices.push_back(p2);

        }

        h += delta_h;
    }

    return ModelSkeletonGenerator(vertices,normais,texturas);

}

ModelSkeletonGenerator geraPlano(double length, double divisions) {

    vector<Ponto> vertices;
    vector<VetorNormal> normais;
    vector<Textura> texturas;

    double inicio = length/2;
    double salto = length / divisions;

    VetorNormal normal = VetorNormal(0,1,0);

    for (int i = 0; i < divisions; i++) {

        for (int j = 0; j < divisions ; j++) {

            double ponto_inicial_x = -inicio;
            ponto_inicial_x += (i*salto);

            double ponto_inicial_z = -inicio;
            ponto_inicial_z += (j*salto);

            Ponto p1 = Ponto(ponto_inicial_x + salto,0,ponto_inicial_z + salto);
            Ponto p2 = Ponto(ponto_inicial_x + salto,0,ponto_inicial_z);
            Ponto p3 = Ponto(ponto_inicial_x,0,ponto_inicial_z);
            Ponto p4 = Ponto(ponto_inicial_x,0,ponto_inicial_z + salto);

            Textura t1 = Textura((i+1)* salto / length,(j+1)* salto / length);
            Textura t2 = Textura((i+1)* salto / length,(j)* salto / length);
            Textura t3 = Textura((i)* salto / length,(j)* salto / length);
            Textura t4 = Textura((i)* salto / length,(j+1)* salto / length);


            vertices.push_back(p1); normais.push_back(normal); texturas.push_back(t1);
            vertices.push_back(p2); normais.push_back(normal); texturas.push_back(t2);
            vertices.push_back(p3); normais.push_back(normal); texturas.push_back(t3);

            vertices.push_back(p1); normais.push_back(normal); texturas.push_back(t1);
            vertices.push_back(p3); normais.push_back(normal); texturas.push_back(t3);
            vertices.push_back(p4); normais.push_back(normal); texturas.push_back(t4);

        }

    }

    return ModelSkeletonGenerator(vertices,normais,texturas);

}

ModelSkeletonGenerator geraTorus(double R, double r, int slices, int stacks) {
    
    vector<Ponto> vertices;
    vector<VetorNormal> normais;
    vector<Textura> texturas;

    for (int i = 0; i < stacks; i++) { // r
        double v1 = (2.0 * M_PI * i) / stacks;
        double v2 = (2.0 * M_PI * (i + 1)) / stacks;

        for (int j = 0; j < slices; j++) { // R
            double u1 = (2.0 * M_PI * j) / slices;
            double u2 = (2.0 * M_PI * (j + 1)) / slices;

           
            Ponto p1((R + r * cos(v1)) * cos(u1),
                     r * sin(v1),
                     (R + r * cos(v1)) * sin(u1));

            Ponto p2((R + r * cos(v2)) * cos(u1),
                     r * sin(v2),
                     (R + r * cos(v2)) * sin(u1));

            Ponto p3((R + r * cos(v2)) * cos(u2),
                     r * sin(v2),
                     (R + r * cos(v2)) * sin(u2));

            Ponto p4((R + r * cos(v1)) * cos(u2),
                     r * sin(v1),
                     (R + r * cos(v1)) * sin(u2));

            
            vertices.push_back(p1);
            vertices.push_back(p2);
            vertices.push_back(p3);
            vertices.push_back(p3);
            vertices.push_back(p4);
            vertices.push_back(p1);

        }
    }

    return ModelSkeletonGenerator(vertices,normais,texturas);

}

ModelSkeletonGenerator geraPatch(const char* filename, int tessLevel) {
    std::ifstream patchfile(filename);
    if (!patchfile.is_open()) {
        throw std::runtime_error("Não consegui abrir o ficheiro .patch");
    }

    // numero de patches -> linha 1
    int numPatches;
    patchfile >> numPatches;
    std::string line;
    std::getline(patchfile, line); // descartar resto da linha

    //  indice de cada patch
    const char* delim = ", ";
    std::vector<std::array<int,16>> patchesIdx;
    for(int p = 0; p < numPatches; ++p) {
        std::getline(patchfile, line);
        std::array<int,16> idx;
        int count = 0;
        char* tok = std::strtok(const_cast<char*>(line.data()), delim);
        while(tok && count < 16) {
            idx[count++] = std::atoi(tok);
            tok = std::strtok(nullptr, delim);
        }
        patchesIdx.push_back(idx);
    }

    // nº de pontos de controlo
    int numPoints;
    patchfile >> numPoints;
    std::getline(patchfile, line);

    // control points
    struct P3 { float x,y,z; };
    std::vector<P3> ctrlPts(numPoints);
    for(int i = 0; i < numPoints; ++i) {
        std::getline(patchfile, line);
        for(char& c : line) if(c==',') c=' ';
        std::stringstream ss(line);
        ss >> ctrlPts[i].x >> ctrlPts[i].y >> ctrlPts[i].z;
    }

    // matriz base de bezier
    float M[4][4] = {
        {-1,  3, -3, 1},
        { 3, -6,  3, 0},
        {-3,  3,  0, 0},
        { 1,  0,  0, 0}
    };

    // auxs
    auto multMat = [&](float A[4][4], float B[4][4], float R[4][4]){
        for(int i=0;i<4;i++) for(int j=0;j<4;j++){
            R[i][j]=0;
            for(int k=0;k<4;k++) R[i][j] += A[i][k]*B[k][j];
        }
    };
    auto multMatVec = [&](float M[4][4], float V[4], float R[4]){
        for(int i=0;i<4;i++){
            R[i]=0;
            for(int k=0;k<4;k++) R[i] += M[i][k]*V[k];
        }
    };
    auto calcB = [&](float u, float v, float C[4][4]){
        float U[4] = {u*u*u, u*u, u, 1};
        float V[4] = {v*v*v, v*v, v, 1};
        float tmp[4];
        multMatVec(C, U, tmp);
        float r=0;
        for(int i=0;i<4;i++) r += tmp[i]*V[i];
        return r;
    };

    vector<Ponto> vertices;
    vector<VetorNormal> normais;
    vector<Textura> texturas;

    // Função auxiliar para derivadas de Bézier
    auto derivB = [&](float u, float v, float C[4][4], bool du) {
        float baseU[4], baseV[4], derivadaBaseU[4], derivadaBaseV[4];

        if (du) {
            derivadaBaseU[0] = 3 * u * u; derivadaBaseU[1] = 2 * u; derivadaBaseU[2] = 1; derivadaBaseU[3] = 0;
            baseV[0] = v * v * v; baseV[1] = v * v; baseV[2] = v; baseV[3] = 1;
            float tmp[4];
            multMatVec(C, derivadaBaseU, tmp);
            float r = 0;
            for (int i = 0; i < 4; i++) r += tmp[i] * baseV[i];
            return r;
        } else {
            baseU[0] = u * u * u; baseU[1] = u * u; baseU[2] = u; baseU[3] = 1;
            derivadaBaseV[0] = 3 * v * v; derivadaBaseV[1] = 2 * v; derivadaBaseV[2] = 1; derivadaBaseV[3] = 0;
            float tmp[4];
            multMatVec(C, baseU, tmp);
            float r = 0;
            for (int i = 0; i < 4; i++) r += tmp[i] * derivadaBaseV[i];
            return r;
        }
    };

    float du = 1.0f/tessLevel;
    // para cada patch
    for(auto& idxArr : patchesIdx) {
        // montar 3 matrizes X, Y, Z a partir dos control points
        float MX[4][4], MY[4][4], MZ[4][4], tmp[4][4];
        for(int i=0;i<4;i++) for(int j=0;j<4;j++){
            auto& P = ctrlPts[ idxArr[i*4 + j] ];
            MX[i][j] = P.x;
            MY[i][j] = P.y;
            MZ[i][j] = P.z;
        }
        // C = M * G * M^T  para X, Y, Z
        multMat(M,MX,tmp);multMat(tmp,M,MX);
        multMat(M,MY,tmp);multMat(tmp,M,MY);
        multMat(M,MZ,tmp);multMat(tmp,M,MZ);

        for(int iu=0; iu < tessLevel; ++iu) {
            for(int iv=0; iv < tessLevel; ++iv) {
                float u = iu * du, v = iv * du;
                Ponto p1(calcB(u,v,MX),
                         calcB(u,v,MY),
                         calcB(u,v,MZ));
                Ponto p2(calcB(u+du,v,MX),
                         calcB(u+du,v,MY),
                         calcB(u+du,v,MZ));
                Ponto p3(calcB(u,v+du,MX),
                         calcB(u,v+du,MY),
                         calcB(u,v+du,MZ));
                Ponto p4(calcB(u+du,v+du,MX),
                         calcB(u+du,v+du,MY),
                         calcB(u+du,v+du,MZ));

                // Calcular normais e texturas
                float xu = derivB(u, v, MX, true);
                float xv = derivB(u, v, MX, false);
                float yu = derivB(u, v, MY, true);
                float yv = derivB(u, v, MY, false);
                float zu = derivB(u, v, MZ, true);
                float zv = derivB(u, v, MZ, false);

                float nx = yu * zv - zu * yv;
                float ny = zu * xv - xu * zv;
                float nz = xu * yv - yu * xv;

                VetorNormal normal(nx, ny, nz);
                normal.normalize();

                // Triângulos com normais e texturas
                vertices.push_back(p1); normais.push_back(normal); texturas.push_back(Textura(u, v));
                vertices.push_back(p2); normais.push_back(normal); texturas.push_back(Textura(u + du, v));
                vertices.push_back(p3); normais.push_back(normal); texturas.push_back(Textura(u, v + du));

                vertices.push_back(p2); normais.push_back(normal); texturas.push_back(Textura(u + du, v));
                vertices.push_back(p4); normais.push_back(normal); texturas.push_back(Textura(u + du, v + du));
                vertices.push_back(p3); normais.push_back(normal); texturas.push_back(Textura(u, v + du));
            }
        }
    }

    return ModelSkeletonGenerator(vertices,normais,texturas);

}


//Main do Gerador
int main(int argn, char** argv) {

    const char* uso_torus = "./generator torus [RAIO MAIOR] [RAIO MENOR] [SLICES] [STACKS] [NOME DO FICHEIRO]\n";
    const char* uso_sphere = "./generator sphere [RAIO] [SLICES] [STACKS] [NOME DO FICHEIRO]\n";
    const char* uso_box = "./generator box [TAMANHO] [DIVISÃO] [NOME DO FICHEIRO]\n";
    const char* uso_cone = "./generator cone [RAIO] [ALTURA] [SLICES] [STACKS] [NOME DO FICHEIRO]\n";
    const char* uso_plane = "./generator plane [TAMANHO] [DIVISÕES] [NOME DO FICHEIRO]\n";
    const char* uso_txt = "./generator text [NOME DO FICHEIRO .3D] [NOME DO FICHEIRO TEXTO]\n";

    if (argn < 2) {
        cerr << "Argumentos inválidos!\n";
        cerr << "USO:\n";
        cerr << uso_sphere;
        cerr << uso_box;
        cerr << uso_cone;
        cerr << uso_plane;
        cerr << uso_txt;

        return 1;
    }

        // Torus
    if (strcmp(argv[1],"torus") == 0) {

        if (argn >= 6) {

            double R = strtod(argv[2],nullptr);
            double r = strtod(argv[3],nullptr);
            int slices = strtol(argv[4],nullptr, 10);
            int stacks = strtol(argv[5],nullptr, 10);

          
            ModelSkeletonGenerator torus = geraTorus(R, r, slices, stacks);
           
            if (escreverBinario(argv[6], torus)) {
                cout << "Ficheiro " << argv[6] << " foi criado!\n";
                return 0;
            } else {
                cerr << "Não foi possível criar o " << argv[6] << "!\n";
                return 1;
            }

        } else {
            cerr << "Argumentos em falta\n";
            cerr << uso_torus;
            return 2;
        }
    }

    //Esfera
    if (strcmp(argv[1],"sphere") == 0) {

        if (argn >= 6) {

            double radius = strtod(argv[2],nullptr);
            double slides = strtod(argv[3],nullptr);
            double stacks = strtod(argv[4],nullptr);
            
            //Gerar esfera - sucesso
            if (escreverBinario(argv[5],geraEsfera(radius,slides,stacks))) {

                cout << "Ficheiro " << argv[5] << " foi criado!\n";
                return 0;

            }
            else {

                cerr << "Não foi possivel criar o " << argv[5] << "!\n";
                return 1;

            }

        }
        else {
            cerr << "Argumentos em falta";
            cerr << uso_sphere;
            return 2;
        }

    }

    //Caixa
    if (strcmp(argv[1],"box") == 0) {

        if (argn >= 5) {

            double length = strtod(argv[2],nullptr);
            double divisions = strtod(argv[3],nullptr);

            //Gerar Caixa - sucesso
            if (escreverBinario(argv[4],geraCaixa(length,divisions))) {

                cout << "Ficheiro " << argv[4] << " foi criado!\n";
                return 0;

            }
            else {

                cerr << "Não foi possivel criar o " << argv[4] << "!\n";
                return 1;

            }

        }
        else {
            cerr << "Argumentos em falta";
            cerr << uso_box;
            return 2;
        }

    }

    //Cone
    if (strcmp(argv[1],"cone") == 0) {

        if (argn >= 7) {

            double radius = strtod(argv[2],nullptr);
            double height = strtod(argv[3],nullptr);
            double slides = strtod(argv[4],nullptr);
            double stacks = strtod(argv[5],nullptr);

            //Gerar Cone - sucesso
            if (escreverBinario(argv[6],geraCone(radius,height,slides,stacks))) {

                cout << "Ficheiro " << argv[6] << " foi criado!\n";
                return 0;

            }
            else {

                cerr << "Não foi possivel criar o " << argv[6] << "!\n";
                return 1;

            }

        }
        else {
            cerr << "Argumentos em falta";
            cerr << uso_cone;
            return 2;
        }

    }

    //Plano
    if (strcmp(argv[1],"plane") == 0) {

        if (argn >= 5) {

            int length = strtod(argv[2],nullptr);
            int divisions = strtod(argv[3],nullptr);

            //Gerar plano - sucesso
            if (escreverBinario(argv[4],geraPlano(length,divisions))) {

                cout << "Ficheiro " << argv[4] << " foi criado!\n";
                return 0;

            }
            else {

                cerr << "Não foi possivel criar o " << argv[4] << "!\n";
                return 1;

            }

        }
        else {
            cerr << "Argumentos em falta";
            cerr << uso_plane;
            return 2;
        }

    }

    //.3D para Texto
    if (strcmp(argv[1],"text") == 0) {

        if (argn >= 4) {

            //Criar ficheiro texto
            if (ficheiroParaTexto(argv[2],argv[3])) {

                cout << "Ficheiro " << argv[3] << " foi criado!\n";
                return 0;

            }
            else {

                cerr << "Não foi possivel criar o " << argv[3] << "!\n";
                return 1;

            }

        }
        else {
            cerr << "Argumentos em falta";
            cerr << uso_txt;
            return 2;
        }

    }
    const char* uso_patch = "./generator patch [FICHEIRO.patch] [TESSELATION] [OUT_FILE]\n";
    // ...
    if (strcmp(argv[1],"patch") == 0) {
        if (argn >= 5) {
            try {
                int tess = std::atoi(argv[3]);
                auto tris = geraPatch(argv[2], tess);
                if (escreverBinario(argv[4], tris)) {
                    std::cout << "Ficheiro " << argv[4] << " foi criado!\n";
                    return 0;
                } else {
                    std::cerr << "Não foi possivel criar o " << argv[4] << "!\n";
                    return 1;
                }
            }
            catch(const std::exception& e) {
                std::cerr << "Erro ao processar patch: " << e.what() << "\n";
                return 2;
            }
        } else {
            std::cerr << "Argumentos em falta\n";
            std::cerr << uso_patch;
            return 2;
        }
    }

    //Erro
    cerr << "Opção " << argv[1] <<" não disponível\n";
    cerr << "USO:\n";
    cerr << uso_torus;
    cerr << uso_sphere;
    cerr << uso_box;
    cerr << uso_cone;
    cerr << uso_plane;
    cerr << uso_txt;

    return 1;

}