#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>

int window;
double centreX = 0, centreY = 0, radiusX = 100, radiusY = 80, prevX = 0 , prevY = 0;

void drawParametricEllipsePoints(int x, int y){
    printf("Drawing X=%d, Y=%d\n",x,y);
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
    glVertex2f(x+centreX,y+centreY);
    glVertex2f(x+centreX,-y+centreY);
    glEnd();
    glFlush();
}



void drawParametricEllipse(){
  double i=0, x, y=1;
  while(y>=0){
    x = (radiusX*cos(i));
    y = (radiusY*sin(i));
    if(prevX == x && prevY== y){
      i = i+0.001;
      prevX = x;
      prevY = y;
      continue;
    }
    drawParametricEllipsePoints(x,y);
    i = i+0.001;
    prevX = x;
    prevY = y;
  }

}


void keyPressed(unsigned char key, int x, int y){
  if(key == 27)
  glutDestroyWindow(window);
  if(key == 13)
  {
    drawParametricEllipse();
  }
}


void mouseEvents(int button, int state, int x, int y){
  if( GLUT_DOWN == state && GLUT_RIGHT_BUTTON == button )
  {
    x = x - 683;
    y = 384 -y;
    printf("X=%d, Y=%d\n", x, y);
    centreX = x;
    centreY = y;
  }
}

void grid(){
  glColor3f(0,0,1);
  glBegin(GL_LINES);
  glVertex2i(0,384);
  glVertex2i(0,-384);
  glEnd();
  glBegin(GL_LINES);
  glVertex2i(683,0);
  glVertex2i(-683,0);
  glEnd();
}

void display()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  grid();
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
  window = glutCreateWindow("Ellipse");
  /* Initialize drawing colors */
  Init();
  /* Call the displaying function */
  glutDisplayFunc(display);
  glutMouseFunc(mouseEvents);
  glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
  /* Keep displaying untill the program is closed */
  glutMainLoop();
}
