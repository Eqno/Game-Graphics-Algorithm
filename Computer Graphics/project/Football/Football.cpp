#include <iostream>
#include <GL/glut.h>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <utility>
#include <cmath>
using namespace std;

#define WHITE 1,1,1
#define RED 1,0,0
#define YELLOW 1,1,0
#define GREEN 0,1,0

#define ACTCOLOR YELLOW
#define BALCOLOR GREEN
#define WINCOLOR WHITE
#define LOSCOLOR RED

int                     W = 1600, H = 900;  // 窗口大小。
double       		    WIDTHRAT = 0.8, HEIGHTRAT = 0.8,
                        WINWIDTH = W*WIDTHRAT, WINHEIGHT = H*HEIGHTRAT;  // 场景大小。
double 		            ACTORSTEP = 80,  // actor 步长。
                        ACTWIDTH = 10, ACTHEIGHT = 200;  // actor 大小。
const unsigned int      BALLSPEED = 20,
                        BALLID = 0,
                        BALLACC = 50;
const double 		    BALLRAD = 30, BALLSTEP = 20, OFFSET = 0.5;
const unsigned int 	    LOSTIME = 5;

vector <double> scene({-WINWIDTH, -WINHEIGHT, -WINWIDTH,
	WINHEIGHT, WINWIDTH, WINHEIGHT, WINWIDTH, -WINHEIGHT});
vector <double> actorA({-WINWIDTH, -ACTHEIGHT, -WINWIDTH, ACTHEIGHT,
    -WINWIDTH+2*ACTWIDTH, ACTHEIGHT, -WINWIDTH+2*ACTWIDTH, -ACTHEIGHT});
vector <double> actorB({WINWIDTH, -ACTHEIGHT, WINWIDTH, ACTHEIGHT,
    WINWIDTH-2*ACTWIDTH, ACTHEIGHT, WINWIDTH-2*ACTWIDTH, -ACTHEIGHT});
vector <double> ball;


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
	draw(actorA);
	glEnd();
	glBegin(GL_POLYGON);
	draw(actorB);
	glEnd();
}
void displayBall()
{
	glColor3d(BALCOLOR);
	glBegin(GL_POLYGON);
	draw(ball);
	glEnd();
}
void gamePlay()
{
    glClear(GL_COLOR_BUFFER_BIT);
	buildScene();
	addActor();
	displayBall();
	glutSwapBuffers();
}
void move(vector <double> &actor, double d)
{
	double n = actor[1] + d;
	if (n > WINHEIGHT-2*ACTHEIGHT)
	{
		actor[1] = WINHEIGHT-2*ACTHEIGHT;
		actor[3] = WINHEIGHT;
		actor[5] = WINHEIGHT;
		actor[7] = WINHEIGHT-2*ACTHEIGHT;
	}
	else if (n < -WINHEIGHT)
	{
		actor[1] = -WINHEIGHT;
		actor[3] = -WINHEIGHT+2*ACTHEIGHT;
		actor[5] = -WINHEIGHT+2*ACTHEIGHT;
		actor[7] = -WINHEIGHT;
	}
    else
	{
		for (int i=1; i<actor.size(); i+=2)
			actor[i] += d;
	}
}
void specialKeyListener(int cmd, int x, int y)
{
	switch (cmd)
	{
		case GLUT_KEY_UP: move(actorB, ACTORSTEP); break;
		case GLUT_KEY_DOWN: move(actorB, -ACTORSTEP); break;
		default: break;
	}
	glutPostRedisplay();
}
void keyboardListener(unsigned char cmd, int x, int y)
{
	switch (cmd)
	{
		case 'w': move(actorA, ACTORSTEP); break;
		case 's': move(actorA, -ACTORSTEP); break;
		default: break;
	}
	glutPostRedisplay();
}
void adjustActor(vector <double> &actor)
{
	if (actor == actorA)
	{
		actor[0] = actor[2] = -WINWIDTH;
		actor[4] = actor[6] = -WINWIDTH+2*ACTWIDTH;
	}
	if (actor == actorB)
	{
		actor[0] = actor[2] = WINWIDTH;
		actor[4] = actor[6] = WINWIDTH-2*ACTWIDTH;
	}
	if (actor[1]<-WINHEIGHT && actor[3]>WINHEIGHT)
	{
		actor[1] = actor[7] = -WINHEIGHT;
		actor[3] = actor[5] = WINHEIGHT;
	}
	else if (actor[1] < -WINHEIGHT)
	{
		actor[1] = actor[7] = -WINHEIGHT;
		actor[3] = actor[5] = -WINHEIGHT+ACTHEIGHT;
	}
	else if (actor[3] > WINHEIGHT)
	{
		actor[1] = actor[7] = WINHEIGHT-ACTHEIGHT;
		actor[3] = actor[5] = WINHEIGHT;
	}
}
void reshape(int x, int y)
{
	W = x, H = y, WINWIDTH = W*WIDTHRAT, WINHEIGHT = H*HEIGHTRAT;
	scene = vector <double> ({-WINWIDTH, -WINHEIGHT, -WINWIDTH,
	WINHEIGHT, WINWIDTH, WINHEIGHT, WINWIDTH, -WINHEIGHT});
	adjustActor(actorA);
	adjustActor(actorB);
	// adjustBall();
    glViewport(0, 0, x, y);
}
void lose(const vector <double> &actor)
{
    for (int i=0; i<LOSTIME; i++)
    {
        if (i & 1) glColor3d(ACTCOLOR);
        else glColor3d(LOSCOLOR);
        glBegin(GL_POLYGON);
        draw(actor);
        glEnd();
        glutSwapBuffers();
        usleep(500000);
    }
    exit(0);
}
void ballLoop(int id)
{
	static double lx = 0, ly = 0;
	static double xstep = BALLSTEP, ystep = 0;
	for (int i=0; i<ball.size(); i+=2)
	{
		if (ball[i] <= -WINWIDTH+ACTWIDTH)
		{
			if (ball[1]>=actorA[1]-BALLRAD && ball[1]<=actorA[3]+BALLRAD)
			{
				double del = ball[1]-actorA[1];
				double xtmp = 2*atan(1)*del/ACTHEIGHT;
				xstep = abs(BALLSTEP * ((1-OFFSET)*sin(xtmp)+OFFSET));
				double ytmp = sqrt(BALLSTEP*BALLSTEP-xstep*xstep);
				ystep = del>=ACTHEIGHT ? ytmp : -ytmp;
			}
			else lose(actorA);
		}
		if (ball[i] >= WINWIDTH-ACTWIDTH)
		{
			if (ball[1]>=actorB[1]-BALLRAD && ball[1]<=actorB[3]+BALLRAD)
			{
				double del = ball[1]-actorB[1];
				double xtmp = 2*atan(1)*del/ACTHEIGHT;
				xstep = -abs(BALLSTEP * ((1-OFFSET)*sin(xtmp)+OFFSET));
				double ytmp = sqrt(BALLSTEP*BALLSTEP-xstep*xstep);
				ystep = del>=ACTHEIGHT ? ytmp : -ytmp;
			}
			else lose(actorB);
		}
	}
	for (int i=1; i<ball.size(); i+=2)
	{
		if (ball[i] <= -WINHEIGHT) ystep = abs(ystep);
		if (ball[i] >= WINHEIGHT) ystep = -abs(ystep);
	}
	for (int i=0; i<ball.size(); i+=2)
	{
		ball[i] += xstep;
		ball[i+1] += ystep;
	}
	glutPostRedisplay();
    glutTimerFunc(BALLSPEED, ballLoop, id);
    if (xstep!=lx || ystep!=ly)
	{
		cout << xstep << " " << ystep << endl;
		lx = xstep, ly = ystep;
	}
}

void makeBall(int r, int n)
{
	for (int i=0; i<n; i++)
	{
		const double pi = 4*atan(1);
		ball.push_back(r*cos(2*pi/n*i));
		ball.push_back(r*sin(2*pi/n*i));
	}
}

// main
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Foot Ball");
	makeBall(BALLRAD, BALLACC);
	glutDisplayFunc(gamePlay);
	glutReshapeFunc(reshape);
	glutTimerFunc(BALLSPEED, ballLoop, BALLID);
	glutSpecialFunc(specialKeyListener);
	glutKeyboardFunc(keyboardListener);
	glutMainLoop();
	return 0;
}
