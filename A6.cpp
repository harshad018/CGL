#include<iostream>
#include<GL/glut.h>
#include<cmath>

using namespace std;

float A[3][3];
float B[3][3];
float C[3][3];

void init()
{
    glClearColor(0,0,0,0);
    gluOrtho2D(-320,320,-240,240);
}

void drawQuadrants()
{
    glBegin(GL_LINES);
        glVertex2i(-320,0);
        glVertex2i(320,0);
        
        glVertex2i(0,-240);
        glVertex2i(0,240);
    glEnd();
}

void drawPolygon(float final[3][3]){
    glBegin(GL_POLYGON);
    for (int i = 0; i<3; i++){
        glVertex2f(final[i][0],final[i][1]);
    }
    glEnd();
}

void input(){
    cout<<"Enter the value in A Matrix"<<endl;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cin>>A[i][j];
        }
    }
}

void multiply(){
    for(int i = 0; i < 3 ; i++){
        for(int j = 0; j < 3 ; j++){
            C[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void rotation(){
    int a;
    float b;
    cout<<"Enter the value of a: ";
    cin>>a;
    b = a * 3.14 / 180.0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            B[i][j] = 0;
        }
    }
    B[0][0] = cos(b);
    B[1][1] = cos(b);
    B[2][2] = 1;
    B[1][0] = sin(b);
    B[0][1] = -sin(b);
    multiply();
    cout<<"Final product of multiplication"<<endl;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout<<C[i][j]<<endl;
        }
    }
}

void translation(){
    float xc, yc;
    cout<<"Enter the value of xc: ";
    cin>>xc;
    cout<<"Enter the value of yc: ";
    cin>>yc;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (i == j){
                B[i][j] = 1;
            } else {
                B[i][j] = 0;
            }
        }
    }
    B[0][2] = xc;
    B[1][2] = yc;
    multiply();
    cout<<"Final product of multiplication"<<endl;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout<<C[i][j]<<endl;
        }
    }
}

void scale(){
    float sx, sy;
    cout<<"Enter the value of sx: ";
    cin>>sx;
    cout<<"Enter the value of sy: ";
    cin>>sy;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            B[i][j] = 0;
        }
    }
    B[0][0] = sx;
    B[1][1] = sy;
    B[2][2] = 1;
    multiply();
    cout<<"Final product of multiplication"<<endl;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout<<C[i][j]<<endl;
        }
    }
}

void reflectionx(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (i == j){
                B[i][j] = 1;
            } else {
                B[i][j] = 0;
            }
        }
    }
    B[1][1] = -1;
    multiply();
    cout<<"Final product of multiplication"<<endl;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout<<C[i][j]<<endl;
        }
    }
}

void reflectiony(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (i == j){
                B[i][j] = 1;
            } else {
                B[i][j] = 0;
            }
        }
    }
    B[0][0] = -1;
    multiply();
    cout<<"Final product of multiplication"<<endl;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout<<C[i][j]<<endl;
        }
    }
}

void reflectionxy(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (i == j){
                B[i][j] = 1;
            } else {
                B[i][j] = 0;
            }
        }
    }
    B[1][1] = -1;
    B[0][0] = -1;
    multiply();
    cout<<"Final product of multiplication"<<endl;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout<<C[i][j]<<endl;
        }
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawQuadrants();
    glColor3f(1.0f, 1.0f, 1.0f);
    drawPolygon(C);
    glFlush(); 
}

int main(int argc,char **argv){
    input();
    int ch;
    cout<<"Enter the choice of transformation: \n1. Scaling \n2. Rotation \n3. Translation \n4. Reflection \n5. Exit: ";
    cin>>ch;
    switch(ch){
        case 1: scale();
                break;
        case 2: rotation();
                break;
        case 3: translation();
                break;
        case 4: int ch2;
                cout<<"Which reflection \n1. x \n2. y \n3. xy: ";
                cin>>ch2;
                switch(ch2)
                {
			
				case 1: reflectionx();
					break;
					
				case 2: reflectiony();
					break;
					
				case 3: reflectionxy();
					break;
			
			}
	
			break;
	
	
	
	
	
	}
	//scale();
	//rotation();
	//translation();
	
	
	
	
	
	glutInit(&argc,argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Sample Program");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
} 

