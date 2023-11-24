#include <GL/glut.h>
#include <iostream>
using namespace std;

struct ToaDo
{
    int x, y;
};

void nhapDaGiac(ToaDo p[], int v)
{
    int i;
    for(i = 0; i < v; i++)
    {
        cout << "\nNhap toa do dinh " << i + 1 << " : ";
        cout << "\n\tx[" << i + 1 << "] = "; cin >> p[i].x;
        cout << "\n\ty[" << i + 1 << "] = "; cin >> p[i].y;
    }
    p[i].x = p[0].x;
    p[i].y = p[0].y;
}

void veDaGiac(ToaDo p[], int v)
{
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < v; i++)
        glVertex2i(p[i].x, p[i].y);
    glEnd();
}

void ScanLine(ToaDo p[], int v)
{
    int xmin, xmax, ymin, ymax, c, mang[50];
    xmin = xmax = p[0].x;
    ymin = ymax = p[0].y;
    for(int i = 0; i < v; i++)
    {
        if(xmin > p[i].x) xmin = p[i].x;
        if(xmax < p[i].x) xmax = p[i].x;
        if(ymin > p[i].y) ymin = p[i].y;
        if(ymax < p[i].y) ymax = p[i].y;
    }

    float y;
    y = ymin + 0.01;
    while(y <= ymax)
    {
        c = 0;
        for(int i = 0; i < v; i++)
        {
            int x, x1, x2, y1, y2, tg;
            x1 = p[i].x;
            y1 = p[i].y;
            x2 = p[(i + 1) % v].x;
            y2 = p[(i + 1) % v].y;
            if(y2 < y1)
            {
                tg = x1; x1 = x2; x2 = tg;
                tg = y1; y1 = y2; y2 = tg;
            }
            if(y <= y2 && y >= y1)
            {
                if(y1 != y2) x = ((y - y1) * (x2 - x1)) / (y2 - y1) + x1;
                if(x <= xmax && x >= xmin)
                    mang[c++] = x;
            }
        }

        for(int i = 0; i < c; i += 2)
        {
            glBegin(GL_LINES);
                glVertex2i(mang[i], y);
                glVertex2i(mang[i + 1], y);
            glEnd();
        }

        y++;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    ToaDo p[10] = {{75,250},{210,250},{250,128},{291,250},{425,250},
                  {318,331},{360,460},{249,380},{140,460},{182,331}};

    veDaGiac(p, 10);
    glColor3f(0.0, 1.0, 0.0);
    ScanLine(p, 10);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Scan Line Algorithm");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, 500, 0, 600);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

