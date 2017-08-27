#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>


//Moon
void moon(){
  //circle
  float i= 0.00000;
  glColor3f(1.000, 1.000, 0.878);
  glBegin(GL_POLYGON);
  for(i = 0; i< 360; i = i+0.0001)
  glVertex2f((-250+250*cos(i)),(100+250*sin(i)));
  glEnd();
}


//lAND LAYER 1
void landLayer1(){
  glColor3f(0.902, 0.902, 0.980);
  glBegin(GL_POLYGON);
  glVertex2f(-683,320);
  glVertex2f(683,-350);
  glVertex2f(683,-384);
  glVertex2f(-683,-384);
  glEnd();
}

//lAND LAYER 2
void landLayer2(){
  glColor3f(0.878, 1.000, 1.000);
  glBegin(GL_POLYGON);
  glVertex2f(683,-10);
  glVertex2f(300,-10);
  glVertex2f(-300,-384);
  glVertex2f(683,-384);
  glEnd();
}

//lAND LAYER 3
void landLayer3(){
  glColor3f(0.561, 0.737, 0.561);
  glBegin(GL_POLYGON);
  glVertex2f(-683,-384);
  glVertex2f(-683,-180);
  glVertex2f(683,-350);
  glVertex2f(683,-384);
  glEnd();
}
//TREE ONE
void tree1(){
  glColor3f(0.333, 0.420, 0.184);
  glBegin(GL_POLYGON);
  glVertex2f(-500,-202.775);
  glVertex2f(-530,-202.775);
  glVertex2f(-530,-132.775);
  glVertex2f(-500,-132.775);
  glEnd();

  //leaf
  glColor3f(0.565, 0.933, 0.565);
  glBegin(GL_POLYGON);
  glVertex2f(-450,-132.775);
  glVertex2f(-515, 18);
  glVertex2f(-580,-132.775);
  glEnd();

  //leaf
  glColor3f(	0.596, 0.984, 0.596);
  glBegin(GL_POLYGON);
  glVertex2f(-450,-82.775);
  glVertex2f(-515, 68);
  glVertex2f(-580,-82.775);
  glEnd();

  //leaf
  glColor3f(0.565, 0.933, 0.565);
  glBegin(GL_POLYGON);
  glVertex2f(-450,-32.775);
  glVertex2f(-515, 118);
  glVertex2f(-580,-32.775);
  glEnd();
}

//TREE TWO
void tree2(){
  glColor3f(0.333, 0.420, 0.184);
  glBegin(GL_POLYGON);
  glVertex2f(-360,-222.775);
  glVertex2f(-330,-222.775);
  glVertex2f(-330,-132.775);
  glVertex2f(-360,-132.775);
  glEnd();

  //leaf
glColor3f(0.565, 0.933, 0.565);
  glBegin(GL_POLYGON);
  glVertex2f(-410,-132.775);
  glVertex2f(-345,15);
  glVertex2f(-280,-132.775);
  glEnd();

  //leaf
  glColor3f(	0.596, 0.984, 0.596);
  glBegin(GL_POLYGON);
  glVertex2f(-410,-82.775);
  glVertex2f(-345, 68);
  glVertex2f(-280,-82.775);
  glEnd();

  //leaf
  glColor3f(0.565, 0.933, 0.565);
  glBegin(GL_POLYGON);
  glVertex2f(-410,-32.775);
  glVertex2f(-345, 118);
  glVertex2f(-280,-32.775);
  glEnd();
}

//TREE THREE
void tree3(){
  glColor3f(0.545, 0.271, 0.075);
  glBegin(GL_POLYGON);
  glVertex2f(683,-10);
  glVertex2f(633,-10);
  glVertex2f(633,90);
  glVertex2f(683,90);
  glEnd();

  float i= 0.000;
  glColor4f(0.125, 0.698, 0.667, 0.1);
  glBegin(GL_POLYGON);
  for(i = 0; i< 360; i = i+0.001)
  glVertex2f((683+300*cos(i)),(384+300*sin(i)));
  glEnd();
}

//HUT
void hut(){
  //Wall
  glColor3f(0.941, 0.902, 0.549);
  glBegin(GL_POLYGON);
  glVertex2f(320,-10);
  glVertex2f(610,-10);
  glVertex2f(610,190);
  glVertex2f(465,345);
  glVertex2f(320,190);
  glEnd();

  glColor4f(0.412, 0.412, 0.412,0.65);
  glBegin(GL_POLYGON);
  glVertex2f(415,90);
  glVertex2f(515,90);
  glVertex2f(515,170);
  glVertex2f(415,170);
  glEnd();

  glColor3f(1.000, 0.388, 0.278);
  glBegin(GL_POLYGON);
  glVertex2f(465,371);
  glVertex2f(660,190);
  glVertex2f(610,190);
  glVertex2f(465,324);
  glVertex2f(320,190);
  glVertex2f(270,190);
  glVertex2f(465,371);
  glEnd();

}

//DISPLAY METHOD
void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  //MAJOR SCENE OBJECTS
  moon();
  landLayer1();
  landLayer2();
  tree1();
  tree2();
  tree3();
  hut();
  landLayer3();
  glFlush();
}

//INIT FUNCTION
void init(){
  glClearColor(0.847, 0.749, 0.847,0.3);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//MAIN FUNCTION
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(300,300);
  glutInitWindowSize(1366,768);
  glutCreateWindow("SCENE");
  gluOrtho2D(-683, 683, -384, 384);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}
