#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    auto matrix = SquareMatrix(3, 10);

    matrix[0][0] = 12;
    matrix++;
    matrix++;
    matrix--;
    matrix.print_matrix();
//    cout << matrix[0][0] << endl;

    return 0;
}
