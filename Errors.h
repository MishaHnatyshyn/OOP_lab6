#include <string>
#include <iostream>
using namespace std;

class Error{
public:
    virtual void printError(){
        cout << "ERROR! ";
    }

    void abort(){
        string answer;
        cout << "Try again? [Yes/No]" << endl;
        cin >> answer;
        if (answer == "No") exit(1);
    }
};

class SizeError : public Error{
    int height, width;
public:
    SizeError(int h, int w): width(w), height(h){}
    virtual void printError(){
        Error::printError();
        cout << "Your matrix is not square! Width: " << width << "; Height: " << height << ";\n";
    }
};

class DetError : public Error{
public:
    virtual void printError(){
        Error::printError();
        cout << "Determinant is 0!" << endl;
    }
};

class HeightError : public Error{
public:
    virtual void printError(){
        Error::printError();
        cout << "Height value can`t be negative or equals 0!" << endl;
    }
};

class WidthError : public Error{
public:
    virtual void printError(){
        Error::printError();
        cout << "Width value can`t be negative or equals 0!" << endl;
    }
};