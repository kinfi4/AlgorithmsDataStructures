from random import sample

import numpy as np


class Node:
    def __init__(self, state, level, f_value):
        self.state = state
        self.level = level
        self.f_value = f_value

    def generate_children(self):
        x, y = self.find('_')

        val_list = [[x, y - 1], [x, y + 1], [x - 1, y], [x + 1, y]]

        children = []
        for position in val_list:
            child_board = self.shuffle(x, y, position[0], position[1])
            if child_board is not None:
                child_node = Node(child_board, self.level + 1, 0)
                children.append(child_node)

        return children

    def shuffle(self, empty_cell_x, empty_cell_y, x2, y2):
        if 0 <= x2 < len(self.state) and 0 <= y2 < len(self.state):
            temp_board = self.copy(self.state)
            temp_board[x2][y2], temp_board[empty_cell_x][empty_cell_y] = temp_board[empty_cell_x][empty_cell_y], temp_board[x2][y2]
            return temp_board
        else:
            return None

    def copy(self, root):
        temp = []
        for i in root:
            t = []
            for j in i:
                t.append(j)
            temp.append(t)
        return temp

    def find(self, goal_cell):
        for i in range(len(self.state)):
            for j in range(len(self.state)):
                if self.state[i][j] == goal_cell:
                    return i, j


class PuzzleBoard:
    def __init__(self):
        sequence_of_nodes = sample([str(i) for i in range(1, 9)] + ['_'], 9)
        self.board = [[sequence_of_nodes[x] for x in range(3*y, 3*y + 3)] for y in range(3)]

        self.goal_state = [[str(x) for x in range(3*y, 3*y + 3)] for y in range(3)]
        self.goal_state[-1][-1] = '_'

        self.open = []
        self.closed = []

    def h(self, start, goal):
        return sum(int(start[i][j] != goal[i][j]) for j in range(3) for i in range(3))

    def f(self, start, goal):
        return self.h(start.state, goal) + start.level

    @staticmethod
    def print_current_board(current):
        for row in current:
            for cell in row:
                print(cell, end=' ')

            print()

        print('\n----------\n')

    def node_is_closed(self, node):
        for closed_node in self.closed:
            closed_state = closed_node.state
            if np.array_equal(node.state, closed_state):
                return True

        return False

    def find_path(self):
        start = Node(self.board, 0, 0)
        start.f_value = self.f(start, self.goal_state)
        self.open.append(start)

        print(start.state)
        print(self.f(start, self.goal_state))

        while True:
            current = self.open[0]
            # self.print_current_board(current.state)

            if self.h(current.state, self.goal_state) == 0:
                self.print_current_board(current.state)
                break

            for child_node in current.generate_children():
                if not self.node_is_closed(child_node):
                    child_node.f_value = self.f(child_node, self.goal_state)
                    self.open.append(child_node)

            self.closed.append(current)

            self.open.pop(0)
            self.open.sort(key=lambda x: x.f_value)


puzzle = PuzzleBoard()
puzzle.find_path()
