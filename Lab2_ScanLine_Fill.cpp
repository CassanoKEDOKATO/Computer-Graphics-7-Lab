#include <GL/glut.h>
#include <stack>

// Kích thý?c c?a s?
const int WIDTH = 800;
const int HEIGHT = 600;

// Màu s?c
float fillColor[] = {0.0, 1.0, 0.0};   // Màu tô
float boundaryColor[] = {0.0, 0.0, 0.0}; // Màu ðý?ng biên

// Hàm ki?m tra màu
bool isColorEqual(float* color1, float* color2) {
    for (int i = 0; i < 3; i++) {
        if (color1[i] != color2[i])
            return false;
    }
    return true;
}

// Hàm tô màu theo d?ng quét
void scanlineFill(int x, int y, float* fillColor, float* boundaryColor) {
    // Ð?c màu t?i ði?m ban ð?u
    float pixelColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixelColor);

    // N?u ði?m ban ð?u là màu ðý?ng biên ho?c màu tô, không c?n th?c hi?n tô màu
    if (isColorEqual(pixelColor, boundaryColor) || isColorEqual(pixelColor, fillColor))
        return;

    // T?o m?t ngãn x?p ð? lýu tr? các c?nh c?a ða giác
    std::stack<int> edgeStack;

    // Thêm ði?m ban ð?u vào ngãn x?p
    edgeStack.push(x);
    edgeStack.push(y);

    while (!edgeStack.empty()) {
        // L?y các ði?m c?nh t? ngãn x?p
        int y1 = edgeStack.top();
        edgeStack.pop();
        int x1 = edgeStack.top();
        edgeStack.pop();

        // Di chuy?n ð?n ði?m bên trái c?a c?nh
        while (!isColorEqual(pixelColor, boundaryColor) && !isColorEqual(pixelColor, fillColor)) {
            x1--;
            glReadPixels(x1, y1, 1, 1, GL_RGB, GL_FLOAT, pixelColor);
        }
        x1++;

        // T?m ði?m bên ph?i c?a c?nh
        int x2 = x1;
        glReadPixels(x2, y1, 1, 1, GL_RGB, GL_FLOAT, pixelColor);
        while (!isColorEqual(pixelColor, boundaryColor) && !isColorEqual(pixelColor, fillColor)) {
            x2++;
            glReadPixels(x2, y1, 1, 1, GL_RGB, GL_FLOAT, pixelColor);
        }
        x2--;

        // Tô màu t? ði?m bên trái ð?n ði?m bên ph?i c?a c?nh
        glColor3fv(fillColor);
        glBegin(GL_POINTS);
        for (int i = x1; i <= x2; i++) {
            glVertex2i(i, y1);
        }
        glEnd();
        glFlush();

        // Ki?m tra các ði?m trên và dý?i c?a c?nh
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

// Hàm v?
void display() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // V? ðý?ng biên màu ðen
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(200, 200);
    glVertex2i(300, 200);
    glVertex2i(300, 300);
    glVertex2i(200, 300);
    glEnd();

    // G?i hàm tô màu theo d?ng quét
    scanlineFill(250, 250, fillColor, boundaryColor);

    glFlush();
}

// Hàm kh?i t?o
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
