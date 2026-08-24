#include <stdio.h>

#define MAX_ROWS 1000

void merge(float arr[], float temp[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = temp[i];
}

void mergeSort(float arr[], float temp[], int left, int right)
{
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    mergeSort(arr, temp, left, mid);
    mergeSort(arr, temp, mid + 1, right);

    merge(arr, temp, left, mid, right);
}

int main()
{
    FILE *fp = fopen("customer_churn_data.csv", "r");

    if (fp == NULL)
    {
        printf("Cannot open file.\n");
        return 1;
    }

    char line[500];

    // Skip header
    fgets(line, sizeof(line), fp);

    float values[MAX_ROWS];
    float temp[MAX_ROWS];

    int count = 0;

    char customerID[50];
    char gender[20];

    int age;
    int tenure;
    float balance;
    int numProducts;
    int hasCard;
    int activeMember;
    float salary;
    int exited;

    while (fscanf(fp,
                  "%49[^,],%d,%19[^,],%d,%f,%d,%d,%d,%f,%d",
                  customerID,
                  &age,
                  gender,
                  &tenure,
                  &balance,
                  &numProducts,
                  &hasCard,
                  &activeMember,
                  &salary,
                  &exited) == 10)
    {
        values[count] = salary;
        count++;

        if (count >= MAX_ROWS)
            break;
    }

    fclose(fp);

    // Apply Merge Sort
    mergeSort(values, temp, 0, count - 1);

    printf("\nSorted Customer Salaries:\n");

    for (int i = 0; i < count; i++)
        printf("%.2f\n", values[i]);

    return 0;
}