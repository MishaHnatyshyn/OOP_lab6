#include "Matrix.h"
using namespace std;

int main() {
    while (true){
        try{
            Matrix matrix;
            Matrix res = matrix.getInvertibleMatrix();
            cout << "RESULT" << endl;
            res.display();
            break;
        }catch (Error &err){
            err.printError();
            err.abort();
        }
    }
    return 0;
}
