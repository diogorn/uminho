
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <IL/il.h>

//#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "figuras/Triangles.h"
#include "ficheiro3d/Ficheiro.h"
#include "tinyxml/tinyxml.h"
#include "engine/World.h"
#include <utility>

#include "engine/processaXML.h"

using namespace std;

World world;

GLuint VBO_vertices, VBO_vertices_indices;
GLuint VBO_normais;
GLuint VBO_texturas;

//Free Camera
float free_ultimo_X = 0;
float free_ultimo_Y = 0;
bool free_primeiro_click = true;
bool free_rato_pressionado = false;
bool keys[256];
// ----------

void buildRotMatrix(float *x, float *y, float *z, float *m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float *a, float *b, float *res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}

//normalização (para float)
void normalize(float *a) {

	
	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	if (l == 0.0f) return;
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}

//normalização (para double)
void normalize(double *a) {

	
	double l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	if (l == 0.0f) return;
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}

//multiplicação de matrizes
void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

// calcula a nova posição do objeto e derivada da curva no instante t 
void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv) {

	float m[16] = {
		-0.5f, 1.5f, -1.5f, 0.5f,
		 1.0f,-2.5f,  2.0f,-0.5f,
		-0.5f, 0.0f,  0.5f, 0.0f,
		 0.0f, 1.0f,  0.0f, 0.0f
	};

	float px[4] = { p0[0], p1[0], p2[0], p3[0] };
	float py[4] = { p0[1], p1[1], p2[1], p3[1] };
	float pz[4] = { p0[2], p1[2], p2[2], p3[2] };

	float Ax[4], Ay[4], Az[4];

	multMatrixVector(m, px, Ax);
	multMatrixVector(m, py, Ay);
	multMatrixVector(m, pz, Az);

	float T[4] = { t * t * t, t * t, t, 1 };
	float Td[4] = { 3 * t * t, 2 * t, 1, 0 };

	pos[0] = Ax[0] * T[0] + Ax[1] * T[1] + Ax[2] * T[2] + Ax[3] * T[3];
	pos[1] = Ay[0] * T[0] + Ay[1] * T[1] + Ay[2] * T[2] + Ay[3] * T[3];
	pos[2] = Az[0] * T[0] + Az[1] * T[1] + Az[2] * T[2] + Az[3] * T[3];

	deriv[0] = Ax[0] * Td[0] + Ax[1] * Td[1] + Ax[2] * Td[2] + Ax[3] * Td[3];
	deriv[1] = Ay[0] * Td[0] + Ay[1] * Td[1] + Ay[2] * Td[2] + Ay[3] * Td[3];
	deriv[2] = Az[0] * Td[0] + Az[1] * Td[1] + Az[2] * Td[2] + Az[3] * Td[3];
}

// retorna o ponto na curva no instante t
void getGlobalCatmullRomPoint(float gt, float** p, int POINT_COUNT, float* pos, float* deriv) {

	float t = gt * POINT_COUNT; // O valor do tempo
	int index = floor(t);

	if (index == POINT_COUNT) {
		index = 0;
		t = 0.0f;
	}

	t = t - index;

	int indices[4]; 
	indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;	
	indices[1] = (indices[0]+1)%POINT_COUNT;
	indices[2] = (indices[1]+1)%POINT_COUNT; 
	indices[3] = (indices[2]+1)%POINT_COUNT;

	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}

//desenha a curva de Catmull-Rom
void renderCatmullRomCurve(vector<Ponto>* pontos) {

	if (pontos->size() < 4)
		return;

		
	int numSegments = 100;
	float pos[3], deriv[3];
	int POINT_COUNT = pontos->size();
	
	std::vector<std::vector<float>> pontosConvertidos;
	std::vector<float*> pVec;

	for (Ponto ponto : *(pontos)) {
		pontosConvertidos.push_back({(float)ponto.x, (float)ponto.y, (float)ponto.z});
	}

	for (vector<float>& f : pontosConvertidos) {
		pVec.push_back(f.data());
	}

	float** p = pVec.data();

	vector<float> curva_pontos;

	for (int i = 0; i < numSegments; i++) {
		float t = (float)i / numSegments;
		getGlobalCatmullRomPoint(t, p, POINT_COUNT, pos, deriv);
		curva_pontos.push_back(pos[0]);
		curva_pontos.push_back(pos[1]);
		curva_pontos.push_back(pos[2]);
	}

	float* pontos_buffer = curva_pontos.data();
	
	// VBO para os vertices da curva
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*curva_pontos.size() , pontos_buffer, GL_STATIC_DRAW);
	
	//Desenhar Modelo
	glColor3f(1, 1, 1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
	glVertexPointer(3, GL_FLOAT,0,0);
	glDrawArrays(GL_LINE_LOOP, 0, curva_pontos.size() / 3);

}

//Função que atualiza as direções da camera
void atualizarDirecoesCamera() {

	// 180º         -> 1 radiano * pi
	// angulo_atual -> y
	float rad_alfa = (world.free_alfa * M_PI) / 180.0;
	float rad_beta = (world.free_beta * M_PI) / 180.0;

	// Alfa = rotação horizontal (esquerda-direita)
	// Beta = rotação vertical (cima baixo)

	float vetor[3];

	//Pre-condição : estão normalizados

	vetor[0] = cos(rad_alfa) * cos(rad_beta);
	//Primeiro encosto em z=0, depois calculo o x

	vetor[1] = sin(rad_beta);
	//Primeiro encosto em z=0 e x=0, depois calculo o y

	vetor[2] = sin(rad_alfa) * cos(rad_beta);
	//Primeiro encosto em x=0, depois calculo o z

	normalize(vetor);

	world.camera_x = vetor[0];
	world.camera_y = vetor[1];
	world.camera_z = vetor[2];

}

//Função que inicializa as direções da camera
void inicializarDirecoesCamera() {

	//Calcular o vetor de direção
	double vetor_direcao[3];

	vetor_direcao[0] = world.camera_x - world.pos_x;
	vetor_direcao[1] = world.camera_y - world.pos_y;
	vetor_direcao[2] = world.camera_z - world.pos_z;

	normalize(vetor_direcao);

	// 180º  -> 1 radiano * pi
	// x     -> radianos_atuais

	// sin(beta) = altura/comprimento (comprimento = 1 -> normalizado)
	world.free_beta = (asin(vetor_direcao[1]) * 180.0f) / M_PI;

	// sin(alfa) = inversa da tangente (-180) - (+180)
	world.free_alfa = atan2(vetor_direcao[2], vetor_direcao[0]) * 180.0f / M_PI;

	atualizarDirecoesCamera();

}

void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you can�t make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the perspective
	gluPerspective(world.fov,ratio,world.near,world.far);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);

	// finally set the viewport to be the entire window
	glViewport(0, 0, w, h);
}


//Buffer dos eixos
double eixo_pontos[] = {
	-100.0f, 0.0f, 0.0f,
	100.0f, 0.0f, 0.0f,
	0.0f, -100.0f, 0.0f,
	0.0f, 100.0f, 0.0f,
	0.0f, 0.0f, -100.0f,
	0.0f, 0.0f,  100.0f
};

unsigned int eixo_indices[] {
	0 , 1 , 2 , 3 , 4 , 5
};

//Função que desenha os eixos
void desenhaEixos() {

	glDisable(GL_LIGHTING);

	// VBO para os vertices do eixo
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(eixo_pontos), eixo_pontos, GL_STATIC_DRAW);

	// VBO para os indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_vertices_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(eixo_indices), eixo_indices, GL_STATIC_DRAW);

	//Desenhar Modelo
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
	glVertexPointer(3, GL_DOUBLE,0,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_vertices_indices);

	//Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));

	//Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(2 * sizeof(GLuint)));

	//Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(4 * sizeof(GLuint)));

	glEnable(GL_LIGHTING);

}

//Função que efetua transformações
void efetuaTransformacoes(RoseTreeNode* iter) {

	//Não há transformações
	if (iter->transform == nullptr)
		return;

	//Iterar sobre as transformações
	for (TransformElement transElemento : iter->transform->transformacoes) {

		//Se o tipo for translação
		if (transElemento.tipo == TRANSLACAO) {

			if (transElemento.tempo > 0 && transElemento.pontos && transElemento.pontos->size() >= 4) {

				if (transElemento.drawCurve == true)
					renderCatmullRomCurve(transElemento.pontos); //desenha a curva

				float pos[3], deriv[3];

				int pointCount = transElemento.pontos->size();

				std::vector<std::vector<float>> pontosConvertidos;
				std::vector<float*> pVec;

				// Converte o vector de pontos para um array de float*
				for (Ponto ponto : *(transElemento.pontos)) {
					pontosConvertidos.push_back({(float)ponto.x, (float)ponto.y, (float)ponto.z});
				}
			
				for (vector<float>& f : pontosConvertidos) {
					pVec.push_back(f.data());
				}

				float** p = pVec.data();

				double tempo = transElemento.tempo;

				float gt = fmod(glutGet(GLUT_ELAPSED_TIME), tempo) / tempo;

				getGlobalCatmullRomPoint(gt, p, pointCount, pos, deriv);

				// Calcular posição com Catmull-Rom
				glTranslatef(pos[0], pos[1], pos[2]);

				if (transElemento.align) {
					float x[3], y[3], z[3], m[16];
					y[0] = 0.0f; y[1] = 1.0f; y[2] = 0.0f;

					x[0] = deriv[0]; x[1] = deriv[1]; x[2] = deriv[2];
					normalize(x);
					cross(x, y, z);
					normalize(z);
					cross(z, x, y);
					normalize(y);
					buildRotMatrix(x, y, z, m);
					glMultMatrixf(m);  // Atualiza a matriz de rotação
				}

			}
			else {

				glTranslated(transElemento.x, transElemento.y, transElemento.z);
			}
		}
		
		//Se o tipo for rotação
		if (transElemento.tipo == ROTACAO) {

			// Não tem tempo
			if (transElemento.angulo != 0)
				glRotated(transElemento.angulo, transElemento.x, transElemento.y, transElemento.z);
			else {

				//   time - 360º
				//   current_time - angle_to_be_performed

				int angulo_a_ser_executado = (glutGet(GLUT_ELAPSED_TIME) * 360) / transElemento.tempo;
				//cout << angulo_a_ser_executado << "\n";
				glRotated(angulo_a_ser_executado, transElemento.x, transElemento.y, transElemento.z);

			}

		}
		
		//Se o tipo for escala
		if (transElemento.tipo == ESCALA) {
			glScaled(transElemento.x, transElemento.y, transElemento.z);
		}

	}

}

map <string, unsigned int> texturasID;

int carregarTextura(char* s) {

	if (s == nullptr)
		return 0;

	string texturaPath(s);

	if (texturasID.find(texturaPath) != texturasID.end()) {
        // Se já foi carregada, retorna o ID armazenado no cache
        return texturasID[texturaPath];
    }

	unsigned int t,tw,th;
	unsigned char *texData;
	unsigned int texID;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1,&t);
	ilBindImage(t);

	// Carrega a imagem
    if (!ilLoadImage(s)) {
        printf("Erro ao carregar a textura: %s\n", s);
        return 0; // Retorna 0 se falhar no carregamento
    }

	//ilLoadImage(s);
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1,&texID);
	
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	// Armazena a textura no cache com o caminho como chave
	texturasID[texturaPath] = texID;

	return texID;

}

//Função que efetua desenha os modelos
void desenhaModelos(RoseTreeNode* iter) {

	//Não há modelos
	if (iter->models == nullptr) {
		return;
	}
	
	if (world.luzes == nullptr)
		glDisable(GL_LIGHTING);

	//Itera sobre os modelos
	for (ModelElement* modelo : iter->models->modelos) {

		//Carregar Textura
		int textura_id = carregarTextura(modelo->textura);

		if(textura_id > 0) {

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,textura_id);

		}
		else {
			glDisable(GL_TEXTURE_2D);
		}

		if (modelo->hasColor == true) {

			glMaterialfv(GL_FRONT, GL_DIFFUSE, modelo->color_diffuse);
			glMaterialfv(GL_FRONT, GL_AMBIENT, modelo->color_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, modelo->color_specular);
			glMaterialfv(GL_FRONT, GL_EMISSION, modelo->color_emissive);
			glMaterialf(GL_FRONT, GL_SHININESS, modelo->color_shininess);

		}
		else
			glColor3f(1.0f,1.0f,1.0f);


		if (modelo->hasColor == false && textura_id <= 0)
			glPolygonMode(GL_FRONT, GL_LINE);

		

		// VBO para os vertices
		glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * modelo->modelo->vertices_N, modelo->modelo->vertices, GL_STATIC_DRAW);

		// VBO para as normais
		glBindBuffer(GL_ARRAY_BUFFER, VBO_normais);
		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * modelo->modelo->normais_N, modelo->modelo->normais, GL_STATIC_DRAW);


		if (textura_id > 0) {

			// VBO para as texturas
			glBindBuffer(GL_ARRAY_BUFFER, VBO_texturas);
			glBufferData(GL_ARRAY_BUFFER, sizeof(double) * modelo->modelo->texturas_N, modelo->modelo->texturas, GL_STATIC_DRAW);

		}


		// ######### VERTICES #####################
		//Desenhar Modelo - Vertices
		glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
		glVertexPointer(3, GL_DOUBLE,0,0);
		glEnableClientState(GL_VERTEX_ARRAY);

		// ######### NORMAIS #####################
		//Desenhar Modelo - Normais
		glBindBuffer(GL_ARRAY_BUFFER, VBO_normais);
		glNormalPointer(GL_DOUBLE,0,0);
		glEnableClientState(GL_NORMAL_ARRAY);

		// ######### TEXTURAS #####################

		if (textura_id > 0) {
			//Desenhar Modelo - Texturas
			glBindBuffer(GL_ARRAY_BUFFER, VBO_texturas);
			glTexCoordPointer(2, GL_DOUBLE,0,0);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		}


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_vertices_indices);
		glDrawArrays(GL_TRIANGLES, 0, modelo->modelo->vertices_N);
		
	}

}

//Função que efetua desenha as luzes
void desenhaLuzes() {

	if (world.luzes == nullptr)
		return;

	glEnable(GL_LIGHTING);

	for (int i = 0 ; i < 8 ; i++) {

		if (i >= (int) world.luzes->size())
			break;

		int tipo_luz = GL_LIGHT0 + i;

		Luz* luz = &((*world.luzes)[i]);

		switch (luz->tipo) {

			case POINT: {

				GLfloat pos[4] = {luz->pos_x,luz->pos_y,luz->pos_z,1.0f}; //Ponto
				glLightfv(tipo_luz,GL_POSITION,pos);

				break;
			}
			case DIRECTIONAL: {

				GLfloat dir[4] = {luz->dir_x,luz->dir_y,luz->dir_z,0.0f}; //Vetor
				glLightfv(GL_LIGHT0,GL_POSITION, dir);

				break;
			}
			case SPOTLIGHT: {

				GLfloat pos[4] = {luz->pos_x,luz->pos_y,luz->pos_z,1.0f}; //Ponto
				GLfloat dir[3] = {luz->dir_x,luz->dir_y,luz->dir_z}; //Vetor

				glLightfv(tipo_luz,GL_POSITION,pos);
				glLightfv(tipo_luz,GL_SPOT_DIRECTION,dir);
				glLightf(tipo_luz,GL_SPOT_CUTOFF,luz->cutoff);

				break;
			}
				
		}
		
		glEnable(GL_NORMALIZE); // importante se houver escalas

	}


}

//Função que desenha
void renderScene(void) {

	//Iniciando a camera e posição ##########
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    gluLookAt(world.pos_x, 					world.pos_y, 				  world.pos_z,  // Câmera ajustada
			  world.pos_x + world.camera_x, world.pos_y + world.camera_y, world.pos_z + world.camera_z,
              world.normal_x, world.normal_y, world.normal_z);

			  
	//Desenhar Eixos
	desenhaEixos();
	glColor3f(1,1,1);
			  
	//Desenhar Luz
	desenhaLuzes();
	
	//Inicia Iterador
	world.grupos->startIter();
	RoseTreeNode* iter = nullptr;

	//Iterador
	while ((iter = world.grupos->next()) != nullptr) {

		//1 Passo -> dar Pops da matrix
		//Calcular a quantidade de pops
		int quantidades_de_pops = world.grupos->shouldPop();
			
			while (quantidades_de_pops > 0) {
				glPopMatrix();
				quantidades_de_pops--;
			}

		//2 Passo -> dar Push da matrix
		if (world.grupos->shouldPush()) {
			glPushMatrix();
		}

		//3 Passo -> Efetua Transformações
		efetuaTransformacoes(iter);

		//4 Passo -> Desenha os Modelos
		desenhaModelos(iter);
		//testeLuz(iter);
		//testeCaixa(iter);

	}

	//5 Passo -> Fazer pops restantes
	int quantidades_de_pops = world.grupos->PopsRestantes();

		while (quantidades_de_pops > 0) {
			glPopMatrix();
			quantidades_de_pops--;
		}

    glutSwapBuffers();

}

//Função da Function Motion
void funcMotion(int x, int y) {

	//Se estiver desativado, para a execução
	if (world.free_disable == true)
		return;

	//Se precisa de clique e não está pressionado, pára a execução
    if (world.free_needClick == true && free_rato_pressionado == false) 
		return;


	//Atualizar os primeiros valores que serão usados
    if (free_primeiro_click == true) {
        free_ultimo_X = x;
        free_ultimo_Y = y;
        free_primeiro_click = false;
        return;
    }

	//Movimento do comprimento da tela
    double delta_x = x - free_ultimo_X;
	//Movimento da altura da tela
    double delta_y = y - free_ultimo_Y;

	//Registar os ultimos movimentos
    free_ultimo_X = x;
    free_ultimo_Y = y;

	//Aplica a sensibilidade
    delta_x *= world.sensitivity;
    delta_y *= world.sensitivity;

	//Atualiza os angulos
    world.free_alfa += delta_x;
    world.free_beta -= delta_y;

	//Se o angulo é limitado, então evita que a camera vire de cabeça para baixo
	if (world.free_limitedAngle == true) {

    	if (world.free_beta > 89.9f)
			world.free_beta = 89.9f;

    	if (world.free_beta < -89.9f)
			world.free_beta = -89.9f;

	}

    atualizarDirecoesCamera();
    glutPostRedisplay();

}

//Função que deteta clicks do rato
void mouseClick(int botao, int estado, int x, int y) {

    if (botao == GLUT_LEFT_BUTTON) {

        if (estado == GLUT_DOWN) {

            free_rato_pressionado = true;
            free_primeiro_click = true; //Reseta sempre, indicando que é o primeiro clique

        } 
		else {

			if (estado == GLUT_UP)
				free_rato_pressionado = false;

        }
    }

}

//Atualiza posição da Camera
void atualizarPosicaoCamera() {
	
	//Obter vetor perpendicular
	double vetor_perpendicular[3];

	vetor_perpendicular[0] = world.camera_y * world.normal_z - world.camera_z * world.normal_y;
	vetor_perpendicular[1] = world.camera_z * world.normal_x - world.camera_x * world.normal_z;
	vetor_perpendicular[2] = world.camera_x * world.normal_y - world.camera_y * world.normal_x;

	normalize(vetor_perpendicular);

	//Anda para a frente
    if (keys['w']) {
        world.pos_x += world.camera_x * world.free_speed;
        world.pos_y += world.camera_y * world.free_speed;
        world.pos_z += world.camera_z * world.free_speed;
    }

	//Anda para tras
    if (keys['s']) {
        world.pos_x -= world.camera_x * world.free_speed;
        world.pos_y -= world.camera_y * world.free_speed;
        world.pos_z -= world.camera_z * world.free_speed;
    }

	//Anda para a esquerda
    if (keys['a']) {
        world.pos_x -= vetor_perpendicular[0] * world.free_speed;
        world.pos_z -= vetor_perpendicular[2] * world.free_speed;
    }

	//Anda para a direita
    if (keys['d']) {
        world.pos_x += vetor_perpendicular[0] * world.free_speed;
        world.pos_z += vetor_perpendicular[2] * world.free_speed;
    }

}


//Função Idle
void idleFunc() {

	if (world.free_disable == true && world.hasTime == false)
		return;


    atualizarPosicaoCamera();
    glutPostRedisplay();

}

void pressionarTecla(unsigned char key, int x, int y) {
    keys[key] = true;
}

void soltarTecla(unsigned char key, int x, int y) {
    keys[key] = false;
}

//Função que processa as teclas normais
void pressKey(unsigned char key, int x, int y) {

	glutPostRedisplay();
}

void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
}

void initGL() {

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	if (world.luzes != nullptr && world.luzes->size() != 0) {

		glEnable(GL_LIGHTING);
		glEnable(GL_RESCALE_NORMAL);
		float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white);

		for (int i = 0; i < (int) world.luzes->size(); i++) {

      		glEnable(GL_LIGHT0 + i);
      		glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, white);
      		glLightfv(GL_LIGHT0 + i, GL_SPECULAR, white);

		}

		glEnable(GL_NORMALIZE);

	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glGenBuffers(1, &VBO_vertices);
	glGenBuffers(1, &VBO_vertices_indices);
	glGenBuffers(1, &VBO_normais);
	glGenBuffers(1, &VBO_texturas);

}

void initLuzes() {

	//Não há luzes
	if (world.luzes == nullptr)
		return;

	if (world.luzes->size() != 0) {

		glEnable(GL_LIGHTING);
		glEnable(GL_RESCALE_NORMAL);
		float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

		for (int i = 0; i < (int) world.luzes->size(); i++) {

			float white[4] = {1.0, 1.0, 1.0, 1.0};
			float dark[4] = {0.2, 0.2, 0.2, 1.0};
			//float black[4] = {0.0f,0.0f,0.0f,0.0f};
		
			glEnable(GL_LIGHT0 + i);
			glLightfv(GL_LIGHT0 + i, GL_AMBIENT, dark);
			glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, white);
			glLightfv(GL_LIGHT0 + i, GL_SPECULAR, white);

		}

	}
  
}

int main(int argc, char** argv)
{

	//Não há argumentos suficientes
	if (argc < 2) {

		cerr << "Argumentos em falta\n";
		cerr << "USO : ./engine [CAMINHO PARA XML]\n";

		return 1;

	}
	//Há argumentos suficientes
	else {

		//Inicializar mundo
		world = World();

		//Ler dados do xml
		TiXmlDocument xml(argv[1]);

		//XML falhou
		if (xml.LoadFile() == false) {

			cerr << "Erro ao carregar o ficheiro XML\n";
			return 2;

		}

		//Processar XML - correu bem
		if (processaXML(world,xml)) {

			// put GLUT init here
			glutInit(&argc,argv);
			glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    		glutInitWindowPosition(100,100);
			glutInitWindowSize(world.width,world.height);
			glutCreateWindow("Projeto CG - 24/25");

			inicializarDirecoesCamera();

			// put callback registry here
			//glutKeyboardFunc(&pressKey);
			//glutSpecialFunc(&pressSpecialKey);

			glutDisplayFunc(&renderScene);
			glutReshapeFunc(&changeSize);
			glutPostRedisplay();

			glutMouseFunc(&mouseClick);
    		glutMotionFunc(&funcMotion);
			glutPassiveMotionFunc(&funcMotion);
    		glutKeyboardFunc(&pressionarTecla);
    		glutKeyboardUpFunc(&soltarTecla);

			glutIdleFunc(&idleFunc);

			// init GLEW
			#ifndef __APPLE__
				glewInit();
			#endif

			initGL();
			
			// some OpenGL settings
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

			// enter GLUT�s main cycle
			atualizarPosicaoCamera();
			glutMainLoop();

			return 0;

		}
		else {

			cerr << "Ficheiro XML não foi corretamente processado\n";
			return 1;

		}

	}

}
