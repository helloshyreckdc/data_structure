#include "stdio.h" 
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 

typedef int status; //status为函数类型，此处为int,其值为OK,ERROR等
typedef int elemType; //元素类型，此处为int

status visit(elemType c)
{
		printf("%d ", c);
		return OK;
}

typedef struct Node
{
		elemType data;
		struct Node *next;
}Node;

typedef struct Node *linkList; //定义linkList

/* 初始化 */
status initList(linkList *L)
{
		*L = (linkList)malloc(sizeof(Node)); //产生头结点，并使L指向此结点
		if(!(*L))
			return ERROR; //地址分配失败
		(*L)->next = NULL;

		return OK;
} 

/* 表是否为空 */
status listEmpty(linkList L)
{
		if(!L->next)
				return TRUE;
		else
				return FALSE;
}

/* 清空表 */
status clearList(linkList L)
{
		linkList p, q;
		p = L->next;
		while(p)
		{
			q = p->next;
			free(p);
			p = q;
		}

		L->next = NULL;
		return OK;
}

/* 返回表长度 */
int listLength(linkList L)
{
		linkList p, q;
		int count = 0;
		p = L->next;
		while(p)
		{
			p = p->next;
			count++;
		}
		return count;
}

/* 返回第i个元素 */
status getElem(linkList L, int i, elemType *e)
{
		int count = 1;
		linkList p;
		p = L->next;
		while(p && count<i)
		{
			p = p->next;
			count++;
		}
		if(!p || count>i)
			return ERROR;
		*e = p->data;
		return OK;
}

/* 查询元素，存在则返回位置，不存在返回0 */
int locateElem(linkList L, elemType e)
{
		int count = 1;
		linkList p = L->next;
		while(p)
		{
			if(p->data == e)
				return count;
			p = p->next;
			count++;
		}
		return 0;
}

/* 插入元素 */
status listInsert(linkList L, int i, elemType e)
{
		linkList p, s;
		int count = 1;
		p = L;
		while(p && count<i)
		{
			p = p->next;
			count++;
		}
		if (!p || count>i)
			return ERROR;

		s = (linkList)malloc(sizeof(Node));
		s->data = e;
		s->next = p->next;
		p->next = s;
		return OK;
}

/* 删除表中大于min,小于max的数据 */
status deleteElement(linkList L, int min, int max)
{
	linkList p;
	p = L;
	while(p->next)
	{
		if(p->next->data > min && p->next->data < max)
		{
			linkList q = p->next;
			p->next = q->next;
			free(q);
		}
		else
		{
			p = p->next;
		}
	}
	return 0;
}

/* 删除元素 */
status listDelete(linkList L, int i, elemType *e)
{

		linkList p, q;
		int count = 1;
		p = L;
		while(p->next && count<i)
		{
			p = p->next;
			count++;
		}
		if (!(p->next) || count>i)
			return ERROR;

		q = p->next;
		p->next = q->next;
		*e = q->data;
		free(q);
		return OK;
}

/* 输出所有元素 */
status listTraverse(linkList L)
{
		linkList p = L->next;
		while(p)
		{
			visit(p->data);
			p = p->next;
		}	
		printf("\n");
		return OK;
}

/* 创建表并头插元素 */
void createListHead(linkList *L, int n)
{
		linkList p;
		srand(time(0));
		*L = (linkList)malloc(sizeof(Node));
		(*L)->next = NULL;

		for(int i=0; i<n; i++)
		{
			p = (linkList)malloc(sizeof(Node));
			p->data = rand()%100 + 1;
			p->next = (*L)->next;
			(*L)->next = p;
		}
}

/* 创建表并尾插元素 */
void createListTail(linkList *L, int n)
{
		linkList p, r;
		srand(time(0));
		*L = (linkList)malloc(sizeof(Node));
		(*L)->next = NULL;
		r = *L; //r指向尾部结点

		for(int i=0; i<n; i++)
		{
			p = (linkList)malloc(sizeof(Node));
			p->data = rand()%100 + 1;
			r->next = p;
			r = p;
		}	
}

int main()
{

    linkList L;
    elemType e;
    status i;
    int j,k;
    i=initList(&L);
    printf("初始化L后：listLength(L)=%d\n",listLength(L));
    for(j=1;j<=5;j++)
            i=listInsert(L,1,j);
    printf("在L的表头依次插入1～5后：L.data=");
    listTraverse(L); 

    printf("listLength(L)=%d \n",listLength(L));
    i=listEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    i=clearList(L);
    printf("清空L后：listLength(L)=%d\n",listLength(L));
    i=listEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    for(j=1;j<=10;j++)
            listInsert(L,j,j);
    printf("在L的表尾依次插入1～10后：L.data=");
    listTraverse(L); 

    printf("listLength(L)=%d \n",listLength(L));

    listInsert(L,1,0);
    printf("在L的表头插入0后：L.data=");
    listTraverse(L); 
    printf("listLength(L)=%d \n",listLength(L));

    getElem(L,5,&e);
    printf("第5个元素的值为：%d\n",e);
    for(j=3;j<=4;j++)
    {
            k=locateElem(L,j);
            if(k)
                    printf("第%d个元素的值为%d\n",k,j);
            else
                    printf("没有值为%d的元素\n",j);
    }
    

    k=listLength(L); /* k为表长 */
    for(j=k+1;j>=k;j--)
    {
            i=listDelete(L,j,&e); /* 删除第j个数据 */
            if(i==ERROR)
                    printf("删除第%d个数据失败\n",j);
            else
                    printf("删除第%d个的元素值为：%d\n",j,e);
    }
    printf("依次输出L的元素：");
    listTraverse(L); 

    j=5;
    listDelete(L,j,&e); /* 删除第5个数据 */
    printf("删除第%d个的元素值为：%d\n",j,e);

    printf("依次输出L的元素：");
    listTraverse(L); 

    i=clearList(L);
    printf("\n清空L后：listLength(L)=%d\n",listLength(L));
    createListHead(&L,20);
    printf("整体创建L的元素(头插法)：");
    listTraverse(L); 
    
    i=clearList(L);
    printf("\n删除L后：listLength(L)=%d\n",listLength(L));
    createListTail(&L,20);
    printf("整体创建L的元素(尾插法)：");
    listTraverse(L); 

// test an algorithm
    linkList Ltest;
    i=initList(&Ltest);
    for(j=10;j>=1;j--)
            listInsert(Ltest,1,j);
    printf("在L的表尾依次插入1～10后：Ltest.data=");
    listTraverse(Ltest); 
	deleteElement(Ltest, -5, -3);
	listTraverse(Ltest);


    return 0;
}



