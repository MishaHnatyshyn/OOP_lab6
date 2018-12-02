#include "Matrix.h"

Matrix::Matrix(){
    cout << "Enter please, number of rows" << endl;
    cin >> height;
    if (height < 1) throw HeightError();
    cout << "Enter please, number of columns" << endl;
    cin >> width;
    if (width < 1) throw WidthError();
    size = (width == height) ? width : -1;
    this->matrix = new double *[height];
    for (int i = 0; i < height; ++i) {
        this->matrix[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            cout << "Enter please (" << i << ";"<< j << ") element" << endl;
            cin >> this->matrix[i][j];
        }
    }
    cout <<endl;
}

Matrix::Matrix(double ** mat, int x, int y): width(x), height(y){
    size = (x == y) ? x : -1;
    matrix = new double *[y];
    for (int i = 0; i < y; ++i) {
        matrix[i] = new double[x];
        for (int j = 0; j < x; ++j) {
            matrix[i][j] = mat[i][j];
        }
    }
}

Matrix::~Matrix(){
    delete[] matrix;
}

Matrix Matrix::getInvertibleMatrix(){
    if (size == -1) throw SizeError(height, width);
    double det = this->getDet();
    if (det == 0) throw DetError();
    double ** adjugatedMatrix = this->getAdjugateMatrix();
    adjugatedMatrix = this->getTransposeMatrix(adjugatedMatrix, size, size);
    multiplyMatrixAndScalar(1/det, adjugatedMatrix, size, size);
    Matrix result(adjugatedMatrix, size, size);
    delete[] adjugatedMatrix;
    return result;
}

double Matrix::getDet(){
    double result = 1;
    double **tempMatrix;
    tempMatrix = new double *[size];
    for (int i = 0; i < size; ++i) {
        tempMatrix[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            tempMatrix[i][j] = matrix[i][j];
        }
    }

    for (int i = 0; i < this->size-1; ++i) {
        if (this->matrix[i][i] == 0) {
            bool flag = false;
            for (int j = i; j <this->size-1 ; ++j) {
                if (matrix[j][i] != 0) {
                    swap(matrix[i], matrix[j]);
                    flag = true;
                    break;
                }
            }
            if (flag) return 0;
        }
        for (int k = i + 1; k < this->size; ++k) {
            float coef = tempMatrix[k][i]/tempMatrix[i][i];
            for (int j = 0; j < this->size; ++j) {
                tempMatrix[k][j+i] = tempMatrix[k][j+i] - tempMatrix[i][j+i]*coef;
            }
        }
    }
    for (int l = 0; l < this->size; ++l) {
        result *= tempMatrix[l][l];
    }
    delete[] tempMatrix;
    return result;
}

void Matrix::display(){
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}

double** Matrix::getTransposeMatrix(double** mat, int height, int width){
    double **tempMatrix;
    tempMatrix = new double *[width];
    for (int i = 0; i < width; ++i) {
        tempMatrix[i] = new double[height];
        for (int j = 0; j < height; ++j) {
            tempMatrix[i][j] = mat[j][i];
        }
    }
    return tempMatrix;
};

double ** Matrix::getAdjugateMatrix(){
    double **tempMatrix;
    tempMatrix = new double *[size];
    for (int i = 0; i < size; ++i) {
        tempMatrix[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            tempMatrix[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int tempIndex1 = 0;
            double **tempMinorMatrix;
            tempMinorMatrix = new double *[size -1];
            for (int k = 0; k < size; ++k) {
                if (k == i) continue;
                tempMinorMatrix[tempIndex1] = new double[size-1];
                int tempIndex2 = 0;
                for (int p = 0; p < size; ++p) {
                    if (p != j) {
                        tempMinorMatrix[tempIndex1][tempIndex2] = matrix[k][p];
                        tempIndex2++;
                    }
                }
                tempIndex1++;
            }
            Matrix tempMinorMatrixClass(tempMinorMatrix, size -1 , size-1);
            double det = tempMinorMatrixClass.getDet();
            tempMatrix[i][j] = -1 * det;
            delete[] tempMinorMatrix;
        }
    }
    return tempMatrix;
}

void Matrix::multiplyMatrixAndScalar(double scalar, double** Matrix, int width, int height){
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Matrix[i][j] *= scalar;
        }
    }
}
