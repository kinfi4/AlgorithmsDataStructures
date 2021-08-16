import numpy as np
import matplotlib.pyplot as plt


class GeneticBackpackFinder:
    BACKPACK_SIZE = 100
    INTERBREED_PROPORTION = 0.3
    MUTATION_RATE = 0.7
    EPOCHS = 1000

    def __init__(self, capacity):
        self.capacity = capacity
        self.items_weights = np.random.randint(1, 25, self.BACKPACK_SIZE)
        self.items_prices = np.random.randint(2, 30, self.BACKPACK_SIZE)

        self.record = 0
        self.best_set = None

        self.population = np.eye(self.BACKPACK_SIZE)

    def start_evolution(self):
        self.record = np.max(np.apply_along_axis(self.fitness, 1, self.population))
        self.best_set = self.population[np.argmax(np.apply_along_axis(self.fitness, 1, self.population))]

        records = []

        for i in range(self.EPOCHS):
            records.append(self.record)

            if i % 20 == 0:
                self._plot_record_results(i, records)
                self._plot_population()
                plt.show(block=False)

            random_index_1 = np.random.choice(self.population.shape[0], size=1)[0]  # getting two random sets from population
            random_set_1 = self.population[random_index_1, :]

            first_descendant, second_descendant = self._interbreed(self.best_set, random_set_1)

            if np.random.random() < self.MUTATION_RATE:
                self._mutate(first_descendant)
            if np.random.random() < self.MUTATION_RATE:
                self._mutate(second_descendant)

            # TODO local improvement operator

            if self.fit_backpack(first_descendant):  # if descendant fits the backpack, we replace the worst set with it
                sum_prices_for_each_set = np.apply_along_axis(self.fitness, 1, self.population)
                self.population[np.argmin(sum_prices_for_each_set)] = first_descendant

                self.record = max(self.record, self.fitness(first_descendant))

            if self.fit_backpack(second_descendant):  # here the same, as 5 rows above
                sum_prices_for_each_set = np.apply_along_axis(self.fitness, 1, self.population)
                self.population[np.argmin(sum_prices_for_each_set)] = second_descendant

                self.record = max(self.record, self.fitness(second_descendant))

            self.best_set = self.population[np.argmax(np.apply_along_axis(self.fitness, 1, self.population))]

        return self.best_set
    
    def items_set_weight(self, items_set):
        return np.sum(self.items_weights[items_set == 1])

    def fit_backpack(self, items_set) -> bool:
        return self.items_set_weight(items_set) < self.capacity

    def fitness(self, items_set):
        return np.sum(self.items_prices[items_set == 1])

    def _interbreed(self, first_set, second_set):
        interbreed_index = int(self.INTERBREED_PROPORTION * self.BACKPACK_SIZE)
        first_new_set = np.concatenate((first_set[:interbreed_index], second_set[interbreed_index:]))
        second_new_set = np.concatenate((second_set[:interbreed_index], first_set[interbreed_index:]))

        return first_new_set, second_new_set

    def _mutate(self, items_set):
        indexes_with_1 = np.where(items_set == 1)[0]
        indexes_with_0 = np.where(items_set == 0)[0]

        if not len(indexes_with_1):
            items_set[np.random.choice(self.BACKPACK_SIZE)] = 1
        elif not len(indexes_with_0):
            items_set[np.random.choice(self.BACKPACK_SIZE)] = 0
        else:
            rand_idx_1, rand_idx_0 = np.random.choice(indexes_with_1), np.random.choice(indexes_with_0)
            items_set[rand_idx_1], items_set[rand_idx_0] = items_set[rand_idx_0], items_set[rand_idx_1]

    @staticmethod
    def _plot_record_results(iteration, fitness):
        plt.title('Training...')

        _ = plt.figure(1)
        plt.clf()
        plt.title('Training...')
        plt.xlabel('Number of iterations')
        plt.ylabel('Maximum price')
        plt.plot(list(range(iteration + 1)), fitness, label='Record price')
        plt.legend()
        plt.pause(0.00001)

    def _plot_population(self):
        _ = plt.figure(2)
        plt.clf()
        plt.title('Training...')
        plt.xlabel('Individuals')
        plt.ylabel('Prices')
        plt.ylim(50, max(self.record + 100, 600))

        plt.plot(list(range(self.BACKPACK_SIZE)),
                 np.apply_along_axis(self.fitness, 1, self.population),
                 linestyle="",
                 marker="o",
                 markersize=1)

        manager = plt.get_current_fig_manager()
        manager.window.setGeometry(700, 100, 640, 520)

        plt.pause(0.00001)


if __name__ == '__main__':
    backpack = GeneticBackpackFinder(capacity=250)
    bast_set = backpack.start_evolution()
    print(f'Best set price: {backpack.fitness(bast_set)} Best set weight: {backpack.items_set_weight(bast_set)}')

    # avg for cross: random - random = 430
    # avg for cross: best - random = 653
    input()
