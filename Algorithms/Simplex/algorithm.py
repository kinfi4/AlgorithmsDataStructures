import math
import numpy as np


def make_table(c, A, b):
    xb = [eq + [x] for eq, x in zip(A, b)]
    z = c + [0]
    return xb + [z]


def can_be_improved(tableau):
    z = tableau[-1]
    return any(x > 0 for x in z[:-1])


def is_basic_solution(column):
    return sum(column) == 1 and len([c for c in column if c == 0]) == len(column) - 1


def propose_solution(tableau):
    columns = np.array(tableau).T
    solutions = []
    for column in columns[:-1]:
        solution = 0
        if is_basic_solution(column):
            one_index = column.tolist().index(1)
            solution = columns[-1][one_index]
        solutions.append(solution)

    return solutions


def pivot_step(tableau, pivot_position):
    new_tableau = [[] for eq in tableau]

    i, j = pivot_position
    pivot_value = tableau[i][j]
    new_tableau[i] = np.array(tableau[i]) / pivot_value

    for eq_i, eq in enumerate(tableau):
        if eq_i != i:
            multiplier = np.array(new_tableau[i]) * tableau[eq_i][j]
            new_tableau[eq_i] = np.array(tableau[eq_i]) - multiplier

    return new_tableau


def get_pivot(tableau):
    z = tableau[-1]
    column = next(i for i, x in enumerate(z[:-1]) if x > 0)

    restrictions = []
    for eq in tableau[:-1]:
        el = eq[column]
        restrictions.append(math.inf if el <= 0 else eq[-1] / el)

    row = restrictions.index(min(restrictions))
    return row, column


def simplex(z_coef, matrix, b):
    table_form = make_table(z_coef, matrix, b)

    while can_be_improved(table_form):
        pivot = get_pivot(table_form)
        table_form = pivot_step(table_form, pivot)

    return propose_solution(table_form)


c1 = [-6, 0, 1, -1, -2]

A1 = [
    [4, 0, 5, 2, 1 ],
    [2, -1, 0, 1, 0],
    [1, 1, 0, 0, 1 ],
]

b1 = [8, 2, 2]


result = simplex(c1, A1, b1)

for idx, x_value in enumerate(result):
    print(f'x_{idx} = {x_value}')
