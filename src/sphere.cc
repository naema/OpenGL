#include <stdlib.h>
#include <stdio.h>

#include <GL/freeglut.h>

#include <opencv/highgui.h>
#include <opencv/cv.h>

static GLfloat angle = 0.0;
GLuint	texture[2];
GLUquadricObj* quadric;

void displaySphere(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	//	glTranslatef(0.0, 0.0, -2.0);
	//	glColor3f(1.0,1.0,1.0);

	glBegin(GL_POLYGON);
	glTexCoord2f(-1.0, 1.0);	glVertex3f(-1.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0); 	glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(1.0, -1.0); 	glVertex3f(1.0, -1.0, 0.0);
	glTexCoord2f(-1.0, -1.0); 	glVertex3f(-1.0, -1.0, 0.0);
	glEnd();
	glFlush();
	glDisable(GL_TEXTURE_2D);

	glLoadIdentity();

	// "nahtstelle" verdecken
	glRotatef(80, 1.0, 0.0, 0.0);
	// textur in gewünschte richtung drehen
	glRotatef(30, 1.0, 1.0, 0.0);
	// rotationsachse festlegen
	glRotatef(angle, 0.0, 0.0, -1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	gluSphere(quadric,0.3,50,50);


	glDisable(GL_TEXTURE_2D);

	glLoadIdentity();
	angle += 0.5;
	if (angle > 360.0)
	{
		angle = angle - 360.0;
	}
	glutSwapBuffers();
}

void resizeWin(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void loadGLtextures()
{
	IplImage* image1 = cvLoadImage("./Data/sky.bmp");

	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->width, image1->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->imageData);

	IplImage* image2 = cvLoadImage("./Data/sonne.bmp");

	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image2->width, image2->height, 0, GL_BGR, GL_UNSIGNED_BYTE, image2->imageData);

	cvReleaseImage(&image1);
	cvReleaseImage(&image2);
}
void initGL(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	loadGLtextures();

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 40.0, 0.0, 30.0);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE);
}

int main__(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("sphere");
	initGL();
	glutDisplayFunc(displaySphere);

	glutReshapeFunc(resizeWin);
	glutIdleFunc(displaySphere);
	glutMainLoop();

	return 0;
}
