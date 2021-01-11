#include <stdio.h>
#include <stdlib.h>
#define INF 110

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

void create_G(Graph *g,int *s, int *t){
	int v,e;
	scanf("%d%d",&v,&e);
    scanf("%d%d",s,t);
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
		}
		else{
			if(adj->w_edge > w){
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

void dijkstra(Graph g,int s, int t){
    int *prev = (int*)malloc((g.vexnum+1)*sizeof(int));
    int *dist = (int*)malloc((g.vexnum+1)*sizeof(int));
    int *flag = (int*)malloc((g.vexnum+1)*sizeof(int));
    int i,j,k;
    int min;
    Vertex *v = &(g.vexs[s-1]);
    
    for(i = 0; i <= g.vexnum; i++){
        flag[i] = 0;
        prev[i] = 0;
        dist[i] = INF;       
    }
    for(;v != NULL; v = v->next){
        dist[v->id] = v->w_edge;
    }

    int tmp;

    for(i = 0; i < g.vexnum; i++){
        min = INF;
        for (j = 0; j < g.vexnum; j++)
        {
            if (flag[j]==0 && dist[j]<min)
            {
                min = dist[j];
                k = j;
            }
        }
        flag[k] = 1;

        for (j = 0; j < g.vexnum; j++)
        {
            tmp = get_weight(g, k, j);
            tmp = (tmp==INF ? INF : (min + tmp)); // 防止溢出
            if (flag[j] == 0 && (tmp  < dist[j]) )
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }
    // printf("dijkstra(%d): \n", g.vexs[s-1].id);
    // for (i = 0; i < g.vexnum; i++)
    //     printf("  shortest(%d, %d)=%d\n", g.vexs[s-1].id, g.vexs[i].id, dist[i+1]);
	int error = -1;
    if(dist[t] != INF)
		printf("%d",dist[t]);
	else
		printf("%d",error);
}

int main(){
    Graph g;
    int s,t;
	create_G(&g,&s,&t);
	//print(g);
    dijkstra(g,s,t);
	return 0;
}