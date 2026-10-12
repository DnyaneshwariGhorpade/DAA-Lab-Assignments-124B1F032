
#include <stdio.h>
#include <string.h>

#define MAX 5000
#define INF 1000000000

int head[MAX], to[MAX * 10], nextEdge[MAX * 10];
int weight[MAX * 10], edgeCount = 0;
int stage[MAX], cost[MAX], path[MAX];
int N, E, K;

void addEdge(int u, int v, int w) {
    to[edgeCount] = v;
    weight[edgeCount] = w;
    nextEdge[edgeCount] = head[u];
    head[u] = edgeCount++;
}

void shortestPath(int source, int destination) {
    int i, j, u, v, w;

    for (i = 0; i < N; i++) {
        cost[i] = INF;
        path[i] = -1;
    }

    cost[destination] = 0;

    /* Process stages backward */
    for (int s = K - 1; s >= 0; s--) {
        for (u = 0; u < N; u++) {
            if (stage[u] != s || u == destination)
                continue;

            for (j = head[u]; j != -1; j = nextEdge[j]) {
                v = to[j];
                w = weight[j];

                if (stage[v] == s + 1 && cost[v] != INF &&
                    w + cost[v] < cost[u]) {
                    cost[u] = w + cost[v];
                    path[u] = v;
                }
            }
        }
    }

    if (cost[source] == INF) {
        printf("No valid route exists.\n");
        return;
    }

    printf("Minimum delivery cost: %d\n", cost[source]);
    printf("Optimal route: ");

    u = source;
    while (u != -1) {
        printf("%d ", u);

        if (u == destination)
            break;

        u = path[u];
    }

    printf("\n");
}

int main() {
    int i, u, v, w;
    int source, destination, requests;

    printf("Enter number of cities, routes and stages: ");
    scanf("%d %d %d", &N, &E, &K);

    if (N < 1 || N > MAX || E < 0 || E > MAX * 10 ||
        K < 1 || K > N) {
        printf("Invalid input limits.\n");
        return 0;
    }

    for (i = 0; i < N; i++)
        head[i] = -1;

    printf("Enter stage number for each city (0 to %d):\n", K - 1);
    for (i = 0; i < N; i++) {
        scanf("%d", &stage[i]);

        if (stage[i] < 0 || stage[i] >= K) {
            printf("Invalid stage number.\n");
            return 0;
        }
    }

    printf("Enter routes as: source destination cost\n");
    for (i = 0; i < E; i++) {
        scanf("%d %d %d", &u, &v, &w);

        if (u < 0 || u >= N || v < 0 || v >= N ||
            w < 0 || w >= INF) {
            printf("Invalid route.\n");
            return 0;
        }

        if (stage[v] != stage[u] + 1) {
            printf("Route must connect consecutive stages.\n");
            return 0;
        }

        addEdge(u, v, w);
    }

    printf("Enter number of delivery requests: ");
    scanf("%d", &requests);

    for (i = 0; i < requests; i++) {
        printf("Enter source and destination: ");
        scanf("%d %d", &source, &destination);

        if (source < 0 || source >= N ||
            destination < 0 || destination >= N ||
            stage[source] != 0 || stage[destination] != K - 1) {
            printf("Invalid source or destination.\n");
            continue;
        }

        printf("\nRequest %d:\n", i + 1);
        shortestPath(source, destination);
    }

    return 0;
}
