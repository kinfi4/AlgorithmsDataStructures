from random import choice, sample

import numpy as np
import matplotlib.pyplot as plt

np.seterr(divide='ignore')


class Salesman:
    def __init__(self, alpha, beta, evaporation, number_of_cities, number_of_ants, epochs=1000):
        self.alpha = alpha
        self.beta = beta
        self.evaporation = evaporation
        self.number_of_cities = number_of_cities
        self.number_of_ants = number_of_ants
        self.epochs = epochs

        self.cities_distances = np.random.randint(1, 50, size=(number_of_cities, number_of_cities))
        self.cities_distances = (self.cities_distances + self.cities_distances.T) / 2

        self.cities_distances_inverted = 1 / self.cities_distances

        self.pheromone = np.random.random((number_of_cities, number_of_cities))
        self.pheromone = (self.pheromone + self.pheromone.T) / 2

        self.probability_matrix = self._calculate_probability_matrix()
        self.not_visited_nodes = list(range(number_of_cities))

        np.fill_diagonal(self.cities_distances_inverted, 0)
        np.fill_diagonal(self.pheromone, 0)
        np.fill_diagonal(self.cities_distances, np.inf)

        self.best_path, self.record = self._find_greedy_path_length()
        # self.best_path, self.record = self._find_random_path()

    def fit(self):
        record_list = [self.record]

        for iteration_idx in range(self.epochs):
            routes = [self.best_path]

            for _ in range(self.number_of_ants):
                route = []

                start_node = choice(self.not_visited_nodes)
                self.not_visited_nodes.remove(start_node)

                route.append(start_node)

                current_node = start_node
                while self.not_visited_nodes:
                    current_node_index = self._choose_next_node(current_node)
                    current_node = self.not_visited_nodes.pop(current_node_index)
                    route.append(current_node)

                routes.append(route)
                self.not_visited_nodes = list(range(self.number_of_cities))

            paths_lengths = np.apply_along_axis(self.fitness, 1, routes)
            self.best_path = routes[np.argmin(paths_lengths)]
            self.record = self.fitness(self.best_path)
            record_list.append(self.record)

            if iteration_idx % 5 == 0 or iteration_idx < 3:  # plotting
                self._plotting_record(iteration_idx, record_list)
                self._plotting_population(paths_lengths)
                plt.show(block=False)

            self._update_pheromone(routes)
            self.probability_matrix = self._calculate_probability_matrix()

        return self.best_path, self.record, record_list

    def fitness(self, route):
        """
        Calculates the total price for passed route
        :param route: iterable obj with size of CITIES_AMOUNT, represents the route of salesman
        :return: int - total price for this route
        """
        return np.sum([self.cities_distances[route[i], route[i + 1]] for i in range(-1, self.number_of_cities - 1)])

    def _choose_next_node(self, current_node):
        weights = self.probability_matrix[current_node, self.not_visited_nodes]
        probabilities = weights / np.sum(weights)

        if np.isnan(np.sum(probabilities)):
            return int(np.argmax(weights))

        return int(np.random.choice(range(len(weights)), p=probabilities))

    def _update_pheromone(self, routes: list):
        self.pheromone *= (1 - self.evaporation)

        for route in routes:
            pheromone_change = self.record / self.fitness(route)

            for i in range(len(route) - 1):
                from_town, to_town = route[i], route[i + 1]
                self.pheromone[from_town, to_town] += pheromone_change
                self.pheromone[to_town, from_town] = self.pheromone[from_town, to_town]

    def _calculate_probability_matrix(self):
        return self.pheromone**self.alpha * self.cities_distances_inverted**self.beta

    def _find_greedy_path_length(self):
        current_node, path = 0, []
        visited = set()

        for _ in range(self.number_of_cities):
            path.append(current_node)
            distances = list(self.cities_distances[current_node])

            min_dis_idx, min_dis = None, None
            for index, dist in enumerate(distances):
                if index not in visited:
                    if min_dis_idx is None or dist < min_dis:
                        min_dis_idx = index
                        min_dis = dist

            visited.add(current_node)
            current_node = min_dis_idx

        return path, self.fitness(path)

    def _find_random_path(self):
        random_path = sample(range(self.number_of_cities), self.number_of_cities)
        return random_path, self.fitness(random_path)

    def _plotting_record(self, iteration, records):
        _ = plt.figure(1)
        plt.clf()
        plt.xlabel('Iterations')
        plt.ylabel('Route length')
        plt.plot(list(range(iteration + 2)), records, label='Record')

        manager = plt.get_current_fig_manager()
        manager.window.setGeometry(50, 100, 640, 520)

        plt.title('Training...')
        plt.pause(0.000001)

    def _plotting_population(self, paths_lengths):
        _ = plt.figure(2)
        plt.clf()
        plt.xlabel('Ants')
        plt.ylabel('Paths chosen')

        plt.ylim(self.number_of_cities, self.number_of_cities * 20)

        plt.plot(list(range(1, self.number_of_ants + 1)),
                 paths_lengths[1:],
                 linestyle="",
                 marker="o",
                 markersize=2)

        plt.plot(['Best path'], paths_lengths[0], linestyle="", color='red', marker="o", markersize=4)

        manager = plt.get_current_fig_manager()
        manager.window.setGeometry(700, 100, 640, 520)

        plt.title('Training...')
        plt.pause(0.000001)

