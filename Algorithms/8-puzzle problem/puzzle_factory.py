from random import sample

from utils import MATRIX


class PuzzleFactory:
    def create_puzzle(self) -> MATRIX:
        puzzle = self._generate_random_puzzle()

        while not self.is_solvable(puzzle):
            puzzle = self._generate_random_puzzle()

        return puzzle

    def is_solvable(self, puzzle: MATRIX) -> bool:
        invs = self._get_inversion_count([element for row in puzzle for element in row])
        return invs % 2 == 0

    @staticmethod
    def _generate_random_puzzle() -> MATRIX:
        sequence_of_nodes = sample([str(i) for i in range(1, 9)] + ['_'], 9)
        return [[sequence_of_nodes[x] for x in range(3 * y, 3 * y + 3)] for y in range(3)]

    @staticmethod
    def _get_inversion_count(arr) -> int:
        inv_count = 0
        empty_value = '_'

        for i in range(0, 9):
            for j in range(i + 1, 9):
                if arr[j] != empty_value and arr[i] != empty_value and arr[i] > arr[j]:
                    inv_count += 1

        return inv_count if inv_count < 5 else 1
