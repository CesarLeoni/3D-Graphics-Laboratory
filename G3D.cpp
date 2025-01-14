// Program HelloGlut.cpp
#include <GL/glut.h>
#include <math.h>


//LAB 3 - 3.4. Deplasarea obiectelor scenei.
//float angleXs = 45.0f, angleYs = 45.0f, angleZs = 0.0f;

//LAB 3 - 3.3. Miºcarea observatorului.
//float angleXv = 10.0f, angleYv = 0.0f, angleZv = 34.0f;

// Pozitionare obiecte scena
float Xs = 0.0f, Ys = 0.0f, Zs = 0.0f;
float angleXs = 0.0f, angleYs = 0.0f, angleZs = 0.0f;

// Pozitionare observator
float Xv = 0.0f, Yv = 0.0f, Zv = 5.0f;
float angleXv = 0.0f, angleYv = 0.0f, angleZv = 0.0f;

// Mouse
bool pressed = false;
int mouse_x;
int mouse_y;

// Functia de initializare a starii OpenGL
void Init(){
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // culoare stergere negru

	//LAB 1 - 1.1. Studiul culorilor în OpenGL
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f); // culoare stergere

	//LAB 1 - 1.2. Modurile de desenare a suprafeþelor
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //setare implicita REDUNDANTA
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	//LAB 1 - 1.3. Interpolarea culorilor la desenarea primitivelor geometrice
	//glShadeModel(GL_SMOOTH);// setare implicita REDUNDANTA
	//glShadeModel(GL_FLAT);//doar o culoare - rosu = prima culoare din DrawRectangleColor()

	//LAB 2 - 2.5. Orientarea suprafetelor
	glEnable(GL_CULL_FACE);//elimina fetele care au orientarea precizatã prin funcþia glCullFace
	glCullFace(GL_BACK);//orientare spre spate
	//glFrontFace(GL_CCW);//setarea implicita REDUNDANTA
	//glFrontFace(GL_CW);//parcurgerea listei de vârfuri a primitivei este în sensul acelor de ceas (ClockWise
	//glCullFace(GL_FRONT);//orientare spre fata
	//glFrontFace(GL_CW); glCullFace(GL_FRONT); e echivalent cu  glCullFace(GL_BACK);


	glClearDepth(1.0f); //adancimea maxima Z buffer
	glEnable(GL_DEPTH_TEST); // validare Z buffer
}

void DrawRectangle(){
	glBegin(GL_POLYGON);
	glVertex3d(-1.0, 1.0, 0.0);
	glVertex3d( 1.0, 1.0, 0.0);
	glVertex3d( 1.0,-1.0, 0.0);
	glVertex3d(-1.0,-1.0, 0.0);
	glEnd();
}

//LAB 1 - 1.3. Interpolarea culorilor la desenarea primitivelor geometrice
void DrawRectangleColor(){
	glBegin(GL_POLYGON);
	glColor3d(1.0, 0.0, 0.0); // rosu
	glVertex3d(-1.0, 1.0, 0.0);
	glColor3d(0.0, 1.0, 0.0); // verde
	glVertex3d( 1.0, 1.0, 0.0);
	glColor3d(0.0, 0.0, 1.0); // albastru
	glVertex3d( 1.0,-1.0, 0.0);
	glColor3d(1.0, 1.0, 1.0); // alb
	glVertex3d(-1.0,-1.0, 0.0);
	glEnd();
}

//LAB 2 - 2.1. Modelul unui dreptunghi
void DrawRectangleFor(){
	GLfloat rectangle[4][3] = {
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f
	};
	glBegin(GL_POLYGON);
	for (int i=0;i<4;i++){
		glColor3f(rectangle[i][0],rectangle[i][1],rectangle[i][2]);
		glVertex3f(rectangle[i][0],rectangle[i][1],rectangle[i][2]);
	}
	glEnd();
	//Culorile vârfurilor pãtratului vor fi
	//verde (0,1,0), galben (1,1,0), roºu (1,0,0) ºi negru (0,0,0)
}

//LAB 2 - 2.2. Modelul unui poligon regulat în planul z = 0.
void DrawPolygon(){
	int n = 10;
	GLfloat coords[10*3];
	for (int i=0;i<n;i++){
		float angle = 2*3.14*i/n;
		coords[i*3+0] = cos (angle);
		coords[i*3+1] = sin(angle);
		coords[i*3+2] = 0;
	}
	glBegin(GL_POLYGON);
	for (int i=0;i<n;i++){
		glColor3f(coords[i*3],coords[i*3+1],coords[i*3+2]);
		glVertex3f(coords[i*3],coords[i*3+1],coords[i*3+2]);
	}
	glEnd();
}

//LAB 2 - 2.3. Modelul cu feþe separate al unui cub
void DrawCube(){
	double cube[6][4][3] = {
		-1,-1,-1, 1,-1,-1, 1,-1, 1, -1,-1, 1, // fata 0
		-1, 1, 1, 1, 1, 1, 1, 1,-1, -1, 1,-1, // fata 1
		-1,-1, 1, 1,-1, 1, 1, 1, 1, -1, 1, 1, // fata 2
		1,-1,-1, -1,-1,-1, -1, 1,-1, 1, 1,-1, // fata 3
		1,-1, 1, 1,-1,-1, 1, 1,-1, 1, 1, 1, // fata 4
		-1,-1, 1, -1, 1, 1, -1, 1,-1, -1,-1,-1 // fata 5
	};

	for (int fata=0;fata<6;fata++){
		glBegin(GL_POLYGON);
		for (int i=0;i<4;i++){
			glColor3f(cube[fata][i][0],cube[fata][i][1],cube[fata][i][2]);
			glVertex3f(cube[fata][i][0],cube[fata][i][1],cube[fata][i][2]);
		}
		glEnd();
	}

}

//LAB 2 - 2.4. Modelul cu feþe indexate al unui cub.
void DrawCubeVertices(){
	double cubeCoords[8][3]={
		-1,-1, 1,
		1,-1, 1,
		1,-1,-1,
		-1,-1,-1,
		-1, 1, 1,
		1, 1, 1,
		1, 1,-1,
		-1, 1,-1
	};
	int cubeIndex[6][4]={
		3, 2, 1, 0,
		4, 5, 6, 7,
		0, 1, 5, 4,
		2, 3, 7, 6,
		1, 2, 6, 5,
		0, 4, 7, 3
	};

	for (int fata=0;fata<6;fata++){
		glBegin(GL_POLYGON);
		for (int varf=0;varf<4;varf++){
			int ce_varf = cubeIndex[fata][varf]; //varf reprezinta la al catalea varf din cadrul patratului desenat acum am ajuns
			//ce_varf reprezinta numarul varfului dintre cele 8 ale cubului, care au coordonatele in cubeCoords
			glColor3f(cubeCoords[ce_varf][0],cubeCoords[ce_varf][1],cubeCoords[ce_varf][2]);
			glVertex3f(cubeCoords[ce_varf][0],cubeCoords[ce_varf][1],cubeCoords[ce_varf][2]);
		}
		glEnd();
	}
}

// functie pentru desenarea axelor - pentru analiza mai clara
void DrawAxis(){
	glLineWidth(2.0f);

	//x pozitiv
	glColor3f(1.0f,0.2f,0.2f);
	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(5.0, 0.0, 0.0);
	glEnd();

	//x negativ
	glColor3f(0.5f,0.1f,0.1f);
	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(-5.0, 0.0, 0.0);
	glEnd();

	//y pozitiv
	glColor3f(0.2f,1.0f,0.2f);
	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 5.0, 0.0);
	glEnd();

	//y negativ
	glColor3f(0.1f,0.5f,0.1f);
	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, -5.0, 0.0);
	glEnd();

	//z pozitiv
	glColor3f(0.2f,0.2f,1.0f);
	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 5.0);
	glEnd();

	//z negativ
	glColor3f(0.1f,0.1f,0.5f);
	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, -5.0);
	glEnd();

	glLineWidth(1.0);
}

// Functia callback de desenare
void Display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	//LAB 3 - 3.2. Transformarea de observare ºi transformãrile de modelare.
	// Transformarea de observare
	glRotatef(-angleZv, 0.0,0.0,1.0);
	glRotatef(-angleXv, 1.0,0.0,0.0);
	glRotatef(-angleYv, 0.0,1.0,0.0);
	glTranslatef(-Xv, -Yv, -Zv); // se initializeaza Zv = 5;
	// Transformare de modelare (pozitionare) obiecte din scena
	glTranslatef(Xs,Ys,Zs);
	glRotatef(angleYs, 0.0,1.0,0.0);
	glRotatef(angleXs, 1.0,0.0,0.0);
	glRotatef(angleZs, 0.0,0.0,1.0);

	glColor3d(1.0, 0.0, 0.0); // culoare curenta

	//DrawRectangle();
	//DrawRectangleColor();
	//DrawRectangleFor();
	//DrawPolygon();
	//DrawCube();
	//DrawCubeVertices();

	//LAB 1 - 1.4. alte figuri de desenat
	//glutSolidSphere(1.0, 20, 20);
	//glutSolidCone (1.0, 3.0, 64, 64);
	//glutSolidTorus (0.1, 0.85, 64, 64);
	//glutSolidTeapot(1.0);

	glPushMatrix();
		DrawAxis();
	glPopMatrix();

	//LAB 3 - 3.5 modelarea scenelor complexe
/*	glPushMatrix();
		glTranslatef(1,1,1);
		glColor3d(1,1,1); // culoare curenta
		glutSolidSphere(0.4, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1,1,1);
		glColor3d(-1,1,1); // culoare curenta
		glutSolidSphere(0.4, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1,-1,1);
		glColor3d(1,-1,1); // culoare curenta
		glutSolidSphere(0.4, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1,1,-1);
		glColor3d(1,1,-1); // culoare curenta
		glutSolidSphere(0.4, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1,-1,1);
		glColor3d(-1,-1,1); // culoare curenta
		glutSolidSphere(0.4, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1,-1,-1);
		glColor3d(1,-1,-1); // culoare curenta
		glutSolidSphere(0.4, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1,1,-1);
		glColor3d(-1,1,-1); // culoare curenta
		glutSolidSphere(0.4, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1,-1,-1);
		glColor3d(-1,-1,-1); // culoare curenta
		glutSolidSphere(0.4, 20, 20);
	glPopMatrix();

	glPushMatrix();
		DrawCubeVertices();
	glPopMatrix();
*/

	//LAB 3 - 3.6. Transformãri compuse.
/*	glPushMatrix();
		DrawCubeVertices();
	glPopMatrix();

	float angle36 = 45.0;
	glPushMatrix();
		glTranslatef(1,1,0);
		glRotatef(angle36,0.0,0.0,1);
		DrawCube();
	glPopMatrix();
*/

	glPopMatrix();

//	//LAB 3 - 3.5. Modelarea scenelor complexe.
//	glPushMatrix();
//		//Transformarea de observare
//		//Transformarea de poziþionare a tuturor obiectelor scenei
//			glPushMatrix();
//				//Transformarea de modelare a primului obiect
//				//Redarea primului obiect
//			glPopMatrix();
//			glPushMatrix();
//				//Transformarea de modelare al celui de-al doilea obiect
//				//Redarea celui de-al doilea obiect
//			glPopMatrix();
//	glPopMatrix();

	glFinish();
	glutSwapBuffers(); // comutare buffer
}
// Functia CALLBACK de redimensionare a ferestrei
void Reshape(int w, int h){
	h = (h == 0) ? 1 : h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); //selectie stiva PROJECTION
	glLoadIdentity();

	gluPerspective(45.0f, (GLdouble)w/h, 1.0f, 100.0f);
	//LAB 3 - 3.1. Transformarea de proiecþie
	//gluPerspective(45.0f, (GLdouble)w/h, 3.0f, 6.0f);


	glMatrixMode(GL_MODELVIEW); // selectie stiva MODELVIEW
	glLoadIdentity();
}

// Functia callback de tastatura
void Keyboard(unsigned char key, int x, int y){
	switch (key){
		// tastele z si Z modifica pozitia obiectelor
	case 'z':
		Zs -= 0.5;
		glutPostRedisplay();
		break;
	case 'Z':
		Zs += 0.5;
		glutPostRedisplay();
		break;
	}
}

// Functia callback de tratare evenimente de apasare butoane mouse
void Mouse(int button, int state, int x, int y){
	switch(button){
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN){
			pressed = true;
			mouse_x = x;
			mouse_y = y;
		}
		else pressed = false;
		break;
	}
}

// Functia callback de tratare evenimente de miscare mouse
void Motion(int x, int y){
	if (pressed){
		float w = 500;
		float h = 500;
		angleYs += 180.0f*(x - mouse_x)/w;
		angleXs += 180.0f*(y - mouse_y)/h;
		mouse_x = x;
		mouse_y = y;
		glutPostRedisplay();
	}
}

// Functia principala a programului
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Laboratorul de Grafica 3D");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard); // Inregistrare func. Keyboard
	glutMouseFunc(Mouse); // Inregistrare func. Mouse
	glutMotionFunc(Motion); // Inregistrare func. Motion
	glutMainLoop();
	return 0;
}