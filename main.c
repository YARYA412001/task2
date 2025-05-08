#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CYLINDERS 5000


int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// FCFS: First Come First Serve
void fcfs(int requests[], int n, int head) {
    int total_movement = 0;
    int current = head;

    printf("Servicing order: %d", head);
    for (int i = 0; i < n; i++) {
        total_movement += abs(requests[i] - current);
        current = requests[i];
        printf(" -> %d", requests[i]);
    }

    printf("\nTotal seek time (FCFS): %d\n", total_movement);
}

// SCAN: Elevator algorithm
void scan(int requests[], int n, int head, int direction) {
    int total_movement = 0;
    int current = head;

    int *sorted = (int *)malloc(n * sizeof(int));
    memcpy(sorted, requests, n * sizeof(int));
    qsort(sorted, n, sizeof(int), compare);

    printf("Servicing order: %d", head);

    if (direction == 1) { // Inward: from low to high
        int i = 0;
        while (i < n && sorted[i] < head) i++;
        for (int j = i; j < n; j++) {
            total_movement += abs(sorted[j] - current);
            current = sorted[j];
            printf(" -> %d", sorted[j]);
        }
        if (i > 0) {
            total_movement += abs((CYLINDERS - 1) - current);
            current = CYLINDERS - 1;
            for (int j = i - 1; j >= 0; j--) {
                total_movement += abs(sorted[j] - current);
                current = sorted[j];
                printf(" -> %d", sorted[j]);
            }
        }
    } else { // Outward: from high to low
        int i = n - 1;
        while (i >= 0 && sorted[i] > head) i--;
        for (int j = i; j >= 0; j--) {
            total_movement += abs(sorted[j] - current);
            current = sorted[j];
            printf(" -> %d", sorted[j]);
        }
        if (i < n - 1) {
            total_movement += abs(current - 0);
            current = 0;
            for (int j = i + 1; j < n; j++) {
                total_movement += abs(sorted[j] - current);
                current = sorted[j];
                printf(" -> %d", sorted[j]);
            }
        }
    }

    free(sorted);
    printf("\nTotal seek time (SCAN): %d\n", total_movement);
}

// C-SCAN: Circular SCAN
void cscan(int requests[], int n, int head, int direction) {
    int total_movement = 0;
    int current = head;

    int *sorted = (int *)malloc(n * sizeof(int));
    memcpy(sorted, requests, n * sizeof(int));
    qsort(sorted, n, sizeof(int), compare);

    printf("Servicing order: %d", head);

    if (direction == 1) { // Inward: from low to high
        int i = 0;
        while (i < n && sorted[i] < head) i++;
        for (int j = i; j < n; j++) {
            total_movement += abs(sorted[j] - current);
            current = sorted[j];
            printf(" -> %d", sorted[j]);
        }
        total_movement += abs((CYLINDERS - 1) - current);
        total_movement += CYLINDERS - 1;
        current = 0;
        for (int j = 0; j < i; j++) {
            total_movement += abs(sorted[j] - current);
            current = sorted[j];
            printf(" -> %d", sorted[j]);
        }
    } else { // Outward: from high to low
        int i = n - 1;
        while (i >= 0 && sorted[i] > head) i--;
        for (int j = i; j >= 0; j--) {
            total_movement += abs(sorted[j] - current);
            current = sorted[j];
            printf(" -> %d", sorted[j]);
        }
        total_movement += abs(current - 0);
        total_movement += CYLINDERS - 1;
        current = CYLINDERS - 1;
        for (int j = n - 1; j > i; j--) {
            total_movement += abs(sorted[j] - current);
            current = sorted[j];
            printf(" -> %d", sorted[j]);
        }
    }

    free(sorted);
    printf("\nTotal seek time (C-SCAN): %d\n", total_movement);
}

int main() {
    int n, head;
    char algorithm[10];
    int direction = 1; // 1 = inward (low to high), 0 = outward (high to low)

    printf("Enter size of request queue: ");
    scanf("%d", &n);

    int *requests = (int *)malloc(n * sizeof(int));
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
        if (requests[i] < 0 || requests[i] >= CYLINDERS) {
            printf("Invalid request: must be between 0 and %d\n", CYLINDERS - 1);
            return 1;
        }
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);
    if (head < 0 || head >= CYLINDERS) {
        printf("Invalid head position.\n");
        return 1;
    }

    printf("Enter algorithm (FCFS, SCAN, C-SCAN): ");
    scanf("%s", algorithm);

    if (strcmp(algorithm, "SCAN") == 0 || strcmp(algorithm, "C-SCAN") == 0 || strcmp(algorithm, "CSCAN") == 0) {
        printf("Enter direction (1 = inward (low to high), 0 = outward (high to low)): ");
        scanf("%d", &direction);
    }

    if (strcmp(algorithm, "FCFS") == 0) {
        fcfs(requests, n, head);
    } else if (strcmp(algorithm, "SCAN") == 0) {
        scan(requests, n, head, direction);
    } else if (strcmp(algorithm, "C-SCAN") == 0 || strcmp(algorithm, "CSCAN") == 0) {
        cscan(requests, n, head, direction);
    } else {
        printf("Unknown algorithm.\n");
    }

    free(requests);
    return 0;
}
