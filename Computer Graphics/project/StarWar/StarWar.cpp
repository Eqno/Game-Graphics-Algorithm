#include <iostream>
#include <GL/glut.h>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <utility>
#include <random>
using namespace std;

#define WHITE 1,1,1
#define RED 1,0,0
#define YELLOW 1,1,0

#define ACTCOLOR WHITE
#define BULCOLOR RED
#define ENECOLOR YELLOW
#define LIFCOLOR RED
#define WINCOLOR WHITE

int                 W = 1600, H = 900;  // 窗口大小。
double       		WIDTHRAT = 0.8, HEIGHTRAT = 0.8,
                    WINWIDTH = W*WIDTHRAT, WINHEIGHT = H*HEIGHTRAT;  // 场景大小。
const unsigned int 	BULLSPEED = 10,  // 子弹 loop 速度。
	  				BULLID = 0;  // 子弹 loop ID。
const double 		BULLSTEP = 10,  // 子弹步长。
	  				BULLSIZE = 10;  // 子弹大小。
const unsigned int 	ENEMSPEED = 50,  // 敌人 loop 速度。
	  				ENEMID = 1;  // 敌人 loop ID。
const double 		ENEMSTEP = 10,  // 敌人步长。
					ENEMSIZE = 40;  // 敌人大小。
const unsigned int 	GENESPEED = 40, // 刷怪 loop 速度。
	  				GENEID = 2;  // 刷怪 loop ID。w
const unsigned int	ACTSPEED = 50, ACTID = 3;  // actor loop。
const double 		ACTORSTEP = 50,  // actor 步长。
	  				ACTPOSX = 0, ACTPOSY = -WINHEIGHT*3/4,  // actor 初始位置。
					ACTWIDTH = 50, ACTHEIGHT = 50;  // actor 大小。
const unsigned int 	INITLIFE = 3;  // 初始生命。
const double 		LIFESIZE = 15;  // 生命大小。
const double 		FAILSTEP = 10;  // 幕布步长。
unsigned int 		SHOTSPEED = 40;  // 鼠标射击速度。
unsigned int 		life = INITLIFE;  // 当前生命。

// scene and actor
vector <double> scene({-WINWIDTH, -WINHEIGHT, -WINWIDTH,
	WINHEIGHT, WINWIDTH, WINHEIGHT, WINWIDTH, -WINHEIGHT});
vector <double> actor({ACTPOSX, ACTPOSY, ACTPOSX-ACTWIDTH,
	ACTPOSY-ACTHEIGHT, ACTPOSX+ACTWIDTH, ACTPOSY-ACTHEIGHT});
vector <pair <double, double>> bullet;
vector <pair <double, double>> enemy;
bool moveLeft = false, moveRight = false, moveUp = false, moveDown = false;

// draw
void draw(vector <double> &v)
{
	for(int i=0; i<v.size(); i+=2)
		glVertex2d(v[i]/W, v[i+1]/H);
}

// actor and bullet response
void moveX(double d)
{
	double n = actor[0] + d;
	if (n < -WINWIDTH+ACTWIDTH)
	{
		actor[0] = -WINWIDTH+ACTWIDTH;
		actor[2] = -WINWIDTH;
		actor[4] = -WINWIDTH+2*ACTWIDTH;
	}
	else if (n > WINWIDTH-ACTWIDTH)
	{
		actor[0] = WINWIDTH-ACTWIDTH;
		actor[2] = WINWIDTH;
		actor[4] = WINWIDTH-2*ACTWIDTH;
	}
	else for (int i=0; i<actor.size(); i+=2)
        actor[i] += d;
}
void moveY(double d)
{
	double n = actor[1] + d;
	if (n > WINHEIGHT)
	{
		actor[1] = WINHEIGHT;
		actor[3] = WINHEIGHT-ACTHEIGHT;
		actor[5] = WINHEIGHT-ACTHEIGHT;
	}
	else if (n < -WINHEIGHT+ACTHEIGHT)
	{
		actor[1] = -WINHEIGHT+ACTHEIGHT;
		actor[3] = -WINHEIGHT;
		actor[5] = -WINHEIGHT;
	}
    else
	{
		for (int i=1; i<actor.size(); i+=2)
    		actor[i] += d;
	}
}
void shoot()
{
	bullet.push_back(make_pair(actor[0], actor[1]));
}
void harmed()
{
	life --;
    if (life == 0)
    {
        sleep(1);
        glColor3d(RED);
        double h = WINHEIGHT;
        while (h >= -WINHEIGHT)
        {
            h -= FAILSTEP;
            glBegin(GL_POLYGON);
            glVertex2d(-WINWIDTH/W, h/H);
            glVertex2d(-WINWIDTH/W, WINHEIGHT/H);
            glVertex2d(WINWIDTH/W, WINHEIGHT/H);
            glVertex2d(WINWIDTH/W, h/H);
            glEnd();
            glutSwapBuffers();
            usleep(10000);
        }
        exit(0);
    }
}

// keyboard listener
void strike()
{
	for (int i=0; i<actor.size(); i+=2)
		for (int j=0; j<enemy.size(); j++)
		{
			double L = enemy[j].first-ENEMSIZE;
			double R = enemy[j].first+ENEMSIZE;
			double B = enemy[j].second-ENEMSIZE;
			double T = enemy[j].second+ENEMSIZE;
			if (actor[i]<=R && actor[i]>=L
				&& actor[i+1]>=B && actor[i+1]<=T)
			{
				enemy.erase(enemy.begin()+j);
				harmed();
			}
		}
}
void specialKeyListener(int cmd, int x, int y)
{
	switch (cmd)
	{
		case GLUT_KEY_UP: moveUp = true; break;
		case GLUT_KEY_DOWN: moveDown = true; break;
		case GLUT_KEY_LEFT: moveLeft = true; break;
		case GLUT_KEY_RIGHT: moveRight = true;; break;
		default: break;
	}
	glutPostRedisplay();
}
void keyboardListener(unsigned char cmd, int x, int y)
{
	switch (cmd)
	{
		case 'w': moveUp = true; break;
		case 's': moveDown = true; break;
		case 'a': moveLeft = true; break;
		case 'd': moveRight = true; break;
		case ' ': shoot(); break;
		default: break;
	}
	glutPostRedisplay();
}
void specialKeyUpListener(int cmd, int x, int y)
{
	switch (cmd)
	{
		case GLUT_KEY_UP: moveUp = false; break;
		case GLUT_KEY_DOWN: moveDown = false; break;
		case GLUT_KEY_LEFT: moveLeft = false; break;
		case GLUT_KEY_RIGHT: moveRight = false; break;
		default: break;
	}
	glutPostRedisplay();
}
void keyboardUpListener(unsigned char cmd, int x, int y)
{
	switch (cmd)
	{
		case 'w': moveUp = false; break;
		case 's': moveDown = false; break;
		case 'a': moveLeft = false; break;
		case 'd': moveRight = false; break;
		default: break;
	}
	glutPostRedisplay();
}
void mouseListener(int x0, int y0)
{
	double x = x0*2-W;
	double y = -y0*2+H+ACTHEIGHT/2;
	if (x<=WINWIDTH-ACTWIDTH && x>=-WINWIDTH+ACTWIDTH
		&& y<WINHEIGHT && y>-WINHEIGHT+ACTHEIGHT)
		{
			actor = vector <double> ({
				x, y,
				x-ACTWIDTH, y-ACTHEIGHT,
				x+ACTWIDTH, y-ACTHEIGHT});
		}
	static unsigned int cot = 0;
	// if (cot >= SHOTSPEED) shoot(), cot = 0;
	// else cot ++;
	glutPostRedisplay();
}

// display
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
	draw(actor);
	glEnd();
}
void displayLife()
{
	glColor3d(LIFCOLOR);
	for (int i=0; i<life; i++)
	{
		glBegin(GL_POLYGON);
		glVertex2d((-WINWIDTH+3*(i+1)*LIFESIZE-LIFESIZE)/W,
             (WINHEIGHT-3*LIFESIZE-LIFESIZE)/H);
		glVertex2d((-WINWIDTH+3*(i+1)*LIFESIZE-LIFESIZE)/W,
             (WINHEIGHT-3*LIFESIZE+LIFESIZE)/H);
		glVertex2d((-WINWIDTH+3*(i+1)*LIFESIZE+LIFESIZE)/W,
             (WINHEIGHT-3*LIFESIZE+LIFESIZE)/H);
		glVertex2d((-WINWIDTH+3*(i+1)*LIFESIZE+LIFESIZE)/W,
             (WINHEIGHT-3*LIFESIZE-LIFESIZE)/H);
		glEnd();
	}
}
void displayBullet()
{
	glColor3d(BULCOLOR);
	for (auto i: bullet)
	{
		glBegin(GL_POLYGON);
		glVertex2d((i.first-BULLSIZE)/W, (i.second-BULLSIZE)/H);
		glVertex2d((i.first-BULLSIZE)/W, (i.second+BULLSIZE)/H);
		glVertex2d((i.first+BULLSIZE)/W, (i.second+BULLSIZE)/H);
		glVertex2d((i.first+BULLSIZE)/W, (i.second-BULLSIZE)/H);
		glEnd();
	}
}
void displayEnemy()
{
	glColor3d(ENECOLOR);
	for (auto i: enemy)
	{
		glBegin(GL_POLYGON);
		glVertex2d((i.first-ENEMSIZE)/W, (i.second-ENEMSIZE)/H);
		glVertex2d((i.first-ENEMSIZE)/W, (i.second+ENEMSIZE)/H);
		glVertex2d((i.first+ENEMSIZE)/W, (i.second+ENEMSIZE)/H);
		glVertex2d((i.first+ENEMSIZE)/W, (i.second-ENEMSIZE)/H);
		glEnd();
	}
}

// functions
void gamePlay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	buildScene();
	addActor();
	displayLife();
	displayBullet();
	displayEnemy();
	glutSwapBuffers();
}
void adjustActor()
{
    if (actor[0] < -WINWIDTH+ACTWIDTH)
    {
        actor[0] = -WINWIDTH + ACTWIDTH;
        actor[2] = -WINWIDTH;
        actor[4] = -WINWIDTH + 2*ACTWIDTH;
    }
    if (actor[0] > WINWIDTH-ACTWIDTH)
    {
        actor[0] = WINWIDTH - ACTWIDTH;
        actor[2] = WINWIDTH;
        actor[4] = WINWIDTH - 2*ACTWIDTH;
    }
    if (actor[1] < -WINHEIGHT+ACTHEIGHT)
    {
        actor[1] = -WINHEIGHT + ACTHEIGHT;
        actor[3] = -WINHEIGHT;
        actor[5] = -WINHEIGHT;
    }
    if (actor[1] > WINHEIGHT)
    {
        actor[1] = WINHEIGHT;
        actor[3] = WINHEIGHT - ACTHEIGHT;
        actor[5] = WINHEIGHT - ACTHEIGHT;
    }
}
void adjustEnemy()
{
	for (int i=0; i<enemy.size(); i++)
	{
		enemy[i].first = max(enemy[i].first, -WINWIDTH+ENEMSIZE);
		enemy[i].first = min(enemy[i].first, WINWIDTH-ENEMSIZE);
		enemy[i].second = max(enemy[i].second, -WINHEIGHT+ENEMSIZE);
		enemy[i].second = min(enemy[i].second, WINHEIGHT-ENEMSIZE);
	}
}
void reshape(int x, int y)
{
	W = x, H = y, WINWIDTH = W*WIDTHRAT, WINHEIGHT = H*HEIGHTRAT;
	scene = vector <double> ({-WINWIDTH, -WINHEIGHT, -WINWIDTH,
	WINHEIGHT, WINWIDTH, WINHEIGHT, WINWIDTH, -WINHEIGHT});
	adjustActor();
	adjustEnemy();
    glViewport(0, 0, x, y);
}
void bulletLoop(int id)
{
	for (int i=0; i<bullet.size(); i++)
	{
		double n = bullet[i].second + BULLSTEP;
		if (n>=-WINHEIGHT+BULLSIZE && n<=WINHEIGHT-BULLSIZE)
		{
			bullet[i].second = n;
			double leftBound = bullet[i].first-BULLSIZE;
			double rightBound = bullet[i].first+BULLSIZE;
			double uppBound = bullet[i].second+BULLSIZE;
			double lowBound = bullet[i].second-BULLSIZE;
			for (int j=0; j<enemy.size(); j++)
			{
				double L = enemy[j].first-ENEMSIZE;
				double R = enemy[j].first+ENEMSIZE;
				double B = enemy[j].second-ENEMSIZE;
				double T = enemy[j].second+ENEMSIZE;
				if (leftBound<=R && rightBound>=L
					&& uppBound>=B && lowBound<=T)
				{
					bullet.erase(bullet.begin()+i);
					enemy.erase(enemy.begin()+j);
				}
			}
		}
		else bullet.erase(bullet.begin()+i);
	}
	glutPostRedisplay();
	glutTimerFunc(BULLSPEED, bulletLoop, id);
}
void enemyLoop(int id)
{
	for (int i=0; i<enemy.size(); i++)
	{
		double n = enemy[i].second - ENEMSTEP;
		if (n>=-WINHEIGHT+ENEMSIZE && n<=WINHEIGHT-ENEMSIZE)
			enemy[i].second = n;
		else
		{
			enemy.erase(enemy.begin()+i);
			harmed();
		}
	}
	strike();
	glutPostRedisplay();
	glutTimerFunc(ENEMSPEED, enemyLoop, id);
}
void genenemyLoop(int id)
{
	static unsigned int cot = 0;
	if (cot >= GENESPEED)
	{
		double x = -WINWIDTH+ENEMSIZE
			+ (rand()/double(RAND_MAX))*2*(WINWIDTH-ENEMSIZE);
		enemy.push_back(make_pair(x, WINHEIGHT-ENEMSIZE));
		cot = 0;
	}
	else cot ++;
	glutTimerFunc(GENESPEED, genenemyLoop, id);
}
void actorLoop(int id)
{
	if (moveLeft) moveX(-ACTORSTEP);
	if (moveRight) moveX(ACTORSTEP);
	if (moveUp) moveY(ACTORSTEP);
	if (moveDown) moveY(-ACTORSTEP);
	glutTimerFunc(ACTSPEED, actorLoop, id);
}

// main
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Star War");
	glutDisplayFunc(gamePlay);
	glutReshapeFunc(reshape);
	glutTimerFunc(BULLSPEED, bulletLoop, BULLID);
	glutTimerFunc(ENEMSPEED, enemyLoop, ENEMID);
	glutTimerFunc(ACTSPEED, actorLoop, ACTID);
	glutTimerFunc(0, genenemyLoop, GENEID);
	glutSpecialFunc(specialKeyListener);
	glutKeyboardFunc(keyboardListener);
	glutSpecialUpFunc(specialKeyUpListener);
	glutKeyboardUpFunc(keyboardUpListener);
	glutMotionFunc(mouseListener);
	glutMainLoop();
	return 0;
}
