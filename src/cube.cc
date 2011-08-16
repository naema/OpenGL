#include <stdlib.h>
#include <stdio.h>

#include <GL/freeglut.h>

static GLfloat angle = 0.0;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
//	glTranslatef(0.0, 0.0, -2);
	glRotatef(angle, 1.0, 1.0, 1.0);
	glColor3f(0.5, 0.5, 0.5);

	glutWireCube(0.7);

	glLoadIdentity();
	angle += 0.5;
	if (angle > 360.0)
	{
		angle = angle - 360.0;
	}
	glutSwapBuffers();
}

void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
//	glOrtho(0.0, 50.0, 0.0, 50.0, -50.0, 50.0);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

}

int main_(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("cube");
	init();
	glutDisplayFunc(display);

	glutReshapeFunc(resize);
	glutIdleFunc(display);
	glutMainLoop();

	return 0;
}
