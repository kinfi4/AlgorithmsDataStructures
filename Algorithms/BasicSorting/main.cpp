#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int find_minimum_index(vector<int> numbers, int start = 0) {
    int m = numbers[start];
    int min_index = start;
    for (int i = start; i < numbers.size(); ++i) {
        if (m > numbers[i]) {
            m = numbers[i];
            min_index = i;
        }
    }

    return min_index;
}


vector<int> bubble_sort(vector<int> arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        for (int j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return arr;
}

vector<int> select_sort(vector<int> arr) {
    for (int i = 0; i < arr.size(); ++i) {
        int min_index = find_minimum_index(arr, i);
        int temp = arr[i];

        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }

    return arr;
}

vector<int> insertion_sort(vector<int> arr) {
    for (int i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 and arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }

    return arr;
}

vector<int> shakerSort(vector<int> arr) {
    int k = arr.size() - 1;
    int lower_b = 1, upper_b = arr.size() - 1;

    do {
        for (int j = upper_b; j > 0; j--) {
            if (arr[j - 1] > arr[j]) {
                int temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;

                k = j;
            }
        }
        lower_b = k + 1;

        for (int j = lower_b; j <= upper_b; j++) {
            if (arr[j - 1] > arr[j]) {
                int temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;

                k = j;
            }
        }
        upper_b = k - 1;

    } while (lower_b < upper_b);

    return arr;
}


auto test_sorting_speed(vector<int> (*algorithm)(vector<int>), int array_size=100, bool verbose=true) {
    vector<int> arr = vector<int>();
    for (int i = 0; i < array_size; ++i) {
        arr.push_back(rand() % 259 + 1);
    }

    auto start_time = clock();
    arr = algorithm(arr);

    if (verbose) {
        for (auto i : arr) {
            cout << i << ' ';
        }
        cout << endl;
        cout << "It took: " << clock() - start_time << " ms" << endl;
    }

    return clock() - start_time;
}

void shakerTask(){
    vector<int> randomArray = vector<int>();
    for (int i = 0; i < 10; ++i) {
        randomArray.push_back(rand() % 261 + 1);
    }

    for(auto i : randomArray){
        cout << i << " ";
    }
    cout << "\nSorting" << endl;
    randomArray = shakerSort(randomArray);

    for(auto i : randomArray){
        cout << i << " ";
    }
    cout << endl << endl << endl;

}

int main() {
//    srand((unsigned) time(0));
//
//    shakerTask();


    vector<double> times_1420 = vector<double>();
    vector<double> times_14300 = vector<double>();
    vector<double> times_130000 = vector<double>();

    // sorting time results for 1420
    times_1420.push_back(test_sorting_speed(insertion_sort, 110, false));
    times_1420.push_back(test_sorting_speed(select_sort, 110, false));
    times_1420.push_back(test_sorting_speed(bubble_sort, 110, false));
    times_1420.push_back(test_sorting_speed(shakerSort, 110, false));

    // sorting time results for 14300
    times_14300.push_back(test_sorting_speed(insertion_sort, 14300, false));
    times_14300.push_back(test_sorting_speed(select_sort, 14300, false));
    times_14300.push_back(test_sorting_speed(bubble_sort, 14300, false));
    times_14300.push_back(test_sorting_speed(shakerSort, 14300, false));
//
//    // sorting time results for 130000
    times_130000.push_back(test_sorting_speed(insertion_sort, 130000, false));
    times_130000.push_back(test_sorting_speed(select_sort, 130000, false));
    times_130000.push_back(test_sorting_speed(bubble_sort, 130000, false));
    times_130000.push_back(test_sorting_speed(shakerSort, 130000, false));

    cout << "Insertion sort " << times_1420[0] /CLOCKS_PER_SEC << "s     " << times_14300[0] / CLOCKS_PER_SEC << "s     " << times_130000[0] / CLOCKS_PER_SEC<< "s" << endl;
    cout << "Select sort    " << times_1420[1] /CLOCKS_PER_SEC<< "s     " << times_14300[1] / CLOCKS_PER_SEC << "s     " << times_130000[1] / CLOCKS_PER_SEC<< "s" << endl;
    cout << "Bubble sort    " << times_1420[2] /CLOCKS_PER_SEC<< "s     " << times_14300[2] / CLOCKS_PER_SEC << "s     " << times_130000[2] / CLOCKS_PER_SEC<< "s" << endl;
    cout << "Shaker sort    " << times_1420[3] /CLOCKS_PER_SEC<< "s     " << times_14300[3] / CLOCKS_PER_SEC << "s     " << times_130000[3] / CLOCKS_PER_SEC<< "s" << endl;



//    cout << "Insertion sort " << times_1420[0] / CLOCKS_PER_SEC * 1000<< "ms     " << times_14300[0] / CLOCKS_PER_SEC * 1000<< "ms     " << endl;
//    cout << "Select sort    " << times_1420[1] / CLOCKS_PER_SEC * 1000<< "ms     " << times_14300[1] / CLOCKS_PER_SEC * 1000<< "ms     " << endl;
//    cout << "Bubble sort    " << times_1420[2] / CLOCKS_PER_SEC * 1000<< "ms     " << times_14300[2] / CLOCKS_PER_SEC * 1000<< "ms     " << endl;
//    cout << "Shaker sort    " << times_1420[3] / CLOCKS_PER_SEC * 1000<< "ms     " << times_14300[3] / CLOCKS_PER_SEC * 1000 << "ms     " << endl;

    return 0;
}
