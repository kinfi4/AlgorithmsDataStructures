from time import perf_counter

from ids_for_solving_queen_problem import IDSBoardStrategy
from rbfs_fro_solving_queen_problem import RBFSBoardStrategy


def measure_algorithm(strategy_class, iterations_number=20, difficulty=2):
    times, states, iterations = [], [], []
    for _ in range(iterations_number):
        b = strategy_class(difficulty=difficulty)

        start_time = perf_counter()
        b.solve()
        end_time = perf_counter()

        times.append(end_time - start_time)
        states.append(b.number_of_states)
        iterations.append(b.number_of_iterations)

        print(f'It took {end_time - start_time} to solve the problem for {strategy_class.__name__}')

    with open(f'{strategy_class.__name__}.txt', 'w') as file:
        file.write(str(f'{times}\n'))
        file.write(str(f'{states}\n'))
        file.write(str(f'{iterations}\n'))


if __name__ == '__main__':
    measure_algorithm(RBFSBoardStrategy, 20, difficulty=1)
    measure_algorithm(IDSBoardStrategy, 20, difficulty=1)
