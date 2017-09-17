#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
int points[2][2], count = 0;
double X1, Y1, X2, Y2;

void display(void)
{  glClear (GL_COLOR_BUFFER_BIT);
	 glClearColor(0,0,0,1);
   glFlush();
}
/* Function that returns -1,0,1 depending on whether x */
/* is <0, =0, >0 respectively */
#define sign(x) ((x>0)?1:((x<0)?-1:0))
/* Generalized Bresenham's Algorithm */
void bres_general(int x1, int y1, int x2, int y2)
{
  int dx, dy, x, y, d, s1, s2, swap=0, temp;

  dx = abs(x2 - x1);
  dy = abs(y2 - y1);
  s1 = sign(x2-x1);
  s2 = sign(y2-y1);

  /* Check if dx or dy has a greater range */
  /* if dy has a greater range than dx swap dx and dy */
  if(dy > dx){temp = dx; dx = dy; dy = temp; swap = 1;}

  /* Set the initial decision parameter and the initial point */
  d = 2 * dy - dx;
  x = x1;
  y = y1;

  int i;
  for(i = 1; i <= dx; i++)
  {
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();

    while(d >= 0)
    {
      if(swap) x = x + s1;
      else
      {
        y = y + s2;
        d = d - 2* dx;
      }
    }
    if(swap) y = y + s2;
    else x = x + s1;
    d = d + 2 * dy;
  }
       printf("Bresenham\n");
  glFlush();
}


//KEYBOARD EVENTS
void keyPressed (unsigned char key, int x, int y) {

  if(key == 'B' || key == 'b'){
    bres_general(X1,Y1,X2,Y2);
  }
}


//MOUSE EVENTS
void mouseEvents( int button, int state, int x, int y )
{
    if( GLUT_DOWN == state && GLUT_LEFT_BUTTON == button && count < 2 )
    {
      x = x - 683;
      y = 384 -y;
      printf("Left Click  X=%d, Y=%d\n", x, y);
      points[count][0] = x;
      points[count][1] = y;
      count++;

    }
    else if(GLUT_DOWN == state && GLUT_RIGHT_BUTTON == button){
      X1 = points[0][0];
      Y1 = points[0][1];
      X2 = points[1][0];
      Y2 = points[1][1];
      printf("Right Click\n" );
    }
}


void Init()
{
  /* Set clear color to white */
  glClearColor(1.0,1.0,1.0,0);
  /* Set fill color to black */
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(-683, 683, -384, 384);
}
int main(int argc, char **argv)
{

  /* Initialise GLUT library */
  glutInit(&argc,argv);
  /* Set the initial display mode */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  /* Set the initial window position and size */
  glutInitWindowPosition(0,0);
  glutInitWindowSize(1366,768);
  /* Create the window with title "DDA_Line" */
  glutCreateWindow("DDA_Line");
  /* Initialize drawing colors */
  Init();
  /* Call the displaying function */
  glutDisplayFunc(display);
  glutMouseFunc(mouseEvents);
  glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
  /* Keep displaying untill the program is closed */
  glutMainLoop();
}
