#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

// void drawBitmapText(char *string,float x,float y)
// {
//     char *c;
//     glRasterPos2f(x,y);
//     for(c=string;*c!='\0';c++)
//     {
//       glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
//     }
// }

void display()
{
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(0,0,0);



 //sky
 glColor4f(0,0,1,0.2);
 glBegin(GL_POLYGON);
 glVertex2f(-150,0);
 glVertex2f(-150,150);
 glVertex2f(150,150);
 glVertex2f(150,0);
 glEnd();

//window side wall
glColor3f(0.8,0.6,1);
glBegin(GL_POLYGON);
glVertex2f(0,60);
glVertex2f(80,60);
glVertex2f(80,0);
glVertex2f(0,0);
glEnd();

//door side wall
 glColor3f(0,0.6,1);
glBegin(GL_POLYGON);
glVertex2f(0,60);
glVertex2f(-40,60);
glVertex2f(-40,0);
glVertex2f(0,0);
glEnd();

//above door wall
glColor3f(0,1,1);
glBegin(GL_TRIANGLES);
glVertex2f(0,60);
glVertex2f(-40,60);
glVertex2f(-20,108);
glEnd();

//roof top
glColor3f(0.6,0.3,0);
glBegin(GL_POLYGON);
glVertex2f(-20,108);
glVertex2f(0,60);
glVertex2f(80,60);
glVertex2f(65,108);
glEnd();


//door
glColor3f(1,1,1);
glBegin(GL_POLYGON);
glVertex2f(-10,0);
glVertex2f(-10,40);
glVertex2f(-30,40);
glVertex2f(-30,0);
glEnd();


//window
glColor3f(1,1,1);
glBegin(GL_POLYGON);
glVertex2f(30,20);
glVertex2f(30,40);
glVertex2f(60,40);
glVertex2f(60,20);
glEnd();

//circle
float i= 0.000;
glColor3f(1,0,1);
glBegin(GL_POLYGON);
for(i = 0; i< 360; i = i+0.001)
glVertex2f((-20+5*cos(i)),(84+5*sin(i)));
glEnd();

//chimney
glColor3f(1,0,1);
glBegin(GL_POLYGON);
glVertex2f(50,108);
glVertex2f(60,108);
glVertex2f(60,115);
glVertex2f(50,115);
glEnd();

//ground
glColor3f(0,1,0);
glBegin(GL_POLYGON);
glVertex2f(-150,0);
glVertex2f(-150,-150);
glVertex2f(150,-150);
glVertex2f(150,0);
glEnd();



  //  glLoadIdentity();
  //  glColor3f(0,0,0);
  //  drawBitmapText("Sumit Kumar Das",-0.3,-0.6);
  //  drawBitmapText("R11215128",-0.2,-0.8);

 glFlush();
}
void init()
{
 glClearColor(1,1,1,0);
 glEnable(GL_BLEND);
 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
int main(int argc, char** argv)
{//this is init function
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(300,300);
  glutInitWindowSize(500,500);
  glutCreateWindow("HUT");
  gluOrtho2D(-150,150,-150,150);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}
