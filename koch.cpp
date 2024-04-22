#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define PIE 3.1415926535898

int n;

using namespace std;

void Koch(float xa, float ya, float xd, float yd, int n)
{
    float xc, yc, xb, yb, midx, midy;

    xb = (2 * xa + xd) / 3;
    xc = (2 * xd + xa) / 3;

    yb = (2 * ya + yd) / 3;
    yc = (2 * yd + ya) / 3;

    midx = xb + ((xc - xb) * cos((-60 * PIE) / 180)) + ((yc - yb) * sin((-60 * PIE) / 180));
    midy = yb - ((xc - xb) * sin((-60 * PIE) / 180)) + ((yc - yb) * cos((-60 * PIE) / 180));

    if (n > 0)
    {
        Koch(xa, ya, xb, yb, n - 1);
        Koch(xb, yb, midx, midy, n - 1);
        Koch(midx, midy, xc, yc, n - 1);
        Koch(xc, yc, xd, yd, n - 1);
    }
    else
    {
        glBegin(GL_LINE_STRIP);
        
        glVertex2f(xa, ya);
        
        glVertex2f(xb, yb);
      
        glVertex2f(midx, midy);
        
        glVertex2f(xc, yc);
       
        glVertex2f(xd, yd);
        glEnd();
    }
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
   
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    float w = glutGet(GLUT_WINDOW_WIDTH);
    float h = glutGet(GLUT_WINDOW_HEIGHT);

    Koch(w * 0.1, h * 0.5, w * 0.9, h * 0.5, n); // Draw a horizontal line
    glFlush();
}

int main(int argc, char **argv)
{
    cout << "Enter the number of iterations: ";
    cin >> n;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(300, 50);

    glutCreateWindow("Koch Curve");

    init();
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

