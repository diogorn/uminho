#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void drawCylinder(float radius, float height, int slices) {
    float angleStep = (2.0f * M_PI) / slices;  // Agora usamos M_PI

    glBegin(GL_TRIANGLES);

    // Base Inferior (sentido anti-horário quando vista de baixo)
    for (int i = 0; i < slices; i++) {
        float alpha = i * angleStep;
        float nextAlpha = (i + 1) * angleStep;

        float x1 = radius * sin(alpha);
        float z1 = radius * cos(alpha);
        float x2 = radius * sin(nextAlpha);
        float z2 = radius * cos(nextAlpha);

        glColor3f(0.5f, 0.5f, 0.5f); // Cinza

        glVertex3f(0.0f, 0.0f, 0.0f); // Centro da base
        glVertex3f(x2, 0.0f, z2);
        glVertex3f(x1, 0.0f, z1);
    }

    // Base Superior (sentido anti-horário quando vista de cima)
    for (int i = 0; i < slices; i++) {
        float alpha = i * angleStep;
        float nextAlpha = (i + 1) * angleStep;

        float x1 = radius * sin(alpha);
        float z1 = radius * cos(alpha);
        float x2 = radius * sin(nextAlpha);
        float z2 = radius * cos(nextAlpha);

        glColor3f(0.7f, 0.7f, 0.7f); // Cinza Claro

        glVertex3f(0.0f, height, 0.0f); // Centro da base superior
        glVertex3f(x1, height, z1);
        glVertex3f(x2, height, z2);
    }

    // Laterais (corrigindo a ordem dos triângulos)
    for (int i = 0; i < slices; i++) {
        float alpha = i * angleStep;
        float nextAlpha = (i + 1) * angleStep;

        float x1 = radius * sin(alpha);
        float z1 = radius * cos(alpha);
        float x2 = radius * sin(nextAlpha);
        float z2 = radius * cos(nextAlpha);

        glColor3f(0.8f, 0.2f, 0.2f); // Vermelho

        // Primeiro triângulo (base inferior -> superior direito -> superior esquerdo)
        glVertex3f(x1, 0.0f, z1);
        glVertex3f(x2, height, z2);
        glVertex3f(x1, height, z1);

        // Segundo triângulo (base inferior -> base superior direito -> base inferior direito)
        glVertex3f(x1, 0.0f, z1);
        glVertex3f(x2, 0.0f, z2);
        glVertex3f(x2, height, z2);
    }

    glEnd();
}

void drawAxis(){
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f( 100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}
void drawBox(){
	
}

void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0,  // eye
		      0.0,0.0,0.0, // look at origin
			  0.0f,1.0f,0.0f); // up vector
	
	drawAxis();
	drawBox();
	//drawCylinder(1,2,10);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here

}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
