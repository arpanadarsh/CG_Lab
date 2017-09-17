//A PROGRAM TO DRAW A POLYGON ON MOUSE CLICK
//Author: Sumit Kumar Das
//SAP: 500044616
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
int points[6][2], count = 0;
void drawPolygon();
void drawPoints(int x, int y);

void drawPoints(int x, int y)
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0, 0.0, 0.0);
glPointSize(5);
glBegin(GL_POINTS);
glVertex2i(x, y);
glEnd();
glFlush();
// glutPostRedisplay();
}


void drawPolygon()
{
  int i;
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0, 0.0, 0.0);
glLineWidth(3.0);
glBegin(GL_POLYGON);
for (i = 0; i < count; i++) {
    glVertex2i(points[i][0], points[i][1]);
}
glEnd();
glFlush();
}

//DISPLAY METHOD
void display()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}
//KEYBOARD EVENTS
void keyPressed (unsigned char key, int x, int y) {
  if(key == "e" || key == "E"){
    close();
  }
  }
}

//MOUSE EVENTS
void mouseEvents( int button, int state, int x, int y )
{
    if( GLUT_DOWN == state && GLUT_LEFT_BUTTON == button && count < 5 )
    {
      x = x - 683;
      y = 384 -y;
      printf("X=%d, Y=%d\n", x, y);
      drawPoints(x,y);
      points[count][0] = x;
      points[count][1] = y;
      count++;

    }
    else if(GLUT_DOWN == state && GLUT_RIGHT_BUTTON == button){
      // drawPoints();
      drawPolygon();
      printf("Right Click\n" );
    }
}

//INIT FUNCTION
void init(){
  glClearColor(1,1, 1,1);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_PROGRAM_POINT_SIZE );
}

//MAIN FUNCTION
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(300,300);
  glutInitWindowSize(1366,768);
  glutCreateWindow("MOUSE");
  gluOrtho2D(-683, 683, -384, 384);
  init();
  glutDisplayFunc(display);
  glutMouseFunc(mouseEvents);
    glutKeyboardFunc(keyPressed);
  glutMainLoop();
}
