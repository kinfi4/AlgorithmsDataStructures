#include <iostream>
#include "BinaryTree.h"


#include "tests/adding_nodes_tests.h"
#include "tests/factory_method_tests.h"
#include "tests/indexator_tests.h"
#include "tests/clearing_tests.h"
#include "tests/removing_tests.h"
#include "tests/index_existing_tests.h"
#include "tests/keys_and_values_tests.h"


using namespace std;

class Worker{
public:
    Worker(string id, string name, string specialization, int years_exp, double salary){
        this->id = id;
        this->name = name;
        this->salary = salary;
        this->specialization = specialization;
        this->years_exp = years_exp;
    }

    Worker(){}

    string id, name, specialization;
    int years_exp;
    double salary;
};

ostream& operator << (ostream& os, const Worker& worker){
    os << worker.id << " " << worker.name << " (" << worker.salary << ")";
    return os;
}

int main() {
//    test_adding_nodes();
//    test_tree_from_vector();
//    test_several_identical_indexes();
//    test_operator_indexator();
//    test_clearing();
//    test_tree_from_vector();
//    test_index_existing();
//    test_removing();
//    test_keys();
//    test_values();

    auto workers = vector<Worker> {
        Worker("1234214", "Lucy", "Whore", 12, 5000.2),
        Worker("1234213", "Tomas", "Backender", 3, 120000.0),
        Worker("1234212", "Andrey", "Fronteder", 5, 140.7),
        Worker("1234211", "Marina", "Fronteder", 1, 1.7),

        Worker("1234216", "Anton", "Boss", 30, 8740.4),
        Worker("1234217", "Sam", "Backender", 9, 900000.0),
        Worker("1234218", "William", "Frontender", 4, 2.9),
        Worker("1234219", "Ilya", "None here, just a crap", 18, 0.0)
    };

    auto tree = BinaryTree<string, Worker>();
    for(auto &worker : workers){
        tree.add(worker.id, worker);
    }

    for(const auto& key : tree.keys()){
        cout << tree[key] << endl;
    }

    cout << endl << endl;

    auto another_tree = BinaryTree<double, Worker>();
    for(auto &worker : workers){
        another_tree.add(worker.salary, worker);
    }

    for(const auto& key : another_tree.keys()){
        cout << another_tree[key] << endl;
    }

    cout << endl << endl;

    double sum = 0;
    auto tree_values = tree.values();
    for(auto &worker : tree_values)
        sum += worker.salary;

    cout << "Average salary = " << sum / tree.size() << endl << endl;


    return 0;
}
