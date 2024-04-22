#include <iostream>
#include <GL/glut.h>
#include <cmath>
using namespace std;


int x1_, x2_, x3_, x4_;
int y1_, y2_, y3_, y4_;
double xt, yt;

void init() {
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(-320, 320, -240, 240);
}

void drawQuadrants() {
    glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(320, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 240);
    glEnd();
}

void brazier() {
    cout << "Enter the four coordinates: " << endl;
    double x1, x2, x3, x4, y1, y2, y3, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    for (double u = 0.0; u < 1.0; u += 0.005) {
        xt = pow(u, 3) * x4 + (3 * x3 * pow(u, 2) * (1 - u)) + (3 * x2 * u * pow(1 - u, 2)) + x1 * pow(1 - u, 3);
        yt = pow(u, 3) * y4 + (3 * y3 * pow(u, 2) * (1 - u)) + (3 * y2 * u * pow(1 - u, 2)) + y1 * pow(1 - u, 3);
        glBegin(GL_POINTS);
        glVertex2f(xt, yt);
        glEnd();
    }
    
    glBegin(GL_LINES);
    	glVertex2f(x1,y1);
    	glVertex2f(x2,y2);
    	glVertex2f(x3,y3);
    	glVertex2f(x4,y4);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawQuadrants();
    brazier();
    glFlush(); // Add this to ensure all OpenGL commands are executed
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sample Program");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

