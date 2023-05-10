#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <bits/stdc++.h>
#define ROUND(a) ((long) (a+0.5))

using namespace std;

void initGL(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //R=0,G=0,B=0,alpha=1
	gluOrtho2D(-330, 330, -330, 330); // dat truc chính giua màn h´nh trai - phai - duoi - tren
}

void putVertext(int xc, int yc, int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(xc+x,yc+y);
	glVertex2i(xc-x,yc-y);
	glVertex2i(xc+x,yc-y);
	glVertex2i(xc-x,yc+y);
	glEnd();	
}

//Draw Line

//TH1: 0 < k < 1
void LineMidPoint_1(int x1, int y1, int x2, int y2)	{
	if(x1 > x2){
		swap(x1,x2);
		swap(y1,y2);
	}
   	int Dx = x2-x1; 
	int Dy = y2-y1;
   	int p = Dy-Dx/2;
  	int x = x1;	
	int y = y1;
  	glBegin(GL_POINTS);
	glVertex2i(x,y);
	while (x <= x2)  
	{
		if (p < 0)	 
            p += Dy;
		else
            {
            	p += Dy-Dx;
			    y++;
			}
		x++;
        glVertex2i(x,y);
	}
	glEnd();
  	
}

//TH2: k > 1
void LineMidPoint_2(int x1, int y1, int x2, int y2)	{
	if(y1 > y2){
		swap(x1,x2);
		swap(y1,y2);
	}
   	int Dx = x2-x1; 
	int Dy = y2-y1;
   	int p = Dy/2-Dx;
  	int x = x1;	
	int y = y1;
  	glBegin(GL_POINTS);
	glVertex2i(x,y);
	while (y <= y2)  
	{
		if (p <= 0){
            p += Dy - Dx;
            x++;			
		}	 
		else
            {
            	p += -Dx;
			}
		y++;
        glVertex2i(x,y);
	}
	glEnd();	
}

//TH3: -1 < k < 0
void LineMidPoint_3(int x1, int y1, int x2, int y2)	{
	if(x1 > x2){
		swap(x1,x2);
		swap(y1,y2);
	}	
   	int Dx = x2-x1; 
	int Dy = y2-y1;
   	int p = Dy+Dx/2;
  	int x = x1;	
	int y = y1;
  	glBegin(GL_POINTS);
	glVertex2i(x,y);
	while (x <= x2)  
	{
		if (p <= 0){
            p += Dy + Dx;	
			y--;	
		}	 
		else
            {
            	p += Dy;
			}
		x++;
        glVertex2i(x,y);
	}
	glEnd();	
}

//TH4: k < -1
void LineMidPoint_4(int x1, int y1, int x2, int y2)	{
	if(y1 > y2){
		swap(x1,x2);
		swap(y1,y2);
	}
   	int Dx = x2-x1; 
	int Dy = y2-y1;
   	int p = -Dy/2-Dx;
  	int x = x1;	
	int y = y1;
  	glBegin(GL_POINTS);
	glVertex2i(x,y);
	while (y <= y2)  
	{
		if (p >= 0){
            p += -Dy - Dx;	
			x--;		
		}	 
		else
            {
            	p += -Dx;
			}
		y++;
        glVertex2i(x,y);
	}
	glEnd();	
}

// Draw Circle
void Circle_MidPoint(int xc,int yc, int Radius){
	int x,y,p;
	x = 0;
	y = Radius;
	p = 1 - Radius;
	putVertext(xc,yc,Radius,0);
	while (x < y){
		if (p < 0) p += 2*x + 3;
		else{
			p += 2*(x-y) + 5;
			y--;
		}
		x++;
		putVertext(xc,yc,x,y);
		putVertext(xc,yc,y,x);
	}
	putVertext(xc,yc,y,y);
}

//Draw Elip
void Ellipse_MidPoint(int xc, int yc, int a, int b){
	long x,y,fx,fy,a2,b2,p;
	x = 0;
	y = b;
	a2 = a * a;
	b2 = b * b;
	fx = 0;
	fy = 2 * a2 * y;
	putVertext(xc,yc,x,y);
	p = ROUND(b2 - (a2*b) + (0.25*a));
	while(fx < fy){
		x++;
		fx += 2*b2;
		if (p<0){
			p += b2*(2*x+3);
		}
		else{
			y--;
			p += b2*(2*x+3) + a2*(-2*y+2);
			fy -= 2*a2;
		}
		putVertext(xc,yc,x,y);
	}
	p = ROUND(b2*(x+0.5)*(x+0.5)+a2*(y-1)*(y-1)-a2*b2);
	while(y>0){
		y--;
		fy -= 2 * a2;
		if(p>=0){
			p += a2 * (3 - 2*y);
		}
		else{
			x++;
			fx += 2*b2;
			p += b2*(2*x+2) + a2*(-2*y+3);
		}
		putVertext(xc,yc,x,y);
	}
}

void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	glLineWidth(0.3);
	glPointSize(0.3);
	
	//Set color for x-axis and y-axis
	glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(1, 0, 0); glVertex3f(-330, 0, 0);
    glColor3f(1, 0, 0); glVertex3f(1, 0, 0); glVertex3f(330, 0, 0);
    glColor3f(1, 0, 0); glVertex3f(1, 0, 0); glVertex3f(0, -330, 0);
    glColor3f(1, 0, 0); glVertex3f(1, 0, 0); glVertex3f(0, 330, 0);
  	glEnd();

	glLineWidth(2.0);
	glPointSize(2.0);
	glColor3f(1.0, 0.0, 0.0);
		  
	//Draw Line using MidPoint algorithm
	
	//TH1: 0 < k < 1
	LineMidPoint_1(-20,-100, 100, -70); // k = 0.25
	//TH2: k > 1
	LineMidPoint_2(20,20,150,300); // k = 2.15
	//TH3: -1 < k < 0
	LineMidPoint_3(-20,-100,100,-120); // k =-0.166
	//TH4: k < -1  
	LineMidPoint_4(20,-100,40,-300); // k = -10
	
	//Draw Circle using MidPoint algorithm
	Circle_MidPoint(0,0,70);
	//Draw Elip using MidPoint algorithm
	Ellipse_MidPoint(0,0,150,80);

	glFlush();
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	int mode = GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
	glutInitWindowSize(720, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TEST");
	
	initGL();  
	
	glutDisplayFunc(mydisplay);   
	 
	glutMainLoop();
	
	return 0;
}
