from time import perf_counter

from node import Node
from utils import MATRIX
from puzzle_factory import PuzzleFactory


def print_current_board(current):
    for row in current:
        for cell in row:
            print(cell, end=' ')

        print()

    print('\n----------\n')


class PuzzleBoard:
    def __init__(self):
        factory = PuzzleFactory()
        self._board = factory.create_puzzle()

        print("PUZZLE INITIALIZED")

        self.goal_state = [[str(x) for x in range(1 + 3*y, 3*y + 3 + 1)] for y in range(3)]
        self.goal_state[-1][-1] = '_'

        self._open_list = []
        self._closed_list = []

        self._max_time_seconds = 60 * 10

    def h(self, start: MATRIX, goal: MATRIX) -> int:
        return sum(int(start[i][j] != goal[i][j]) for j in range(3) for i in range(3))

    def f(self, start: Node, goal: MATRIX) -> int:
        return self.h(start.state, goal)

    def _is_win_state(self, state: MATRIX) -> bool:
        return self.h(state, self.goal_state) == 0

    def _time_was_exceeded(self, start_time: float) -> bool:
        current_time = perf_counter()
        return (current_time - start_time) > self._max_time_seconds

    def find_a_star_solution(self, verbose: bool = False) -> tuple[float, int, int]:
        start_time = perf_counter()
        total_states_generated = 0
        max_states_in_memory = 0

        iterations = 0

        start_node = Node(self._board, 0, 0)
        start_node.f_value = self.f(start_node, self.goal_state)

        self._open_list.append(start_node)

        while True:
            if self._time_was_exceeded(start_time):
                raise RuntimeError("Time for A* algorithm was exceeded!")

            iterations += 1

            current_node = self._open_list[0]

            if verbose:
                print_current_board(current_node.state)

            if self._is_win_state(current_node.state):
                print_current_board(current_node.state)

                end_time = perf_counter()
                return round(end_time - start_time, 2), total_states_generated, max_states_in_memory
            for child_node in current_node.generate_children():
                if child_node not in self._closed_list:
                    child_node.f_value = self.f(child_node, self.goal_state)
                    self._open_list.append(child_node)

                    total_states_generated += 1

            self._closed_list.append(current_node)

            self._open_list.pop(0)
            self._open_list.sort(key=lambda x: x.f_value)

            max_states_in_memory = max(max_states_in_memory, len(self._open_list))

    def find_ucs_solution(self, verbose: bool = False) -> tuple[float, int, int]:
        start_time = perf_counter()
        total_states_generated = 0
        max_states_in_memory = 0

        iterations = 0

        start_node = Node(self._board, 0, 0)

        self._open_list.append(start_node)

        while True:
            # if self._time_was_exceeded(start_time):
            #     raise RuntimeError("Time for A* algorithm was exceeded!")

            iterations += 1

            current_node = self._open_list[0]

            if verbose:
                print_current_board(current_node.state)

            if self._is_win_state(current_node.state):
                print_current_board(current_node.state)

                end_time = perf_counter()
                return round(end_time - start_time, 2), total_states_generated, max_states_in_memory

            for child_node in current_node.generate_children():
                if child_node not in self._closed_list:
                    self._open_list.append(child_node)

                    total_states_generated += 1

            self._closed_list.append(current_node)

            self._open_list.pop(0)
            self._open_list.sort(key=lambda x: x.level)

            if total_states_generated % 1000 == 0:
                print(f"TOTAL STATES GENERATED: {total_states_generated}")

            max_states_in_memory = max(max_states_in_memory, len(self._open_list))
