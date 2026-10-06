#include <stdio.h>

#define INF 9999
#define MAX 10

void dijkstra(int graph[MAX][MAX], int n, int start)
{
    int distance[MAX];
    int visited[MAX];
    int i, j, count, min, next;

    // Initialize
    for (i = 0; i < n; i++)
    {
        distance[i] = graph[start][i];
        visited[i] = 0;
    }

    distance[start] = 0;
    visited[start] = 1;

    // Find shortest paths
    for (count = 1; count < n; count++)
    {
        min = INF;
        next = -1;

        // Find unvisited vertex with minimum distance
        for (i = 0; i < n; i++)
        {
            if (!visited[i] && distance[i] < min)
            {
                min = distance[i];
                next = i;
            }
        }

        if (next == -1)
            break;

        visited[next] = 1;

        // Update distances
        for (j = 0; j < n; j++)
        {
            if (!visited[j] &&
                graph[next][j] != INF &&
                distance[next] + graph[next][j] < distance[j])
            {
                distance[j] =
                    distance[next] + graph[next][j];
            }
        }
    }

    // Display result
    printf("\nShortest distances from vertex %d:\n", start);

    for (i = 0; i < n; i++)
    {
        printf("To %d = %d\n", i, distance[i]);
    }
}

int main()
{
    int graph[MAX][MAX];
    int n, start;
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("\nEnter adjacency matrix:\n");
    printf("(Enter 9999 if there is no edge)\n\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nEnter starting vertex: ");
    scanf("%d", &start);

    dijkstra(graph, n, start);

    return 0;
}