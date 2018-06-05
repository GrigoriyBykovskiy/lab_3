#ifndef __GRAPHS__
#define __GRAPHS__

typedef struct TNode {
	void *payload;
};
typedef struct TEdge {
	TNode *previous;
	TNode *next;
	void *payload;
};
typedef struct TGraph {
	TNode **nodes;
	TEdge **edges;
	unsigned node_count, edge_count;
};
void init(TGraph *graph);
void g_add_node(TGraph *graph, void *data);
void g_add_edge(TGraph *graph, TNode *node_1, TNode *node_2, void *data);
void g_delete_edge(TGraph *graph, TEdge *edge_del);
void g_delete_node(TGraph *graph, TNode *node_del);
void g_show_graph(TGraph *graph, void(*show_edge)(TEdge *edge), void(*show_node)(TNode *node));
void show_node(TNode *node);
void show_edge(TEdge *edge);
int cmp_edges(TEdge *a, TEdge *b);
void min_ost_tree(TGraph *graph);
#endif
