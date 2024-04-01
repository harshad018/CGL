#include<iostream>
#include<GL/glut.h>
#include "stack.cpp";
using namespace std;

stack s;
int A[2][2] = {{1,2},
		{3,4},
		};
		
int B[2][2] = {{5,6},
		{7,8},
		};
		
int C[2][2];

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
void drawPolygon(){

	glBegin(GL_POLYGON);
		glVertex2i(100,100);
		glVertex2i(150,100);
		glVertex2i(150,150);
		glVertex2i(100,150);
	glEnd();


}

void multiply(){

	int add;

	for(int i = 0; i < 2 ; i++){
	
		for( int j = 0 ; j < 2 ; j++){
			C[i][j-1] = add;
			int result = A[i][j] * B[j][i];
			s.push(result);
		
		
		}
			int first = s.pop();
			int second = s.pop();
			
			add = first + second;
			
			
	
	
	
	}

cout<<C[2][2]<<endl;

}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//clear the screen
	
	drawQuadrants();
	drawPolygon();
	
	
	glFlush(); 	
}

int main(int argc,char **argv)

{

	mutliply();
	glutInit(&argc,argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Sample Program");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
