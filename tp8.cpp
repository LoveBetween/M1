//
//  tp6_squelette.cpp
//  
//
//  Created by Caroline Larboulette on 10/10/2021.
//
//  g++ tp8.cpp -lglut -lGL -lGLU

#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;


void drawHouse(){
        //face avant
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glBegin(GL_POLYGON);
        glColor3f(1.0, 0, 0);
        glVertex3f(0, 0, 54);
        glVertex3f(0, 10, 54);
        glVertex3f(8, 16, 54);
        glVertex3f(16, 10, 54);
        glVertex3f(16, 0, 54);
        glEnd();

        //face arriere
        glBegin(GL_POLYGON);
        glColor3f(0, 1.0, 0);
        glVertex3f(0, 0, 30);
        glVertex3f(0, 10, 30);
        glVertex3f(8, 16, 30);
        glVertex3f(16, 10, 30);
        glVertex3f(16, 0, 30);
        glEnd();

        //wall 1
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glVertex3f(0, 0, 54);
        glVertex3f(0, 0, 30);
        glVertex3f(0, 10, 30);
        glVertex3f(0, 10, 54);
        glEnd();

        //wall 2
        glBegin(GL_QUADS);
        glVertex3f(0, 10, 30);
        glVertex3f(0, 10, 54);
        glVertex3f(8, 16, 54);
        glVertex3f(8, 16, 30);
        glEnd();

        //wall 3
        glBegin(GL_QUADS);
        glVertex3f(8, 16, 54);
        glVertex3f(8, 16, 30);
        glVertex3f(16, 10, 30);
        glVertex3f(16, 10, 54);
        glEnd();

        //wall 4
        glBegin(GL_QUADS);
        glVertex3f(16, 10, 30);
        glVertex3f(16, 10, 54);
        glVertex3f(16, 0, 54);
        glVertex3f(16, 0, 30);
        glEnd();

        //wall 5
        glBegin(GL_QUADS);
        glVertex3f(16, 0, 54);
        glVertex3f(16, 0, 30);
        glVertex3f(0, 0, 30);
        glVertex3f(0, 0, 54);
        glEnd();
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity();
    gluLookAt(8, 12, 61, 8, 12, 60, 0, 1, 0);// Add parameters here that are not default ones
   
    //Draw axes
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES); //Draws x-axis
    glVertex3f(-50,0,0);
    glVertex3f(50,0,0);
    glEnd();
    
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES); //Draws y-axis
    glVertex3f(0,-50,0);
    glVertex3f(0,50,0);
    glEnd();
    
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES); //Draws z-axis
    glVertex3f(0,0,-50);
    glVertex3f(0,0,50);
    glEnd();
  
    drawHouse();
    glFlush();
}

void reshape(int w, int h)
{

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  
    glMatrixMode(GL_MODELVIEW); //Ready to transform the object matrix
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); //Background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //perspective projection left right bottom top near far
    //Change parameters to see your object
    glFrustum(-50.0,50.0,-50.0,50.0,25,80);
    glMatrixMode(GL_MODELVIEW);
}

/**
 void keyboard(unsigned char key, int x, int y)
 key returns the character hit by the user
 **/
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q': exit(0);  //exits the program
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (250, 250); //Window size in pixels
    glutInitWindowPosition (100, 100); //Window position on screen in pixels
    glutCreateWindow ("Bonjour les amis !"); //Creates a window with the title of your choice^^
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop(); //Calls the rendering loop
    return 0;
}
