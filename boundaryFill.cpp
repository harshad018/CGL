#include<iostream>
#include<GL/glut.h>
using namespace std;
int X1,X2,Y1,Y2,x,y;
float Color[3];
float bgColor[3] = {1,1,1};
float fillColor[3] = {1,0,0}; // Change this line
void init()
{
	glClearColor(0,0,0,0);
	gluOrtho2D(0,640,0,480);//set screen dimensions
}

void setPixel(int x,int y,float fillColor[3])
{
	glColor3fv(fillColor);
	glBegin(GL_POINTS);
        	glVertex2i(x,y);
        glEnd(); 
        glFlush();
}

void getPixel(int x,int y,float Color[3])
{
	glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,Color);
	
}

void boundaryFill(int x, int y,float fillColor[3],float bgColor[3]){
	
	
	 getPixel(x,y,Color);
	
	
	if((Color[0] != bgColor[0] && Color[1] != bgColor[1] && Color[2] != bgColor[2]) ){
	
		setPixel(x,y,fillColor);
		boundaryFill(x+1,y,fillColor,bgColor);
		boundaryFill(x-1,y,fillColor,bgColor);
		boundaryFill(x,y+1,fillColor,bgColor);        	
        	boundaryFill(x,y-1,fillColor,bgColor);
	}

}

void drawPolygon(){
glColor3fv(bgColor);
	glBegin(GL_LINES);
		glVertex2i(X1,Y1);
		glVertex2i(X1,Y2);
		glVertex2i(X1,Y2);
		glVertex2i(X2,Y2);
		glVertex2i(X2,Y2);
		glVertex2i(X2,Y1);
		glVertex2i(X2,Y1);
		glVertex2i(X1,Y1);
	glEnd();

glFlush();
}
void display()
{glClearColor(0,0,0,0);//Background color and foreground color of screen
	glClear(GL_COLOR_BUFFER_BIT);//clear
	drawPolygon();
	
	boundaryFill(40,60,fillColor,bgColor);
	
	
	glFlush(); 	
}

int main(int argc,char **argv)
{
   
   	cout<<"Enter the value of X1 coordinate:"<<endl;
	cin>>X1;
	cout<<"Enter the value of Y1 coordinate:"<<endl;
	cin>>Y1;
	cout<<"Enter the value of X2 coordinate:"<<endl;
	cin>>X2;
	cout<<"Enter the value of Y2 coordinate:"<<endl;
	cin>>Y2;
	glutInit(&argc,argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Sample Program");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
