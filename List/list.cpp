#include "stdio.h" 

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
		printf("%d", c);
		return OK;
}

typedef struct
{
		elemType data[MAXSIZE]; //数组，存取数据元素
		int length; //线性表当前长度
}sqlist;

/* 初始化 */
status initList(sqlist *L)
{
		L->length = 0;
		return OK;
} 

/* 表是否为空 */
status listEmpty(sqlist L)
{
		if(L.length == 0)
				return TRUE;
		else
				return FALSE;
}

/* 清空表 */
status clearList(sqlist *L)
{
		L->length = 0;
		return OK;
}

/* 返回表长度 */
int listLength(sqlist L)
{
		return L.length;
}

/* 返回第i个元素 */
status getElem(sqlist L, int i, elemType *e)
{
		//查询是否合法
		if(i<1 || i>L.length)
				return ERROR;
		*e = L.data[i-1];

		return OK;
}

/* 查询元素，存在则返回位置，不存在返回0 */
int locateElem(sqlist L, elemType e)
{
		int location;
		for(location = 0; location < L.length; location++)
		{
				if(L.data[location] == e)
						break;
		}

		if(location >= L.length)
				return 0;

		return location + 1;  //c语言是从下标0开始的
}

/* 插入元素 */
status listInsert(sqlist *L, int i, elemType e)
{
		if(L->length == MAXSIZE) //表满了不允许插入
				return ERROR;
		if(i<1 || i>L->length+1) //位置不合法
				return ERROR;	

		if(i <= L->length)  //插入元素不在表尾，插入位置后方元素后移
		{
				for(int k=L->length-1; k>=i-1; k--)
						L->data[k+1] = L->data[k];	
		}	

		L->data[i-1] = e;
		L->length++;

		return OK;
}

/* 删除元素 */
status listDelete(sqlist *L, int i, elemType *e)
{
		if(L->length == 0) //表为空
				return ERROR;

		if(i<1 || i>L->length) //删除未知不合法
				return ERROR;

		*e = L->data[i-1];

		if(i < L->length) //删除的值不在末尾，后面数据前移
		{
				for(int k=i; k<L->length; k++)
						L->data[k-1] = L->data[k];
		}

		L->length--;

		return OK;
}

/* 输出所有元素 */
status listTraverse(sqlist L)
{
		for(int i=0; i<L.length; i++)
				visit(L.data[i]);
		printf("\n");
		return OK;
}

void unionL(sqlist *La, sqlist Lb)
{
		int La_len, Lb_len;
		elemType e;
		La_len = listLength(*La);
		Lb_len = listLength(Lb);
		for(int i=1; i<Lb_len; i++)
		{
				getElem(Lb, i, &e);
				if(!locateElem(*La, e))
						listInsert(La, ++La_len, e);
		}
}

int main()
{



		sqlist L;

		sqlist Lb;



		elemType e;

		status i;

		int j,k;

		i=initList(&L);

		printf("初始化L后：L.length=%d\n",L.length);

		for(j=1;j<=5;j++)

				i=listInsert(&L,1,j);

		printf("在L的表头依次插入1～5后：L.data=");

		listTraverse(L); 



		printf("L.length=%d \n",L.length);

		i=listEmpty(L);

		printf("L是否空：i=%d(1:是 0:否)\n",i);



		i=clearList(&L);

		printf("清空L后：L.length=%d\n",L.length);

		i=listEmpty(L);

		printf("L是否空：i=%d(1:是 0:否)\n",i);



		for(j=1;j<=10;j++)

				listInsert(&L,j,j);

		printf("在L的表尾依次插入1～10后：L.data=");

		listTraverse(L); 



		printf("L.length=%d \n",L.length);



		listInsert(&L,1,0);

		printf("在L的表头插入0后：L.data=");

		listTraverse(L); 

		printf("L.length=%d \n",L.length);



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

				i=listDelete(&L,j,&e); /* 删除第j个数据 */

				if(i==ERROR)

						printf("删除第%d个数据失败\n",j);

				else

						printf("删除第%d个的元素值为：%d\n",j,e);

		}

		printf("依次输出L的元素：");

		listTraverse(L); 



		j=5;

		listDelete(&L,j,&e); /* 删除第5个数据 */

		printf("删除第%d个的元素值为：%d\n",j,e);



		printf("依次输出L的元素：");

		listTraverse(L); 



		//构造一个有10个数的Lb

		i=initList(&Lb);

		for(j=6;j<=15;j++)

				i=listInsert(&Lb,1,j);



		unionL(&L,Lb);



		printf("依次输出合并了Lb的L的元素：");

		listTraverse(L); 



		return 0;

}
