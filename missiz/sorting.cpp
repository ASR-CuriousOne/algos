#include <algorithm>
#include <chrono>
#include <climits>
#include <functional>
#include <iostream>
#include <random>
#include <ratio>
#include <stdexcept>
#include <utility>
#include <vector>

#define RUN_SORT_BENCHMARK(SORT_FUNC)                                          \
  std::cout << std::endl;                                                      \
  std::cout << #SORT_FUNC "..." << std::endl;                                  \
  std::cout << "\nFor sorted array: " << std::endl;                            \
  sortBenchmark(SORT_FUNC, initializeSorted, sortedArray, numOfIters);         \
  std::cout << "\nFor reverse sorted array: " << std::endl;                    \
  sortBenchmark(SORT_FUNC, initializeReverseSorted, reverseArray, numOfIters); \
  std::cout << "\nFor random array: " << std::endl;                            \
  sortBenchmark(SORT_FUNC, initializeRandom, randomArray, numOfIters);

void initializeRandom(std::vector<int> &a) {
  static std::random_device randomDevice;
  static std::mt19937 generator(randomDevice());
  std::uniform_int_distribution<> distri(0, INT_MAX);

  int size = a.size();

  for (int i = 0; i < size; i++) {
    a[i] = distri(generator);
  }
}

void initializeSorted(std::vector<int> &a) {
  for (int i = 0; i < a.size(); i++) {
    a[i] = i;
  }
}
void initializeReverseSorted(std::vector<int> &a) {
  int N = a.size();
  for (int i = 0; i < N; i++) {
    a[i] = N - i - 1;
  }
}



void merge(std::vector<int> &a, int l, int m, int r) {
  int n1 = m - l + 1, n2 = r - m;

  std::vector<int> L(n1), R(n2);
  for(int i = 0; i < n1; i++) L[i] = a[l + i];
	for(int j = 0; j < n2; j++) R[j] = a[m + 1 + j];

  int i = 0, j = 0, k = l;

  while (i < n1 && j < n2)
    a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
  while (i < n1)
    a[k++] = L[i++];
  while (j < n2)
    a[k++] = R[j++];
}

void mergeSortRec(std::vector<int> &a, int l, int r) {
  if (l >= r)
    return;

  int m = l + (r - l) / 2;

  mergeSortRec(a, l, m);
  mergeSortRec(a, m + 1, r);
  merge(a, l, m, r);
}
void mergeSort(std::vector<int> &a) { mergeSortRec(a, 0, a.size() - 1); }

bool checkIsSorted(std::vector<int> &a) {

  for (int i = 0; i < a.size() - 1; i++) {
    if (a[i] > a[i + 1]) {
      return false;
    }
  }

  return true;
}

void sortBenchmark(std::function<void(std::vector<int> &)> sortFunction,
                   std::function<void(std::vector<int> &)> initialize,
                   std::vector<int> a, int numOfIters) {
  std::cout << "Warm Up Runs...." << std::endl;
  std::cout << (checkIsSorted(a) ? "Is Sorted\n" : "Not Sorted\n");
  for (int i = 0; i < 5; i++) {
    sortFunction(a);
    if (!checkIsSorted(a))
      throw std::runtime_error("Array not sorted");
    initialize(a);
  }

  std::cout << "Running benchmark....." << std::endl;
  long long duration = 0;
  long long worst = 0;
  for (int i = 0; i < numOfIters; i++) {
    auto startTime = std::chrono::high_resolution_clock::now();
    sortFunction(a);
    auto endTime = std::chrono::high_resolution_clock::now();
    duration += std::chrono::duration_cast<std::chrono::microseconds>(endTime -
                                                                      startTime)
                    .count();
    worst = std::max(
        (long long)std::chrono::duration_cast<std::chrono::microseconds>(
            endTime - startTime)
            .count(),
        worst);
    initialize(a);
  }

  duration = duration / numOfIters;

  std::cout << "Avg time taken: " << duration << " us" << std::endl;
  std::cout << "Worst time taken: " << worst << " us" << std::endl;
}

void printVector(std::vector<int> &a) {
  for (auto i : a) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
}

int main() {
  const int size = 1000;
  const int numOfIters = 100;

  std::vector<int> empty(0, 0);

  std::vector<int> singleElement(1, 10);

  std::vector<int> sortedArray(size, 0);
  initializeSorted(sortedArray);

  std::vector<int> reverseArray(size, 0);
  std::reverse_copy(sortedArray.begin(), sortedArray.end(),
                    reverseArray.begin());

  std::vector<int> randomArray(size, 0);
  initializeRandom(randomArray);

  RUN_SORT_BENCHMARK(mergeSort);
}
