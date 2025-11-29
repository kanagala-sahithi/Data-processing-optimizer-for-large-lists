#include <stdio.h>
#include <stdlib.h>

long long quick_comps = 0;
long long merge_comps = 0;
long long insertion_comps = 0;
long long selection_comps = 0;
long long heap_comps = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low + 1;
    for (int j = low + 1; j <= high; j++) {
        quick_comps++;
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[low], &arr[i - 1]);
    return i - 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int x = 0; x < n1; x++)
        L[x] = arr[l + x];
    for (int y = 0; y < n2; y++)
        R[y] = arr[m + 1 + y];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        merge_comps++;
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            insertion_comps++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            } else
                break;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            selection_comps++;
            if (arr[j] < arr[min_index])
                min_index = j;
        }
        swap(&arr[min_index], &arr[i]);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        heap_comps++;
        if (arr[left] > arr[largest]) largest = left;
    }
    if (right < n) {
        heap_comps++;
        if (arr[right] > arr[largest]) largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void copyArray(int *src, int *dest, int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    int *original = (int *)malloc(n * sizeof(int));
    int *temp = (int *)malloc(n * sizeof(int));
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &original[i]);

    quick_comps = merge_comps = insertion_comps = selection_comps = heap_comps = 0;

    printf("\nSorting Comparison Results:\n");

    copyArray(original, temp, n);
    quickSort(temp, 0, n - 1);
    printf("Quick Sort      : %lld comparisons\n", quick_comps);

    copyArray(original, temp, n);
    mergeSort(temp, 0, n - 1);
    printf("Merge Sort      : %lld comparisons\n", merge_comps);

    copyArray(original, temp, n);
    insertionSort(temp, n);
    printf("Insertion Sort  : %lld comparisons\n", insertion_comps);

    copyArray(original, temp, n);
    selectionSort(temp, n);
    printf("Selection Sort  : %lld comparisons\n", selection_comps);

    copyArray(original, temp, n);
    heapSort(temp, n);
    printf("Heap Sort       : %lld comparisons\n", heap_comps);

    long long counts[5] = {quick_comps, merge_comps, insertion_comps, selection_comps, heap_comps};
    char *names[5] = {"Quick Sort", "Merge Sort", "Insertion Sort", "Selection Sort", "Heap Sort"};
    long long best = counts[0];
    int bestIndex = 0;
    for (int i = 1; i < 5; i++) {
        if (counts[i] < best) {
            best = counts[i];
            bestIndex = i;
        }
    }
    printf("\nBest Sorting Algorithm : %s\n", names[bestIndex]);
    free(original);
    free(temp);
    return 0;
}

