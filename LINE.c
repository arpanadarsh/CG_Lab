#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
GLfloat SIDE=50, A[30][2]={};
GLfloat BLUE[3] = {0,0,1}, GREEN[3] = {0,1,0}, RED[3] = {1,0,0};
int i=0, l=0;

void drawb() // Bresenham's
{
    float dx, dy, p, x, y, m;
    glLoadIdentity();
    gluOrtho2D(0,700,0,700);
    glColor3fv(GREEN);

    dx = A[1][0] - A[0][0];
    dy = A[1][1] - A[0][1];

    x=A[0][0];
    y=A[0][1];
    m = dy/dx;
    if (m<1)
    {
        p=2*dy-dx;
        glBegin(GL_POINTS);
        while(x<=A[1][0])
        {
            if(p>=0)
            {
                glVertex3f(x,y,0);
                y=y+1;
                p=p+2*dy-2*dx;
            }
            else
            {
                glVertex3f(x,y,0);
                p=p+2*dy;
            }
            x=x+1;
        }
        glEnd();
    }
    else
    {
        p=2*dx-dy;
        glBegin(GL_POINTS);
        while(y<=A[1][1])
        {
            if(p>=0)
            {
                glVertex3f(x,y,0);
                x=x+1;
                p=p+2*dy+2*dx;
            }
            else
            {
                glVertex3f(x,y,0);
                p=p+2*dy;
            }
            y=y+1;
        }
        glEnd();
    }
    glFlush();
}
void drawd() //dda
{   float x, y, dx, dy, m, xinc, yinc, k;
    int j;
    glLoadIdentity();
    gluOrtho2D(0,700,0,700);
    glColor3fv(BLUE);
	dx = A[1][0] - A[0][0];
    dy = A[1][1] - A[0][1];

    m = dy/dx;
    x = A[0][0];
    y = A[0][1];
	if (abs(m)<1)
        {
        glBegin(GL_POINTS);
        while(x<=A[1][0])
        {glVertex3f(x, y,0);
        x = x + 1.0;
        y = y + m;
        }
        glEnd();
        }
    else
        {
        glBegin(GL_POINTS);
        while(y<=A[1][1])
        {glVertex3f(x, y,0);
        x = x + 1.0/m;
        y = y + 1.0;
        }
        glEnd();
        }
    glFlush();
}

void display(void)
{  glClear (GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,1);
glFlush();
}



void setX(int x)
{
    A[i][0]=x;
}

void setY(int y)
{
    A[i][1]=700-y;
}
void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        setX(x);
        setY(y);
	i++;
	if(i==2)
        i=0;
    }

}

void Keyboard(unsigned char Key, int x, int y)
{
switch(Key)
{
case 'd':
{
drawd();
break;}
case 'b':
{
drawb();
break;}
case 27:
exit(1);
break;
};
}

int main(int argc, char **argv)
{   glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Drawing Polygon");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(Keyboard);
    glutMainLoop();
}
