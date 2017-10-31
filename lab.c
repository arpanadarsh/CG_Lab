#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include <GL/gl.h>

int window,	liangBarskySubwindow, cohenSudherlandSubwindow, startX, startY;
int xmin, xmax, ymin, ymax, a[2][2] = {{-683,384},{683,-384}};
int glutGetWindow(void);
void randomClippingWindow(int minX, int minY, int maxX, int maxY);
void liangBarsky();
void cohenSudherland();

//LBRT CODE
const int LEFT =2;
const int BOTTOM=1;
const int RIGHT= 8;
const int TOP=4;

int regionCode(double x,double y);

void cohenSudherlandClipping(int x0,int y0,int x1,int y1)
{

  int regionCodeP1,regionCodeP2,resultCode,clipped = 0,acceptLine = 0;

    //compute region Codes
  regionCodeP1= regionCode(x0,y0);
  regionCodeP2= regionCode(x1,y1);

  do
  {
      if(!(regionCodeP1|regionCodeP2))
      {
        acceptLine=1;
        clipped=1;
      }

      else
          if(regionCodeP1 & regionCodeP2)
               clipped=1;
          else
          {
              double x,y;
              resultCode = regionCodeP1?regionCodeP1:regionCodeP2;

  if(resultCode & TOP)
     {
       x= x0+(x1-x0)*(ymax-y0)/(y1-y0);
       y=ymax;
     }
        else if(resultCode & BOTTOM)
          {
            x= x0+(x1-x0)*(ymin-y0)/(y1-y0);
            y=ymin;
          }
          else if(resultCode & RIGHT)
            {
              y= y0+(y1-y0)*(xmax-x0)/(x1-x0);
              x=xmax;
             }
          else
           {
               y= y0+(y1-y0)*(xmin-x0)/(x1-x0);
               x=xmin;
           }

          if(resultCode == regionCodeP1)
                 {
                   x0=x;
                   y0=y;
                   regionCodeP1 = regionCode(x0,y0);

                 }
            else
                 {
                   x1=x;
                   y1=y;
                   regionCodeP2 = regionCode(x1,y1);
                 }
          }
  }while(!clipped);


  if(acceptLine)
  {
    glColor3f(0.0,1.0,0.0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2d(x0,y0);
    glVertex2d(x1,y1);
    glEnd();
    glFlush();
    glLineWidth(1);
  }
}

int regionCode(double x,double y)
{
    int output = 0;

     if(y>ymax)
         output |= TOP;
    if(y<ymin)
         output |= BOTTOM;
    if(x>xmax)
         output |= RIGHT;
    if(x<xmin)
         output |= LEFT;

     return output;
}

void liangBarskyClip()
{
    float x1,y1,x2,y2,t1,t2,r[4],q[4],p[4],dx,dy;
    dx=a[1][0]-a[0][0];
    dy=a[1][1] - a[0][1];

    p[0]=-dx;
    p[1]=dx;
    p[2]=-dy;
    p[3]=dy;

    q[0]=a[0][0]-xmin;
    q[1]=xmax-a[0][0];
    q[2]=a[0][1]-ymin;
    q[3]=ymax - a[0][1];

    t1=0;
    t2=1;
    for(int i=0;i<4;i++)
    {
        if(p[i]==0)
        {
          return;
        }
        else
        {
            r[i]=(q[i]/p[i]);
            if(p[i]<0)
            {
                if(r[i]>t1)
                    t1=r[i];
            }
            else
            {
                if(r[i]<t2)
                    t2=r[i];
            }
        }
    }


    if(t1<t2)
    {
        x1=a[0][0]+(t1*dx);
        y1=a[0][1]+(t1*dy);
        x2=a[0][0]+(t2*dx);
        y2=a[0][1]+(t2*dy);



    glLineWidth(3);
    glBegin(GL_LINES);
    glColor4f(0,1,0,1);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
    glFlush();
    glLineWidth(1);
  }

}


void randomClippingWindow(){
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
  glutSetWindow(liangBarskySubwindow);
  liangBarsky();
  srand (time(NULL));
  startX = (rand() % (1077) - 603);//(rand() % (max + 1 - min)) + min
  startY = (rand() % (589) - 308);



  glColor3f(0,0,0);
  glBegin(GL_LINE_LOOP);
  glVertex2i(startX, startY);
  glVertex2i(startX + 200, startY);
  glVertex2i(startX + 200, startY - 100);
  glVertex2i(startX, startY-100);
  glEnd();
  glFlush();

  xmin =  startX;
  xmax = startX + 200;
  ymin = startY-100;
  ymax = startY;
  liangBarskyClip();

  glutSetWindow(cohenSudherlandSubwindow);
  cohenSudherland();
  startX = (rand() % (1077) - 603);//(rand() % (max + 1 - min)) + min
  startY = (rand() % (589) - 308);


  glColor3f(1,1,1);
  glBegin(GL_LINE_LOOP);
  glVertex2i(startX, startY);
  glVertex2i(startX + 200, startY);
  glVertex2i(startX + 200, startY - 100);
  glVertex2i(startX, startY-100);
  glEnd();
  glFlush();

  xmin =  startX;
  xmax = startX + 200;
  ymin = startY-100;
  ymax = startY;
  cohenSudherlandClipping(a[0][0], a[0][1], a[1][0], a[1][1]);
}
void timer(int value){
  randomClippingWindow();
  glutTimerFunc(1000,timer,0);
}

void liangBarsky() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0,0,0);
  glBegin(GL_LINES);
  glVertex2i(-683,384);
  glVertex2i(683,-384);
  glEnd();
  glFlush();
}
void cohenSudherland() {
  glClearColor(0, 0, 0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1,1,1);
  glBegin(GL_LINES);
  glVertex2i(-683,384);
  glVertex2i(683,-384);
  glEnd();
  glFlush();
}


void keyPressed(unsigned char key, int x, int y){
    if(key == 27)
      glutDestroyWindow(window);
    if(key == 32){
      timer(0);
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
  /* Create the window with title "Lab" */
  window = glutCreateWindow("Circle");
  /* Initialize drawing colors */
  init();
  /* Call the displaying function */
  glutDisplayFunc(display);

  // sub windows
	liangBarskySubwindow = glutCreateSubWindow(window, 0,0,683,768 );
	glutDisplayFunc(liangBarsky);
	init();
  cohenSudherlandSubwindow = glutCreateSubWindow(window, 683,0,683,768 );
  glutDisplayFunc(cohenSudherland);
  init();

  glutSetWindow(2);
  // printf("Current Window: %d\n",glutGetWindow());

  glutKeyboardFunc(keyPressed);
  glutMainLoop();
}
