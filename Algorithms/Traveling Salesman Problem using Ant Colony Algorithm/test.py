from salesman import Salesman


if __name__ == '__main__':
    salesman = Salesman(alpha=2, beta=4, evaporation=0.1, number_of_cities=250, number_of_ants=45)
    best_path, record, record_list = salesman.fit()

    print(f'Best path: {best_path}')
    print(f'Record path length: {record}')
    print(record_list)

    with open('file.txt', 'w') as file:
        file.write(str(record_list))

    input()
