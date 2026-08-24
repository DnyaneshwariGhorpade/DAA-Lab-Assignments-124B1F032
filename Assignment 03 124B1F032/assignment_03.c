#include <stdio.h>

#define MAX 100

struct Item
{
    char name[30];
    float weight;
    float value;
    float ratio;
    float taken;
};

struct Item items[MAX];
int n;

/* Sort items by value/weight ratio */
void sortItems()
{
    int i, j;
    struct Item temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (items[j].ratio < items[j + 1].ratio)
            {
                temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}

/* Fill the boat using Greedy method */
float fillBoat(float capacity)
{
    float totalValue = 0;
    float remaining = capacity;

    for (int i = 0; i < n; i++)
    {
        if (remaining == 0)
            break;

        if (items[i].weight <= remaining)
        {
            items[i].taken = items[i].weight;

            totalValue += items[i].value;
            remaining -= items[i].weight;
        }
        else
        {
            /* Take only the required fraction */
            items[i].taken = remaining;

            totalValue += items[i].ratio * remaining;
            remaining = 0;
        }
    }

    return totalValue;
}

int main()
{
    float capacity;
    float totalValue;

    printf("Emergency Relief Boat Loading\n");

    printf("\nEnter boat capacity (kg): ");
    scanf("%f", &capacity);

    printf("Enter number of items: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("\nItem %d\n", i + 1);

        printf("Name: ");
        scanf("%s", items[i].name);

        printf("Weight (kg): ");
        scanf("%f", &items[i].weight);

        printf("Utility Value: ");
        scanf("%f", &items[i].value);

        items[i].ratio =
            items[i].value / items[i].weight;

        items[i].taken = 0;
    }

    /* Sort according to value/weight */
    sortItems();

    /* Load the boat */
    totalValue = fillBoat(capacity);

    printf("\n--- Relief Loading Result ---\n");

    printf("%-15s %-10s %-10s %-10s %-10s\n",
           "Item", "Weight", "Value", "Ratio", "Taken");

    for (int i = 0; i < n; i++)
    {
        printf("%-15s %-10.2f %-10.2f %-10.2f %-10.2f\n",
               items[i].name,
               items[i].weight,
               items[i].value,
               items[i].ratio,
               items[i].taken);
    }

    printf("\nMaximum Boat Capacity: %.2f kg\n", capacity);
    printf("Total Utility Value: %.2f\n", totalValue);

    return 0;
}