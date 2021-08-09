
def transpose(matrix):
    for i in range(len(matrix)):
        for k in range(i, len(matrix[i])):
            matrix[i][k], matrix[k][i] = matrix[k][i], matrix[i][k]
    
    return matrix


if __name__ == '__main__':
    matrix = [[k for k in range(3*i, 3*i + 3)] for i in range(3)]

    for row in matrix:
        print(row)

    print('-' * 40)

    matrix = transpose(matrix)

    for row in matrix:
        print(row)
