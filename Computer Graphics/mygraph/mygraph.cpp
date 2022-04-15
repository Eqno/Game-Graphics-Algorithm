#define ll long long
#define absx (x<0?-x:x)
#define swapmn (m^=n^=m^=n)
#define maxmn (m>n?m:n)
#define minmn (m>n?n:m)

const int hashSeed = 1024;
const int INF = 0x3f3f3f3f;

ll _abs(ll x) { return absx; }
int _abs(int x) { return absx; }
double _abs(double x) { return absx; }
void _swap(ll &m, ll &n) { swapmn; }
void _swap(int &m, int &n) { swapmn; }
void _swap(double &m, double &n) { double t=m; m=n, n=t; }
ll _max(ll m, ll n) { return maxmn; }
int _max(int m, int n) { return maxmn; }
double _max(double m, double n) { return maxmn; }
ll _max(ll a, ll b, ll c) { return _max(a, _max(b, c)); }
int _max(int a, int b, int c) { return _max(a, _max(b, c)); }
double _max(double a, double b, double c) { return _max(a, _max(b, c)); }
ll _min(ll m, ll n) { return minmn; }
int _min(int m, int n) { return minmn; }
double _min(double m, double n) { return minmn; }
ll _min(ll a, ll b, ll c) { return _min(a, _min(b, c)); }
int _min(int a, int b, int c) { return _min(a, _min(b, c)); }
double _min(double a, double b, double c) { return _min(a, _min(b, c)); }

struct V2d { int x, y; };
struct V3d { int x, y, z; };
struct L2d { V2d a, b; };
struct L3d { V3d a, b; };

#include <GL/glut.h>
void draw();
void reshape(int x, int y)
{
	int dis = x > y ? y : x;
	glViewport(0, 0, dis, dis);
}
void renderScene()
{
	static float rotate = 0;
	static int times = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    times++;
    if(times > 1) times = 0;
    if(times % 1 == 0) rotate += 0.3;
    glRotatef(rotate, 0, 1, 0);
    glRotatef(rotate, 1, 0, 0);
    draw();
	glLoadIdentity();
    glutSwapBuffers();
}
void drawing()
{
	draw();
	glutSwapBuffers();
}
int SIZEP, OFFSETX, OFFSETY, OFFSETZ;
void myinit2d(int argc, char **argv,
	int sizex, int sizey, int sizep,
	int posx, int posy, int offsetx, int offsety,
	void (* draw)(), char *name)
{
	SIZEP = sizep, OFFSETX = offsetx, OFFSETY = offsety;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(sizex, sizey);
	glutInitWindowPosition(posx, posy);
	glutCreateWindow(name);
	glutDisplayFunc(drawing);
	glutReshapeFunc(reshape);
    glClear(GL_COLOR_BUFFER_BIT);
	glutMainLoop();
}
void myinit3d(int argc, char **argv,
	int sizex, int sizey, int sizep, int posx, int posy,
	int offsetx, int offsety, int offsetz, 
	void (* draw)(), char *name)
{
	SIZEP = sizep, OFFSETX = offsetx, OFFSETY = offsety, OFFSETZ = offsetz;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(sizex, sizey);
	glutInitWindowPosition(posx, posy);
	glutCreateWindow(name);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

enum { WHITE, YELLOW, RED, GREEN, BLACK };
void putpixel(int x, int y, int color)
{
	if (color == WHITE) glColor3d(1, 1, 1);
	if (color == YELLOW) glColor3d(1, 1, 0);
	if (color == RED) glColor3d(1, 0, 0);
	if (color == GREEN) glColor3d(0, 1, 0);
	if (color == BLACK) glColor3d(0, 0, 0);
	glBegin(GL_POINTS);
	glVertex2d((x+OFFSETX)/(double)SIZEP,
		(y+OFFSETY)/(double)SIZEP);
	glEnd();
	glFlush();
}
void putpixel(int x, int y, int z, int color)
{
	if (color == WHITE) glColor3d(1, 1, 1);
	if (color == YELLOW) glColor3d(1, 1, 0);
	if (color == RED) glColor3d(1, 0, 0);
	if (color == GREEN) glColor3d(0, 1, 0);
	if (color == BLACK) glColor3d(0, 0, 0);
	glBegin(GL_POINTS);
	glVertex3d((x+OFFSETX)/(double)SIZEP,
		(y+OFFSETY)/(double)SIZEP, (z+OFFSETZ)/(double)SIZEP);
	glEnd();
	glFlush();
}

#include <cmath>
#include <stack>
#include <vector>
#include <gl/gl.h>
#include <utility>
#include <wingdi.h>
#include <winreg.h>
#include <iostream>
#include <gl/glu.h>
#include <windows.h>
#include <unordered_set>
#include <gl/freeglut_std.h>
const double pi = 4*atan(1);

#include "./draw/line2d/bresenhamEx.cpp"
#include "./draw/line3d/DDA.cpp"
#include "./draw/polygon.cpp"
#include "./draw/polyhedron.cpp"
// #include "./fill/scanner.cpp"
#include "./tran/plane.cpp"
#include "./tran/solid.cpp"
#include "./observe/crop/line/liangBarsky.cpp"
#include "./draw/circle/bresenham.cpp"
#include "./draw/ellipse/bresenham.cpp"
#include "./draw/curve2d/Bezier.cpp"
#include "./get/line2d/bresenhamEx.cpp"
#include "./get/polygon/border.cpp"
#include "./fill/inner.cpp"
#include "./fill/border.cpp"