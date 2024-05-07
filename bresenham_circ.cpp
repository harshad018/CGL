#include <iostream>
#include <GL/glut.h>
using namespace std;

float x1;
float y1;
float dl;
float dt;
float r;
float xc;
float yc;

void mh();
void mv();
void md();
void init();
void drawQuadrants();
void bresenham_circ();
void drawEye(float offsetX, float offsetY);
void smile();
void display();

void init() {
    glClearColor(1, 1, 1, 0); // Background color and foreground color of screen
    gluOrtho2D(-320, 320, -240, 240); // Set screen dimensions
}

void drawQuadrants() {
    glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(320, 0);

    glVertex2i(0, -240);
    glVertex2i(0, 240);
    glEnd();
}

void bresenham_circ() {
    x1 = 0;
    y1 = r;
    dt = 2 * (1 - r);
    int limit = 0;

    while (y1 >= limit) {
        glBegin(GL_POINTS);
        glVertex2i(xc + x1, yc + y1);
        glVertex2i(xc + x1, yc - y1);
        glVertex2i(xc - x1, yc - y1);
        glVertex2i(xc - x1, yc + y1);
        glEnd();

        if (dt < 0) {
            dl = 2 * dt + 2 * y1 - 1;
            if (dl <= 0) {
                mh();
            } else {
                md();
            }
        } else if (dt > 0) {
            dl = 2 * dt - 2 * x1 - 1;
            if (dl <= 0) {
                md();
            } else {
                mv();
            }
        } else if (dt == 0) {
            md();
        }
    }
}

void mh() {
    x1 = x1 + 1;
    dt = dt + 2 * x1 + 1;
}

void md() {
    x1 = x1 + 1;
    y1 = y1 - 1;
    dt = dt + 2 * x1 - 2 * y1 + 2;
}

void mv() {
    y1 = y1 - 1;
    dt = dt - 2 * y1 + 1;
}

void drawEye(float offsetX, float offsetY) {
    float eyeRadius = r / 6;
    x1 = 0;
    y1 = eyeRadius;
    dt = 2 * (1 - eyeRadius);
    int limit = 0;

    while (y1 >= limit) {
        glBegin(GL_POINTS);
        glVertex2i(xc + offsetX + x1, yc + offsetY + y1);
        glVertex2i(xc + offsetX + x1, yc + offsetY - y1);
        glVertex2i(xc + offsetX - x1, yc + offsetY - y1);
        glVertex2i(xc + offsetX - x1, yc + offsetY + y1);
        glEnd();

        if (dt < 0) {
            dl = 2 * dt + 2 * y1 - 1;
            if (dl <= 0) {
                mh();
            } else {
                md();
            }
        } else if (dt > 0) {
            dl = 2 * dt - 2 * x1 - 1;
            if (dl <= 0) {
                md();
            } else {
                mv();
            }
        } else if (dt == 0) {
            md();
        }
    }
}

void smile() {
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    // Coordinates for the endpoints of the line
    glVertex2f(xc - 10, yc - 30); // Start of the line
    glVertex2f(xc + 10, yc - 30); // End of the line
    glEnd();
}


void display() {
    glColor3f(0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawQuadrants();
    bresenham_circ();
    smile();
    drawEye(-20, 20); // Draw left eye
    drawEye(20, 20); // Draw right eye
    glFlush();
}

int main(int argc, char **argv) {
    cout << "Enter the value of radius: ";
    cin >> r;
    cout << "Enter the coordinates of center x, y: ";
    cin >> xc >> yc;

    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sample Program");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

