#include "kruskal.h"

int main(int argc, char *argv[])
{
	int nedge, num_vertex, i;
	EDGE *Graph, *Tree;

	Graph = read_graph(argv[1], &nedge, &num_vertex);
	Tree = (EDGE *)malloc(sizeof(EDGE) * (num_vertex - 1));
	KruskalMST(Graph, Tree, nedge, num_vertex);

	for (i = 0; i < num_vertex - 1; i++)
	{
		printf("%3d  %3d  %4d\n", Tree[i].u, Tree[i].v, Tree[i].w);
	}
}


