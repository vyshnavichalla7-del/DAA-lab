#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int a[MAX], n;

/* Display Array */
void display()
{
    int i;

    printf("\nArray: ");

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

/* Linear Search */
void linearSearch()
{
    int key, i, found = 0;

    printf("Enter element to search: ");
    scanf("%d", &key);

    for (i = 0; i < n; i++)
    {
        if (a[i] == key)
        {
            printf("Element found at position %d\n", i + 1);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Element not found\n");
}

/* Binary Search */
void binarySearch()
{
    int key, low = 0, high = n - 1, mid;

    printf("Enter element to search: ");
    scanf("%d", &key);

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (a[mid] == key)
        {
            printf("Element found at position %d\n", mid + 1);
            return;
        }
        else if (key < a[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    printf("Element not found\n");
}

/* Bubble Sort */
void bubbleSort()
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    printf("Bubble Sort completed.\n");
}

/* Selection Sort */
void selectionSort()
{
    int i, j, min, temp;

    for (i = 0; i < n - 1; i++)
    {
        min = i;

        for (j = i + 1; j < n; j++)
        {
            if (a[j] < a[min])
                min = j;
        }

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }

    printf("Selection Sort completed.\n");
}

/* Insertion Sort */
void insertionSort()
{
    int i, j, key;

    for (i = 1; i < n; i++)
    {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }

    printf("Insertion Sort completed.\n");
}

/* Merge */
void merge(int low, int mid, int high)
{
    int temp[MAX];
    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high)
    {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= high)
        temp[k++] = a[j++];

    for (i = low; i <= high; i++)
        a[i] = temp[i];
}

/* Merge Sort */
void mergeSort(int low, int high)
{
    int mid;

    if (low < high)
    {
        mid = (low + high) / 2;

        mergeSort(low, mid);
        mergeSort(mid + 1, high);

        merge(low, mid, high);
    }
}

/* Partition for Quick Sort */
int partition(int low, int high)
{
    int pivot = a[high];
    int i = low - 1;
    int j, temp;

    for (j = low; j < high; j++)
    {
        if (a[j] < pivot)
        {
            i++;

            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;

    return i + 1;
}

/* Quick Sort */
void quickSort(int low, int high)
{
    int p;

    if (low < high)
    {
        p = partition(low, high);

        quickSort(low, p - 1);
        quickSort(p + 1, high);
    }
}

/* Heapify */
void heapify(int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int temp;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i)
    {
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        heapify(n, largest);
    }
}

/* Heap Sort */
void heapSort()
{
    int i, temp;

    /* Build max heap */
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(n, i);

    /* Extract elements */
    for (i = n - 1; i > 0; i--)
    {
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(i, 0);
    }

    printf("Heap Sort completed.\n");
}

/* Main */
int main()
{
    int choice;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    while (1)
    {
        printf("\n\n========== SEARCHING & SORTING ==========\n");

        printf("1. Display Array\n");

        printf("\n--- Searching ---\n");
        printf("2. Linear Search\n");
        printf("3. Binary Search\n");

        printf("\n--- Sorting ---\n");
        printf("4. Bubble Sort\n");
        printf("5. Selection Sort\n");
        printf("6. Insertion Sort\n");
        printf("7. Merge Sort\n");
        printf("8. Quick Sort\n");
        printf("9. Heap Sort\n");

        printf("\n10. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                display();
                break;

            case 2:
                linearSearch();
                break;

            case 3:
                /* Binary search requires sorted array */
                insertionSort();
                printf("Array sorted for Binary Search.\n");
                display();
                binarySearch();
                break;

            case 4:
                bubbleSort();
                display();
                break;

            case 5:
                selectionSort();
                display();
                break;

            case 6:
                insertionSort();
                display();
                break;

            case 7:
                mergeSort(0, n - 1);
                printf("Merge Sort completed.\n");
                display();
                break;

            case 8:
                quickSort(0, n - 1);
                printf("Quick Sort completed.\n");
                display();
                break;

            case 9:
                heapSort();
                display();
                break;

            case 10:
                printf("Program ended.\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}