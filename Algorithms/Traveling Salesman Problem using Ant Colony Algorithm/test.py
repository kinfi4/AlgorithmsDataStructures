from salesman import Salesman


if __name__ == '__main__':
    salesman = Salesman(alpha=2, beta=4, evaporation=0.6, number_of_cities=100, number_of_ants=45)
    salesman.fit()
