#include <stdio.h>
#include <stdlib.h>

struct Node {
  int vertex;
  struct Node* next;
};

struct Graph {
  int numVertices;
  struct Node** adjLists;
  int* visited;
};

struct Node* createNode(int v) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

struct Graph* createGraph(int vertices) {
  struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));
  graph->visited = (int*)malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }
  return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
  struct Node* newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

void DFS(struct Graph* graph, int vertex) {
  struct Node* adjList = graph->adjLists[vertex];
  struct Node* temp = adjList;

  graph->visited[vertex] = 1;
  printf("Node %d -> ", vertex);

  while (temp != NULL) {
    int connectedVertex = temp->vertex;
    if (graph->visited[connectedVertex] == 0) {
      DFS(graph, connectedVertex);
    }
    temp = temp->next;
  }
}

int main() {
  int numVertices, numEdges, u, v;
  printf("Enter the number of vertices: ");
  scanf("%d", &numVertices);
  struct Graph* graph = createGraph(numVertices);
  printf("Enter the number of edges: ");
  scanf("%d", &numEdges);
  printf("Enter source and destination for each edge (u v format):\n");
  for (int i = 0; i < numEdges; i++) {
    scanf("%d %d", &u, &v);
    addEdge(graph, u, v);
  }

  printf("DFS Traversal Order: ");
  DFS(graph, 1);
  printf("\n");
  return 0;
}
