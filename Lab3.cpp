#include <iostream>
#include <cmath>

class Matrix2D {
public:
    float matrix[3][3];

    Matrix2D() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                matrix[i][j] = (i == j) ? 1.0 : 0.0; // Kh?i t?o ma tr?n don v?
            }
        }
    }

    void translate(float dx, float dy) {
        matrix[0][2] += dx;
        matrix[1][2] += dy;
    }

    void scale(float sx, float sy) {
        matrix[0][0] *= sx;
        matrix[1][1] *= sy;
    }

    void rotate(float angle) {
        float radian = angle * (M_PI / 180.0);
        float cosA = cos(radian);
        float sinA = sin(radian);

        float temp00 = matrix[0][0] * cosA - matrix[0][1] * sinA;
        float temp01 = matrix[0][0] * sinA + matrix[0][1] * cosA;
        float temp10 = matrix[1][0] * cosA - matrix[1][1] * sinA;
        float temp11 = matrix[1][0] * sinA + matrix[1][1] * cosA;

        matrix[0][0] = temp00;
        matrix[0][1] = temp01;
        matrix[1][0] = temp10;
        matrix[1][1] = temp11;
    }
};

int main() {
    Matrix2D transformation;

    // Thi?t l?p ma tr?n ban d?u
    std::cout << "Ma tran ban dau:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << transformation.matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Áp d?ng các phép bi?n d?i
    transformation.translate(2, 3);
    transformation.scale(2, 2);
    transformation.rotate(45);

    // Hi?n th? ma tr?n sau bi?n d?i
    std::cout << "\nMa tran sau bien doi:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << transformation.matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}

