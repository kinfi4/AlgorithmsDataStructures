from random import sample, choices

import numpy as np
import matplotlib.pyplot as plt

plt.ion()


class Salesman:
    CITIES_AMOUNT = 300
    WORK_BEES_AMOUNT = 60
    SCOUTERS_AMOUNT = 15
    NOT_CHANGING_LIMIT = 50
    EPOCHS = 100

    def __init__(self):
        self.cities = np.random.randint(5, 151, size=(self.CITIES_AMOUNT, self.CITIES_AMOUNT))
        np.fill_diagonal(self.cities, 0)

        self.population = np.array([self._generate_random_route() for _ in range(self.SCOUTERS_AMOUNT)])  # generating 100 initial random routes
        self.route_not_changing = np.array([0] * self.SCOUTERS_AMOUNT)

        self.record = np.inf
        self.best_route = None

    def find_optimal_path(self):
        records = []

        for i in range(self.EPOCHS):
            self._improve_all_areas()
            self._onlooker_bees_stage()
            self._scouter_bees_step()
            self.best_route = self.population[np.argmin(np.apply_along_axis(self.fitness, 1, self.population))]
            self.record = self.fitness(self.best_route)

            records.append(self.record)

            # if i % 2 == 0:
            #     self._plotting_records(i, records)
            #     self._plotting_population()

        return self.record, self.best_route

    def _improve_all_areas(self):
        for i in range(self.SCOUTERS_AMOUNT):
            chosen_route = self.population[i]
            random_neighbor = self._generate_neighbor(chosen_route)

            best_route = min(chosen_route, random_neighbor, key=self.fitness)
            self._set_best_route(i, best_route)

    def _onlooker_bees_stage(self):
        for _ in range(self.WORK_BEES_AMOUNT):
            probabilities = [self._route_probability(route) for route in self.population]
            chosen_index = choices(range(len(self.population)), probabilities)[0]
            chosen_route = self.population[chosen_index]
            random_neighbor = self._generate_neighbor(chosen_route)

            best_route = min(chosen_route, random_neighbor, key=self.fitness)
            self._set_best_route(chosen_index, best_route)

    def _scouter_bees_step(self):
        for i in range(self.SCOUTERS_AMOUNT):
            if self.route_not_changing[i] > self.NOT_CHANGING_LIMIT and self.fitness(self.population[i]) != self.record:
                self.population[i] = self._generate_random_route()
                self.route_not_changing[i] = 0

    def _set_best_route(self, old_route_index, new_best_route):
        old_route = self.population[old_route_index]

        if np.array_equal(old_route, new_best_route):
            self.route_not_changing[old_route_index] += 1
        else:
            self.population[old_route_index] = new_best_route
            self.route_not_changing[old_route_index] = 0

    def _generate_neighbor(self, route, distance=6):
        route_copy = route.copy()
        random_indexes = sample(range(self.CITIES_AMOUNT), distance)

        for index_of_index in range(len(random_indexes) - 1):
            first_index = random_indexes[index_of_index]
            second_index = random_indexes[index_of_index + 1]
            route_copy[first_index], route_copy[second_index] = route_copy[second_index], route_copy[first_index]

        return route_copy

    def _generate_random_route(self):
        return np.array(sample(range(self.CITIES_AMOUNT), self.CITIES_AMOUNT))

    def _plotting_records(self, iteration, records):
        _ = plt.figure(1)
        plt.clf()
        plt.title('Training...')
        plt.xlabel('Iterations')
        plt.ylabel('Route length')
        plt.plot(list(range(iteration + 1)), records, label='Record')
        plt.legend()
        plt.pause(0.000001)

    def _plotting_population(self):
        _ = plt.figure(2)
        plt.clf()
        plt.title('Training...')
        plt.xlabel('Individuals')
        plt.ylabel('Routes length')
        plt.ylim(5 * self.CITIES_AMOUNT, 150 * self.CITIES_AMOUNT)

        plt.plot(list(range(self.SCOUTERS_AMOUNT)),
                 np.apply_along_axis(self.fitness, 1, self.population),
                 linestyle="",
                 marker="o",
                 markersize=4)

        manager = plt.get_current_fig_manager()
        manager.window.setGeometry(700, 100, 640, 520)

        plt.pause(0.000001)

    def _route_probability(self, route):
        return self.fitness(route) / np.sum([self.fitness(route) for route in self.population])

    def fitness(self, route):
        """
        Calculates the total price for passed route

        :param route: iterable obj with size of CITIES_AMOUNT, represents the route of salesman
        :return: int - total price for this route
        """
        return np.sum([self.cities[route[i], route[i + 1]] for i in range(-1, self.CITIES_AMOUNT - 1)])


if __name__ == '__main__':
    salesman = Salesman()
    results = salesman.find_optimal_path()
    print(results)

    input('Press any key, to quit the script...')
