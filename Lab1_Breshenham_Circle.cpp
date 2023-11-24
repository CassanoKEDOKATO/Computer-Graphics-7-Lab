#include <GL/glut.h>
#include <iostream>
#include <math.h>
int xc, yc, radius;

void drawCircle(int xc, int yc, int radius) {
    int x = 0;
    int y = radius;
    int p = 1 - radius;

    while (x <= y) {
        glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
        glEnd();

        if (p < 0) {
            x++;
            p += 2 * x + 1;
        } else {
            x++;
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(xc, yc, radius);
    glFlush();
}

void mouse(int button, int state, int mouseX, int mouseY) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (xc == 0 && yc == 0) {
            xc = mouseX;
            yc = 480 - mouseY;
        } else {
            int x = mouseX;
            int y = 480 - mouseY;
            radius = sqrt((x - xc) * (x - xc) + (y - yc) * (y - yc));
            glutPostRedisplay();
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle Drawing");
    glClearColor(0.0, 0.0,0.0, 0.0);
    gluOrtho2D(0, 640, 0, 480);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
