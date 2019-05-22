#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define INF 10000
#define MAX_ELTS 1000

static int __parent[MAX_ELTS], num[MAX_ELTS];

typedef struct EDGE
{
	int u, v;                   // (u,v)
	int w;                      // weight
}EDGE;
//G=(V,E)

EDGE *read_graph(char *GFile, int *m, int *n);
void KruskalMST(EDGE * elist, EDGE * T, int nedges, int nvertex);
int check_cycle(EDGE E);
void set_init(int n);
int set_find(int v);
void set_union(int s1, int s2);
int e_order(const void *, const void *);