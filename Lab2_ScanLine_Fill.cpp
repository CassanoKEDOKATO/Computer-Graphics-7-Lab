#include <GL/glut.h>
#include <stack>

// K�ch th�?c c?a s?
const int WIDTH = 800;
const int HEIGHT = 600;

// M�u s?c
float fillColor[] = {0.0, 1.0, 0.0};   // M�u t�
float boundaryColor[] = {0.0, 0.0, 0.0}; // M�u ��?ng bi�n

// H�m ki?m tra m�u
bool isColorEqual(float* color1, float* color2) {
    for (int i = 0; i < 3; i++) {
        if (color1[i] != color2[i])
            return false;
    }
    return true;
}

// H�m t� m�u theo d?ng qu�t
void scanlineFill(int x, int y, float* fillColor, float* boundaryColor) {
    // �?c m�u t?i �i?m ban �?u
    float pixelColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixelColor);

    // N?u �i?m ban �?u l� m�u ��?ng bi�n ho?c m�u t�, kh�ng c?n th?c hi?n t� m�u
    if (isColorEqual(pixelColor, boundaryColor) || isColorEqual(pixelColor, fillColor))
        return;

    // T?o m?t ng�n x?p �? l�u tr? c�c c?nh c?a �a gi�c
    std::stack<int> edgeStack;

    // Th�m �i?m ban �?u v�o ng�n x?p
    edgeStack.push(x);
    edgeStack.push(y);

    while (!edgeStack.empty()) {
        // L?y c�c �i?m c?nh t? ng�n x?p
        int y1 = edgeStack.top();
        edgeStack.pop();
        int x1 = edgeStack.top();
        edgeStack.pop();

        // Di chuy?n �?n �i?m b�n tr�i c?a c?nh
        while (!isColorEqual(pixelColor, boundaryColor) && !isColorEqual(pixelColor, fillColor)) {
            x1--;
            glReadPixels(x1, y1, 1, 1, GL_RGB, GL_FLOAT, pixelColor);
        }
        x1++;

        // T?m �i?m b�n ph?i c?a c?nh
        int x2 = x1;
        glReadPixels(x2, y1, 1, 1, GL_RGB, GL_FLOAT, pixelColor);
        while (!isColorEqual(pixelColor, boundaryColor) && !isColorEqual(pixelColor, fillColor)) {
            x2++;
            glReadPixels(x2, y1, 1, 1, GL_RGB, GL_FLOAT, pixelColor);
        }
        x2--;

        // T� m�u t? �i?m b�n tr�i �?n �i?m b�n ph?i c?a c?nh
        glColor3fv(fillColor);
        glBegin(GL_POINTS);
        for (int i = x1; i <= x2; i++) {
            glVertex2i(i, y1);
        }
        glEnd();
        glFlush();

        // Ki?m tra c�c �i?m tr�n v� d�?i c?a c?nh
        for (int i = x1; i <= x2; i++) {
            glReadPixels(i, y1 + 1, 1, 1, GL_RGB, GL_FLOAT, pixelColor);
            if (!isColorEqual(pixelColor, boundaryColor) && !isColorEqual(pixelColor, fillColor)) {
                edgeStack.push(i);
                edgeStack.push(y1 + 1);
            }

            glReadPixels(i, y1 - 1, 1, 1, GL_RGB, GL_FLOAT, pixelColor);
            if (!isColorEqual(pixelColor, boundaryColor) && !isColorEqual(pixelColor, fillColor)) {
                edgeStack.push(i);
                edgeStack.push(y1 - 1);
            }
        }
    }
}

// H�m v?
void display() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // V? ��?ng bi�n m�u �en
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(200, 200);
    glVertex2i(300, 200);
    glVertex2i(300, 300);
    glVertex2i(200, 300);
    glEnd();

    // G?i h�m t� m�u theo d?ng qu�t
    scanlineFill(250, 250, fillColor, boundaryColor);

    glFlush();
}

// H�m kh?i t?o
void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Scan Line Fill Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
