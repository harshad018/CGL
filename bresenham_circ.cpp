#include<iostream>
#include<GL/glut.h>
using namespace std;
float x1;
float y1;
float dl;
float dt;
float r;
float xc;
float yc;
void mh();
void mv();
void md();
void init()
{
	glClearColor(1,1,1,0);//Background color and foreground color of screen
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

void bresenham_circ(){

	
	
	x1 =0;
	y1 = r;
	
	dt = 2*(1-r);
	int limit = 0;
	
	while (y1 >= limit){
		
		glBegin(GL_POINTS);
			glVertex2i(xc+x1,yc+y1);
			glVertex2i(xc+x1,yc-y1);
			glVertex2i(xc-x1,yc-y1);
			glVertex2i(xc-x1,yc+y1);
			
		glEnd();
		
		if (dt < 0){
			dl = 2*dt + 2*y1 - 1;
			
			if( dl <= 0){
				mh();
			
			}
			else{
			
				md();
			
			}
		
		}
	
		else if( dt > 0){
		
			dl = 2*dt - 2*x1 -1;
			
			if( dl <= 0){
			
				md();
			}
			else{
				mv();
			
			}
		
		
		
		}
		
	       else if( dt ==0){
	       		md();
	       
	       
	       
	       
	       }
	
	
	
	
	
	
	}
	
	
}







void mh(){

	x1 = x1 + 1;
	dt = dt + 2*x1 + 1;



}

void md(){

	x1 = x1 + 1;
	y1 = y1 - 1;
	dt = dt + 2*x1 - 2*y1 + 2;



}

void mv(){

	y1 = y1 -1;
	dt = dt - 2*y1 + 1;



}

void eye_left(){

r = r/6;


x1 =0;
	y1 = r;
	
	dt = 2*(1-r);
	int limit = 0;
	
	while (y1 >= limit){
		
		glBegin(GL_POINTS);
			glVertex2i(xc -20 +x1,yc+20+y1);
			glVertex2i(xc-20+x1,yc+20-y1);
			glVertex2i(xc-20-x1,yc+20-y1);
			glVertex2i(xc-20+x1,yc+20+y1);
			
		glEnd();
		
		if (dt < 0){
			dl = 2*dt + 2*y1 - 1;
			
			if( dl <= 0){
				mh();
			
			}
			else{
			
				md();
			
			}
		
		}
	
		else if( dt > 0){
		
			dl = 2*dt - 2*x1 -1;
			
			if( dl <= 0){
			
				md();
			}
			else{
				mv();
			
			}
		
		
		
		}
		
	       else if( dt ==0){
	       		md();
	       
	       
	       
	       
	       }
	
	
	
	
	
	
	}
	
	
}

	















void eye_right(){



x1 =0;
	y1 = r;
	
	dt = 2*(1-r);
	int limit = 0;
	
	while (y1 >= limit){
		
		glBegin(GL_POINTS);
			glVertex2i(xc +20 +x1,yc+20+y1);
			glVertex2i(xc+20+x1,yc+20-y1);
			glVertex2i(xc+20-x1,yc+20-y1);
			glVertex2i(xc+20+x1,yc+20+y1);
			
		glEnd();
		
		if (dt < 0){
			dl = 2*dt + 2*y1 - 1;
			
			if( dl <= 0){
				mh();
			
			}
			else{
			
				md();
			
			}
		
		}
	
		else if( dt > 0){
		
			dl = 2*dt - 2*x1 -1;
			
			if( dl <= 0){
			
				md();
			}
			else{
				mv();
			
			}
		
		
		
		}
		
	       else if( dt ==0){
	       		md();
	       
	       
	       
	       
	       }
	
	
	
	
	
	
	}
	
	
}

	













void smile(){
	int x;
	int y;
	cout<<"Enter x"<<endl;
	cin>>x;
	cout<<"Enter y"<<endl;
	cin>>y;
	
	for (int i = 0; i < 40; i++){
		glBegin(GL_POINTS);
			glVertex2i(x-i,y);
			glVertex2i(x+i,y);
		glEnd();
	
	}


}

void display()
{
	glColor3f(0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);//clear the screen
	
	drawQuadrants();
	
	bresenham_circ();
	smile();
	eye_right();
	eye_left();
	
	glFlush(); 	
}

int main(int argc,char **argv)
{
	cout<<"Enter the value of radius: "<<endl;
	cin>>r;
	cout<<"Enter the co-ordinates of center x,y: "<<endl;
	cin>>xc;
	cin>>yc;
	
	glutInit(&argc,argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Sample Program");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
