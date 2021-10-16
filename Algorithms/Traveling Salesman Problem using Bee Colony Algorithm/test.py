import matplotlib.pyplot as plt

from Salesman import Salesman


def test_set_of_arguments(workers, scouters):
    salesman = Salesman(work_bees_amount=workers, scouters_amount=scouters, epochs=300, not_changing_limit=100, show_plots=False)
    return salesman.find_optimal_path()


def find_best_salesman_arguments(min_workers=50, max_workers=200, min_scouters=5, max_scouters=40):
    paths_for_workers, paths_for_scouters = [], []
    best_workers_amount, best_scouters_amount = None, None

    for workers_amount in range(min_workers, max_workers, 2):
        result, _ = test_set_of_arguments(workers_amount, min_scouters)

        if best_workers_amount is None or result > max(paths_for_workers):
            best_workers_amount = result

        paths_for_workers.append(result)
        plt.plot(range(min_workers, workers_amount + 2, 2), paths_for_workers)
        plt.pause(0.0001)
        plt.show(block=False)

    for scouters_amount in range(min_scouters, max_scouters):
        result, _ = test_set_of_arguments(best_workers_amount, scouters_amount)

        if best_scouters_amount is None or result > max(paths_for_scouters):
            best_scouters_amount = result

        paths_for_scouters.append(result)
        plt.plot(range(min_scouters, scouters_amount + 1), paths_for_scouters)
        plt.pause(0.0001)
        plt.show(block=False)


if __name__ == '__main__':
    find_best_salesman_arguments()

    input('Press any key, to quit the script...')
