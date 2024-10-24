void drawPlane(){
        glLineWidth(5);
        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 1.0, 1.0); // blue
        
        glVertex3f(-1.2 ,-0.5, 0);
        glVertex3f(0  ,-0.5, 0);
        glVertex3f(0  ,-1.5, 0);
        glVertex3f(0.5,-1.5, 0); // right wing
        glVertex3f(1.0,-0.5, 0);
        glVertex3f(3  , 0  , 0); // nose of the plane
        glVertex3f(1.0, 0.5, 0);
        glVertex3f(0.5, 1.5, 0); // left wing
        glVertex3f(0  , 1.5, 0);
        glVertex3f(0  , 0.5, 0);
        glVertex3f(-1.2 , 0.5, 0);
        glVertex3f(-1.2 ,-0.5, 0); // back

        glEnd();

        glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 0.0, 0.0); // red

        glVertex3f(-0.3 , 0, 0);
        glVertex3f(-1.4, 0, 0.5);
        glVertex3f(-1.2, 0, 0);

        glEnd();

}
