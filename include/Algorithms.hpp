#pragma once
#include <vector>

namespace algo {
// Sorting
void bubbleSort(std::vector<int>& arr);
void insertionSort(std::vector<int>& arr);
void selectionSort(std::vector<int>& arr);
void quickSort(std::vector<int>& arr, int low, int high);
void mergeSort(std::vector<int>& arr, int left, int right);

// Searching
int linearSearch(const std::vector<int>& arr, int key);
int binarySearch(const std::vector<int>& arr, int key, int low, int high);
}
