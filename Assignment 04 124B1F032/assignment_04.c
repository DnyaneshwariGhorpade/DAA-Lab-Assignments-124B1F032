#include <stdio.h>

#define MAX 100
#define INF 99999

int graph[MAX][MAX];
int distance[MAX];
int visited[MAX];
int parent[MAX];
int n;

/* Find the unvisited node with minimum distance */
int findMinNode()
{
    int min = INF;
    int node = -1;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && distance[i] < min)
        {
            min = distance[i];
            node = i;
        }
    }

    return node;
}

/* Dijkstra's Algorithm */
void dijkstra(int source)
{
    for (int i = 0; i < n; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    distance[source] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int u = findMinNode();

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < n; v++)
        {
            if (graph[u][v] != 0 && !visited[v])
            {
                if (distance[u] + graph[u][v] < distance[v])
                {
                    distance[v] =
                        distance[u] + graph[u][v];

                    parent[v] = u;
                }
            }
        }
    }
}

/* Print shortest path */
void printPath(int node)
{
    if (parent[node] == -1)
    {
        printf("%d", node);
        return;
    }

    printPath(parent[node]);
    printf(" -> %d", node);
}

int main()
{
    int source, destination;
    int edges;
    int u, v, weight;

    printf("Smart City Emergency Route System\n");

    printf("\nEnter number of intersections: ");
    scanf("%d", &n);

    /* Initialize graph */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            graph[i][j] = 0;
        }
    }

    printf("Enter number of roads: ");
    scanf("%d", &edges);

    printf("\nEnter road details:\n");
    printf("Format: source destination travel_time\n");

    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d %d", &u, &v, &weight);

        graph[u][v] = weight;
        graph[v][u] = weight;
    }

    printf("\nEnter ambulance source node: ");
    scanf("%d", &source);

    printf("Enter hospital destination node: ");
    scanf("%d", &destination);

    /* Calculate shortest path */
    dijkstra(source);

    if (distance[destination] == INF)
    {
        printf("\nNo route available to the hospital.\n");
    }
    else
    {
        printf("\nFastest Route:\n");
        printPath(destination);

        printf("\nShortest Travel Time: %d minutes\n",
               distance[destination]);
    }

    return 0;
}