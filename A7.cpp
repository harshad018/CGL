#include <GL/glut.h>
#include <iostream>
#include <math.h>



int n;

using namespace std;

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

void Koch(float xa, float ya, float xd, float yd, int n)
{
    float xc, yc, xb, yb, midx, midy;

    xb = (2 * xa + xd) / 3;
    xc = (2 * xd + xa) / 3;

    yb = (2 * ya + yd) / 3;
    yc = (2 * yd + ya) / 3;
    
    double angle = (-60 * M_PI) / 180;

    midx = xb + ((xc - xb) * cos(angle)) + ((yc - yb) * sin(angle));
    midy = yb - ((xc - xb) * sin(angle)) + ((yc - yb) * cos(angle));

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

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w/2, w/2, -h/2, h/2); 
    glMatrixMode(GL_MODELVIEW);
}

void draw()
{	int choice;
	
	cout<<"1.Brazier \n2.Koch \nWhich curve you want to use: ";
	cin>>choice;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    switch(choice) {
        case 1:
            drawQuadrants();
            brazier();
            break;
        case 2:
            cout << "Enter the number of iterations for Koch curve: ";
   	    cin >> n;
            float w = glutGet(GLUT_WINDOW_WIDTH);
            float h = glutGet(GLUT_WINDOW_HEIGHT);
            Koch(-w/2, 0, w/2, 0, n); 
            break;
    }
  
    glFlush();
    
}



int main(int argc, char **argv)
{
    

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(300, 50);

    glutCreateWindow("Draw Curve");

    init();

    glutReshapeFunc(reshape);

    

    glutDisplayFunc(draw); 
    glutMainLoop();
}

