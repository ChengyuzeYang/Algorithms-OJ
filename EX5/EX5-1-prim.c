#include <stdio.h>
#include <stdlib.h> 
#define INF 1100

typedef struct Vertex{
	int id;
	int w_edge;
	int isSet;
	struct Vertex* next;
}Vertex;

typedef struct {
	int vexnum;
	int edgnum;
    Vertex* vexs;        //存储图中顶点数据
}Graph;


Vertex* isAdj(Graph *g, int id1, int id2){
	Vertex* v = &(g->vexs[id1-1]);
	for(; v != NULL; v = v->next){
		if(v->id == id2)break;
	}
	return v;
}

void AddEdge(Graph *g, int id1, int id2, int w){
	Vertex* v = &(g->vexs[id1-1]);
	for(; v->next != NULL; v = v->next){}
	Vertex* new_e = (Vertex*)malloc(sizeof(Vertex));
	new_e->id = id2;
	new_e->isSet = 0;
	new_e->next = NULL;
	new_e->w_edge = w;
	v->next = new_e;
}

void create_G(Graph *g){
	int v,e;
	scanf("%d%d",&v,&e);
	g->vexnum = v;
	g->edgnum = e;
	g->vexs = (Vertex*)malloc(v*sizeof(Vertex));
	for(int i = 0; i < v; i++){
		g->vexs[i].id = i+1;
		g->vexs[i].isSet = 0;
		g->vexs[i].next = NULL;
		g->vexs[i].w_edge = 0; 
	}
	for(int i = 0; i < e; i++){
		int v1,v2,w;
		scanf("%d%d%d",&v1,&v2,&w);
		Vertex* adj = isAdj(g,v1,v2);
		if(adj == NULL){
			AddEdge(g,v1,v2,w);
			AddEdge(g,v2,v1,w);
		}
		else{
			if(adj->w_edge > w){
				adj->w_edge = w;
				adj = isAdj(g,v2,v1);
				adj->w_edge = w;
			}
		}
	}
}

void print(Graph g){
	for(int i = 0; i < g.vexnum; i++){
		printf("vex:%d==",g.vexs[i].id);
		for(Vertex* v = g.vexs[i].next; v != NULL; v = v->next){
			printf("\n%d %d",v->id,v->w_edge);
		}
		printf("\n");
	}
}

int get_weight(Graph g, int s, int t){
    Vertex *v = g.vexs[s-1].next;
    for(;v != NULL; v = v->next){
        if(v->id == t)
            return v->w_edge;
    }
    return INF;
}

void prim(Graph g, int start){
    int min,i,j,k,m,n,tmp,sum;
    int index = 1;         // prim最小树的索引，即prims数组的索引
    int *prims = (int*)malloc((g.vexnum+1)*sizeof(int));;     // prim最小树的结果数组
    int *weights = (int*)malloc((g.vexnum+1)*sizeof(int));;    // 顶点间边的权值

    // prim最小生成树中第一个数是"图中第start个顶点"，因为是从start开始的。
    prims[index++] = g.vexs[start-1].id;
    

    // 初始化"顶点的权值数组"，
    // 将每个顶点的权值初始化为"第start个顶点"到"该顶点"的权值。
   
    for(i = 0; i <= g.vexnum; i++)
        weights[i] = INF;
    for(Vertex *v = &(g.vexs[start-1]);v != NULL; v = v->next){
        weights[v->id] = v->w_edge;
    }

    for (i = 0; i < g.vexnum; i++)
    {
        // 由于从start开始的，因此不需要再对第start个顶点进行处理。
        if(start-1 == i)
            continue;

        j = 1;
        k = 1;
        min = INF;
        // 在未被加入到最小生成树的顶点中，找出权值最小的顶点。
        while (j <= g.vexnum)
        {
            // 若weights[j]=0，意味着"第j个节点已经被排序过"(或者说已经加入了最小生成树中)。
            if (weights[j] != 0 && weights[j] < min)
            {
                min = weights[j];
                k = j;
            }
            j++;
        }

        // 经过上面的处理后，在未被加入到最小生成树的顶点中，权值最小的顶点是第k个顶点。
        // 将第k个顶点加入到最小生成树的结果数组中
        prims[index++] = k;
        // 将"第k个顶点的权值"标记为0，意味着第k个顶点已经排序过了(或者说已经加入了最小树结果中)。
        weights[k] = 0;
        // 当第k个顶点被加入到最小生成树的结果数组中之后，更新其它顶点的权值。
        for (j = 1; j <= g.vexnum; j++)
        {
            // 获取第k个顶点到第j个顶点的权值
            if (weights[j] != 0){
                tmp = get_weight(g, k, j);
                // 当第j个节点没有被处理，并且需要更新时才被更新。
                if (tmp < weights[j])
                    weights[j] = tmp;
            }
        }
    }

    // 计算最小生成树的权值
    sum = 0;
    for (i = 2; i < index; i++)
    {
        min = INF;
        // 获取prims[i]在G中的位置
        n = prims[i];
        // 在vexs[0...i]中，找出到j的权值最小的顶点。
        for (j = 1; j < i; j++)
        {
            m = prims[j];
            tmp = get_weight(g, m, n);
            if (tmp < min)
                min = tmp;
        }
        sum += min;
    }
    // 打印最小生成树
    printf("%d\n",sum);
    // for (i = 0; i < index; i++)
    //     printf("%d ", prims[i]);
    // printf("\n");
}

int main(){
    Graph g;
	create_G(&g);
	//print(g);
    prim(g,1);
	return 0;
}