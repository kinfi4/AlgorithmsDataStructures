from enum import Enum
from collections import namedtuple


BOARD_SIZE = 8
INFINITY = int(10e20)
SUCCESS, FAIL = 'SUCCESS', 'FAIL'


class Figures(Enum):
    QUEEN = 'q'
    EMPTY = '_'


Point = namedtuple('Point', 'x y')


SOLVED_BOARDS = [
    [
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN],
        [Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY],
    ],
    [
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY],
        [Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
    ],
    [
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
    ],
    [
        [Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN],
        [Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
    ],
    [
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY],
        [Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.QUEEN, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
    ],
]

EMPTY_BOARD = [
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
        [Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY, Figures.EMPTY],
    ]
