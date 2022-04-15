#include <iostream>
#include <GL/glut.h>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <utility>
#include <cmath>
#include <random>
using namespace std;

#define WHITE 1,1,1
#define RED 1,0,0
#define YELLOW 1,1,0
#define GREEN 0,1,0

#define ACTCOLOR WHITE
#define BALCOLOR GREEN
#define WINCOLOR WHITE
#define LOSCOLOR RED

#define RAND (0.5*rand()/double(RAND_MAX)+0.25)

unsigned int            W = 1600, H = 900;  // 窗口大小。
double       		    WINRAT = 0.8, WINWIDTH = W*WINRAT, WINHEIGHT = H*WINRAT;  // 场景大小。
const unsigned int      BALLSPEED = 20, BALLID = 0,
                        BALLNUM = 10, BALLACC = 50;
const double 		    BALLRAD = 30, BALLSTEP = 20,
                        ACTICX = -500, ACTICY = 0,  // 初始位置。
                        ACTIVX = 10, ACTIVY = 0,  // 初始速度。
                        BALICX = 300, BALICY = 0,
                        BALIVX = 0, BALIVY = 0;

vector <double> scene({-WINWIDTH, -WINHEIGHT, -WINWIDTH,
	WINHEIGHT, WINWIDTH, WINHEIGHT, WINWIDTH, -WINHEIGHT});
struct Ball
{
    // x, y -> center; vx, vy -> velocity; a, b, c -> color;
    double x, y, vx, vy, a, b, c;
    vector <double> vertex;  // vertex -> ball vertexes;
};
Ball *actor;
vector <Ball> ball;

void draw(const vector <double> &v)
{
	for(int i=0; i<v.size(); i+=2)
		glVertex2d(v[i]/W, v[i+1]/H);
}
void buildScene()
{
	glColor3d(WINCOLOR);
	glBegin(GL_LINE_LOOP);
	draw(scene);
	glEnd();
}
void addActor()
{
    glColor3d(ACTCOLOR);
    glBegin(GL_POLYGON);
    draw(actor->vertex);
    glEnd();
}
void displayBall()
{
    for (auto i: ball)
    {
        glColor3d(i.a, i.b, i.c);
        glBegin(GL_POLYGON);
        draw(i.vertex);
        glEnd();
    }
}
void gamePlay()
{
    glClear(GL_COLOR_BUFFER_BIT);
	buildScene();
    addActor();
	displayBall();
	glutSwapBuffers();
}
void reshape(int x, int y) { glViewport(0, 0, W=x, H=y); }
vector <double> getBallVertex(double x, double y)
{
    vector <double> v;
    for (int i=0; i<BALLACC; i++)
    {
        const double pi = 4*atan(1);
        v.push_back(x+BALLRAD*cos(2*pi/BALLACC*i));
        v.push_back(y+BALLRAD*sin(2*pi/BALLACC*i));
    }
    return v;
}
void initBall()
{
    for (int i=0, t=0; t<BALLNUM; i++)
        for (int j=0; j<=i&&t<BALLNUM; j++, t++)
        {
            double x = BALICX+sqrt(3)*(BALLRAD+10)*i, y = BALICY+(BALLRAD+10)*(2*j-i);
            ball.push_back((Ball){ x, y, BALIVX, BALIVY, RAND, RAND, RAND, getBallVertex(x, y) });
        }
    actor = new (Ball) { ACTICX, ACTICY, ACTIVX, ACTIVY, ACTCOLOR, getBallVertex(ACTICX, ACTICY) };
}
void updateVelocity(Ball &a)
{
    if (a.x<=-WINWIDTH+BALLRAD || a.x>=WINWIDTH-BALLRAD) a.vx = -a.vx;
    if (a.y<=-WINHEIGHT+BALLRAD || a.y>=WINHEIGHT-BALLRAD) a.vy = -a.vy;
}
double getDegree(double x1, double y1, double x2, double y2)
{
    return atan((y2-y1)/(x2-x1));
}
void updateVelocity(Ball &a, Ball &b)
{
    double da = abs(atan((a.y-b.y)/(a.x-b.x))-atan(a.vy/a.vx));
    double db = abs(atan((a.y-b.y)/(a.x-b.x))-atan(b.vy/b.vx));
    double nvx = cos(da)*sqrt(a.vx*a.vx+a.vy*a.vy)+cos(db)*sqrt(b.vx*b.vx+b.vy*b.vy);
    double nvy = sin(da)*sqrt(a.vx*a.vx+a.vy*a.vy)+sin(db)*sqrt(b.vx*b.vx+b.vy*b.vy);
}
void updateVertex(Ball &a)
{
    a.x += a.vx, a.y += a.vy;
    for (int i=0; i<a.vertex.size(); i+=2) a.vertex[i] += a.vx;
    for (int i=1; i<a.vertex.size(); i+=2) a.vertex[i] += a.vy;
}
bool judgeCollision(const Ball &a, const Ball &b)
{
    if (sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y))<=2*BALLRAD) return true;
    return false;
}
void ballLoop(int id)
{
    for (int i=0; i<ball.size(); i++)
        updateVelocity(ball[i]);
    updateVelocity(*actor);

    for (int i=0; i<ball.size(); i++)
        for (int j=i+1; j<ball.size(); j++)
            if (judgeCollision(ball[i], ball[j]))
                updateVelocity(ball[i], ball[j]);
    for (int i=0; i<ball.size(); i++)
        if (judgeCollision(*actor, ball[i]))
            updateVelocity(*actor, ball[i]);

    for (int i=0; i<ball.size(); i++)
        updateVertex(ball[i]);
    updateVertex(*actor);

    printf("%f %f\n", actor->vx, actor->x);
    glutPostRedisplay();
    glutTimerFunc(BALLSPEED, ballLoop, id);
}

// main
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Billiard");
	initBall();
	glutDisplayFunc(gamePlay);
	glutReshapeFunc(reshape);
	glutTimerFunc(BALLSPEED, ballLoop, BALLID);
//	glutSpecialFunc(specialKeyListener);
//	glutKeyboardFunc(keyboardListener);
	glutMainLoop();
	return 0;
}
