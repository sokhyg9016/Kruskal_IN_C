# Kruskal_IN_C
크러스컬 알로리즘을 통해 최소신장트리(BST)를 찾아보자.

[실행 환경]: CMD<br>
[코드 작성 환경]: Visual Stdio 2017[IDE]<br>
[입력]: <font style = "color: red;">C:\Users\user\source\repos\Project97_190501\Debug></font><font style = "color: blue;"><b>Project97_190501.exe</b></font>&nbsp;<font style = "color: orange"><b>gex1.dat</b></font><br>
<br>
*red: 경로명<br>
*blue: 실행 파일(.exe)<br>
*orange: 입력 파일(.dat) [메모장을 통해 입력]<br>
<br>
<ul>
  <li>파일 입출력을 사용한 코드이다. [read_graph 참조]</li>
  <li>Graph의 정렬을 위해 stdlib.h에 있는 qsort()를 사용한다.</li>
  <li>VS2017 사용시 파일/콘솔 입출력 함수 사용시 오류 발생 -->  #pragma warning(disable:4996)을 사용해
입출력 함수 관련 오류 메세지를 무시</li>
  <li>배열내의 BST 생성을 위해 전역 변수로 'static int __parent[MAX_ELTS], num[MAX_ELTS];'을 사용.</li><br>
  
  <li>사용한 라이브러리 및 매크로 상수
    
      #pragma once
      #pragma warning(disable:4996)
      #include <stdio.h>
      #include <stdlib.h>
      #define INF 10000
      #define MAX_ELTS 1000
   
  </li><br>
  <li>코드내에서 주로 사용되는 구조체 변수<br>
  
      typedef struct EDGE
      {
        int u, v;                   // (u,v)
        int w;                      // weight
      }EDGE;
      //G=(V,E)
  </li><br>
 <li>사용된 함수
  <ol>
    <li>
      <b>EDGE *read_graph(char *GFile, int *m, int *n);</b><br>
      <p>입력으로 들어온 파일에 데이터를 이용해 기본적인 그래프 배열의 값을 설정하는 함수이다.</p>
    </li>
    <li>
      <b>int e_order(const void *, const void *);</b><br>
      <p>stdlib.h에 있는 qsort()함수를 쓰기 위해서는 비교함수가 필요하다. 따라서 이 함수는 비교함수로 사용된다.</p>
    </li>
    <li>
      <b>void KruskalMST(EDGE * elist, EDGE * T, int nedges, int nvertex);</b><br>
      <p>크리스컬 알로리즘을 구현한 코드의 핵심 함수. 이 함수에서 부가적으로 다른 함수들을 호출하여 BST를 생성한다.</p>
    </li>
    <li>
      <b>void set_init(int n);</b><br>
      <p>BST 생성을 위한  __parent, num 배열을 초기화 한다.</p>
    </li>
    <li>
      <b>int check_cycle(EDGE E);</b><br>
      <p>현재 Graph 배열에서 가중치가 가장 작은 선분을 가져오면 그 선분 E에 대하여 사이클이 만들어지는지 아닌지 확인한다.</p>
    </li>
    
        가져온 선분 E를 추가했을때 사이클을 만들지 않으면 E를 Tree에 추가시키고 트리의 선분 수를 증가시킨다. 만약 사이클을 만들면 선분E를 
        버린다. 이때 선분 E는 해당 코드에선 이미 퀵 소트를 통해 오름차순으로 정렬된 Graph배열에서 하나씩 가져오는 것으로 Graph 배열의 각 
        요소의 값은 [노드1{u}, 노드2{2}, 노드1와 노드2 사이의 가중치] 로 이루어져 있다. 사이클의 생성 여부는 set_find()함수를 통해 각 노드!
        과 노드2가 속해져 있는 집합의 대표 노드(루트)를 가져와 같은지 같지 않은지 비교한다. 만약 같지 않다면 두 집합을 합치기 위해 set_union()
        함수를 호출한다.
    
   <li>
      <b>int set_find(int v);</b><br>
      <p>입력 값으로 들어온 노드가 해당 집합에 있는지를 확인하고 입력 노드의 집합(트리)의 대표 노드(루트)를 리턴한다. 해당 노드의 루트에 한번에 접       근하기 위해 루트 노드에 대하여 루트를 제외한 모든 노드가 루트의 자식 노드가 될 수 있도록 만든다.</p>
    </li>
    
    이는 set_find를 통해 비교할 때, 두 노드에 대해 이미 속해있는지의 여부를 따지기 위한 반환 값이 필요하므로 그 반환 값으로
    그 집합(트리)의 대표가되는 값을 반환해야 한다. 따라서 루트 값을 반환시켜 주는 것이며, 또한 이 후에 입력 값으로 들어온 노드가
    이 집합에 속해있는지 알기 위해서는 대표 노드(루트)에 빠르게 접근할 필요가 있다.

    따라서 set_find()를 통해 모든 노드들이 하나의 루트에 대해 높이가 2인 단순 계층 구조의 트리가 생성되는 것은
    ([n]: 하나의 루트, n-1의 자식노드) 입력 값으로 들어온 노드가 빠르게 루트에 접근할 수 있게 하기 위함이다.
    복잡한 계층 구조로 트리를 구성하면 접근하는데 시간이 오래 걸리기 때문이다.

    *이 코드에서 check_cycle함수의 비교를 위해 쓰이는 set_find()함수는 해당 노드의 대표 노드를 이용해 s1, s2가 set_find()를 통해
     같은 값이 나오면 s1,s2에 입력 값으로 들어간 두 노드가 같은 집합에 이미 속해있음을 나타낸다.

    만약 두 노드의 값이 서로 다르다면 두 노드를 대표하는 루트가 다르다는 말이다.
    [즉, 한 배열 안에 포레스트가 생성, 서로다른 트리들이 존재]
    
    
  <li>
    <b>void set_union(int s1, int s2);</b><br>
    <p>s1,s2를 비교하여 합하는 함수이다. 이때 s1과 s2는 단일의 노드 일수도 아니면 한 집합을 대표하는 루트 노드들일 수도 있다.</p>
  </li>
        
  </ol>
    </li>
</ul>
