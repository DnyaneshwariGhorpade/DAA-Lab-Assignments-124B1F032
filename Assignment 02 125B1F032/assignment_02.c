#include <stdio.h>

#define MAX_MOVIES 100000
#define NAME_LEN 100

struct Movie
{
    int id;
    char title[NAME_LEN];
    int year;
    float rating;
    int watch_time;
};

struct Movie movies[MAX_MOVIES];
int count = 0;

/* Swap two movies */
void swap(struct Movie *a, struct Movie *b)
{
    struct Movie temp = *a;
    *a = *b;
    *b = temp;
}

/* Compare movies according to selected parameter */
int compare(struct Movie a, struct Movie b, int choice)
{
    if (choice == 1)
        return a.rating > b.rating;

    if (choice == 2)
        return a.year > b.year;

    if (choice == 3)
        return a.watch_time > b.watch_time;

    return 0;
}

/* Partition */
int partition(int low, int high, int choice)
{
    struct Movie pivot = movies[high];

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (compare(movies[j], pivot, choice))
        {
            i++;
            swap(&movies[i], &movies[j]);
        }
    }

    swap(&movies[i + 1], &movies[high]);

    return i + 1;
}

/* Quick Sort */
void quickSort(int low, int high, int choice)
{
    if (low < high)
    {
        int p = partition(low, high, choice);

        quickSort(low, p - 1, choice);
        quickSort(p + 1, high, choice);
    }
}

/* Read dataset */
void readFile(char filename[])
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    char line[300];

    /* Skip header */
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp) != NULL &&
           count < MAX_MOVIES)
    {
        sscanf(line,
               "%99[^,],%d,%f,%d",
               movies[count].title,
               &movies[count].year,
               &movies[count].rating,
               &movies[count].watch_time);

        movies[count].id = count + 1;

        count++;
    }

    fclose(fp);
}

/* Display movies */
void display(int n)
{
    if (n > count)
        n = count;

    printf("\nID\tTitle\t\t\tYear\tRating\tWatch Time\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%-25s\t%d\t%.1f\t%d\n",
               movies[i].id,
               movies[i].title,
               movies[i].year,
               movies[i].rating,
               movies[i].watch_time);
    }
}

int main()
{
    char filename[100];
    int choice;
    int n;

    printf("StreamFlix Movie Recommendation System\n");

    printf("\nEnter CSV filename: ");
    scanf("%99s", filename);

    readFile(filename);

    if (count == 0)
    {
        printf("No movies found.\n");
        return 0;
    }

    printf("\n%d movies loaded successfully.\n", count);

    printf("\nSort Movies By:\n");
    printf("1. IMDb Rating\n");
    printf("2. Release Year\n");
    printf("3. Watch Time\n");

    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 3)
    {
        printf("Invalid choice.\n");
        return 0;
    }

    /* Apply Quick Sort */
    quickSort(0, count - 1, choice);

    printf("\nHow many movies do you want to display? ");
    scanf("%d", &n);

    printf("\nSorted Movie Recommendations:\n");

    display(n);

    return 0;
}