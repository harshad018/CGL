#include<iostream>
#include<GL/glut.h>
#include<unistd.h>
using namespace std;

int n, xmin, ymin, xmax, ymax;
float x[10], y[10];
float xx[10], yy[10];
int i;
float m[20];

void init()
{
    glClearColor(1, 0, 1, 0);
    gluOrtho2D(0, 640, 0, 480);
}
void clearscreen(){
	sleep(2);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


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
        cout << "enter the x, y vertices" << endl;
        for ( i = 0; i < n; i++)
        {
            cout << "enter " << i + 1 << " vertex" << endl;
            cin >> x[i]>>y[i];
            
        }
       
       	x[i] = x[0];
       	y[i] = y[0];
        
        
    }
}



void window(int xmin, int ymin, int xmax, int ymax)
{
    
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmin, ymax);
    glVertex2i(xmax, ymax);
    glVertex2i(xmax, ymin);
   glEnd();
    
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
    glColor3f(0,1,1);
    window(xmin, ymin, xmax, ymax);
    glFlush();
}

void slope()
{
    for(int i=0;i<n;i++)
   {
   	if((x[i+1]-x[i])==0){
   	m[i] = 0;
   	}
   	else{
     		m[i]=(y[i+1]-y[i])/(x[i+1]-x[i]);
     }
   }
}

void Lclip()
{
  int k = 0;
  slope();
  for(int i=0;i<n;i++)
  {
  if(x[i]>xmin && x[i+1] > xmin)
  {
   	xx[k]=x[i+1];
   	yy[k]=y[i+1];
   	k++;
   }
   else if(x[i]>xmin && xmin > x[i+1])
   {
   	xx[k]=xmin;
   	yy[k]=y[i]+m[i]*(xmin-x[i]);
   	k++;
   }
   else if(x[i]<xmin && x[i+1]>xmin)
   {
    	xx[k]=xmin;
    	yy[k]=y[i]+m[i]*(xmin-x[i]);
    	k++;
    	xx[k]=x[i+1];
    	yy[k]=y[i+1];
    	k++;
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
  for(i=0;i<n;i++)
  {
  if(x[i]<xmax && x[i+1]<xmax)
  {
   	xx[k]=x[i+1];
   	yy[k]=y[i+1];
  	 k++;
   }
   else if(x[i]<xmax  && x[i+1]>xmax)
   {
   	xx[k]=xmax;
   	yy[k]=y[i]+m[i]*(xmax-x[i]);
   	k++;
   }
   else if (x[i]>xmax  &&x[i+1]<xmax)
   {
    	xx[k]=xmax;
    	yy[k]=y[i]+m[i]*(xmax-x[i]);
    	k++;
   	 xx[k]=x[i+1];
    	yy[k]=y[i+1];
    	k++;
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

void topclip()
{
    int k = 0;
    slope(); 

    for (int i = 0; i < n; i++)
    {
        if (y[i] <= ymax) 
        {
            xx[k] = x[i];
            yy[k] = y[i];
            k++;
            
            if (y[i + 1] > ymax) 
            {
                xx[k] = x[i] + (ymax - y[i]) / m[i];
                yy[k] = ymax;
                k++;
            }
        }
        else if (y[i] > ymax && y[i + 1] <= ymax) 
        {
            xx[k] = x[i] + (ymax - y[i]) / m[i]; 
            yy[k] = ymax;
            k++;
            xx[k] = x[i + 1];
            yy[k] = y[i + 1];
            k++;
        }
    }

    n = k;

   
    for (int i = 0; i < n; i++)
    {
        x[i] = xx[i];
        y[i] = yy[i];
    }

    
    x[k] = x[0];
    y[k] = y[0];
}
void bottomclip()
{
    int k = 0;
    slope();

    for (int i = 0; i < n; i++)
    {
        if (y[i] >= ymin) 
        {
            xx[k] = x[i];
            yy[k] = y[i];
            k++;

            if (y[i + 1] < ymin) 
            {
                xx[k] = x[i] + (ymin - y[i]) / m[i];
                yy[k] = ymin;
                k++;
            }
        }
        else if (y[i] < ymin && y[i + 1] >= ymin) 
        {
            xx[k] = x[i] + (ymin - y[i]) / m[i]; 
            yy[k] = ymin;
            k++;
            xx[k] = x[i + 1];
            yy[k] = y[i + 1];
            k++;
        }
    }

    n = k;

   
    for (int i = 0; i < n; i++)
    {
        x[i] = xx[i];
        y[i] = yy[i];
    }

   
    x[k] = x[0];
    y[k] = y[0];
}

void display(){

//drawQuadrants();

    

    drawPolygon();
    clearscreen();
    Lclip();
    
    drawPolygon();
    
    clearscreen();
    
    Rclip();
    drawPolygon();
    clearscreen();

    topclip();
    drawPolygon();
    clearscreen();
    
    bottomclip();
    drawPolygon();
    

}
int main(int argc, char**argv)
{
    getdata();

    xmin = 100;
    ymin = 100;
    xmax = 200;
    ymax = 200;

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
