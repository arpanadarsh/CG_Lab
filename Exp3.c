#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
int points[2][2], count = 0;

double X1, Y1, X2, Y2, increment;
double   dy = Y2 - Y1, dx = X2 - X1;

float round_value(float v)
{
  return floor(v + 0.5);
}


void bresenham(double x, double y, int dk)
{
  if(x < X2){
    if(dk > 0){
      dk = dk + (2*dy) - (2*dx);
      glBegin(GL_POINTS);
      glColor3f(0,0,0);
      glVertex2f(x, y);
      glEnd();
      glFlush();
      bresenham(x+1, y+1, dk);
    }
    else{
      glBegin(GL_POINTS);
      glColor3f(0,0,0);
      glVertex2f(x, y);
      glEnd();
      glFlush();
      dk = dk + (2*dy);
      bresenham(x+1, y, dk);
    }
  }

}

void LineDDA(void)
{
  double dx=(X2-X1);
  double dy=(Y2-Y1);
  double slope;
  double xInc,yInc,x=X1,y=Y1;
  /* Find out whether to increment x or y */
  slope = dy/dx;
    if(slope < 1){
      xInc = 1;
      yInc = slope;
    }
    else{
      xInc = (double)(1/slope);
      yInc = 1;
    }


  /* Clears buffers to preset values */
  glClear(GL_COLOR_BUFFER_BIT);

  /* Plot the points */
  glBegin(GL_POINTS);
  /* Plot the first point */
  glVertex2d(x,y);
  while(x != X2 && y != Y2)
  {
    x+=xInc;
    y+=yInc;
    glVertex2d(round_value(x), round_value(y));
  }
       printf("DDA\n");
  glEnd();
  glFlush();
}

//KEYBOARD EVENTS
void keyPressed (unsigned char key, int x, int y) {

  if(key == 'B' || key == 'b'){
    dy = Y2 - Y1;
    dx = X2 - X1;
    if(dy < dx){
      increment = -1;
    }
    double d0 = 2 * (dy) - (dx);
    bresenham(X1, X2, d0);
  }
  if(key == 'D' || key == 'd'){
    LineDDA();
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

void display(){
  glColor3f(1,0,0);
  glFlush();
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
