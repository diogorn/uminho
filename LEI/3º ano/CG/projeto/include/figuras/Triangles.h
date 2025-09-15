#ifndef TRIANGLES_HEADER
#define TRIANGLES_HEADER

#include <vector>

    // Classe para Ponto
    class Ponto {
        public:
            double x, y, z;

            Ponto();
            Ponto(double x, double y, double z);
            bool operator<(const Ponto& other) const;
    };

    // Classe para VetorNormal
    class VetorNormal {
        public:
            double x, y, z;

            VetorNormal();
            VetorNormal(double x, double y, double z);
            bool operator<(const VetorNormal& other) const;
            void normalize();
    };

    // Classe para Textura
    class Textura {
        public:
            double x, y;

            Textura();
            Textura(double x, double y);
            bool operator<(const Textura& other) const;
    };

    //Classe do Modelo - Generator
    class ModelSkeletonGenerator {
        public:

            std::vector<Ponto> vertices;
            std::vector<VetorNormal> normais;
            std::vector<Textura> texturas;

            ModelSkeletonGenerator(std::vector<Ponto> vertices, std::vector<VetorNormal> normais, std::vector<Textura> texturas);


    };

    //Classe do Modelo - Engine
    class ModelSkeletonEngine {
        public:

            double* vertices;
            double* normais;
            double* texturas;

            int vertices_N;
            int normais_N;
            int texturas_N;

            ModelSkeletonEngine(std::vector<double> vertices,std::vector<double> normais,std::vector<double> texturas);

    };


#endif
