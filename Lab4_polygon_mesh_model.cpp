#include <GL/glut.h>
#include <cmath>

const int MAX = 100;

typedef struct _3DPoint {
    float x;
    float y;
    float z;
} _3DPoint;

typedef struct EdgeType {
    int beginP;
    int endP;
} EdgeType;

typedef struct WireFrame {
    int numVertex, numEdge;
    _3DPoint vertex[MAX];
    EdgeType edge[MAX];
} WireFrame;

WireFrame tetrahedron = {
    4, 6,
    {
        {0.5, 0.25, 0}, {1, 0, 0.5}, {0.5, 1, 0}, {0, 0.5, 0.6}
    },
    {
        {0, 1}, {1, 2}, {2, 0},
        {0, 3}, {1, 3}, {2, 3}
    }
};

float angleX = 0.0;
float angleY = 0.0;

void rotateX(float theta) {
    float cosA = cos(theta);
    float sinA = sin(theta);

    for (int i = 0; i < tetrahedron.numVertex; i++) {
        float y = tetrahedron.vertex[i].y;
        float z = tetrahedron.vertex[i].z;
        tetrahedron.vertex[i].y = y * cosA - z * sinA;
        tetrahedron.vertex[i].z = y * sinA + z * cosA;
    }
}

void rotateY(float theta) {
    float cosA = cos(theta);
    float sinA = sin(theta);

    for (int i = 0; i < tetrahedron.numVertex; i++) {
        float x = tetrahedron.vertex[i].x;
        float z = tetrahedron.vertex[i].z;
        tetrahedron.vertex[i].x = x * cosA - z * sinA;
        tetrahedron.vertex[i].z = x * sinA + z * cosA;
    }
}

void drawAxes() {
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); // Màu d? cho tr?c x
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);

    glColor3f(0.0, 1.0, 0.0); // Màu xanh lá cây cho tr?c z
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);

    glColor3f(0.0, 0.0, 1.0); // Màu xanh lam cho tr?c y
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);

    glTranslatef(0.5, 0.5, 0.5); // Di chuy?n tâm quay v? tâm c?a hình

    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);

    glTranslatef(-0.5, -0.5, -0.5); // Di chuy?n ngu?c l?i v? trí ban d?u

    drawAxes(); // V? tr?c to? d?

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for (int i = 0; i < tetrahedron.numEdge; i++) {
        glVertex3f(tetrahedron.vertex[tetrahedron.edge[i].beginP].x, tetrahedron.vertex[tetrahedron.edge[i].beginP].y, tetrahedron.vertex[tetrahedron.edge[i].beginP].z);
        glVertex3f(tetrahedron.vertex[tetrahedron.edge[i].endP].x, tetrahedron.vertex[tetrahedron.edge[i].endP].y, tetrahedron.vertex[tetrahedron.edge[i].endP].z);
    }
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        angleX += 5.0;
    } else if (key == GLUT_KEY_DOWN) {
        angleX -= 5.0;
    } else if (key == GLUT_KEY_LEFT) {
        angleY -= 5.0;
    } else if (key == GLUT_KEY_RIGHT) {
        angleY += 5.0;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tetrahedron");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}
