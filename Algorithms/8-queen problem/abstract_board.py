from copy import deepcopy
from abc import ABC
from random import randint, choice, sample

from const import Figures, Point, BOARD_SIZE, SOLVED_BOARDS


class Board(ABC):
    def __init__(self, difficulty=2):
        if difficulty < 1 or difficulty > 5:
            raise ValueError(f'Value for difficulty = {difficulty} is invalid, difficulty must be an integer in [1, 5]')

        self.difficulty = difficulty
        self.board = self._generate_board()
        self.start_time = None
        self.number_of_states = 0
        self.number_of_iterations = 0

    def evaluate_state(self, board):
        queen_positions = list(self.get_all_queens(board))
        return sum(self._queen_intersect_another_queen(queen_pos, queen_positions) for queen_pos in queen_positions) // 2

    def get_all_possible_child_boards(self, board: list):
        result = []

        for queen_pos in self.get_all_queens(board):
            for move in self.get_all_queens_possible_moves(board, queen_pos):
                new_board = deepcopy(board)
                new_board[queen_pos.y][queen_pos.x] = Figures.EMPTY
                new_board[move.y][move.x] = Figures.QUEEN

                result.append(new_board)

        return result

    def _generate_board(self):
        chosen_random_board = choice(SOLVED_BOARDS)

        queens_to_be_replaced = sample(list(self.get_all_queens(chosen_random_board)), self.difficulty)

        for queen in queens_to_be_replaced:
            chosen_random_board[queen.y][queen.x] = Figures.EMPTY
            chosen_random_board = self.place_queen_to_random_position(chosen_random_board)

        return chosen_random_board

    def get_all_queens_possible_moves(self, board, queens_position: Point):
        moves = []

        y = queens_position.y - 1
        while y >= 0 and board[y][queens_position.x] == Figures.EMPTY:  # moving queen up
            moves.append(Point(queens_position.x, y))
            y -= 1

        y = queens_position.y + 1
        while y < len(board) and board[y][queens_position.x] == Figures.EMPTY:  # moving queen down
            moves.append(Point(queens_position.x, y))
            y += 1

        x = queens_position.x + 1
        while x < len(board) and board[queens_position.y][x] == Figures.EMPTY:  # moving queen right
            moves.append(Point(x, queens_position.y))
            x += 1

        x = queens_position.x - 1
        while x >= 0 and board[queens_position.y][x] == Figures.EMPTY:  # moving queen left
            moves.append(Point(x, queens_position.y))
            x -= 1

        x = queens_position.x - 1
        y = queens_position.y - 1
        while x >= 0 and y >= 0 and board[y][x] == Figures.EMPTY:  # moving queen left up
            moves.append(Point(x, y))
            x -= 1
            y -= 1

        x = queens_position.x + 1
        y = queens_position.y + 1
        while x < len(board) and y < len(board) and board[y][x] == Figures.EMPTY:  # moving queen left up
            moves.append(Point(x, y))
            x += 1
            y += 1

        return moves

    @staticmethod
    def place_queen_to_random_position(board):
        rand_x, rand_y = randint(0, BOARD_SIZE - 1), randint(0, BOARD_SIZE - 1)

        while board[rand_y][rand_x] != Figures.EMPTY:
            rand_x, rand_y = randint(0, BOARD_SIZE - 1), randint(0, BOARD_SIZE - 1)

        board[rand_y][rand_x] = Figures.QUEEN
        return board

    @staticmethod
    def _queen_intersect_another_queen(queen_pos, all_queen_positions):
        horizontal, vertical, right_diagonal, left_diagonal = 'horizontal', 'vertical', 'r-diagonal', 'l-diagonal'
        intersection_directions = []

        for another_queen_pos in all_queen_positions:
            if another_queen_pos == queen_pos:
                continue

            if another_queen_pos.x == queen_pos.x and horizontal not in intersection_directions:
                intersection_directions.append(horizontal)
            elif another_queen_pos.y == queen_pos.y and vertical not in intersection_directions:
                intersection_directions.append(vertical)
            elif another_queen_pos.y - queen_pos.y == another_queen_pos.x - queen_pos.x and right_diagonal not in intersection_directions:
                intersection_directions.append(right_diagonal)
            elif -1 * (another_queen_pos.y - queen_pos.y) == another_queen_pos.x - queen_pos.x and left_diagonal not in intersection_directions:
                intersection_directions.append(left_diagonal)

        return len(intersection_directions)

    @staticmethod
    def get_all_queens(board):
        for y, row in enumerate(board):
            for x, cell in enumerate(row):
                if cell == Figures.QUEEN:
                    yield Point(x, y)

    @staticmethod
    def print_the_board(board):
        for row in board:
            for cell in row:
                if cell == Figures.QUEEN:
                    print('Q', end=' ')
                else:
                    print('_', end=' ')

            print()
