#include <stdlib.h>
#include <stdio.h>

#include <GL/freeglut.h>

#include <opencv/highgui.h>
#include <opencv/cv.h>

static GLfloat angle = 0.0;
GLuint	textures[2];
GLUquadricObj* quad;

void displayScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);

	//	glTranslatef(0.0, 0.0, -2.0);
	//	glColor3f(1.0,1.0,1.0);

	glRotatef(90, 1.0, 0.0, 0.0);

	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	glColor3f(1.0,1.0,1.0);
	glTexCoord2f(1.0, 1.0);	glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(-1.0, 1.0); 	glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(-1.0, 1.0); 	glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 1.0); 	glVertex3f(1.0, 1.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3f(1.0,1.0,0.0);
	glTexCoord2f(-1.0, 1.0);	glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(1.0, 1.0); 	glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(1.0, -1.0); 	glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(-1.0, -1.0); 	glVertex3f(1.0, -1.0, -1.0);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glColor3f(1.0,0.0,1.0);
	glTexCoord2f(-1.0, 1.0);	glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 1.0); 	glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1.0, -1.0); 	glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(-1.0, -1.0); 	glVertex3f(1.0, -1.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3f(0.0,1.0,1.0);
	glTexCoord2f(-1.0, 1.0);	glVertex3f(1.0, -1.0, -1.0);
	glTexCoord2f(1.0, 1.0); 	glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1.0, -1.0); 	glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(-1.0, -1.0); 	glVertex3f(1.0, 1.0, -1.0);

//	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glColor3f(1.0,0.0,0.0);
	glTexCoord2f(-1.0, 1.0);	glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 1.0); 	glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(1.0, -1.0); 	glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(-1.0, -1.0); 	glVertex3f(-1.0, -1.0, 1.0);

//	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glColor3f(0.0,0.0,1.0);
	glTexCoord2f(-1.0, 1.0);	glVertex3f(1.0, 0.0, 1.0);
	glTexCoord2f(1.0, 1.0); 	glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0, -1.0); 	glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(-1.0, -1.0); 	glVertex3f(1.0, -1.0, -1.0);

	glEnd();
	glFlush();
	glDisable(GL_TEXTURE_2D);

	glLoadIdentity();
	glColor3f(1.0,1.0,1.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(30, 1.0, 1.0, 0.0);
	glRotatef(angle, 0.0, 0.0, -1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);

	gluSphere(quad,0.3,50,50);


	glDisable(GL_TEXTURE_2D);

	glLoadIdentity();
	angle += 0.5;
	if (angle > 360.0)
	{
		angle = angle - 360.0;
	}
	glutSwapBuffers();
}

void resizeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void loadScenetextures()
{
	IplImage* image1 = cvLoadImage("./Data/sky.bmp");

	glGenTextures(1, &textures[0]);
	glBindTexture(GL_TEXTURE_2D, textures[0]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->width, image1->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->imageData);

	IplImage* image2 = cvLoadImage("./Data/sonne.bmp");

	glGenTextures(1, &textures[1]);
	glBindTexture(GL_TEXTURE_2D, textures[1]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image2->width, image2->height, 0, GL_BGR, GL_UNSIGNED_BYTE, image2->imageData);

	cvReleaseImage(&image1);
	cvReleaseImage(&image2);
}
void initScene(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	loadScenetextures();

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 40.0, 0.0, 30.0);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	quad = gluNewQuadric();
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluQuadricTexture(quad, GL_TRUE);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("scene");
	initScene();
	glutDisplayFunc(displayScene);

	glutReshapeFunc(resizeWindow);
	glutIdleFunc(displayScene);
	glutMainLoop();

	return 0;
}
