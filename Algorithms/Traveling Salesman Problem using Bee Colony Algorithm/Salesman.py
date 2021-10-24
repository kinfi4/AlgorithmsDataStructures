from random import sample

import numpy as np
import matplotlib.pyplot as plt

plt.ion()


class Salesman:
    def __init__(self, cities_amount=300,
                 work_bees_amount=60,
                 number_of_sectors=50,
                 scouters_amount=15,
                 not_changing_limit=100,
                 epochs=1000,
                 show_plots=True):

        self.cities_amount = cities_amount
        self.work_bees_amount = work_bees_amount
        self.number_of_sectors = number_of_sectors
        self.scouters_amount = scouters_amount
        self.not_changing_limit = not_changing_limit
        self.show_plots = show_plots
        self.epochs = epochs        
        
        self.cities = np.random.randint(5, 151, size=(self.cities_amount, self.cities_amount))
        np.fill_diagonal(self.cities, 0)

        self.population = np.array([self._generate_random_route() for _ in range(self.number_of_sectors)])
        self.route_not_changing = np.array([0] * self.number_of_sectors)

        self.record = np.inf
        self.best_route = None

    def fit(self):
        records = []

        for i in range(self.epochs):
            chosen_areas_indexes = self.scouters_stage()
            self._onlooker_bees_stage(chosen_areas_indexes)

            self._improve_all_areas()
            self._random_search()

            self.best_route = self.population[np.argmax(np.apply_along_axis(self.fitness, 1, self.population))]
            self.record = self.route_length(self.best_route)
            records.append(self.record)

            if self.show_plots and (i % 5 == 0 or i < 3):
                self._plotting_records(i, records)
                self._plotting_population()

        return self.record, self.best_route

    def _improve_all_areas(self):
        for i in range(self.number_of_sectors):
            chosen_route = self.population[i]
            random_neighbor = self._generate_neighbor(chosen_route)

            best_route = max(chosen_route, random_neighbor, key=self.fitness)
            self._set_best_route(i, best_route)

    def _onlooker_bees_stage(self, areas_indexes):
        areas = self.population[areas_indexes]
        probabilities = np.apply_along_axis(self._route_probability, 1, areas, areas)

        for _ in range(self.work_bees_amount):
            chosen_index = np.random.choice(areas_indexes, p=probabilities)
            chosen_route = self.population[chosen_index]
            random_neighbor = self._generate_neighbor(chosen_route, distance=6)

            best_route = max(chosen_route, random_neighbor, key=self.fitness)
            self._set_best_route(chosen_index, best_route)

    def _random_search(self):
        for i in range(self.number_of_sectors):
            if self.route_not_changing[i] > self.not_changing_limit and self.route_length(self.population[i]) != self.record:
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
        random_indexes = sample(range(self.cities_amount), distance)

        for index_of_index in range(len(random_indexes) - 1):
            first_index = random_indexes[index_of_index]
            second_index = random_indexes[index_of_index + 1]
            route_copy[first_index], route_copy[second_index] = route_copy[second_index], route_copy[first_index]

        return route_copy

    def _generate_random_route(self):
        return np.array(sample(range(self.cities_amount), self.cities_amount))

    def _plotting_records(self, iteration, records):
        _ = plt.figure(1)
        plt.clf()
        plt.title('Training...')
        plt.xlabel('Iterations')
        plt.ylabel('Route length')
        plt.plot(list(range(iteration + 1)), records, label='Record')
        plt.legend()

        manager = plt.get_current_fig_manager()
        manager.window.setGeometry(50, 100, 640, 520)

        plt.pause(0.000001)

    def _plotting_population(self):
        _ = plt.figure(2)
        plt.clf()
        plt.title('Training...')
        plt.xlabel('Individuals')
        plt.ylabel('Routes length')
        plt.ylim(10 * self.cities_amount, 100 * self.cities_amount)

        plt.plot(list(range(self.number_of_sectors)),
                 np.apply_along_axis(self.route_length, 1, self.population),
                 linestyle="",
                 marker="o",
                 markersize=4)

        manager = plt.get_current_fig_manager()
        manager.window.setGeometry(700, 100, 640, 520)

        plt.pause(0.000001)

    def _route_probability(self, route, areas):
        return self.fitness(route) / np.sum(np.apply_along_axis(self.fitness, axis=1, arr=areas))

    def fitness(self, route):
        return 1 / self.route_length(route)

    def route_length(self, route):
        """
        Calculates the total price for passed route

        :param route: iterable obj with size of cities_amount, represents the route of salesman
        :return: int - total price for this route
        """
        return np.sum([self.cities[route[i], route[i + 1]] for i in range(-1, self.cities_amount - 1)])

    def scouters_stage(self):
        best_areas_number = (self.scouters_amount * 2) // 3  # we will return first best_areas_number areas and
        random_areas_number = self.scouters_amount - best_areas_number  # random_areas_number random areas

        population_fitness = np.apply_along_axis(self.fitness, axis=1, arr=self.population)
        best_routes_indexes = np.argpartition(population_fitness, -best_areas_number)[-best_areas_number:]

        probabilities = np.array([1] * len(self.population), dtype=np.float)
        probabilities[best_routes_indexes] = 0
        probabilities[probabilities == 1] = 1 / (len(self.population) - best_areas_number)

        population_indexes = list(range(len(self.population)))
        random_routes_indexes = np.random.choice(population_indexes, p=probabilities, size=random_areas_number, replace=False)

        return np.concatenate((best_routes_indexes, random_routes_indexes), axis=None)
