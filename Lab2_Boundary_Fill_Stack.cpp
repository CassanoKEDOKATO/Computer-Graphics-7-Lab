#include <GL/glut.h>
#include <stack>
// Kích thý?c c?a c?a s?
const int WIDTH = 800;
const int HEIGHT = 600;

// Màu s?c
float fillColor[] = {1.0, 0.0, 0.0}; // Màu tô (màu d?)  // Màu tô
float boundaryColor[] = {0.0, 0.0, 0.0}; // Màu ðý?ng biên

// Hàm ki?m tra màu
bool isColorEqual(float* color1, float* color2) {
    for (int i = 0; i < 3; i++) {
        if (color1[i] != color2[i])
            return false;
    }
    return true;
}

// Hàm tô màu theo ðý?ng biên
void floodFill(int x, int y, float* fillColor, float* boundaryColor) {
    std::stack<std::pair<int, int> > stack;
    stack.push(std::make_pair(x, y));

    while (!stack.empty()) {
        std::pair<int, int> point = stack.top();
        stack.pop();
        int currentX = point.first;
        int currentY = point.second;

        float pixelColor[3];
        glReadPixels(currentX, currentY, 1, 1, GL_RGB, GL_FLOAT, pixelColor);

        if (isColorEqual(pixelColor, boundaryColor) || isColorEqual(pixelColor, fillColor)) {
            continue;
        }

        glColor3fv(fillColor);
        glBegin(GL_POINTS);
        glVertex2i(currentX, currentY);
        glEnd();
        glFlush();

        stack.push(std::make_pair(currentX + 1, currentY));
        stack.push(std::make_pair(currentX - 1, currentY));
        stack.push(std::make_pair(currentX, currentY + 1));
        stack.push(std::make_pair(currentX, currentY - 1));
    }
}

// Hàm v? tam giác và tô màu
void drawTriangleAndFill() {
    // V? tam giác
    glColor3f(0.0, 0.0, 0.0); // Màu ðý?ng biên (ðen)
    glBegin(GL_LINE_LOOP);
    glVertex2i(300, 100);
    glVertex2i(400, 200);
    glVertex2i(200, 200);
    glEnd();
    glFlush();

    // Tô màu theo ðý?ng biên t? ði?m (300, 150)
    floodFill(300, 150, fillColor, boundaryColor);
}

// Hàm hi?n th?
void display() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawTriangleAndFill();

    glFlush();
}

// Hàm kh?i t?o
void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
}

// Hàm main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Boundary Fill Algorithm for Triangle use Stack");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
