#include "kruskal.h"

EDGE *read_graph(char *GFile, int *m, int *n)
{
	FILE *fp;
	EDGE *elist;
	int i = 0;

	if ((fp = fopen(GFile, "r")) != NULL)
	{
		fscanf(fp, "%d%d", m, n); // total edge and vertex
		elist = (EDGE *)malloc(sizeof(EDGE) * (*m));

		while (i < *m)
		{
			fscanf(fp, "%d%d%d", &elist[i].u, &elist[i].v, &elist[i].w);
			i++;
		}
	}
	else 
	{
		perror("error : can't read file");
	}
	return elist;
}


void KruskalMST(EDGE * Graph, EDGE * Tree, int nE, int nV)
{
	EDGE E;
	int ntree = 0, i = 0;
	qsort(Graph, nE, sizeof(EDGE), e_order);

	printf("\n[After Sort]\n");
	printf("%3s  %3s  %4s\n\n", "Graph[i].u", "Graph[i].v", "Graph[i].w");
	for (i = 0; i < nE; i++)
	{
		printf("%5d  %10d  %15d : [%02d]\n", Graph[i].u, Graph[i].v, Graph[i].w, i);
	}
	puts("");

	set_init(nV);
	i = 0;
	while (ntree < (nV - 1))
	{
		printf("\n==========================================\n");
		printf("[현재]:[Graph[%d] => %d, %d , %d]\n", i, Graph[i].u, Graph[i].v, Graph[i].w);
		E = Graph[i++];

		if (check_cycle(E))
		{
			*Tree++ = E;
			ntree++;
			printf("[추가됨!]:(%d   %d):%d\n", E.u, E.v, E.w);
		}
		else
		{
			printf("[Error! :: Cycle]:(%d   %d):%d\n", E.u, E.v, E.w);
		}
		puts("==========================================");
	}
}

int check_cycle(EDGE E)
{
	int s1, s2;

	printf("[set_find(%d) <->  set_find(%d)]\n\n", E.u, E.v);
	if ((s1 = set_find(E.u)) != (s2 = set_find(E.v))) {
		set_union(s1, s2);
		return 1;
	}
	else return 0;
}

int e_order(const void *a, const void *b)   //for qsort
{
	EDGE *aa, *bb;
	aa = (EDGE *)a;
	bb = (EDGE *)b;

	if (aa->w < bb->w)    // a가 b보다 작을 때는
		return -1;      // -1 반환
	if (aa->w > bb->w)    // a가 b보다 클 때는
		return 1;       // 1 반환

	return 0;    // a와 b가 같을 때는 0 반환
}

void set_init(int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		__parent[i] = -1;
		num[i] = 1;
	}
}

// 입력 값으로 들어온 노드가 해당 집합에 있는지를 확인한다.
// 해당 노드의 루트에 한번에 접근하기 위해 루트노드에 대하여 
// 모든 노드가 바로 아래의 자식 노드가 될 수 있도록 만든다.

// 이는 set_find를 통해 비교할 때, 두 노드에 대해 이미 속해있는지의 여부를 따지기 위한 반환 값이 필요하므로 그 반환 값으로 그 집합(트리)의 대표가 되는 값을 반환해야 한다. 따라서 루트 값을 반환시켜 주는 것이며, 또한 이 후에 입력 값으로 들어온 노드가 이 집합에 속해있는지 알기 위해서는 대표 노드(루트)에 빠르게 접근할 필요가 있다.

// 따라서 set_find()를 통해 모든 노드들이 하나의 루트에 대해 높이가 2인 단순 계층 구조의 트리가 생성되는 것은
//([n]: 하나의 루트, n-1의 자식노드) 입력 값으로 들어온 노드가 빠르게 루트에 접근할 수 있게 하기 위함이다.
// 복잡한 계층 구조로 트리를 구성하면 접근하는데 시간이 오래 걸리기 때문이다.

//*이 코드에서 check_cycle함수의 비교를 위해 쓰이는 set_find()함수
//는 해당 노드의 대표 노드를 이용해 s1, s2가 set_find()를 통해 같은 값이 나오면 s1,s2에 입력 값으로 들어간 두 노드가 같은 집합에 이미 속해있음을 나타낸다.

// 만약 두 노드의 값이 서로 다르다면 두 노드를 대표하는 루트가 다르다는 말이다.[즉, 한 배열 안에 포레스트가 생성, 서로다른 트리들이 존재]
// 이 경우 set_union을 통해 두개의 노드가 속한 집합을 합친다.
int set_find(int v)
{
	int i = v, p, s;
	static int cnt = 1;

	printf("[입력 노드: %d :: > set_find(%d)]\n", v, v);

	//입력 노드에 대한 루트를 찾는다.
	while ((p = __parent[i]) >= 0)
	{
		i = p;
	}

	s = i; //find root of set tree


	// 해당 노드의 루트에 한번에 접근하기 위해 루트노드에 대하여 
	// 모든 노드가 바로 아래의 자식 노드가 될 수 있도록 만든다.
	for (i = v; (p = __parent[i]) >= 0; i = p)
	{
		printf("[before]s = %d, __parent[%d] = %d\n",s, i, __parent[i]);

		__parent[i] = s;

		printf("[after]s = %d, __parent[%d] = %d\n",s, i, __parent[i]);
	}

	printf("[OUTPUT][%d번째 s = %d]\n\n", cnt++, s);
	return s;
}

void set_union(int s1, int s2)
{
	printf("[set_union(%d, %d)]\n\n", s1, s2);
	if (num[s1] < num[s2])
	{
		__parent[s1] = s2;
		num[s2] += num[s1];

		printf("num[%d] = %d, __parent[%d] = %d\nnum[%d] = %d, __parent[%d] = %d\n", s1, num[s1], s2, __parent[s2],
			s2, num[s2], s1, __parent[s1]);
	}
	else
	{
		__parent[s2] = s1;
		num[s1] += num[s2];
		
		printf("num[%d] = %d, __parent[%d] = %d\nnum[%d] = %d, __parent[%d] = %d\n", s1, num[s1], s2, __parent[s2],
			s2, num[s2], s1, __parent[s1]);
	}
	puts("");
}


