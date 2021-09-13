from abstract_board import Board
from const import FAIL


class IDSBoardStrategy(Board):
    def solve(self):
        result_board = self.ids(self.board, 1)
        self.print_the_board(result_board)

    def ids(self, board, depth):
        for _ in range(8):
            result = self.dls(board, depth)
            depth += 1

            if result != FAIL:
                return result

    def dls(self, board, iteration):
        self.number_of_iterations += 1

        if self.evaluate_state(board) == 0:
            return board

        if iteration > 0:
            children = self.get_all_possible_child_boards(board)
            self.number_of_states += len(children)

            for child_board in children:
                result = self.dls(child_board, iteration - 1)

                if result != FAIL:
                    return result

        return FAIL  # that means that we checked all the possible children, and none of them returned the solution
