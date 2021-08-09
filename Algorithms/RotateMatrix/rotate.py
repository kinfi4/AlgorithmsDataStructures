import math

from transpose import transpose


def rotate(matrix):
    transpose(matrix)  # after transposing matrix, we just need to change the order or columns

    for i in range(len(matrix)):  # for each row
        for k in range(len(matrix) // 2):  # we d like to swap the first and last values and so on
            matrix[i][k], matrix[i][len(matrix) - 1 - k] = matrix[i][len(matrix) - 1 - k], matrix[i][k]
    
    return matrix



if __name__ == '__main__':
    matrix = [[k for k in range(3*i, 3*i + 3)] for i in range(3)]

    for row in matrix:
        print(row)

    print('-' * 40)

    rotate(matrix)

    for row in matrix:
        print(row)
