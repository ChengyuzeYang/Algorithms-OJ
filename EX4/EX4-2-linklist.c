#include<string.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct PCB {
	int id;//任务序号
	int arrivetime;//任务到达时间
	int runtime;//任务需要执行的时间
	int counttime;//记录任务处理一段时间后,剩下的需要处理的时间
	struct PCB* next;
}*task, pcb;

pcb* creattask(int x, int y, int z) {
	task newtask = (task)malloc(sizeof(pcb));
	newtask->id = x;
	newtask->arrivetime = y;
	newtask->runtime = z;
	newtask->counttime = z;
	newtask->next = NULL;
	return newtask;
}

void deltask(pcb* n, int x) {
	task d;
	if (n != NULL) {
		while (n->next->id != x) {
			n = n->next;
		}
		d = n->next;
		n->next = d->next;
		free(d);
	}
}

void count(pcb* n, int t) {  //q用于记录最先到达的任务位置，p用于遍历链表
	pcb* q, * p;
	int qp = 0; //用于记录上一次任务的id号
	int temp = t; int time = 0; //time记录当前时间，temp记录任务个数,便于后续操作
	int sum = 0;  //zt用于记录总周转时间,dt记录总带权周转时间
	while (t != 0) {
		p = n->next;
		q = p;
			while (p != NULL) { //找到最先到达的任务
				if (p->arrivetime < q->arrivetime) {
					q = p;
				}
				p = p->next;
			}
			p = n->next;
			while (p != NULL) { //找到处于就绪的多个任务里面任务最短的任务
				if ((p->arrivetime <= time || p->arrivetime == q->arrivetime) && p->counttime < q->counttime)
					q = p;
				p = p->next;
			}
			q->counttime--;
			if(qp == 0 || qp != q->id)
			qp = q->id;
			if (time < q->arrivetime)//防止时间暂停
				time = q->arrivetime;
			time++;
		if (q->counttime== 0) {
			sum += time - q->arrivetime;
			deltask(n, q->id);
			--t;
		}
	}
    printf("%d", sum);
}

int main() {
	int n, i, y, z;
	task tail = NULL;
	task head = NULL;
	scanf("%d", &n);
	tail = (task)malloc(sizeof(pcb));
	head = tail;
	for (i = 1; i <= n; i++) {
		scanf("%d%d", &y, &z);
		tail->next = creattask(i, y, z);
		tail = tail->next;
	}
	count(head, n);
    return 0;
}