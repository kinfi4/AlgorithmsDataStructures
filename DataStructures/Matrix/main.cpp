#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    auto matrix = SquareMatrix(4, 1);

    matrix[0][0] = 12;
    matrix[1][1] = 12;
    matrix[2][1] = 35;
    matrix[3][3] = 55;
    matrix++;
    matrix++;
    matrix--;
    matrix.print_matrix();
    cout << matrix.get_determinant();
//    cout << matrix[0][0] << endl;

    return 0;
}
