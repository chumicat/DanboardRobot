#pragma once
#ifndef _HAND
#define _HAND


enum {	KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, 
		KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
		KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
		KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_SPACE, KEY_ENTER, IDLE};
/// parameter
float dressAngle = 10;		// unit ~ 60
float headYAngle = 0;		// -90 ~ 90
float headXAngle = 0;		// -90 ~ 90
float armRXAngle = 0;		// -50 ~ 50?
float armLXAngle = 0;		// -50 ~ 50?
float armRZAngle = 0;		// 0 ~ 120
float armLZAngle = 0;		// 0 ~ 120
float legRXAngle = 0;		// -50 ~ 50
float legLXAngle = 0;		// -50 ~ 50
float legRZAngle = 0;		// 0 ~ 10
float legLZAngle = 0;		// 0
float earYAngle = 0;		// -45 ~ 45
float earHight = 0;			// -32.0f/3 ~ 0
const float unit = 0.2;
float x = 28.5714;			// body scale
float y = 44.3290;
float z = 28.5714;
float wx = 25;				// camera rotate angle
float wy = 25;
float wz = 0;
float posx = 0;				// robot offset in space
float posy = 0;
float posz = 0;
int frame_update = 5;
long long int frame_counter = 0;
bool eyelight = false;
int who = 0;
const GLbyte skin_color[][3] = { { 0xdc, 0xd0, 0x9c },{ 0x31, 0x33, 0x33 }, {0xff, 0xff, 0xff} };
const GLbyte eye_color[][6] = { { 0xf7, 0xf5, 0x28, 0xff, 0xff, 0xff }, {0x28, 0xe9, 0xf7, 0x39, 0x66, 0x6b} ,{ 0xf7, 0xf5, 0x28, 0x00, 0x00, 0x00 } };

int action = IDLE;	// select which pos to do
int attri = 0;		// attribute type
bool aa = false;	// attri_active
bool bb = false;	// action_active

// setting
const static GLuint inner_mode = GL_SMOOTH;
static int WinWidth = 800;
static int WinHeight = 600;

// initial opengl
void init(void);

/// binding function
void bindingMenu(void);							// define menu structure and binding with function "menu"
void Amenu(int selection);						// switch gesture with right buttom (action)
void ATmenu(int selection);						// switch gesture with right buttom (attribute)
void sKeyin(int key, int x, int y);				// switch gesture with keyboard special input
void nkeyin(unsigned char key, int x, int y);	// switch gesture with keyboard normal input
void reshape(int w, int h);						// called when resize the window
void display(void);								// called when display
void timerFunction(int value);					// execute action with menu

/// attribute
void speed_up(void);
void speed_down(void);
void x_plus(void);
void x_minus(void);
void y_plus(void);
void y_minus(void);
void z_plus(void);
void z_minus(void);
void light(void);
void skin(void);
void ear(void);


/// adjustMenu
void dress(void);
void hnod(void);
void hno(void);
void rotEar(void);
void hi(void);

// gestureMenu
bool idle(void);
void pose(void);
void sit(void);

// actionMenu
void wave(void);
void walk(void);
void jump(void);

// serialMenu
void fly(void);
void dance(void);
void around(void);
void shy(void);
void roll(void);
void uom(void);




// tool to set active
bool oneWay(const float convergence, float &target);
void cycle(bool &dir, const float max, const float min, float &target);
void cycle(bool dir, float &target);

/// drawing function (called by display function)
void draw(void);
void draw_Danboard(void);
void e_glCircle(double radius);

#endif _HAND