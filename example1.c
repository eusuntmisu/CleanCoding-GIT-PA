#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct g {
    int v;
    int *vis;
    struct Node **alst;
} GPH;


NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}


void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}


GPH *create_g(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(NODE *) * v);
    g->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }

    return g;
}


void DFS(GPH *g, int v_nr) {
    g->vis[v_nr] = 1;
    printf("%d ", v_nr + 1); 

   
    NODE *aux = g->alst[v_nr];
    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0) {
            DFS(g, con_ver);
        }
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr) {
    int src, dest;
    printf("Adauga %d muchii (de la 1 la %d)\n", edg_nr, g->v);

    for (int i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);

        add_edge(g, src - 1, dest - 1);
    }
}


void wipe(GPH *g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}

int main() {
    int nrv, edg_nr;

    printf("Cate noduri are girafa? ");
    scanf("%d", &nrv);
    printf("Cate muchii are giraful? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);

    insert_edges(g, edg_nr);
    wipe(g, nrv);

    printf("DFS: ");
    DFS(g, 0); 
    printf("\n");

    return 0;
}
