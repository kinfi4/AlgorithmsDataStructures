import numpy as np
import matplotlib.pyplot as plt


class GeneticBackpackFinder:
    BACKPACK_SIZE = 100
    INTERBREED_PROPORTION = 0.3
    MUTATION_RATE = 0.7
    EPOCHS = 2000

    def __init__(self, capacity):
        self.capacity = capacity
        self.items_weights = np.random.randint(1, 25, self.BACKPACK_SIZE)
        self.items_prices = np.random.randint(2, 30, self.BACKPACK_SIZE)

        self.record = 0
        self.best_set = None

        self.population = np.eye(self.BACKPACK_SIZE)

    def start_evolution(self):
        self.record = np.max(np.apply_along_axis(self._fitness, 1, self.population))
        self.best_set = self.population[np.argmax(np.apply_along_axis(self._fitness, 1, self.population))]

        records = []

        for i in range(self.EPOCHS):
            records.append(self.record)

            if i % 20 == 0:
                self._plot_results(i, records)
                print(f'Price for best set: {self.record}')

            random_index_1, random_index_2 = np.random.choice(self.population.shape[0], size=2)  # getting two random sets from population
            random_set_1, random_set_2 = self.population[random_index_1, :], self.population[random_index_2, :]

            first_descendant, second_descendant = self._interbreed(random_set_1, random_set_2)

            if np.random.random() < self.MUTATION_RATE:
                self._mutate(first_descendant)
            if np.random.random() < self.MUTATION_RATE:
                self._mutate(second_descendant)

            if self.fit_backpack(first_descendant):  # if descendant fits the backpack, we replace the worst set with it
                sum_prices_for_each_set = np.apply_along_axis(self._fitness, 1, self.population)
                self.population[np.argmin(sum_prices_for_each_set)] = first_descendant

                self.record = max(self.record, self._fitness(first_descendant))

            if self.fit_backpack(second_descendant):  # here the same, as 5 rows above
                sum_prices_for_each_set = np.apply_along_axis(self._fitness, 1, self.population)
                self.population[np.argmin(sum_prices_for_each_set)] = second_descendant

                self.record = max(self.record, self._fitness(second_descendant))

        return self.best_set

    def fit_backpack(self, items_set) -> bool:
        boolean_indexes = list(map(bool, items_set))
        return np.sum(self.items_weights[boolean_indexes]) < self.capacity

    def _fitness(self, items_set):
        boolean_indexes = list(map(bool, items_set))
        return np.sum(self.items_prices[boolean_indexes])

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
    def _plot_results(iteration, fitness):
        plt.clf()
        plt.title('Training...')
        plt.xlabel('Number of iterations')
        plt.ylabel('Maximum price')
        plt.plot(list(range(iteration + 1)), fitness, label='Record price')
        plt.ylim(ymin=0)

        plt.legend()
        plt.show(block=False)
        plt.pause(0.0001)


if __name__ == '__main__':
    backpack = GeneticBackpackFinder(capacity=250)
    bast_set = backpack.start_evolution()
    print(bast_set)
    input()
