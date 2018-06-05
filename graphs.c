#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "malloc.h"
#include "stdlib.h"
#include "graphs.h"

void init(TGraph *graph){
	graph->nodes = NULL;
	graph->edges = NULL;
	graph->edge_count = 0;
	graph->node_count = 0;
};
void g_add_node(TGraph *graph,void *data){
	TNode *new_node;
	TNode **new_nodes;
	if ((new_node =(TNode*)malloc(sizeof(TNode))) == NULL)
		printf("Out of memory!");
	else {
		new_node->payload = data;
		new_nodes = (TNode**)realloc(graph->nodes, (graph->node_count + 1) * sizeof(unsigned));
		if (new_nodes != NULL) {
			graph->nodes = new_nodes;
			graph->nodes[graph->node_count] = new_node;
			graph->node_count += 1;
		}
		else printf("Out of memory!");
	}
};
void g_add_edge(TGraph *graph,TNode *node_1,TNode *node_2,void *data) {
	TEdge *new_edge;
	TEdge **new_edges;
	if ((new_edge = (TEdge*)malloc(sizeof(TEdge))) == NULL)
		printf("Out of memory!");
	else {
		new_edge->next = node_1;
		new_edge->previous = node_2;
		new_edge->payload = data;
		new_edges = (TEdge**)realloc(graph->edges, (graph->edge_count + 1) * sizeof(unsigned));
		if (new_edges != NULL) {
			graph->edges = new_edges;
			graph->edges[graph->edge_count] = new_edge;
			graph->edge_count += 1;
		}
		else printf("Out of memory!");
	}
};
void g_delete_edge(TGraph *graph, TEdge *edge_del) {
	TEdge **new_edges;
	new_edges = (TEdge**)realloc(graph->edges, (graph->edge_count - 1)* sizeof(unsigned));
	if (new_edges != NULL) {
		for (int i = 0; i < (graph->edge_count); i++) {
			if ((i == (graph->edge_count) - 1) && ((graph->edges[i + 1]) != edge_del)) {
				printf("No element to delete!");
				break;
			}
			if (graph->edges[i] == edge_del) {
				new_edges[i] = graph->edges[i + 1];
				continue;
			}
			new_edges[i] = graph->edges[i];
		}
		graph->edges = new_edges;
		free(edge_del->payload);
		free(edge_del);
	}
	else printf("Out of memory!");
}
void g_delete_node(TGraph *graph, TNode *node_del) {
	TNode **new_nodes;
	new_nodes = (TNode**)realloc(graph->nodes, (graph->node_count - 1) * sizeof(unsigned));
	if (new_nodes == NULL) printf("Out of memory!");
	else {
		for (int i = 0; i < (graph->edge_count); i++) {
			if ((graph->edges[i]->next) == node_del || (graph->edges[i]->previous) == node_del) {
				g_delete_edge(graph,graph->edges[i]);
			}
		}
		for (int i = 0; i < (graph->node_count); i++) {
			if ((i == (graph->node_count) - 1) && ((graph->nodes[i + 1]) != node_del)) {
				printf("No element to delete!");
				break;
			}
			if (graph->nodes[i] == node_del) {
				new_nodes[i] = graph->nodes[i + 1];
				continue;
			}
			new_nodes[i] = graph->nodes[i];
		}
		graph->nodes = new_nodes;
		free(node_del->payload);
		free(node_del);
	}
};
void g_show_graph(TGraph *graph,void (*show_edge)(TEdge *edge),void (*show_node)(TNode *node)) {
	for (int i = 0; i < graph->node_count; i++) {
		show_node(graph->nodes[i]);
		printf(" ");
	}
	printf("\n");
	for (int i = 0; i < graph->edge_count; i++) {
		show_edge(graph->edges[i]);
		printf("\n");
	}
}
void show_node(TNode *node){
	printf("%c", *((char*)node->payload));
}
void show_edge(TEdge *edge) {
	printf("%c => %c %d ", *((char*)edge->previous->payload), *((char*)edge->next->payload), *((int*)edge->payload));
}
int cmp_edges(TEdge *a, TEdge *b){//compare weight of 2 edges
	if (a->payload > b->payload) return 1;
	if (a->payload < b->payload) return -1;
	return 0;
}

void min_ost_tree(TGraph *graph) {//with Kraskal algorythm
	TGraph *min_ost_tree=graph;
	TNode **nodes_t = (TNode**)realloc(graph->nodes, (graph->node_count) * sizeof(unsigned));
	TEdge **edges_t = (TEdge**)realloc(graph->edges, (graph->edge_count) * sizeof(unsigned));
	if ((nodes_t==NULL) || (edges_t == NULL)) printf("Out of memory!");
	else {
		for (int i = 0; i < (graph->edge_count); i++) {//init multiplicity of edges
			edges_t[i] = graph->edges[i];
		}
		qsort(edges_t, graph->edge_count, sizeof(TEdge), (int(*)(const void*, const void*)) cmp_edges);//Sorting multiplicity of edges by weight
		for (int i = 0; i < (graph->node_count); i++) {//init multiplicity of nodes (element:one-node)
			nodes_t[i] = graph->nodes[i];
		}
		int num_node = (graph->node_count),w_min_tree=0, num_edge = (graph->edge_count);
		/*for (int i = 0; num_node > 1 && i < num_edge; i++) {// Add next edge with minumum weight 
			if (get_node(edges_t[i])==(edges_t[i]->previous)) continue;
			its not work and i dont know why:(
		}
		*/
		if (num_node != 1) {
			printf("Graph is not connected!");
			free(&min_ost_tree);
		}
		printf("Weidht of min ost tree is %d",w_min_tree);
		g_show_graph(min_ost_tree, &show_edge, &show_node);
	}
}

