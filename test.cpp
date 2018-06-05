// test.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "graphs.h"
#pragma comment(lib,"graphs.lib")
int main()
{
	char a, b, c, d, e;
	int ab, bc, cd, ad, ac;
	a = 'A';
	b = 'B';
	c = 'C';
	d = 'D';
	e = 'E';
	ab = 5;
	bc = 6;
	cd = 10;
	ad = 30;
	TGraph graph;
	init(&graph);
	g_add_node(&graph, &a);
	g_add_node(&graph, &b);
	g_add_node(&graph, &c);
	g_add_node(&graph, &d);
	g_add_node(&graph, &e);

	g_add_edge(&graph, graph.nodes[0], graph.nodes[1], &ab);
	g_add_edge(&graph, graph.nodes[1], graph.nodes[2], &bc);
	g_add_edge(&graph, graph.nodes[2], graph.nodes[3], &cd);
	g_add_edge(&graph, graph.nodes[0], graph.nodes[3], &ad);
	g_show_graph(&graph, &show_edge, &show_node);;
    return 0;
}

