// This is the main project file for VC++ application project 
// generated using an Application Wizard.

#define GLUT_DISABLE_ATEXIT_HACK

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "glut.h"
#include "freeglut.h"
#include "robot.h"




int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// used default buffer
	
	glutInitWindowSize(WinWidth,WinHeight);						// begin window size
	glutInitWindowPosition(0,0);								// begin window position
	glutCreateWindow(argv[0]);									// create window
	
	init();		// initial opengl attribute
	idle();	// initial finger position

	// binding function
	bindingMenu();				// binding and seting menu
	glutKeyboardFunc(nkeyin);	// binding standard input
	glutSpecialFunc(sKeyin);
	glutReshapeFunc(reshape);	// binding resize window function
	glutDisplayFunc(display);	// binding function when work(have change)
	// glutIdleFunc(display);	// binding function when idle
	glutTimerFunc(frame_update, timerFunction, 1);	// start the first timer
		// https://www.opengl.org/resources/libraries/glut/spec3/node64.html
		// http://blog.csdn.net/wl_soft50/article/details/7802810
	glutMainLoop();
	return 0;
}



/// initial opengl
void init(void)
{
	/// light parameter
	GLfloat  ambientLight[] = { 0.1, 0.1, 0.1, 1.0f };
	GLfloat  diffuseLight[] = { 0.8, 0.8, 0.8, 1.0f };
	GLfloat  specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat  specref[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat  dir[] = { 0.0f, 0.0f, -1.0f };
	GLfloat  pos[] = { -200.0f, -30.0f, 150.0f, 1.0f };

	/// enabke used attribute
	glEnable(GL_DEPTH_TEST);		// so it will draw right in the space
	glEnable(GL_CULL_FACE);			// cull the face that not face to you https://learnopengl-cn.readthedocs.io/zh/latest/04%20Advanced%20OpenGL/04%20Face%20culling/
	glEnable(GL_NORMALIZE);			// then it will be like in 3D place
	glEnable(GL_LIGHTING);			// or it will be too dark
	glEnable(GL_COLOR_MATERIAL);	// Enable color tracking

	/// Setup and enable light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100);
	glEnable(GL_LIGHT0);

	/// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);	// ambient, diffuse,
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);				// specular
	glMateriali(GL_FRONT, GL_SHININESS, 128);


	//glGenTextures(2, &texture[0]);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearColor(129.0 / 256, 159.0 / 256, 195.0 / 256, 1.0f);
}

/// binding function
void bindingMenu(void)
{
	// binding menu
	int attributeMenu = glutCreateMenu(ATmenu);
	glutAddMenuEntry("Speed up   (P^)", GLUT_KEY_PAGE_UP);
	glutAddMenuEntry("Speed down (Pv)", GLUT_KEY_PAGE_DOWN);
	glutAddMenuEntry("Robot x+   (>)", GLUT_KEY_RIGHT);
	glutAddMenuEntry("Robot x-   (<)", GLUT_KEY_LEFT);
	glutAddMenuEntry("Robot y+   (^)", GLUT_KEY_UP);
	glutAddMenuEntry("Robot y-   (V)", GLUT_KEY_DOWN);
	glutAddMenuEntry("Show Ear   (F1)", GLUT_KEY_F1);
	glutAddMenuEntry("Eye Light  (F2)", GLUT_KEY_F2);
	glutAddMenuEntry("Change Skin(F3)", GLUT_KEY_F3);

	int adjustMenu = glutCreateMenu(Amenu);
	glutAddMenuEntry("Float Dress(Z)", KEY_Z);
	glutAddMenuEntry("Head Nod   (X)", KEY_X);
	glutAddMenuEntry("Head Shake (C)", KEY_C);
	glutAddMenuEntry("Rotate Ear (V)", KEY_V);
	glutAddMenuEntry("I Watch You(B)", KEY_B);

	int gestureMenu = glutCreateMenu(Amenu);
	glutAddMenuEntry("Idle       ( )", KEY_SPACE);
	glutAddMenuEntry("Pose       (A)", KEY_A);
	glutAddMenuEntry("Sit        (S)", KEY_S);

	int actionMenu = glutCreateMenu(Amenu);
	glutAddMenuEntry("Wave hand  (Q)", KEY_Q);
	glutAddMenuEntry("Walk       (W)", KEY_W);
	glutAddMenuEntry("Jump       (E)", KEY_E);

	int serialMenu = glutCreateMenu(Amenu);
	glutAddMenuEntry("Fly        (0)", KEY_0);
	glutAddMenuEntry("Dance      (1)", KEY_1);
	glutAddMenuEntry("Space walk (2)", KEY_2);
	glutAddMenuEntry("Shy        (3)", KEY_3);
	glutAddMenuEntry("Rolling    (4)", KEY_4);
	glutAddMenuEntry("Big Wheel  (5)", KEY_5);

	glutCreateMenu(Amenu);
	glutAddSubMenu("Attribute", attributeMenu);
	glutAddSubMenu("Gesture", gestureMenu);
	glutAddSubMenu("Action", actionMenu);
	glutAddSubMenu("Serial", serialMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void Amenu(int selection){
	// https://www.opengl.org/resources/libraries/glut/spec3/node54.html
	action = selection;
	bb = true;
	glutPostRedisplay();	// https://www.opengl.org/discussion_boards/showthread.php/168717-I-dont-understand-what-glutPostRedisplay()-does
}
void ATmenu(int selection)
{
	attri = selection;
	aa = true;
	glutPostRedisplay();
}
void sKeyin(int key, int x, int y) {
	// switch special key situation
	attri = key;
	aa = true;
}
void nkeyin(unsigned char key, int x, int y)
{
	bb = true;
	// change character from lower to upper case
	if ('a' <= key && key <= 'z')
		key -= 32;

	// switch normal key situation
	switch (key)
	{
	case '\033':	exit(0);		break;	// ESC
	case ' ':	action = KEY_SPACE;	break;

	case '0':	action = KEY_0;		break;
	case '1':	action = KEY_1;		break;
	case '2':	action = KEY_2;		break;
	case '3':	action = KEY_3;		break;
	case '4':	action = KEY_4;		break;
	case '5':	action = KEY_5;		break;
	case '6':	action = KEY_6;		break;
	case '7':	action = KEY_7;		break;
	case '8':	action = KEY_8;		break;
	case '9':	action = KEY_9;		break;

	case 'A':	action = KEY_A;		break;
	case 'B':	action = KEY_B;		break;
	case 'C':	action = KEY_C;		break;
	case 'D':	action = KEY_D;		break;
	case 'E':	action = KEY_E;		break;
	case 'F':	action = KEY_F;		break;
	case 'G':	action = KEY_G;		break;
	case 'H':	action = KEY_H;		break;
	case 'I':	action = KEY_I;		break;
	case 'J':	action = KEY_J;		break;
	case 'K':	action = KEY_K;		break;
	case 'L':	action = KEY_L;		break;
	case 'M':	action = KEY_M;		break;
	case 'N':	action = KEY_N;		break;
	case 'O':	action = KEY_O;		break;
	case 'P':	action = KEY_P;		break;
	case 'Q':	action = KEY_Q;		break;
	case 'R':	action = KEY_R;		break;
	case 'S':	action = KEY_S;		break;
	case 'T':	action = KEY_T;		break;
	case 'U':	action = KEY_U;		break;
	case 'V':	action = KEY_V;		break;
	case 'W':	action = KEY_W;		break;
	case 'X':	action = KEY_X;		break;
	case 'Y':	action = KEY_Y;		break;
	case 'Z':	action = KEY_Z;		break;

	default:	action = IDLE;		break;
	}
}

void reshape(int w, int h)
{
	WinWidth = w;
	WinHeight = h;
	GLfloat aspect;
	aspect = (GLfloat)w / (GLfloat)h;
	//glViewport(0,0,(GLsizei)w,(GLsizei)h);
	if (aspect > 1.0f)
		glViewport((w - h) / 2.0f, 0, (GLsizei)h, (GLsizei)h);
	else
		glViewport(0, (h - w) / 2.0f, (GLsizei)w, (GLsizei)w);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 1.0f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(inner_mode);

	//Viewport 1
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glViewport(0,0,WinWidth,WinHeight);			
	//gluPerspective(45.0, 1.0, 1.0, 400);// fov, aspect ratio ,near,far
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	draw();

	//Viewport 2
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glViewport(600,0,600,600);
	//gluPerspective(45.0, 1.0, 1.0, 400);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(100, 0, -10, 0, 0, -200, 0.0, 1.0, 0.0);
	//draw();

	glutSwapBuffers();
}

/// timer function and binding gesture function
void timerFunction(int value)
{
	frame_counter++;
	switch (action)
	{
	case IDLE:		idle();			break;
	case KEY_0:		fly();			break;
	case KEY_1:		dance();		break;
	case KEY_2:		around();		break;
	case KEY_3:		shy();			break;
	case KEY_4:		roll();			break;
	case KEY_5:		uom();			break;
	case KEY_6:						break;
	case KEY_7:						break;
	case KEY_8:						break;
	case KEY_9:						break;

	case KEY_Z:		dress();		break;
	case KEY_X:		hnod();			break;
	case KEY_C:		hno();			break;
	case KEY_V:		rotEar();		break;
	case KEY_B:		hi();			break;
	case KEY_N:						break;
	case KEY_M:						break;

	case KEY_A:		pose();			break;
	case KEY_S:		sit();			break;
	case KEY_D:						break;
	case KEY_F:						break;
	case KEY_G:						break;
	case KEY_H:						break;
	case KEY_J:						break;
	case KEY_K:						break;
	case KEY_L:						break;

	case KEY_Q:		wave();			break;
	case KEY_W:		walk();			break;
	case KEY_E:		jump();			break;
	case KEY_R:						break;
	case KEY_T:						break;
	case KEY_Y:						break;
	case KEY_U:						break;
	case KEY_I:						break;
	case KEY_O:						break;
	case KEY_P:						break;

	case KEY_SPACE:	idle();			break;
	case KEY_ENTER:					break;
	default:		idle();			break;
	}
	switch (attri) {
	case GLUT_KEY_UP:			x_plus();		break;
	case GLUT_KEY_DOWN:			x_minus();		break;
	case GLUT_KEY_LEFT:			y_plus();		break;
	case GLUT_KEY_RIGHT:		y_minus();		break;
	case GLUT_KEY_PAGE_UP:		speed_up();		break;
	case GLUT_KEY_PAGE_DOWN:	speed_down();	break;
	case GLUT_KEY_HOME:							break;
	case GLUT_KEY_END:							break;
	case GLUT_KEY_DELETE:						break;
	case GLUT_KEY_INSERT:						break;
	case GLUT_KEY_F1:			ear();			break;
	case GLUT_KEY_F2:			light();		break;
	case GLUT_KEY_F3:			skin();			break;
	case GLUT_KEY_F4:							break;
	case GLUT_KEY_F5:							break;
	case GLUT_KEY_F6:							break;
	case GLUT_KEY_F7:							break;
	case GLUT_KEY_F8:							break;
	case GLUT_KEY_F9:							break;
	case GLUT_KEY_F10:							break;
	case GLUT_KEY_F11:							break;
	case GLUT_KEY_F12:							break;
	default:									break;
	}

	glutPostRedisplay();				// make a flag,
										// it will draw afer next glutMainLoop
	glutTimerFunc(frame_update, timerFunction, 1);	// we want to start another timer
}



/// attribute
void speed_up(void)
{
	if (aa)
		frame_update = frame_update == 1 ? 1 : frame_update - 1;
	aa = false;
}
void speed_down(void)
{
	if (aa)
		frame_update = frame_update == 10 ? 10 : frame_update + 1;
	aa = false;
}
void x_plus(void){
	if(aa)
		wx--;
	aa = false;
}
void x_minus(void){
	if (aa)
		wx++;
	aa = false;
}
void y_plus(void){
	if (aa)
		wy--;
	aa = false;
}
void y_minus(void){
	if (aa)
		wy++;
	aa = false;
}
void z_plus(void) {
	if (aa)
		wz--;
	aa = false;
}
void z_minus(void) {
	if (aa)
		wz++;
	aa = false;
}
void light(void)
{
	if (aa)
		eyelight = !eyelight;
	aa = false;
}
void skin(void)
{
	if (aa)
		who = who == 2 ? 0 : who + 1;
	aa = false;
}
void ear(void)
{
	static bool dir = true;
	const float angleH = -32.0f / 3;
	const float angleL = 0;

	if (aa)
		dir = !dir;
	aa = false;

	if(dir)
		oneWay(angleH, earHight);
	else
		oneWay(angleL, earHight);

	glutPostRedisplay();
}


/// adjustMenu
void dress(void)
{
	static bool dir = true;
	const float angleMax = 60;
	float angleMin = max(fabs(legLXAngle) + unit, fabs(legRXAngle) + unit);

	cycle(dir, angleMax, angleMin, dressAngle);
	glutPostRedisplay();
}
void hnod(void)
{
	static bool dir = true;
	const float angleMax = 10;
	const float angleMin = -10;

	cycle(dir, angleMax, angleMin, headXAngle);

	glutPostRedisplay();
}
void hno(void)
{
	static bool dir = true;
	const float angleMax = 30;
	const float angleMin = -30;

	cycle(dir, angleMax, angleMin, headYAngle);

	glutPostRedisplay();
}
void rotEar(void)
{
	static bool dir = true;
	const float angleMax = 45;
	const float angleMin = -25;

	cycle(dir, angleMax, angleMin, earYAngle);

	glutPostRedisplay();
}
void hi(void)
{
	oneWay(-wx + 5, headXAngle);
	oneWay(-wy, headYAngle);
}

// gestureMenu
bool idle(void)
{
	static bool fin = false;
	if (bb)
		fin = false;

	if (bb || !fin) {
		bool ans = true;
		ans &= oneWay(25, dressAngle);
		ans &= oneWay(10, armRXAngle);
		ans &= oneWay(10, armLXAngle);
		ans &= oneWay(25, armRZAngle);
		ans &= oneWay(25, armLZAngle);
		ans &= oneWay(0, legRXAngle);
		ans &= oneWay(0, legLXAngle);
		ans &= oneWay(0, legRZAngle);
		ans &= oneWay(0, legLZAngle);
		ans &= oneWay(0, earYAngle);
		ans &= oneWay(0, earHight);
		ans &= oneWay(0, headXAngle);
		ans &= oneWay(0, headYAngle);
		ans &= oneWay(25, wx);
		ans &= oneWay(25, wy);
		ans &= oneWay(0, wz);
		ans &= oneWay(0, posx);
		ans &= oneWay(0, posy);
		ans &= oneWay(0, posz);
		fin = ans;
	}

	glutPostRedisplay();
	bb = false;
	return fin;
}
void pose(void)
{
	if (idle()) {
		oneWay(10, legLZAngle);
		oneWay(-1, posx);
		oneWay(25, wx);
		oneWay(120, armLZAngle);
		oneWay(120, armRZAngle);
	}
}
void sit(void)
{
	if (idle()) {
		oneWay(-y / 2 + 5, posy);
		oneWay(50 + unit, dressAngle);
		oneWay(50, legRXAngle);
		oneWay(50, legLXAngle);
	}
	glutPostRedisplay();
}

// actionMenu
void wave(void)
{
	static bool dir = true;
	const float angleMax = 120;
	const float angleMin = 100;

	oneWay(25, armRZAngle);
	oneWay(0, armRXAngle);
	oneWay(0, armLXAngle);
	oneWay(0, legRXAngle);
	oneWay(0, legLXAngle);
	cycle(dir, angleMax, angleMin, armLZAngle);

	glutPostRedisplay();
}
void walk(void)
{
	static bool dir = true;
	const float angleMax = 50;
	const float angleMin = -50;

	if (idle()) {
		oneWay(angleMax + unit, dressAngle);
		oneWay(25, armRZAngle);
		oneWay(25, armLZAngle);
		cycle(dir, angleMax, angleMin, legRXAngle);
		cycle(!dir, legLXAngle);
		cycle(dir, armRXAngle);
		cycle(!dir, armLXAngle);
	}

	glutPostRedisplay();
}
void jump(void)
{
	static bool dir = true;
	static bool dir2 = true;
	const float angleMax = 15;
	const float angleMin = 0;
	const float anglePosMax = 0;
	const float anglePosMin = -10;

	if (idle()) {
		cycle(dir, angleMax, angleMin, legRXAngle);
		cycle(dir2, angleMax, angleMin, legLXAngle);
		cycle(dir, posy);
	}
	glutPostRedisplay();
}

// serialMenu
void fly(void)
{
	if (idle()) {
		bool fin = true;
		fin &= oneWay(90, armLZAngle);
		fin &= oneWay(90, armRZAngle);

		if (fin) {
			wy = wy >= 360 ? wy - 360 : wy + 1;
			posy = posy > 150 ? 150 : posy + unit;
		}
	}
	glutPostRedisplay();
}
void dance(void)
{
	static bool dir0 = true;
	static bool dir = true;
	static bool dir2 = true;
	const float angleArmMax = 120;
	const float angleArmMin = 60;
	const float angleLegMax = 10;
	const float angleLegMin = 0;

	if (idle()) {
		cycle(dir0, angleLegMax, angleLegMin, legLZAngle);
		cycle(dir, angleArmMax, angleArmMin, armLZAngle);
		cycle(dir2, angleArmMax, angleArmMin, armRZAngle);
		wy += 2 * sin(0.01*frame_counter);
	}
	glutPostRedisplay();
}
void around(void)
{
	if (idle()) {
		bool fin = true;
		fin &= oneWay(0, wy);
		fin &= oneWay(0, wz);

		if (fin) {
			static bool dir = true;
			const float angleMax = 50;
			const float angleMin = -50;

			oneWay(angleMax + unit, dressAngle);
			oneWay(25, armRZAngle);
			oneWay(25, armLZAngle);
			cycle(dir, angleMax, angleMin, legRXAngle);
			cycle(!dir, legLXAngle);
			cycle(dir, armRXAngle);
			cycle(!dir, armLXAngle);
			wx = wx <= 0 ? wx + 360 : wx - 0.12;
		}
	}

	glutPostRedisplay();
}
void shy(void)
{
	if (idle()) {
		bool fin = true;
		fin &= oneWay(120, armLXAngle);
		fin &= oneWay(120, armRXAngle);
		fin &= oneWay(-10, armLZAngle);
		fin &= oneWay(-10, armRZAngle);
		fin &= oneWay(10, headXAngle);

		if (fin) {
			static bool dir = false;
			const float angleMax = 25;
			const float angleMin = -25;
			cycle(dir, angleMax, angleMin, headYAngle);
		}
	}

	glutPostRedisplay();
}
void roll(void)
{
	static bool fin = false;
	if (bb)
		fin = false;

	if (bb || !fin) {
		bool ans = true;
		ans &= oneWay(10, dressAngle);
		ans &= oneWay(0, armRXAngle);
		ans &= oneWay(0, armLXAngle);
		ans &= oneWay(0, armRZAngle);
		ans &= oneWay(0, armLZAngle);
		ans &= oneWay(0, legRXAngle);
		ans &= oneWay(0, legLXAngle);
		ans &= oneWay(0, legRZAngle);
		ans &= oneWay(0, legLZAngle);
		ans &= oneWay(0, earYAngle);
		ans &= oneWay(0, earHight);
		ans &= oneWay(0, headXAngle);
		ans &= oneWay(0, headYAngle);
		ans &= oneWay(0, wx);
		ans &= oneWay(0, wy);
		ans &= oneWay(-90, wz);
		ans &= oneWay(0, posx);
		ans &= oneWay(0, posy);
		ans &= oneWay(-60, posz);
		fin = ans;
	}
	else if (fin) {
		wx -= 3 * sin(0.01*frame_counter);
		posz -= 1.2*sin(0.01*frame_counter);
	}

	glutPostRedisplay();
	bb = false;
}
void uom(void)
{
	wx = wx >= 360 ? wx - 360 : wx + 0.1;
	wy = wy >= 360 ? wy - 360 : wy + 0.23;
	wz = wz >= 360 ? wz - 360 : wz + 0.31;
	glutPostRedisplay();
}


/// tool to set active
bool oneWay(const float convergence, float &target){
	if (fabs(convergence - target) < unit)
		return true;
	else if(convergence > target)
		target += unit;
	else if (convergence < target)
		target -= unit;
	return false;
}
void cycle(bool &dir, const float max, const float min, float &target) {
	if (target < max - unit && dir)
		target += unit;
	else if (target > min + unit && !dir)
		target -= unit;
	else
		dir = !dir;
}
void cycle(bool dir, float &target) {
	if (dir)
		target += unit;
	else
		target -= unit;
}

/// drawing function (called by display function)
void draw(void)
{
	glTranslatef(0, 0, -200);			// move original point in front of the camera
	draw_Danboard();
}
void draw_Danboard(void) {
	/// Coordinate
		// y ^
		// x >
		// z *

	/// Source
		// geometry object rendering https://www.opengl.org/resources/libraries/glut/spec3/node80.html
		// glBegin https://www.opengl.org/sdk/docs/man2/xhtml/glBegin.xml
		// simple shape application http://www.cnblogs.com/tornadomeet/archive/2012/08/23/2652592.html

	/// variable (temp store data)
	const float offset = 0.005;

	float p_x, p_y, p_z;
	float pt_x, pt_y, pt_z;

	// draw floor
	//glPushMatrix(); {
	//	glTranslatef(0, -50, 0);
	//	glBegin(GL_QUADS); {
	//		glVertex3f(5, 0, 5);
	//		glVertex3f(5, 0, -5);
	//		glVertex3f(-5, 0, -5);
	//		glVertex3f(-5, 0, 5);
	//	}glEnd();
	//}glPopMatrix();

	// watch turm
	glTranslatef(posx, posy, posz);
	glRotatef(wx, 1, 0, 0);
	glRotatef(wy, 0, 1, 0);
	glRotatef(wz, 0, 0, 1);




	// draw body
	glPushMatrix(); {
		glScalef(x, y*(pt_y = 0.8), z);	// (width, hight, deep (must)= width)
		glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
		glutSolidCube(1);
	}glPopMatrix();

	/// draw coin
	glPushMatrix(); {
		glTranslatef(9, 11, z/2 + unit);
		glColor3ub(0xe8, 0xd8, 0x51);
		glScalef(3.7, 3.7, 0.8);
		glutSolidSphere(1, 30, 30);
	}glPopMatrix();

	/// draw dress
	glPushMatrix(); {
		// p_xyz are scale of body, pt_y is percent of body(v.s. dress)
		float lost = 1 - pt_y;
		glTranslatef(0, -0.5*y*pt_y, 0);
		glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
		for (int n = 0; n < 4; n++) {			// front, left, back, right
			glPushMatrix(); {
				glTranslatef(0, 0, z / 2 + offset);
				glRotatef(-dressAngle, 1, 0, 0);
				glScalef(x, y*lost*2, 0.005*z);	// (width, hight, deep)
				glutSolidCube(1);
			}glPopMatrix();
			glRotatef(90, 0, 1, 0);
		}
	}glPopMatrix();

	/// draw head
	glPushMatrix(); {
		// p_xyz are scale of body, p_y whatever
		glTranslatef(0, y*pt_y/2 + (p_y=15), 0);
		glRotatef(headYAngle, 0, 1, 0);
		glRotatef(headXAngle, 1, 0, 0);
		glPushMatrix(); {
			glScalef(p_x = 45, p_y = 2*p_y, p_z = 40);	// (width, hight, deep)
			glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
			glutSolidCube(1);
		}glPopMatrix();	// head
		glPushMatrix(); {
			glTranslated(0, -0.5386f*p_y / 2, p_z / 2 + offset);
			glColor3ub(0x00, 0x00, 0x00);		// black color
			glBegin(GL_TRIANGLES); {
				glVertex3f(5, 0, 0);
				glVertex3f(0, 5, 0);
				glVertex3f(-5, 0, 0);
			}glEnd();
		}glPopMatrix();	// mouth
		glPushMatrix(); {
			if (eyelight)
				glColor3ub(eye_color[who][0], eye_color[who][1], eye_color[who][2]);
			else
				glColor3ub(eye_color[who][3], eye_color[who][4], eye_color[who][5]);
			glTranslated(0.3278*p_x, 0.23f*p_y / 2, p_z / 2 + offset);
			e_glCircle(0.16*p_y / 2);
		}glPopMatrix();	// left eye
		glPushMatrix(); {
			if (eyelight)
				glColor3ub(eye_color[who][0], eye_color[who][1], eye_color[who][2]);
			else
				glColor3ub(eye_color[who][3], eye_color[who][4], eye_color[who][5]);
			glTranslated(-0.3278*p_x, 0.23f*p_y / 2, p_z / 2 + offset);
			e_glCircle(0.16*p_y / 2);
		}glPopMatrix();	// right eye
		glPushMatrix(); {
			glTranslatef(p_x = 10, p_y/2 + (p_z =8.0f/3), 0);
			glTranslatef(0, earHight, 0);
			glRotatef(90, 0, 0, 1);
			glRotatef(30, 1, 0, 0);
			glRotatef(earYAngle, 1, 0, 0);
			glScalef(p_z * 3, p_z * 3, p_z * 3);
			glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
			glutSolidTetrahedron();
		}glPopMatrix();	// left ear
		glPushMatrix(); {
			glTranslatef(-p_x, p_y / 2 + p_z, 0);
			glTranslatef(0, earHight, 0);
			glRotatef(90, 0, 0, 1);
			glRotatef(30, 1, 0, 0);
			glRotatef(-earYAngle, 1, 0, 0);
			glScalef(p_z * 3, p_z * 3, p_z * 3);
			glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
			glutSolidTetrahedron();
		}glPopMatrix();	// right ear
	}glPopMatrix();	// draw head

	/// draw left arm
	glPushMatrix(); {
		// draw left shoulder part to body
		glTranslatef(x / 2, (y*pt_y) / 2 - (p_x = 0.2*x)-4, 0);
		glRotatef(-armRXAngle, 1, 0, 0);
		glPushMatrix(); {
			glTranslatef(0, 0, -0.3333*x / 2);
			glScalef(1.3336*p_x, p_x, 0.3333*x);	// (width, hight, deep)
			glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
			glutSolidCylinder(1, 1, 30, 30);
		}glPopMatrix();

		// draw left shoulder part to arm
		glTranslatef(p_x, 0, 0);
		glRotatef(armRZAngle, 0, 0, 1);
		glPushMatrix(); {
			glTranslatef(0, 0, -0.3333*x / 2);
			glScalef(p_x, p_x, 0.3333*x);			// (width, hight, deep)
			glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
			glutSolidCylinder(1, 1, 30, 30);
		}glPopMatrix();

		// draw left arm
		glTranslatef(0.25*p_x, -(p_y = 0.65*y) / 2, 0);
		glPushMatrix(); {
			glScalef(0.3333*x, p_y, 0.3333*x);		// (width, hight, deep)
			glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
			glutSolidCube(1);
		}glPopMatrix();
	}glPopMatrix();

	/// draw right arm
	glPushMatrix(); {
		// draw right shoulder part to body
		glTranslatef(-x / 2, (y*pt_y) / 2 - (p_x = 0.2*x)-4, 0);
		glRotatef(-armLXAngle, 1, 0, 0);
		glPushMatrix(); {
			glTranslatef(0, 0, -0.3333*x / 2);
			glScalef(1.3336*p_x, p_x, 0.3333*x);	// (width, hight, deep)
			glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
			glutSolidCylinder(1, 1, 30, 30);
		}glPopMatrix();

		// draw right shoulder part to arm
		glTranslatef(-p_x, 0, 0);
		glRotatef(-armLZAngle, 0, 0, 1);
		glPushMatrix(); {
			glTranslatef(0, 0, -0.3333*x / 2);
			glScalef(p_x, p_x, 0.3333*x);			// (width, hight, deep)
			glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
			glutSolidCylinder(1, 1, 30, 30);
		}glPopMatrix();

		// draw right arm
		glTranslatef(-0.25*p_x, -(p_y = 0.65*y) / 2, 0);
		glPushMatrix(); {
			glRotatef(0, 0, 0, 0);
			glScalef(0.3333*x, p_y, 0.3333*x);		// (width, hight, deep)
			glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
			glutSolidCube(1);
		}glPopMatrix();
	}glPopMatrix();

	/// draw left leg
	glPushMatrix(); {
		/// draw left hip joint
		glTranslatef(0, -y / 2, 0);
		glRotatef(legLZAngle, 0, 0, 1);
		glRotatef(-legLXAngle, 1, 0, 0);
		glPushMatrix(); {
			glTranslatef(0.05*x, 0, 0);
			glScalef(0.4*x, 0.85*z / 2, 0.85*z / 2);	// (width, hight, deep)
			glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
			glRotatef(90, 0, 1, 0);
			glutSolidCylinder(1, 1, 30, 30);
		}glPopMatrix();

		/// draw left leg
		glPushMatrix(); {
			glTranslatef(0.5*x / 2, -0.85*y / 2, 0);
			glScalef(0.4*x, 0.85*y, 0.85*z);		// (width, hight, deep)
			glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
			glutSolidCube(1);
		}glPopMatrix();
	}glPopMatrix();

	/// draw right leg
	glPushMatrix(); {
		/// draw right hip joint
		glTranslatef(-0.4*x, -y / 2, 0);
		glRotatef(-legRZAngle, 0, 0, 1);
		glRotatef(-legRXAngle, 1, 0, 0);
		glPushMatrix(); {
			glTranslatef(-0.05*x, 0, 0);
			glScalef(0.4*x, 0.85*z / 2, 0.85*z / 2);// (width, hight, deep)
			glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
			glRotatef(90, 0, 1, 0);
			glutSolidCylinder(1, 1, 30, 30);
		}glPopMatrix();

		/// draw right leg
		glPushMatrix(); {
			glTranslatef(0.3*x / 2, -0.85*y / 2, 0);
			glScalef(0.4*x, 0.85*y, 0.85*z);		// (width, hight, deep)
			glColor3ub(skin_color[who][0], skin_color[who][1], skin_color[who][2]);
			glutSolidCube(1);
		}glPopMatrix();
	}glPopMatrix();

}

// draw a pie (because opengl didn't offerd a function to draw)
void e_glCircle(double radius) {
#ifndef GL_PI
#define GL_PI 3.1415926
#endif GL_PI

	glPushMatrix(); {
		glBegin(GL_TRIANGLE_FAN); {
			for (int i = 0; i < 100; i++) {
				double angle = 2 * GL_PI*i / 100;
				glVertex3d(radius * cos(angle), radius * sin(angle), 0);
			}
		}glEnd();
	}glPopMatrix();
}

