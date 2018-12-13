#include "Errors.h"
using namespace std;

class Matrix{
    double ** matrix;
    int size, width, height;
public:
    Matrix();

    Matrix(double **, int, int);

    ~Matrix();

    Matrix getInvertibleMatrix();

    double getDet();

    void display();

    double** getTransposeMatrix(double**, int, int);

    double ** getAdjugateMatrix();

    void multiplyMatrixAndScalar(double, double**, int, int);
};
