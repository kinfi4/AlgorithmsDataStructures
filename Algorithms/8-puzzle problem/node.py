from copy import deepcopy
from typing import Optional

import numpy as np

from utils import MATRIX


class Node:
    def __init__(self, state: MATRIX, level: int, f_value: Optional[int] = None):
        self.state = state
        self.level = level
        self.f_value = f_value

    def generate_children(self) -> list["Node"]:
        x, y = self._find_element_coordinates('_')

        val_list = [[x, y - 1], [x, y + 1], [x - 1, y], [x + 1, y]]

        children = []
        for position in val_list:
            child_board = self._swap(x, y, position[0], position[1])

            if child_board is not None:
                child_node = Node(child_board, self.level + 1, 0)
                children.append(child_node)

        return children

    def _swap(self, empty_cell_x: int, empty_cell_y: int, x2: int, y2: int) -> Optional[MATRIX]:
        if 0 <= x2 < len(self.state) and 0 <= y2 < len(self.state):
            temp_board = deepcopy(self.state)
            temp_board[x2][y2], temp_board[empty_cell_x][empty_cell_y] = temp_board[empty_cell_x][empty_cell_y], temp_board[x2][y2]

            return temp_board

    def _find_element_coordinates(self, goal_cell: str) -> tuple[int, int]:
        for i in range(len(self.state)):
            for j in range(len(self.state)):
                if self.state[i][j] == goal_cell:
                    return i, j

    def __eq__(self, other: "Node") -> bool:
        return np.array_equal(self.state, other.state)
