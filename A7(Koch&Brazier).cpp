#include <iostream>
#include <GL/glut.h>
#include <cmath>
using namespace std;
#define PIE 3.1415926535898
int n;
//for brazier
int x1, x2, x3, x4;
int Y1, y2, y3, y4;
double xt, yt;

void init() {
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(-320, 320, -240, 240);
}


//function for brazier
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
//function for koch
void reshape(int h, int w)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}
//function for koch
void drawkoch()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    float w = glutGet(GLUT_WINDOW_WIDTH);
    float h = glutGet(GLUT_WINDOW_HEIGHT);

    Koch(w * 0.1, h * 0.5, w * 0.9, h * 0.5, n); // Draw a horizontal line
    glFlush();
}

void brazier() 
{
 cout << "Enter the four coordinates: " << endl;
    double x1, x2, x3, x4, Y1, y2, y3, y4;
    cin >> x1 >> Y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4; 

    for (double u = 0.0; u < 1.0; u += 0.005) {
        xt = pow(u, 3) * x4 + (3 * x3 * pow(u, 2) * (1 - u)) + (3 * x2 * u * pow(1 - u, 2)) + x1 * pow(1 - u, 3);
        yt = pow(u, 3) * y4 + (3 * y3 * pow(u, 2) * (1 - u)) + (3 * y2 * u * pow(1 - u, 2)) + Y1 * pow(1 - u, 3);
        glBegin(GL_POINTS);
        glVertex2f(xt, yt);
        glEnd();
    }
    
    glBegin(GL_LINES);
    	glVertex2f(x1,Y1);
    	glVertex2f(x2,y2);
    	glVertex2f(x3,y3);
    	glVertex2f(x4,y4);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
       int ch;
     do{ cout<<"Enter your choice\n1.Koch Curve\n2.Brazier Curve\n0.Exit"<<endl;
     cin>>ch;
  
   switch(ch)
    {

     
     case 1: cout << "Enter the number of iterations: ";
             cin >> n;
             reshape(800,800);
               drawkoch();
               break;
     case 2: drawQuadrants();
            brazier();
            break;  
       case 0:
                cout << "Exiting..." << endl;
                exit(0);
                break;

   }
      glFlush();
      
  }  while(true);

}


int main(int argc, char** argv) {

 
      glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sample Program");
    
    
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
