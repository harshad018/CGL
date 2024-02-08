#include<iostream>
#include<GL/glut.h>
using namespace std;
int x1,y1,x2,y2;

void init()
{
	glClearColor(0,0,0,0);//Background color and foreground color of screen
	gluOrtho2D(-320,320,-240,240);//set screen dimensions
}

void drawQuadrants()//for display 4 quadrants
{
	glBegin(GL_LINES);
		glVertex2i(-320,0);
		glVertex2i(320,0);
		
		glVertex2i(0,-240);
		glVertex2i(0,240);
	glEnd();
	
}

void mh(int x1, int y1, int dt){

	x1 = x1 + 1;
	dt = dt + 2*x1 + 1;


}

void md(int x1, int y1, int dt){

	x1 = x1 + 1;
	y1 = y1 - 1;
	dt = dt + 2*x1 - 2*y1 + 2;


}

void mv(int x1, int y1, int dt){

	y1 = y1 - 1;
	dt = dt - 2*x1 + 1;


}
void bresenham(){
	int r = 5;
	x1 = 0;
	y1 = r;
	
	int dt = 2*(1 - r);
	
	int limit = 0;
	
	while( y1 >= limit){
	
		glBegin(GL_POINTS);
					glVertex2i(x1,y1);
				glEnd();
	
	if( dt < 0) {
	
		float dl = 2*dt + 2*y1 - 1;
		
		if ( dl <= 0){
		
			mh(x1,y1,dt);
		
		}
		else{
		
			md(x1,y1,dt);
		
		}
	}
	else if( dt > 0){
	
		float dl2 = 2*dt - 2*x1 - 1;
		
		if ( dl2 <= 0){
		
			md(x1,y1,dt);
		
		}
		else{
		
			mv(x1,y1,dt);
		
		}
	
	
	}
	else if( dt = 0){
		md(x1,y1,dt);
	
	}
	
	
	
	}
	
	

}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//clear the screen
	
	drawQuadrants();
	bresenham();
	
	glFlush(); 	
}

int main(int argc,char **argv)
{	
	glutInit(&argc,argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Sample Program");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}


