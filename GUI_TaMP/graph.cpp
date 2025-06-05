#include "graph.h"
#include <iostream>

Graph::Graph(int vertices) : numVertices(vertices) {
    adjMatrix = new int*[vertices];
    for (int i = 0; i < vertices; i++) {
        adjMatrix[i] = new int[vertices];
        for (int j = 0; j < vertices; j++) {
            adjMatrix[i][j] = -1; // Инициализация значениями -1 (означает отсутствие пути)
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < numVertices; i++) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

void Graph::addEdge(int u, int v, int weight) {
    adjMatrix[u][v] = weight;
    adjMatrix[v][u] = weight; // Так как граф неориентированный
}

void Graph::dijkstra(int start) {
    bool* visited = new bool[numVertices];
    int* dist = new int[numVertices];

    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
        dist[i] = 999999; // Бесконечность
    }

    dist[start] = 0; // Начальная вершина

    for (int count = 0; count < numVertices - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && adjMatrix[u][v] != -1 && dist[u] != 999999 && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
            }
        }
    }

    std::cout << "Shortest distances from vertex " << start << ":\n";
    for (int i = 0; i < numVertices; i++) {
        std::cout << "Vertex " << i << ": " << dist[i] << std::endl;
    }

    delete[] visited;
    delete[] dist;
}

void Graph::dijkstraString(int start, char* result, int resultSize) {
    bool* visited = new bool[numVertices];
    int* dist = new int[numVertices];

    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
        dist[i] = 999999; // Бесконечность
    }

    dist[start] = 0; // Начальная вершина

    for (int count = 0; count < numVertices - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && adjMatrix[u][v] != -1 && dist[u] != 999999 && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
            }
        }
    }

    int pos = 0;
    pos += snprintf(result + pos, resultSize - pos, "Shortest distances from vertex %d:\n", start);

    for (int i = 0; i < numVertices; i++) {
        pos += snprintf(result + pos, resultSize - pos, "Vertex %d: %d\n", i, dist[i]);
    }

    delete[] visited;
    delete[] dist;
}

int Graph::minDistance(int* dist, bool* visited) {
    int min = 999999, minIndex;
    for (int v = 0; v < numVertices; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}







