#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

float lookatX = 0, lookatY = 0, lookatZ = 0, angle = 0;

int window, currentCameraPosition = 0;//change the value of currentCameraPosition from a 0 to 3 to see different viewpoints
struct Camera{
  float x;
  float y;
  float z;
}CameraPosition[4];


//Function Definations
void renderCube(float a, float b, float c);
void setCameraPosition();


void display()
{

   glClear(GL_COLOR_BUFFER_BIT);
   renderCube(CameraPosition[currentCameraPosition].x, CameraPosition[currentCameraPosition].y, CameraPosition[currentCameraPosition].z );
}

void keyPressed(unsigned char key, int x, int y){
  if(key == 'a'){
  }
}


void init()
{
 glClearColor(1,1,1,0);
 glEnable(GL_BLEND);
 glEnable(GL_DEPTH_TEST);
 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


int main(int argc, char** argv)
{//this is init function
  setCameraPosition();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(300,300);
  glutInitWindowSize(700,700);
  window = glutCreateWindow("CUBE");
  glutDisplayFunc(display);
  init();
  glutKeyboardFunc(keyPressed);
  // glutSpecialFunc(SpecialInput);
  glutMainLoop();
}
void renderCube(float a, float b, float c){
    int i = 1;
    float x = 0.5, y = 0.5, z = 0.5;
    float colors[6][3] = { { 0, 0, 1 }, { 0, 0, 0 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 0, 0 }, { 1, 0, 1 } };


    gluLookAt(a, 0.7, c, lookatX, lookatY, lookatZ, 0, 1, 0);
    glColor4f(0,0,0,1);
      glBegin(GL_LINES);
      glVertex3f(0,1,0);
      glVertex3f(0,-1,0);
      glVertex3f(-1,0,0);
      glVertex3f(1,0,0);
      glVertex3f(0,0,1);
      glVertex3f(0,0,-1);
      glEnd();


      glBegin(GL_QUADS);
      //bottom
      glColor4f(colors[i][0],colors[i][1],colors[i][2], 0.6);
      glVertex3f(0,0,0);
      glVertex3f(x,0,0);
      glVertex3f(x,0,z);
      glVertex3f(0,0,z);
      i++;
      glEnd();

      glBegin(GL_QUADS);
      //front
      glColor4f(colors[i][0],colors[i][1],colors[i][2], 0.6);
      glVertex3f(0,0,z);
      glVertex3f(x,0,z);
      glVertex3f(x,y,z);
      glVertex3f(0,y,z);
      glEnd();
      i++;


      glBegin(GL_QUADS);
      //rear
      glColor4f(colors[i][0],colors[i][1],colors[i][2], 0.6);
      glVertex3f(0,0,0);
      glVertex3f(x,0,0);
      glVertex3f(x,y,0);
      glVertex3f(0,y,0);
      i++;
      glEnd();

      glBegin(GL_QUADS);
      //right
      glColor4f(colors[i][0],colors[i][1],colors[i][2], 0.6);
      glVertex3f(x,y,z);
      glVertex3f(x,y,0);
      glVertex3f(x,0,0);
      glVertex3f(x,0,z);
      i++;
      glEnd();

      glBegin(GL_QUADS);
      //top
      glColor4f(colors[i][0],colors[i][1],colors[i][2], 0.6);
      glVertex3f(0,y,0);
      glVertex3f(x,y,0);
      glVertex3f(x,y,z);
      glVertex3f(0,y,z);
      i++;
      glEnd();

      glBegin(GL_QUADS);
      //left
      glColor4f(colors[0][0],colors[0][1],colors[0][2], 0.6);
      glVertex3f(0,y,z);
      glVertex3f(0,y,0);
      glVertex3f(0,0,0);
      glVertex3f(0,0,z);
      glEnd();
      glFlush();
}

void setCameraPosition(){
  CameraPosition[0].x = 0.25;
  CameraPosition[0].y = 0.7;
  CameraPosition[0].z = 0.6;

  CameraPosition[1].x = 0.6 ;
  CameraPosition[1].y = 0.7 ;
  CameraPosition[1].z = 0.25;

  CameraPosition[2].x = 0.1;
  CameraPosition[2].y = 0.6;
  CameraPosition[2].z = -0.3;

  CameraPosition[3].x = -0.3;
  CameraPosition[3].y = 0.5;
  CameraPosition[3].z = -0.05;
}
