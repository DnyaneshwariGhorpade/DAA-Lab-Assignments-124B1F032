#include <stdio.h>
#include <string.h>

#define MAX_COURSES 20000
#define MAX_EDGES 1000000
#define MAX_ENROLL 20000

int head[MAX_COURSES];
int to[MAX_EDGES];
int nextEdge[MAX_EDGES];
int edgeCount = 0;

int color[MAX_COURSES];
int seen[MAX_COURSES];

void addEdge(int u, int v) {
    to[edgeCount] = v;
    nextEdge[edgeCount] = head[u];
    head[u] = edgeCount++;
}

int main(void) {
    int n, students, i, j, k, u, v, cnt;
    int enroll[MAX_ENROLL];
    int slots = 0;
    int stamp = 0;

    printf("Enter number of courses and students: ");
    if (scanf("%d %d", &n, &students) != 2)
        return 0;

    if (n < 1 || n > MAX_COURSES || students < 0) {
        printf("Invalid input limits.\n");
        return 0;
    }

    for (i = 0; i < n; i++)
        head[i] = -1;

    printf("For each student, enter the number of enrolled courses "
           "followed by the course numbers (1 to %d):\n", n);

    for (i = 0; i < students; i++) {
        if (scanf("%d", &cnt) != 1)
            return 0;

        if (cnt < 0 || cnt > n) {
            printf("Invalid enrolment count.\n");
            return 0;
        }

        for (j = 0; j < cnt; j++) {
            if (scanf("%d", &enroll[j]) != 1)
                return 0;

            if (enroll[j] < 1 || enroll[j] > n) {
                printf("Invalid course number.\n");
                return 0;
            }
            enroll[j]--;
        }

        for (j = 0; j < cnt; j++) {
            for (k = j + 1; k < cnt; k++) {
                if (enroll[j] == enroll[k])
                    continue;

                if (edgeCount + 2 > MAX_EDGES) {
                    printf("Conflict limit exceeded.\n");
                    return 0;
                }

                addEdge(enroll[j], enroll[k]);
                addEdge(enroll[k], enroll[j]);
            }
        }
    }

    for (i = 0; i < n; i++)
        color[i] = -1;
    memset(seen, 0, sizeof(seen));

    for (u = 0; u < n; u++) {
        stamp++;

        for (j = head[u]; j != -1; j = nextEdge[j]) {
            v = to[j];
            if (color[v] != -1)
                seen[color[v]] = stamp;
        }

        k = 0;
        while (seen[k] == stamp)
            k++;

        color[u] = k;

        if (k + 1 > slots)
            slots = k + 1;
    }

    printf("\nExam Timetable:\n");
    printf("Course\tTime Slot\n");

    for (i = 0; i < n; i++)
        printf("C%d\tSlot %d\n", i + 1, color[i] + 1);

    printf("\nTotal exam slots required: %d\n", slots);

    return 0;
}
