#include "stdio.h" 
#include "ctype.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 1000

typedef int status; //status为函数类型，此处为int,其值为OK,ERROR等
typedef int elemType; //元素类型，此处为int

status visit(elemType c)
{
		printf("%c ", c);
		return OK;
}

typedef struct
{
		elemType data; 
		int cur; //游标，为0表示无指向
}component, staticLinkList[MAXSIZE];

/* 初始化 */
status initList(staticLinkList space)
{
		for(int i=0; i<MAXSIZE-1; i++)
		{
			space[i].cur = i+1;	
		}
		space[MAXSIZE-1].cur = 0;
		return OK;
} 

/* 分配空间，若备用空间非空，返回分配的结点下标，否则返回0 */
int malloc_SSL(staticLinkList space)
{
		int i = space[0].cur;

		if(i)
			space[0].cur = space[i].cur;

		return i;
}

/* 释放下标为k的结点的空间 */
void free_SSL(staticLinkList space, int k)
{
		space[k].cur = space[0].cur;
		space[0].cur = k;
}

/* 表是否为空 */
status listEmpty(staticLinkList space)
{
		if(space[MAXSIZE-1].cur == 0)
				return TRUE;
		else
				return FALSE;
}

/* 清空表 */
status clearList(staticLinkList L)
{

}

/* 返回表长度 */
int listLength(staticLinkList L)
{
		int i = L[MAXSIZE-1].cur;
		int count = 0;
		while(i)
		{
			i = L[i].cur;
			count++;
		}
		return count;
}

/* 返回第i个元素 */
status getElem(staticLinkList L, int i, elemType *e)
{

}

/* 查询元素，存在则返回位置，不存在返回0 */
int locateElem(staticLinkList L, elemType e)
{

}

/* 插入元素 */
status listInsert(staticLinkList L, int i, elemType e)
{
		int index = MAXSIZE-1;
		if(i<1 || i>listLength(L)+1)
			return ERROR;

		int j = malloc_SSL(L);
		if(j)
		{
			L[j].data = e;
			for(int l=1; l<=i-1; l++)
				index = L[index].cur;
			L[j].cur = L[index].cur;
			L[index].cur = j;
			return OK;
		}

		return ERROR;
}

/* 删除元素 */
status listDelete(staticLinkList L, int i, elemType *e)
{
		int j;
		if(i<1 || i>listLength(L)) //删除未知不合法
				return ERROR;


		int index = MAXSIZE-1;
		for(j=1; j<=i-1; j++)
			index = L[index].cur;
		
		j = L[index].cur;
		L[index].cur = L[j].cur;
		*e = L[j].data;
		free_SSL(L, j);

		return OK;
}

/* 输出所有元素 */
status listTraverse(staticLinkList L)
{
		int count = 0;
		int index = L[MAXSIZE-1].cur;
		while(index)
		{
			visit(L[index].data);
			index = L[index].cur;
			count++;
		}
		return count;
		printf("\n");
		return OK;

}


int main()
{
    staticLinkList L;
	elemType c;
    status i;
    i=initList(L);
    printf("初始化L后：L.length=%d\n",listLength(L));

    i=listInsert(L,1,'F');
    i=listInsert(L,1,'E');
    i=listInsert(L,1,'D');
    i=listInsert(L,1,'B');
    i=listInsert(L,1,'A');

    printf("\n在L的表头依次插入FEDBA后：\nL.data=");
    listTraverse(L); 

    i=listInsert(L,3,'C');
    printf("\n在L的“B”与“D”之间插入“C”后：\nL.data=");
    listTraverse(L); 

    i=listDelete(L,1,&c);
    printf("\n在L的删除“A”后：\nL.data=");
    listTraverse(L); 
	printf("\n删除的元素为");
	visit(c);

    printf("\n");

    return 0;
}

