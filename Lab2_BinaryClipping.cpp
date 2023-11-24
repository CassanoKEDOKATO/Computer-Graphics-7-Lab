#include <GL/glut.h>
#include <iostream>

using namespace std;

float xmin = -100;
float ymin = -100;
float xmax = 200;
float ymax = 150;

float xdA = -1, ydA = -1, xdB = -1, ydB = -1;

void initGL(void) {
    glClearColor(1, 1, 1, 0);
    gluOrtho2D(-300, 300, -300, 300);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmin, ymax);
    glVertex2i(xmax, ymax);
    glVertex2i(xmax, ymin);
    glEnd();

    if (xdA != -1 && xdB != -1) {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2i(xdA, ydA);
        glVertex2i(xdB, ydB);
        glEnd();
    }

    glFlush();
}

int code(float x, float y) {
    int c = 0;
    if (y > ymax) c = 8;
    if (y < ymin) c = 4;
    if (x > xmax) c = 2;
    if (x < xmin) c = 1;
    return c;
}

void cohen_Line(float xA, float yA, float xB, float yB) {
    int cA = code(xA, yA);
    int cB = code(xB, yB);

    while (cA & cB) {
        xdA = ydA = xdB = ydB = -1;
        return;
    }

    while (cA | cB) {
        float xi, yi;
        int c;
        if (cA) {
            c = cA;
            xi = xA;
            yi = yA;
        } else {
            c = cB;
            xi = xB;
            yi = yB;
        }

        float x, y;
        if (c & 8) {
            y = ymax;
            x = xi + 1.0 * (ymax - yi) / (yB - yA);
        } else if (c & 4) {
            y = ymin;
            x = xi + 1.0 * (ymin - yi) / (yB - yA);
        } else if (c & 2) {
            x = xmax;
            y = yi + (xmax - xi) * (yB - yA) / (xB - xA);
        } else if (c & 1) {
            x = xmin;
            y = yi + (xmin - xi) * (yB - yA) / (xB - xA);
        }

        if (c == cA) {
            xdA = x;
            ydA = y;
            cA = code(xdA, ydA);
        } else {
            xdB = x;
            ydB = y;
            cB = code(xdB, ydB);
        }
    }
    display();
}

void mymouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            if (xdA == -1) {
                xdA = x - 300;
                ydA = 300 - y;
            } else if (xdB == -1) {
                xdB = x - 300;
                ydB = 300 - y;
                cohen_Line(xdA, ydA, xdB, ydB);
            }
        }
    }
}

void mykey(unsigned char key, int x, int y) {
    if (key == 'c') {
        cohen_Line(xdA, ydA, xdB, ydB);
        glFlush();
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("DEMO XET DOAN THANG BANG HCN - Chia - Nhi Phan");
    glutDisplayFunc(display);
    glutMouseFunc(mymouse);
    glutKeyboardFunc(mykey);
    initGL();
    glutMainLoop();
    return 0;
}

