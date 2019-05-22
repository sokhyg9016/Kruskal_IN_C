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
		printf("[����]:[Graph[%d] => %d, %d , %d]\n", i, Graph[i].u, Graph[i].v, Graph[i].w);
		E = Graph[i++];

		if (check_cycle(E))
		{
			*Tree++ = E;
			ntree++;
			printf("[�߰���!]:(%d   %d):%d\n", E.u, E.v, E.w);
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

	if (aa->w < bb->w)    // a�� b���� ���� ����
		return -1;      // -1 ��ȯ
	if (aa->w > bb->w)    // a�� b���� Ŭ ����
		return 1;       // 1 ��ȯ

	return 0;    // a�� b�� ���� ���� 0 ��ȯ
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

// �Է� ������ ���� ��尡 �ش� ���տ� �ִ����� Ȯ���Ѵ�.
// �ش� ����� ��Ʈ�� �ѹ��� �����ϱ� ���� ��Ʈ��忡 ���Ͽ� 
// ��� ��尡 �ٷ� �Ʒ��� �ڽ� ��尡 �� �� �ֵ��� �����.

// �̴� set_find�� ���� ���� ��, �� ��忡 ���� �̹� �����ִ����� ���θ� ������ ���� ��ȯ ���� �ʿ��ϹǷ� �� ��ȯ ������ �� ����(Ʈ��)�� ��ǥ�� �Ǵ� ���� ��ȯ�ؾ� �Ѵ�. ���� ��Ʈ ���� ��ȯ���� �ִ� ���̸�, ���� �� �Ŀ� �Է� ������ ���� ��尡 �� ���տ� �����ִ��� �˱� ���ؼ��� ��ǥ ���(��Ʈ)�� ������ ������ �ʿ䰡 �ִ�.

// ���� set_find()�� ���� ��� ������ �ϳ��� ��Ʈ�� ���� ���̰� 2�� �ܼ� ���� ������ Ʈ���� �����Ǵ� ����
//([n]: �ϳ��� ��Ʈ, n-1�� �ڽĳ��) �Է� ������ ���� ��尡 ������ ��Ʈ�� ������ �� �ְ� �ϱ� �����̴�.
// ������ ���� ������ Ʈ���� �����ϸ� �����ϴµ� �ð��� ���� �ɸ��� �����̴�.

//*�� �ڵ忡�� check_cycle�Լ��� �񱳸� ���� ���̴� set_find()�Լ�
//�� �ش� ����� ��ǥ ��带 �̿��� s1, s2�� set_find()�� ���� ���� ���� ������ s1,s2�� �Է� ������ �� �� ��尡 ���� ���տ� �̹� ���������� ��Ÿ����.

// ���� �� ����� ���� ���� �ٸ��ٸ� �� ��带 ��ǥ�ϴ� ��Ʈ�� �ٸ��ٴ� ���̴�.[��, �� �迭 �ȿ� ������Ʈ�� ����, ���δٸ� Ʈ������ ����]
// �� ��� set_union�� ���� �ΰ��� ��尡 ���� ������ ��ģ��.
int set_find(int v)
{
	int i = v, p, s;
	static int cnt = 1;

	printf("[�Է� ���: %d :: > set_find(%d)]\n", v, v);

	//�Է� ��忡 ���� ��Ʈ�� ã�´�.
	while ((p = __parent[i]) >= 0)
	{
		i = p;
	}

	s = i; //find root of set tree


	// �ش� ����� ��Ʈ�� �ѹ��� �����ϱ� ���� ��Ʈ��忡 ���Ͽ� 
	// ��� ��尡 �ٷ� �Ʒ��� �ڽ� ��尡 �� �� �ֵ��� �����.
	for (i = v; (p = __parent[i]) >= 0; i = p)
	{
		printf("[before]s = %d, __parent[%d] = %d\n",s, i, __parent[i]);

		__parent[i] = s;

		printf("[after]s = %d, __parent[%d] = %d\n",s, i, __parent[i]);
	}

	printf("[OUTPUT][%d��° s = %d]\n\n", cnt++, s);
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


