#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

void drawBitmapText(char *string,float x,float y)
{
    char *c;
    glRasterPos2f(x,y);
    for(c=string;*c!='\0';c++)
    {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
    }
}

void display()
{
 glClear(GL_COLOR_BUFFER_BIT);
 // glColor4f(0,0,0,0.5);
 float CONST = 1/6.0*2*3.141;
 float colors[6][3] = { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 0, 0 }, { 1, 0, 1 } };
  for(int i = 0; i < 6; ++i) {

    glColor3f(colors[i][0],colors[i][1],colors[i][2]);
    glBegin(GL_POLYGON);
     glVertex2f(0,0);
      glVertex2f(cos(i*CONST)/2,sin(i*CONST)/2);
      glVertex2f(cos((i+1)*CONST)/2,sin((i+1)*CONST)/2);
      glVertex2f(0,0);
      glEnd();
  }

   glLoadIdentity();
   glColor3f(0,0,0);
   drawBitmapText("Sumit Kumar Das",-0.3,-0.6);
   drawBitmapText("R11215128",-0.2,-0.8);
   glutSwapBuffers();

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
  glutCreateWindow("HEXAGON");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}
