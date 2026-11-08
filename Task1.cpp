#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

// 1. Сортировка пузырьком
long long bubbleSort(std::vector<int> arr) {
    long long comparisons = 0;
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
    return comparisons;
}

// 2. Метод вставок с бинарным поиском
long long insertionSort(std::vector<int>& arr) {
    long long comparisons = 0;
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        
        // Поиск места вставки методом половинного деления
        int left = 0;
        int right = i - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            comparisons++;
            if (arr[mid] > key) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        // Сдвиг элементов вручную или через insert/erase
        arr.erase(arr.begin() + i);
        arr.insert(arr.begin() + left, key);
    }
    return comparisons;
}

// 3. Метод Хоара (Быстрая сортировка)
int hoarePartition(std::vector<int>& arr, int low, int high, long long& comparisons) {
    int pivot = arr[low + (high - low) / 2];
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do {
            i++;
            comparisons++;
        } while (arr[i] < pivot);

        do {
            j--;
            comparisons++;
        } while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }
        std::swap(arr[i], arr[j]);
    }
}

void hoareQuickSort(std::vector<int>& arr, int low, int high, long long& comparisons) {
    if (low < high) {
        int p = hoarePartition(arr, low, high, comparisons);
        hoareQuickSort(arr, low, p, comparisons);
        hoareQuickSort(arr, p + 1, high, comparisons);
    }
}

long long hoareSort(std::vector<int>& arr) {
    long long comparisons = 0;
    if (!arr.empty()) {
        hoareQuickSort(arr, 0, arr.size() - 1, comparisons);
    }
    return comparisons;
}

int main() {
    int n = 10000;
    std::vector<int> original_arr(n);

    // Генерация случайных чисел [-100; 100]
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-100, 100);

    for (int i = 0; i < n; ++i) {
        original_arr[i] = dis(gen);
    }

    // Создаем независимые копии для каждого алгоритма
    std::vector<int> arr1 = original_arr;
    std::vector<int> arr2 = original_arr;
    std::vector<int> arr3 = original_arr;

    // Запускаем сортировки на одинаковых исходных данных
    long long comp_bubble = bubbleSort(arr1);
    long long comp_insertion = insertionSort(arr2);
    long long comp_hoare = hoareSort(arr3);

    std::cout << "Results for n = " << n << " (range: -100 to 100):\n";
    std::cout << "1. Bubble sort (ordinary): " << comp_bubble << " comparisons\n";
    std::cout << "2. Insertion sort:        " << comp_insertion << " comparisons\n";
    std::cout << "3. Hoare sort (Quicksort):  " << comp_hoare << " comparisons\n";

    return 0;
}
