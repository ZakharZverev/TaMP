#ifndef GRAPH_H
#define GRAPH_H

class Graph {
public:
    Graph(int vertices);
    ~Graph();

    void addEdge(int u, int v, int weight);
    void dijkstra(int start);  // Для вывода на консоль
    void dijkstraString(int start, char* result, int resultSize);  // Новый метод для получения строки с результатами

private:
    int** adjMatrix;
    int numVertices;
    int minDistance(int* dist, bool* visited);
};

#endif





