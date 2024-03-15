#include<iostream>
#include<GL/glut.h>
#include<stdlib.h>
using namespace std;

int n, xmin, ymin, xmax, ymax;
int x[10], y[10];
int xx[20], yy[20];
int i;
float m[20];

void init()
{
    glClearColor(1, 0, 1, 0);
    gluOrtho2D(0, 640, 0, 480);
}

void getdata()
{
    cout << "Enter the number of vertices " << endl;
    cin >> n;
    if (n < 2)
    {
        cout << "invlid number of vertices" << endl;
    }
    else
    {
        cout << "enter the x vertices" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "enter " << i + 1 << " vertex" << endl;
            cin >> x[i];
        }
        cout << "enter the y vertices" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "enter " << i + 1 << " vertex" << endl;
            cin >> y[i];
        }
    }
}

void drawQuadrants()
{
    glBegin(GL_LINES);

    glVertex2i(-320, 0);
    glVertex2i(320, 0);

    glVertex2i(0, -240);
    glVertex2i(0, 240);

    glEnd();
}

void window(int xmin, int ymin, int xmax, int ymax)
{
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmin, ymax);
    glVertex2i(xmax, ymax);
    glVertex2i(xmax, ymin);
   glEnd();
    glFlush();
}

void drawPolygon()
{
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++)
    {
        glVertex2i(x[i], y[i]);
    }
    glEnd();
    glFlush();
}

void slope()
{
    for(int i=0;i<n;i++)
   {
     m[i]=(y[i+1]-y[i])/(x[i+1]-x[i]);
   }
}

void Lclip()
{
    int k = 0;
    

    slope();

    for (int i = 0; i < n; i++)
    {
        if (x[i] > xmin && x[i + 1] > xmin)
        {
            xx[k] = x[i + 1];
            yy[k] = y[i + 1];
            k++;
        }
        else if (x[i] > xmin && x[i + 1] < xmin)
        {
            xx[k] = xmin;
            if (m[i] == 100000)
            {
                yy[k] = y[i];
            }
            else
            {
                yy[k] = y[i] + m[i] * (xmin - x[i]);
            }
            k++;
        }
        else if (x[i] < xmin && x[i + 1] > xmin)
        {
            xx[k] = xmin;
            xx[k + 1] = x[i + 1];
            yy[k] = y[i] + m[i] * (xmin - x[i]);
            yy[k + 1] = y[i + 1];
            k += 2;
        }
    }

    n = k;

    for (i = 0; i < n; i++)
    {
        x[i] = xx[i];
        y[i] = yy[i];
    }
    
    x[i] = x[0];
    y[i] = y[0];
}

void Rclip()
{
    int k = 0;
   

    slope();

    for (int i = 0; i < n; i++)
    {
        if (x[i] < xmax && x[i + 1] < xmax)
        {
            xx[k] = x[i + 1];
            yy[k] = y[i + 1];
            k++;
        }
        else if (x[i] < xmax && x[i + 1] > xmax)
        {
            xx[k] = xmax;
            if (m[i] == 100000)
            {
                yy[k] = y[i];
            }
            else
            {
                yy[k] = y[i] + m[i] * (xmax - x[i]);
            }
            k++;
        }
        else if (x[i] > xmax && x[i + 1] < xmax)
        {
            xx[k] = xmax;
            xx[k + 1] = x[i + 1];
            yy[k] = y[i] + m[i] * (xmax - x[i]);
            yy[k + 1] = y[i + 1];
            k += 2;
        }
    }

    n = k;

    for (i = 0; i < n; i++)
    {
        x[i] = xx[i];
        y[i] = yy[i];
    }
}


void display(){

//drawQuadrants();

    window(xmin, ymin, xmax, ymax);

    drawPolygon();

    Lclip();

    Rclip();

    window(xmin, ymin, xmax, ymax);

    drawPolygon();

    glFlush();









}
int main(int argc, char**argv)
{
    getdata();

    xmin = -150;
    ymin = -150;
    xmax = 150;
    ymax = 150;

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(640, 480);

    glutInitWindowPosition(0, 0);

    glutCreateWindow("Line Clipping");\
    
    

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    
    
    return 0;
}
