#include<iostream>
#include<GL/glut.h>
using namespace std;
int x1,y1,x2,y2;
float c[3];
float bcolor[3] = {1.0,1.0,1.0};
float fillColor[3] = {1.0,0.0,0.0};
void init()
{
	glClearColor(0,0,0,0);//Background color and foreground color of screen
	gluOrtho2D(-320,320,-240,240);//set screen dimensions
}

/*void drawQuadrants()//for display 4 quadrants
{
	glBegin(GL_LINES);
		glVertex2i(-320,0);
		glVertex2i(320,0);
		
		glVertex2i(0,-240 the screen
	
	drawQuadrants();
	drawpolygon();
	);                                                    
		glVertex2i(0,240);
	glEnd();
	
}
*/
void drawpolygon()
{
 glBegin(GL_LINE_LOOP);
       glVertex2i(x1,y1);
       glVertex2i(x2,y1);
       glVertex2i(x2,y2);
       glVertex2i(x1,y2);
    glEnd(); 
  }
    
void getPixel(int x, int y){
 
 	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, c);
 
 
}

void setPixel(int x, int y){

	glColor3fv(fillColor);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();

}  

void boundaryFill(int x, int y){
	
	getPixel(x,y);
	
	if(c[0]!=bcolor[0]&&c[1]!=bcolor[1]&&c[2]!=bcolor[2]){
		setPixel(x,y);
		boundaryFill(x,y+1);
        	boundaryFill(x+1,y);
        	boundaryFill(x,y-1);
        	boundaryFill(x-1,y);
	
	}

}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//clear
	drawpolygon();
	boundaryFill(150,100);
	
	
	glFlush(); 	
}

int main(int argc,char **argv)
{
   
   	cin>>x1;
   	cin>>y1;
   	cin>>x2;
   	cin>>y2;
	glutInit(&argc,argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Sample Program");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
