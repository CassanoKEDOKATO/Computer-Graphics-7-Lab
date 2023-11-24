#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
int x1, y1, x2, y2;
//truong hop -1<= m < 0 y2<y1
void drawLine2(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int P = 2 * dy + dx;
    int x = x1;
    int y = y1;

    glBegin(GL_POINTS);
    glVertex2i(x, y);

    while (x < x2) {
        x++;
        if (P < 0) {
            P += 2 * dy + 2 * dx;
        } else {
            y--;
            P += 2 * dy;
        }
        glVertex2i(x, y);
    }

    glEnd();
    glFlush();
}
// truong hop 0<m<=1 x1<x2
void drawLine(int x1, int y1, int x2, int y2){
	int dx = x2 - x1;
    int dy = y2 - y1;
    int P = 2 * dx - dy;
    int x = x1;
    int y = y1;
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    while (x != x2) {
        if (P < 0) {
            P += 2 * dy;
        } else {
            y++;
            P += 2 * (dy - dx);
        }
        x++;
        glVertex2i(x, y);
    }

    glEnd();
    glFlush();
}
//truong hop m>1 ; y2>y1 thì y++
void drawLine1(int x1, int y1, int x2, int y2){
	int dx = x2 - x1;
    int dy = y2 - y1;
    int P = 2 * dx - dy;
    int x = x1;
    int y = y1;
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    
    while (x != x2) {
        if (P >= 0) {
            P += 2 * dx;
        } else {
            x++;
            P += 2 * (dx - dy);
        }
        y++;
        glVertex2i(x, y);
    }

    glEnd();
    glFlush();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    drawLine2(x1, y1, x2, y2);
    glFlush();
}

void mouse(int button, int state, int mouseX, int mouseY) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (x1 == 0 && y1 == 0) {
            x1 = mouseX;
            y1 = 480 - mouseY;
        } else {
            x2 = mouseX;
            y2 = 480 - mouseY;
            glutPostRedisplay();
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line Drawing");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 640, 0, 480);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
