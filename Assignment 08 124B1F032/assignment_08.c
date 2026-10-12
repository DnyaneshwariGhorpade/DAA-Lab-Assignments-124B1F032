
#include <stdio.h>
#include <string.h>

#define MAX 10
#define INF 1000000000
#define MAX_COST 10000

int n, cost[MAX][MAX];
int bestCost = INF, bestPath[MAX + 1];
int path[MAX + 1], visited[MAX];

typedef struct {
    int city;
    int level;
    int costSoFar;
    int bound;
    int path[MAX + 1];
    int visited[MAX];
} Node;

Node pq[100000];
int pqSize = 0;

/* Insert node into priority queue by lower bound */
void push(Node node) {
    int i = pqSize++;
    while (i > 0 && pq[(i - 1) / 2].bound > node.bound) {
        pq[i] = pq[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    pq[i] = node;
}

/* Remove node with smallest bound */
Node pop() {
    Node result = pq[0];
    Node last = pq[--pqSize];
    int i = 0, child;

    while ((child = 2 * i + 1) < pqSize) {
        if (child + 1 < pqSize &&
            pq[child + 1].bound < pq[child].bound)
            child++;

        if (last.bound <= pq[child].bound)
            break;

        pq[i] = pq[child];
        i = child;
    }

    if (pqSize > 0)
        pq[i] = last;

    return result;
}

/* Lower bound using minimum outgoing edges.
   Only cities that still need to depart contribute: the current city and
   every city not yet visited. Cities already departed already have their
   chosen outgoing edge included in costSoFar, so they must be excluded. */
int lowerBound(Node node) {
    int i, j, minEdge, bound = node.costSoFar;

    for (i = 0; i < n; i++) {
        minEdge = INF;

        if (node.visited[i] && i != node.city)
            continue;

        for (j = 0; j < n; j++) {
            if (i != j && cost[i][j] < minEdge)
                minEdge = cost[i][j];
        }

        if (minEdge != INF)
            bound += minEdge;
    }

    return bound;
}

int main() {
    int i, j;

    printf("Enter number of cities (maximum %d): ", MAX);
    scanf("%d", &n);

    if (n < 2 || n > MAX) {
        printf("Invalid number of cities.\n");
        return 0;
    }

    printf("Enter cost matrix (0 means no route, except diagonal):\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (scanf("%d", &cost[i][j]) != 1)
                return 0;

            if (i == j) {
                cost[i][j] = INF;
            } else {
                if (cost[i][j] < 0 || cost[i][j] > MAX_COST) {
                    printf("Invalid cost value.\n");
                    return 0;
                }
                if (cost[i][j] == 0)
                    cost[i][j] = INF;
            }
        }
    }

    Node root;
    memset(&root, 0, sizeof(root));

    root.city = 0;
    root.level = 1;
    root.path[0] = 0;
    root.visited[0] = 1;
    root.bound = lowerBound(root);

    push(root);

    while (pqSize > 0) {
        Node current = pop();

        if (current.bound >= bestCost)
            continue;

        if (current.level == n) {
            if (cost[current.city][0] != INF) {
                int total = current.costSoFar + cost[current.city][0];

                if (total < bestCost) {
                    bestCost = total;

                    for (i = 0; i < n; i++)
                        bestPath[i] = current.path[i];

                    bestPath[n] = 0;
                }
            }
            continue;
        }

        for (j = 0; j < n; j++) {
            if (!current.visited[j] &&
                cost[current.city][j] != INF) {

                Node child = current;
                child.city = j;
                child.level = current.level + 1;
                child.costSoFar =
                    current.costSoFar + cost[current.city][j];

                child.path[current.level] = j;
                child.visited[j] = 1;
                child.bound = lowerBound(child);

                if (child.bound < bestCost)
                    push(child);
            }
        }
    }

    if (bestCost == INF) {
        printf("No complete tour exists.\n");
    } else {
        printf("\nMinimum tour cost: %d\n", bestCost);
        printf("Optimal route: ");

        for (i = 0; i <= n; i++)
            printf("%d ", bestPath[i]);

        printf("\n");
    }

    return 0;
}
