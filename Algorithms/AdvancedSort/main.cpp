#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;


//////////////////// QUICK SORT ////////////////////
int partition(vector<int> &arr, int start, int end) {
    int middle_index = start + (end - start) / 2;
    int middle_value = arr[middle_index];

    while(start <= end) {
        while(arr[start] < middle_value)
            start ++;

        while(arr[end] > middle_value)
            end--;

        if(start <= end) {
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;

            start++;
            end--;
        }
    }

    return start;
}

void quicksort_inner(vector<int> &arr, int left, int right) {
    if(left < right) {
        int new_index = partition(arr, left, right);
        quicksort_inner(arr, left, new_index - 1);
        quicksort_inner(arr, new_index, right);
    }
}

void quick_sort(vector<int> &arr){
    quicksort_inner(arr, 0, int(arr.size() - 1));
}
//////////////////// END QUICK SORT ////////////////////

//////////////////// HEAP SORT ////////////////////
void heapify(vector<int> &arr, int n, int root){
    int largest_index = root;
    int l = 2*root + 1;
    int r = 2*root + 2;

    if(l < n and arr[l] > arr[root])
        largest_index = l;

    if(r < n and arr[r] > arr[root])
        largest_index = r;

    if (largest_index != root){
        swap(arr[root], arr[largest_index]);
        heapify(arr, n, largest_index);
    }
}

void heapSort(vector<int> &arr){
    for (int i = arr.size() / 2 - 1; i >= 0; i--)
        heapify(arr, arr.size(), i);

    for (int i = arr.size() - 1; i >= 0; i--){
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
//////////////////// END HEAP SORT ////////////////////j


///////////////////////////////// MERGE SORT /////////////////////////////////

void merge(vector<int> &arr, int l, int m, int r) {
    const int n1 = m - l + 1;
    const int n2 = r - m;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];


    int i = 0, j = 0;
    while (i < n1 and j < n2) {
        if (L[i] <= R[j]) {
            arr[l] = L[i];
            i++;
        }
        else {
            arr[l] = R[j];
            j++;
        }
        l++;
    }

    while (i < n1) {
        arr[l] = L[i];
        i++;
        l++;
    }
    while (j < n2) {
        arr[l] = R[j];
        j++;
        l++;
    }
}

void mergeSort_inner(vector<int> &arr, int l, int r){
    if(l >= r) {
        return;
    }

    int m = l + (r - l) / 2;

    mergeSort_inner(arr, l, m);
    mergeSort_inner(arr,m + 1, r);
    merge(arr, l, m, r);
}

void merge_sort(vector<int>& arr){
    mergeSort_inner(arr, 0, arr.size() - 1);
}

///////////////////////////////// END MERGE SORT /////////////////////////////////

///////////////////////////////// REDIX SORT /////////////////////////////////
int getMax(vector<int> &arr){
    int mx = arr[0];
    for (int i = 1; i < arr.size(); i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSort(vector<int>&arr, int n, int exp){
    int output[n]; // output array
    int i, count[10] = { 0 };

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixsort(vector<int> &arr){
    int m = getMax(arr);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, arr.size(), exp);
}
///////////////////////////////// END REDIX SORT /////////////////////////////////


///////////////////////////////// UTILS /////////////////////////////////
void stl_sort(vector<int> &arr){
    sort(arr.begin(), arr.end());
}

void print_array(vector<int> &arr){
    for(int i : arr){
        cout << i << ' ';
    }
    cout << endl;
}

bool is_sorted(vector<int> arr){
    for (int i = 0; i < arr.size() - 1; ++i) {
        if(arr[i] > arr[i + 1])
            return false;
    }

    return true;
}

auto test_sorting_speed(void (*algorithm)(vector<int>&), int array_size, bool verbose=true) {
    vector<int> arr = vector<int>();
    for (int i = 0; i < array_size; ++i) {
        arr.push_back(rand() % 500 + 1);
    }

    auto start_time = clock();
    algorithm(arr);
    auto end_time = clock();

    if(not is_sorted(arr))
        cout << "ERROR ARRAY IS NOT SORTED!!" << endl;

    if (verbose) {
        cout << "Array is sorted: " << is_sorted(arr) << " with size: " << arr.size() << endl;
        cout << "It took: " << (end_time - start_time) / 1000 << "ms" << endl;
    }

    return (end_time - start_time) / 1000;
}


int main() {
    srand(time(0));


    vector<double> times_1300;
    vector<double> times_13000;
    vector<double> times_130000;

    cout << "Start heap sorting" << endl;
    times_1300.push_back(test_sorting_speed(heapSort, 1300, false));
    times_13000.push_back(test_sorting_speed(heapSort, 13000, false));
    times_130000.push_back(test_sorting_speed(heapSort, 130000, false));
    cout << "End heap sorting" << endl;

    cout << "Start quick sorting" << endl;
    times_1300.push_back(test_sorting_speed(quick_sort, 1300, false));
    times_13000.push_back(test_sorting_speed(quick_sort, 13000, false));
    times_130000.push_back(test_sorting_speed(quick_sort, 130000, false));
    cout << "End quick sorting" << endl;

    cout << "Start merge sorting" << endl;
    times_1300.push_back(test_sorting_speed(merge_sort, 1300, false));
    times_13000.push_back(test_sorting_speed(merge_sort, 13000, false));
    times_130000.push_back(test_sorting_speed(merge_sort, 130000, false));
    cout << "End merge sorting" << endl;

    cout << "Start stl sorting" << endl;
    times_1300.push_back(test_sorting_speed(stl_sort, 1300, false));
    times_13000.push_back(test_sorting_speed(stl_sort, 13000, false));
    times_130000.push_back(test_sorting_speed(stl_sort, 130000, false));
    cout << "End stl sorting" << endl;

    cout << "Start Radix sorting" << endl;
    times_1300.push_back(test_sorting_speed(radixsort, 1300, false));
    times_13000.push_back(test_sorting_speed(radixsort, 13000, false));
    times_130000.push_back(test_sorting_speed(radixsort, 130000, false));
    cout << "End Radix sorting" << endl << endl << endl;



    cout << "Heap sorting:  " << times_1300[0] << "ms  " << times_13000[0] << "ms  " << times_130000[0] << "ms" << endl;
    cout << "Quick sorting: " << times_1300[1] << "ms  " << times_13000[1] << "ms  " << times_130000[1] << "ms" << endl;
    cout << "Merge sorting: " << times_1300[2] << "ms  " << times_13000[2] << "ms  " << times_130000[2] << "ms" << endl;
    cout << "STL sorting:   " << times_1300[3] << "ms  " << times_13000[3] << "ms  " << times_130000[3] << "ms" << endl;
    cout << "Radix sorting: " << times_1300[4] << "ms  " << times_13000[4] << "ms  " << times_130000[4] << "ms" << endl;




    return 0;
}











//int partition(vector<int> &arr, int left, int right) {
//    int pivotIndex = left + (right - left) / 2;
//    int pivotValue = arr[pivotIndex];
//
//    while(left <= right) {
//        while(arr[left] < pivotValue)
//            left++;
//
//        while(arr[right] > pivotValue)
//            right--;
//
//        if(left <= right) {
//            int temp = arr[left];
//            arr[left] = arr[right];
//            arr[right] = temp;
//            left++;
//            right--;
//        }
//    }
//    return left;
//}

//void quick_sort(vector<int> &arr, int start, int end){
//    if(start < end){
//        int pivotIndex = partition(arr, start, end);
//        quick_sort(arr, start, pivotIndex - 1);
//        quick_sort(arr, pivotIndex, end);
//    }
//}
