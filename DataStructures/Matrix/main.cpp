#include <iostream>
#include "Matrix.h"

using namespace std;

void first_demo(){
    auto matrix = SquareMatrix(3, 5);
    matrix.print_matrix();
    cout << endl << endl;

    matrix[0][0] = 12;
    matrix[1][1] = 14;
    matrix[2][2] = 16;

    matrix.print_matrix();
    cout << endl << endl;

    matrix--;
    matrix--;
    matrix++;

    matrix.print_matrix();
    cout << endl << endl;

    matrix.get_inverse_matrix().print_matrix();
}

void second_demo(){
    auto matrix1 = SquareMatrix(4, 10);
    auto matrix2 = SquareMatrix(4, 40);

    matrix1.print_matrix();
    cout << endl;
    matrix2.print_matrix();

    cout << endl;

    (matrix1 + matrix2).print_matrix();
    cout << endl;
    (matrix1 - matrix2).print_matrix();
    cout << endl;
    matrix1 *= 2;
    matrix1.print_matrix();

    cout << endl;

    matrix2 /= 2;
    matrix2.print_matrix();

    cout << endl << (matrix1 == matrix2);

}


int main() {
    first_demo();
    second_demo();

    return 0;
}
