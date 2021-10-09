from Salesman import Salesman


if __name__ == '__main__':
    salesman = Salesman(epochs=1000)
    results = salesman.find_optimal_path()
    print(results)

    input('Press any key, to quit the script...')
