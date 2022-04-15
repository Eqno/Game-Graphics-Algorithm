/*
*该程序实现点，线，面的绘制
*/

#include <GL/glut.h>

void draw()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    //绘制


    //红色画点
    glColor3f(1.0, 0.0, 0.0); 
    glBegin(GL_POINTS);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.1, 0.1);
    glVertex2f(0.1, 0.2);
    glVertex2f(0.1, 0.3);
    glVertex2f(0.1, 0.4);
    glEnd();

    //绿色画线
    glColor3f(0.0, 1.0, 0.0); 
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, -0.1);
    glVertex2f(-0.1, 0.0);
    glVertex2f(-0.1, -0.1);
    glEnd();

    //蓝色画相邻点相连，首尾不连的线
    glColor3f(0.0, 0.0, 1.0); 
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.2, 0.0);
    glVertex2f(-0.2, -0.1);
    glVertex2f(-0.3, 0.0);
    glVertex2f(-0.3, -0.1);
    glEnd();

    //粉色画相邻点相连，首尾连的线
    glColor3f(1.0, 0.5, 0.5); 
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.4, 0.0);
    glVertex2f(-0.4, -0.1);
    glVertex2f(-0.5, 0.0);
    glVertex2f(-0.5, -0.1);
    glEnd();

    //橘黄色画填充面
    glColor3f(1.0, 0.5, 0.25); 
    glBegin(GL_POLYGON);
    glVertex2f(-0.1, 0.1);
    glVertex2f(-0.2, 0.1);
    glVertex2f(-0.3, 0.3);
    glVertex2f(-0.2, 0.5);
    glVertex2f(-0.1, 0.3);
    glEnd();

    //碧蓝色画填充面，每四个点画一个四边形，相邻不连接
    glColor3f(0.0, 1.0, 1.0); 
    glBegin(GL_QUADS);
    glVertex2f(-0.3, 0.1);
    glVertex2f(-0.4, 0.1);
    glVertex2f(-0.5, 0.3);
    glVertex2f(-0.4, 0.5);
    glVertex2f(-0.5, 0.1);
    glVertex2f(-0.6, 0.1);
    glVertex2f(-0.7, 0.3);
    glVertex2f(-0.6, 0.5);
    glEnd();

    //彩色画填充面，每两个点构成一条线，每两个线构成一个四边形
    glBegin(GL_QUAD_STRIP);
    //线1
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.3, 0.6);
    glVertex2f(-0.2, 0.8);
    //线2
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-0.4, 0.6);
    glVertex2f(-0.5, 0.9);
    //线3
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(-0.5, 0.5);
    glVertex2f(-0.7, 0.7);
    glEnd();

    //褐色填充三角形(将每三个点围成的三角形进行填充，相邻的点之间不填充)
    glColor3f(0.5, 0.25, 0.0); 
    glBegin(GL_TRIANGLES);
    glVertex2f(0.2, 0.1);
    glVertex2f(0.3, 0.2);
    glVertex2f(0.4, 0.1);
    glVertex2f(0.5, 0.1);
    glVertex2f(0.6, 0.3);
    glVertex2f(0.7, 0.1);
    glEnd();

    //白色填充三角形(将每三个点围成的三角形进行填充，相邻的点之间填充)
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(0.2, 0.4);
    glVertex2f(0.3, 0.7);
    glVertex2f(0.4, 0.4);
    glVertex2f(0.5, 0.8);
    glVertex2f(0.6, 0.4);
    glEnd();

    //淡蓝色填充三角形(将每三个点围成的三角形进行填充，相邻的点之间填充)
    glColor3f(0.5, 0.5, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.2, -0.2);
    glVertex2f(0.2, -0.5);
    glVertex2f(0.3, -0.4);
    glVertex2f(0.4, -0.3);
    glVertex2f(0.3, -0.1);
    glEnd();

	glFlush();
}

void reshape(int x, int y)
{
    int dis = x > y ? y : x; //取小的
    glViewport(0, 0, dis, dis);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("绘制点、线、面");
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
