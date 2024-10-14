#include "simpleViewer.h"

using namespace std;

static float angle = 0.0f;

void matrix_mul(const float m[16], const float n[16], float result[16]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i * 4 + j] = 0;
            for (int k = 0; k < 4; k++) {
                result[i * 4 + j] += m[i * 4 + k] * n[k * 4 + j];
            }
        }
    }
}


// Draws a spiral
void transformeMatrix(){
            // Scale by 0.5 uniformely
    float T1[] = {
        2, 0, 0, 0,
        0.0, 2, .0, .0,
        0.0, 0, 2, .0,
        0.0, 0, 0, 1.0
    };

    // Translate by 1,0,0
    float T2[] = {
        1, 0, 0, 0,
        0.0, 1, .0, .0,
        0.0, 0, 1, .0,
        1.0, 0, 0.0, 1.0
    };


    float theta = 60*M_PI/180;
    // Rotate by 60° around z axis
    float T3[] = {
        float(cos(theta)) , float(sin(theta)), 0, 0,
        float(-sin(theta)), float(cos(theta)), .0, .0,
        0.0, 0, 1, .0,
        .0, 0, 0.0, 1.0
    };

    glMultMatrixf(T2);
    glMultMatrixf(T1);
    glMultMatrixf(T3);
    

    // Compound Matrix
    float T4[] = {
        float(cos(theta))*0.5f , float(sin(theta))*0.5f, 0, 0,
        float(-sin(theta))*0.5f, float(cos(theta))*0.5f, .0, .0,
        0.0, 0, 1*0.5, .0,
        1.0, 0, 0.0, 1.0
    };

    
    float T5[16];
    float T6[16];
    matrix_mul(T1, T2, T5);
    matrix_mul(T3, T5, T6);
}

void drawMaison(){
        const float nbSteps = 200.0;
        glBegin(GL_QUAD_STRIP); //Draws points
        glColor3f(1.0, 0.0, 0.0);

        float a = -0.2;
        float b = 0.2;
        float width = 1.0;
        //face1
        glVertex3f(a,a,a*width);
        glVertex3f(b,a,a*width);
        glVertex3f(a,b,a*width);
        glVertex3f(b,b,a*width);

        glColor3f(a, b, a);
        //facewidth
        glVertex3f(a,b,b*width);
        glVertex3f(b,b,b*width);
        glVertex3f(a,a,b*width);
        glVertex3f(b,a,b*width);

        glColor3f(0.0, 0.0, 1.0);

        glEnd();
        glBegin(GL_QUAD_STRIP);
        //face4
        glVertex3f(b,a,a*width);
        glVertex3f(b,b,a*width);
        glVertex3f(b,a,b*width);
        glVertex3f(b,b,b*width);

        glVertex3f(a,a,a*width);
        glVertex3f(a,b,a*width);
        glVertex3f(a,a,b*width);
        glVertex3f(a,b,b*width);
        glEnd();

        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glVertex3f(b,a,a*width);
        glVertex3f(b,a,b*width);
        glVertex3f(a,a,b*width);
        glVertex3f(a,a,a*width);
        glEnd();

        //toit
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_QUADS);
        glVertex3f(a,a,a*width);
        glVertex3f(b,a,a*width);


        glVertex3f(b,(a +b)/2,(a-0.1)*width);
        glVertex3f(a,(a +b)/2,(a-0.1)*width);
        glEnd();

        glBegin(GL_QUADS);
        glVertex3f(b,(a +b)/2,(a-0.1)*width);
        glVertex3f(a,(a +b)/2,(a-0.1)*width);

        glVertex3f(a,b,a*width);
        glVertex3f(b,b,a*width);
        glEnd();

        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_TRIANGLES);

        glVertex3f(b,(a +b)/2,(a-0.1)*width);
        glVertex3f(b,a,a*width);
        glVertex3f(b,b,a*width);

        glEnd();

        glBegin(GL_TRIANGLES);

        glVertex3f(a,(a +b)/2,(a-0.1)*width);
        glVertex3f(a,a,a*width);
        glVertex3f(a,b,a*width);

        glEnd();
        
        //porte
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glVertex3f(b/4,a-0.01,a*width/3);
        glVertex3f(b/4,a-0.01,b*width);
        glVertex3f(a/4,a-0.01,b*width);
        glVertex3f(a/4,a-0.01,a*width/3);
        glEnd();
}

//From genpfault on stackoverflow https://stackoverflow.com/a/7687413 
void drawSphere(double r, int lats, int longs) {
    int i, j;
    for(i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(r * x * zr0, r * y * zr0, r * z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(r * x * zr1, r * y * zr1, r * z1);
        }
        glEnd();
    }
}


void Viewer::draw() {
        // Exercice 1,2
        //transformeMatrix();
        //glPushMatrix();
        //drawMaison();
        //glPopMatrix();

        //Exercice 3
        glColor3f(1.0, 1.0, 0);
        drawSphere(2.0,10,10);
        glPushMatrix();
        
        glRotatef(angle, 0, 1,0);
        glTranslatef(5.0, 0, 0);

        glColor3f(0.0, 0.0, 1.0);
        drawSphere(1, 10, 10);
        glPopMatrix();

        glColor3f(1.0, 0, 0);
        glPushMatrix();
        glRotatef(angle *2, 1, 0, 0);
        glTranslatef(0, 3, 0);
        drawSphere(0.5, 10, 10);
        glPopMatrix();

        angle +=3.0f;
}



void Viewer::init() {
  // Restore previous viewer state.
  restoreStateFromFile();
  setSceneRadius(15.0);
  glDisable(GL_LIGHTING);

  // Opens help window
  help();
}

QString Viewer::helpString() const {
  QString text("<h2>S i m p l e V i e w e r</h2>");
  text += "Use the mouse to move the camera around the object. ";
  text += "You can respectively revolve around, zoom and translate with the "
          "three mouse buttons. ";
  text += "Left and middle buttons pressed together rotate around the camera "
          "view direction axis<br><br>";
  text += "Pressing <b>Alt</b> and one of the function keys "
          "(<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
  text += "Simply press the function key again to restore it. Several "
          "keyFrames define a ";
  text += "camera path. Paths are saved when you quit the application and "
          "restored at next start.<br><br>";
  text +=
      "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
  text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save "
          "a snapshot. ";
  text += "See the <b>Keyboard</b> tab in this window for a complete shortcut "
          "list.<br><br>";
  text += "Double clicks automates single click actions: A left button double "
          "click aligns the closer axis with the camera (if close enough). ";
  text += "A middle button double click fits the zoom of the camera and the "
          "right button re-centers the scene.<br><br>";
  text += "A left button double click while holding right button pressed "
          "defines the camera <i>Revolve Around Point</i>. ";
  text += "See the <b>Mouse</b> tab and the documentation web pages for "
          "details.<br><br>";
  text += "Press <b>Escape</b> to exit the viewer.";
  return text;
}
