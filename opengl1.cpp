#include <iostream>
#include <GL/glut.h>

int fillflag=0;

float bgCol[3]={0.0,1.0,1.0}; //Background Color
float bdCol[3]={0.0,0.0,1.0}; //Boundary Color
float fillCol[3]={1.0,0.0,0.0}; //Red fill Color
void boundaryfill(int x,int y,float fillcolor[3],float bdcolor[3]);
void floodfill(int x,int y,float fillcolor[3],float oldcolor[3]);
void setPixel(int x,int y, float f[3])
{glColor3fv(f);
	glBegin(GL_POINTS);
		
		glVertex2i(x,y);
	glEnd();
	glFlush();
}

void getPixel(int x,int y,float pixels[3])
{
	glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,pixels);
}

void drawPolygon(int x1,int y1,int x2,int y2)
{
	glColor3fv(bdCol); //Blue Boundary
	glBegin(GL_LINE_LOOP);
		glVertex2i(x1,y1);
		glVertex2i(x1,y2);
		glVertex2i(x2,y2);
		glVertex2i(x2,y1);
	glEnd();
	glFlush();
}

void display()
{
	glClearColor(0.0,1.0,1.0,1.0); //window Color
	glClear(GL_COLOR_BUFFER_BIT);
	drawPolygon(150,250,200,300);
	boundaryfill(170,270,fillCol,bdCol);
	glFlush();
}

void floodfill(int x,int y,float fillcolor[3],float oldcolor[3])
{
	float color[3];
	getPixel(x,y,color);
	if(color[0]==oldcolor[0] && color[1]==oldcolor[1] && color[2]==oldcolor[2])
	{
		setPixel(x,y,fillcolor);
		floodfill(x,y-1,fillcolor,oldcolor);
		floodfill(x,y+1,fillcolor,oldcolor);
		floodfill(x+1,y,fillcolor,oldcolor);
		floodfill(x-1,y,fillcolor,oldcolor);		
		
	}
}

void boundaryfill(int x,int y,float fillcolor[3],float bdcolor[3])
{
	float color[3];
	getPixel(x,y,color);
	if(((color[0]!=fillcolor[0])||(color[1]!=fillcolor[1])||(color[2]!=fillcolor[2])) && ((color[0]!=bdcolor[0])||(color[1]!=bdcolor[1])||(color[2]!=bdcolor[2])))
	{
		setPixel(x,y,fillcolor);
		boundaryfill(x+1,y,fillcolor,bdcolor);
		boundaryfill(x-1,y,fillcolor,bdcolor);
		boundaryfill(x,y+1,fillcolor,bdcolor);
		boundaryfill(x,y-1,fillcolor,bdcolor);
		/*boundaryfill(x+1,y-1,fillcolor,bdcolor);
		boundaryfill(x-1,y-1,fillcolor,bdcolor);
		boundaryfill(x+1,y+1,fillcolor,bdcolor);
		boundaryfill(x-1,y-1,fillcolor,bdcolor);*/
	}
}

/*void mouse(int btn, int state,int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		int xi=x;
		int yi=480-y;
		
		if(fillflag==1)
			floodfill(xi,yi,fillCol,bgCol);
		else if(fillflag==2)
			boundaryfill(xi,yi,fillCol,bdCol);
	}
}

//Menu Function
void fillMenu(int option)
{
	if(option==1)
		fillflag=1;
	else if(option==2)
		fillflag=2;
	//display();
}
*/
void myInit()
{
  	gluOrtho2D(0 , 640 , 0 , 480);
}



int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200,200);
	glutCreateWindow("Polygon Filling ");
	myInit();
	glutDisplayFunc(display);
	
	/*//Menu-Driven Code
	glutCreateMenu(fillMenu);
	glutAddMenuEntry("Flood Fill",1);
	glutAddMenuEntry("Boundary Fill",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutMouseFunc(mouse);*/
	glutMainLoop();
	return 0;
}
