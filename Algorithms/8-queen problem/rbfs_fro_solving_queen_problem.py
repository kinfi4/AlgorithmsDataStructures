import math
from time import perf_counter

from abstract_board import Board
from const import INFINITY, FAIL, EMPTY_BOARD


class RBFSBoardStrategy(Board):
    def solve(self):
        self.start_time = perf_counter()

        result_board, _ = self.rbfs(self.board, INFINITY, 1)
        self.print_the_board(result_board)

    def rbfs(self, board, f_limit, depth):
        self.number_of_iterations += 1

        if depth > 8:
            return FAIL, INFINITY

        if self.evaluate_state(board) == 0:
            return board, 0

        board_children = self.get_all_possible_child_boards(board)
        if not board_children:
            return FAIL, INFINITY

        self.number_of_states += len(board_children)

        weights = []
        for board_child in board_children:
            weights.append([board_child, self.evaluate_state(board_child)])

        while True:
            weights = sorted(weights, key=lambda pair: pair[1])

            best_pair = weights[0]  # pair current best board, and its evaluation
            second_best_pair = weights[1] if len(weights) > 1 else None

            if best_pair[1] > f_limit:
                return FAIL, best_pair[1]

            alternative_evaluation = second_best_pair[1] if second_best_pair else INFINITY
            result, weights[0][1] = self.rbfs(best_pair[0], min(f_limit, alternative_evaluation), depth + 1)

            if result != FAIL:
                return result, 0

            if math.fabs(self.start_time - perf_counter()) // 60 > 30:
                break

        print('Time limit exceeded')
        return EMPTY_BOARD

    def _get_two_first_best_solutions_indexes(self, boards):
        sorted_boards = sorted(boards, key=self.evaluate_state)

        if len(sorted_boards) > 2:
            return sorted_boards[0], sorted_boards[1]
        elif len(sorted_boards) == 1:
            return sorted_boards[0], None
        else:
            raise ValueError('Cant get two best boards from empty list')
