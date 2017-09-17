#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>

double centreX=0, centreY=0, radius = 100, prevX=0, prevY=0, error = 0, radiusX = 100, radiusY = 80, X0, Y0;
int window,	midpointCircleSubWindow,midpointEllipseSubWindow, parametricCircleSubWindow, parametricEllipseSubWindow;
int glutGetWindow(void);

void drawPoints(double x, double y){
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
    glVertex2i(x+centreX,y+centreY);
    glVertex2i(y+centreX,x+centreY);
    glVertex2i(y+centreX,-x+centreY);
    glVertex2i(-x+centreX,y+centreY);
    glVertex2i(-x+centreX,-y+centreY);
    glVertex2i(-y+centreX,-x+centreY);
    glVertex2i(-y+centreX,x+centreY);
    glVertex2i(x+centreX,-y+centreY);
    glEnd();
    glFlush();
}

void drawEllipsePoints(int x, int y){
    X0 = x;
    Y0 = y;
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
    glVertex2f(x+centreX,y+centreY);
    glVertex2f(x+centreX,-y+centreY);
    glVertex2f(-x+centreX,-y+centreY);
    glVertex2f(-x+centreX,y+centreY);
    glEnd();
    glFlush();
}

void drawParametricEllipsePoints(int x, int y){
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
    glVertex2f(x+centreX,y+centreY);
    glVertex2f(x+centreX,-y+centreY);
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
  glutSetWindow(midpointEllipseSubWindow);
    double P0;
  P0 = pow(radiusY,2) + pow(radiusX,2)*radiusY + pow(radiusX,2)/4;
  drawRegion1(P0,0, radiusY);
  error = 0;
  P0 = pow(radiusY,2)*pow((X0 + 0.5),2) + pow(radiusX,2)*pow((Y0 - 1),2) - pow(radiusX,2)*pow(radiusY,2);
  drawRegion2(P0,X0,Y0);
}

// void drawMidPointCircle(int pK, double x, double y)
// {
//   glutSetWindow(midpointCircleSubWindow);
//   if(prevX == x && prevY== y){
//     error++;
//   }
//   while(x <= y && error ==0){
//     if(pK < 0){
//       pK = pK + 2*(x+1) + 1;
//       drawPoints(x+1,y);
//       drawMidPointCircle(pK,x+1,y);
//     }
//     else if(pK > 0){
//       pK = pK + 2*(x+1) -2*(y +1);
//       drawPoints(x+1,y-1);
//       drawMidPointCircle(pK,x+1,y-1);
//     }
//     else{
//         pK = pK + 2*(x+1) + 1;
//         drawPoints(x,y);
//         drawMidPointCircle(pK,x,y);
//     }
//     prevX = x;
//     prevY = y;
//   }
// }



void drawMidPointCircle(int pK, double x, double y)
{
  glutSetWindow(midpointCircleSubWindow);
  // printf(" Inside drawMidPointCircle():\nPk=%f X=%f, Y=%f\n",pK,x,y);
  if(prevX == x && prevY== y){
    error++;
  }

  while(x <= y && error == 1){
    if(pK <= 0){
      pK = pK + 2*(x+1) + 1;
      drawPoints(x+1,y);
      // printf(" Next Pk=%d\n",pK);
      drawMidPointCircle(pK,x+1,y);
    }
    else if(pK > 0){
      pK = pK + 2*(x+1) -2*(y +1);
      drawPoints(x+1,y-1);
      drawMidPointCircle(pK,x+1,y-1);
    }
  }
  prevX = x;
  prevY = y;
}


void drawParametricEllipse(){
  glutSetWindow(parametricEllipseSubWindow);
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

void drawParametricCircle(){
  glutSetWindow(parametricCircleSubWindow);
  double i=0, x = 1, y = 0;
  while(x >= y){
    x = (radius*cos(i));
    y = (radius*sin(i));
    drawPoints(x,y);
    i = i+0.0001;
  }
}
void midpointCircle(/* arguments */) {
  glClearColor(1.0, 0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}
void midpointEllipse(/* arguments */) {
  glClearColor(1.0, 1, 0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}
void parametricEllipse(/* arguments */) {
  glClearColor(1, 1, 1, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}
void parametricCircle(/* arguments */) {
  glClearColor(0.5, 1, 0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}


void mouseEvents(int button, int state, int x, int y){
  if( GLUT_DOWN == state && GLUT_LEFT_BUTTON == button )
  {
    x = x - 683;
    y = 384 -y;
    printf("X=%d, Y=%d\n", x, y);
    centreX = x;
    centreY = y;
  }
}

void keyPressed(unsigned char key, int x, int y){
    if(key == 27)
      glutDestroyWindow(window);
    if(key == 'a'){
        printf("Drawing Circle using Parametric Points Algorithm.\n");
        drawParametricCircle();
        error = 0;
        printf("Done!\n");
      }
      if(key == 'b'){
        printf("Drawing Circle using Midpoint Algorithm.\n");
        drawMidPointCircle(1-radius, 0, radius);
        error = 0;
        printf("Done!\n");
      }
      if(key == 'c'){
        printf("Drawing Ellipse using Midpoint Algorithm.\n");
        drawMidpointEllipse();
        printf("Done!\n");
      }
      if(key == 'd'){
        printf("Drawing Ellipse using Parametric Points Algorithm.\n");
        drawParametricEllipse();
        printf("Done!\n");
      }
  }


void display()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void init()
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
  window = glutCreateWindow("Circle");
  /* Initialize drawing colors */
  init();
  /* Call the displaying function */
  glutDisplayFunc(display);

  // sub windows
	midpointCircleSubWindow = glutCreateSubWindow(window, 0,0,683,384 );
	glutDisplayFunc(midpointCircle);
	init();
  parametricCircleSubWindow = glutCreateSubWindow(window, 683,0,683,384 );
  glutDisplayFunc(parametricCircle);
  init();
  midpointEllipseSubWindow = glutCreateSubWindow(window, 0,384,683,384 );
	glutDisplayFunc(midpointEllipse);
	init();
  parametricEllipseSubWindow = glutCreateSubWindow(window, 683,384,683,384 );
	glutDisplayFunc(parametricEllipse);
	init();
  glutSetWindow(2);
  printf("Current Window: %d\n",glutGetWindow());
  glutMouseFunc(mouseEvents);
  glutKeyboardFunc(keyPressed);
  glutMainLoop();
}
