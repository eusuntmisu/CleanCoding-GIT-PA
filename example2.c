#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GPH;


NODE *create_node(int v) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH *create_graph(int vertices) {
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(vertices * sizeof(int));

  
    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}


void add_edge(GPH *graph, int src, int dest) {
   
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

   
    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}


void insert_edges(GPH *graph, int nr_of_edges) {
    int src, dest;
    printf("Adauga %d muchii (de la 1 la %d):\n", nr_of_edges, graph->vertices);

    for (int i = 0; i < nr_of_edges; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src - 1, dest - 1); 
    }
}

// BFS utils
int is_empty(NODE *queue) {
    return queue == NULL;
}

void enqueue(NODE **queue, int data) {
    NODE *new_node = create_node(data);

    
    if (is_empty(*queue)) {
        *queue = new_node;
    } else {
       
        NODE *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE **queue) {
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}


void DFS(GPH *graph, int vertex_nr) {
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d->", vertex_nr + 1);

    // Parcurgem lista de adiacență
    while (temp != NULL) {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex); 
        }
        temp = temp->next;
    }
}


void BFS(GPH *graph, int start) {
    NODE *queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    
    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current + 1); 

        NODE *temp = graph->adjacency_lists[current];

        
        while (temp) {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}


void wipe_visited_list(GPH *graph, int nr_of_vertices) {
    for (int i = 0; i < nr_of_vertices; i++) {
        graph->visited[i] = 0;
    }
}

int main() {
    int nr_of_vertices, nr_of_edges;
    int starting_vertex;

    
    printf("Cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);
    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);


    GPH *graph = create_graph(nr_of_vertices);

    
    insert_edges(graph, nr_of_edges);

    
    printf("De unde plecam in DFS? ");
    scanf("%d", &starting_vertex);

    
    printf("Parcurgere cu DFS: ");
    DFS(graph, starting_vertex - 1); 
    printf("\n");

    
    wipe_visited_list(graph, nr_of_vertices);

    
    printf("De unde plecam in BFS? ");
    scanf("%d", &starting_vertex);

    
    printf("Parcurgere cu BFS: ");
    BFS(graph, starting_vertex - 1); // 0-indexed
    printf("\n");

    return 0;
}
