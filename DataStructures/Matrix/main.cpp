#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    auto matrix = SquareMatrix(2, 5);

    matrix[0][0] = 12;
    matrix[1][1] = 15;
    matrix--;
    matrix.print_matrix();
    cout << endl;

    matrix.get_inverse_matrix().print_matrix();

    return 0;
}
