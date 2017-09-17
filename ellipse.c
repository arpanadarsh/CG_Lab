#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>

int window;
double centreX, centreY, radiusX = 100, radiusY = 80, prevX=0, prevY=0, error = 0;
double X0, Y0;

void drawEllipsePoints(int x, int y){
    X0 = x;
    Y0 = y;
    printf("Drawing X=%d, Y=%d\n",x,y);
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
    glVertex2f(x+centreX,y+centreY);
    glVertex2f(x+centreX,-y+centreY);
    glVertex2f(-x+centreX,-y+centreY);
    glVertex2f(-x+centreX,y+centreY);
    glEnd();
    glFlush();
}


void drawRegion1(double pK, double x, double y)
{
  if(prevX == x && prevY== y){
    error++;
  }

  prevX = x;
  prevY = y;

  while(2*radiusY*radiusY*x <= 2*radiusX*radiusX*y && error < 1){
    if(pK <= 0){
      pK = pK + 2*pow(radiusY,2)*(x+1)+pow(radiusY,2);
      drawEllipsePoints(x+1,y);
      drawRegion1(pK,x+1,y);
    }
    else if(pK > 0){
      pK = pK +2*pow(radiusY,2)*(x+1)+pow(radiusY,2)-2*pow(radiusX,2)*(y+1);
      drawEllipsePoints(x+1,y-1);
      drawRegion1(pK,x+1,y-1);
    }
  }
}

void drawRegion2(double pK, double x, double y)
{
  if(prevX == x && prevY== y){
    error++;
  }

  prevX = x;
  prevY = y;

  while(y >= 0 && error <= 1){
    if(pK <= 0){
      pK = pK + 2*pow(radiusY,2)*(x+1) - 2*pow(radiusX,2)*(y+1) + 2*pow(radiusX,2);
      drawEllipsePoints(x+1,y-1);
      drawRegion2(pK,x+1,y-1);
    }
    else if(pK > 0){
      pK = pK - 2*pow(radiusX,2)*(y+1) + pow(radiusX,2);
      drawEllipsePoints(x,y-1);
      drawRegion2(pK,x,y-1);
    }
  }
}

void drawMidpointEllipse(){
    double P0;
  P0 = pow(radiusY,2) + pow(radiusX,2)*radiusY + pow(radiusX,2)/4;
  printf("Pk=%f X=%f, Y=%f\n",P0,0, radiusY);
  drawRegion1(P0,0, radiusY);
  error = 0;
  P0 = pow(radiusY,2)*pow((X0 + 0.5),2) + pow(radiusX,2)*pow((Y0 - 1),2) - pow(radiusX,2)*pow(radiusY,2);
  printf("Pk=%f X=%f, Y=%f\n",P0,X0,Y0);
  drawRegion2(P0,X0,Y0);
}


void keyPressed(unsigned char key, int x, int y){
  if(key == 27)
  glutDestroyWindow(window);
  if(key == 13)
  {
    drawMidpointEllipse();
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
