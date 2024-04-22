#include <GL/glut.h>
#include <iostream>
using namespace std;

int x1, y1, x2, y2;
int x3, y3, x4, y4;

void drawQuadrants() {
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2i(-320, 0);
    glVertex2i(320, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 240);
    glVertex2i(0, 0);
    glEnd();
}

void drawLine(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

void dda_solid() {
    float length;
    if (abs(x4 - x3) > abs(y4 - y3)) {
        length = abs(x4 - x3);
    } else {
        length = abs(y4 - y3);
    }

    float dx = (x4 - x3) / length;
    float dy = (y4 - y3) / length;

    float x = x3 + 0.5;
    float y = y3 + 0.5;

    int i = 1;
    while (i <= length) {
        glPointSize(1);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();

        x = x + dx;
        y = y + dy;
        i = i + 1;
    }
}

void dda_dotted() {
    float length;
    if (abs(x4 - x3) > abs(y4 - y3)) {
        length = abs(x4 - x3);
    } else {
        length = abs(y4 - y3);
    }

    float dx = (x4 - x3) / length;
    float dy = (y4 - y3) / length;

    float x = x3 + 0.5;
    float y = y3 + 0.5;

    int i = 1;
    while (i <= length) {
        if (i % 5 == 0) {
            glPointSize(1);
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
        }

        x = x + dx;
        y = y + dy;
        i = i + 1;
    }
}

void dda_dashed() {
    float length;
    if (abs(x4 - x3) > abs(y4 - y3)) {
        length = abs(x4 - x3);
    } else {
        length = abs(y4 - y3);
    }

    float dx = (x4 - x3) / length;
    float dy = (y4 - y3) / length;

    float x = x3 + 0.5;
    float y = y3 + 0.5;

    int i = 1;
    int flag = 1;
    while (i <= length) {
        if (i % 4 == 0) {
            if (flag == 0) {
                flag = 1;
            } else {
                glPointSize(1);
                glBegin(GL_POINTS);
                glVertex2i(x, y);
                glEnd();
                flag = 0;
            }
        } else {
            if (flag == 1) {
                glPointSize(1);
                glBegin(GL_POINTS);
                glVertex2i(x, y);
                glEnd();
            }
        }

        x = x + dx;
        y = y + dy;
        i = i + 1;
    }
}

void bresenham_solid() {
    int x = x3;
    int y = y3;

    float dx = x4 - x3;
    float dy = y4 - y3;

    float m = dy / dx;

    float e = m - 0.5;

    for (int i = 0; i < dx; i++) {
        glPointSize(1);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();

        while (e > 0) {
            y = y + 1;
            e = e - 1;
        }
        x = x + 1;
        e = e + m;
    }
}

void bresenham_dotted() {
    int x = x3;
    int y = y3;

    float dx = x4 - x3;
    float dy = y4 - y3;

    float m = dy / dx;

    float e = m - 0.5;

    for (int i = 0; i < dx; i++) {
        if (i % 5 == 0) {
            glPointSize(1);
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
        }

        while (e > 0) {
            y = y + 1;
            e = e - 1;
        }
        x = x + 1;
        e = e + m;
    }
}

void bresenham_dashed() {
    int x = x3;
    int y = y3;

    float dx = x4 - x3;
    float dy = y4 - y3;

    float m = dy / dx;

    float e = m - 0.5;

    for (int i = 0; i < dx; i++) {
        if (i % 4 == 0) {
            if (i % 8 == 0) {  // To create a dashed pattern
                glPointSize(1);
                glBegin(GL_POINTS);
                glVertex2i(x, y);
                glEnd();
            }
        } else {
            glPointSize(1);
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
        }

        while (e > 0) {
            y = y + 1;
            e = e - 1;
        }
        x = x + 1;
        e = e + m;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawQuadrants();

    int ch1, ch2;

    do {
        cout << "Which line drawing algorithm you want to use? \n1.DDA \n2.Bresenham \nEnter your choice: ";
        cin >> ch1;

        switch (ch1) {
            case 1:
                do {
                    cout << "What type of line do you want? \n1.solid \n2.dotted \n3.dashed \nEnter your choice: ";
                    cin >> ch2;
                    switch (ch2) {
                        case 1:
                            dda_solid();
                            break;

                        case 2:
                            dda_dotted();
                            break;

                        case 3:
                            dda_dashed();
                            break;
                    }
                } while (ch2 < 4);
                break;

            case 2:
                do {
                    cout << "What type of line do you want? \n1.solid \n2.dotted \n3.dashed \nEnter your choice: ";
                    cin >> ch2;
                    switch (ch2) {
                        case 1:
                            bresenham_solid();
                            break;

                        case 2:
                            bresenham_dotted();
                            break;

                        case 3:
                            bresenham_dashed();
                            break;
                    }
                } while (ch2 < 1);
                break;
        }
    } while (ch1 < 1);

    glFlush();
}

void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x1 = 0;
        y1 = 0;
        x2 = x - 320;
        y2 = 240 - y;
        drawLine(x1, y1, x2, y2);
        glutPostRedisplay();  // Force a redraw
    } else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        exit(0);  // Proper exit
    }
}

void myinit() {
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(-320, 320, -240, 240);
}

int main(int argc, char **argv) {
    cout << "Enter the value of x3,y3,x4,y4" << endl;
    cin >> x3 >> y3 >> x4 >> y4;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Draw Line With Mouse Click");
    myinit();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

