
#include "stdio.h"    

#include "stdlib.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;          /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;        /* ElemType类型根据实际情况而定，这里假设为int */


Status visit(ElemType c)
{
    printf("%d ",c);
    return OK;
}

typedef struct
{
	ElemType data[MAXSIZE];        /* 数组，存储数据元素 */
    int length;                    /* 线性表当前长度 */
}SqList;

/* 初始化顺序线性表 */
Status InitList(SqList *L) 
{ 
    L->length=0;
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(SqList L)      // 因为已经初始化过了, 所以L不用带*号
{ 
	if(L.length==0)
		return TRUE;
	else
		return FALSE;
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(SqList *L)
{ 
    L->length=0;
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(SqList L)
{
	return L.length;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值,注意i是指位置，第1个位置的数组是从0开始 */
Status GetElem(SqList L,int i,ElemType *e)
{
    if(L.length==0 || i<1 || i>L.length)
        return ERROR;
    *e=L.data[i-1];

    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
int LocateElem(SqList L,ElemType e)
{
    int i;
    if (L.length==0)
        return 0;
    for(i=0;i<L.length;i++)
    {
        // 当i==L.length-1时, 那么L.data[L.length-1]就是最后一个元素,
        // 此时如果最后一个元素等于e, 就break, 不再执行i++, 否则i++到L.length, 然后return 0
        if (L.data[i]==e)
            break;
    }
    if(i>=L.length)
        return 0;

    return i+1;     // 第几个元素从1开始, 所以返回i+1
}


/* 初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(SqList *L,int i,ElemType e)
{ 
	int k;
	if (L->length==MAXSIZE)  /* 顺序线性表已经满 */
		return ERROR;
	if (i<1 || i>L->length+1)/* 当i比第一位置小或者比最后一位置后一位置还要大时 */
		return ERROR;

	if (i<=L->length)        /* 若插入数据位置不在表尾 */
	{
		for(k=L->length-1;k>=i-1;k--)  /* 将要插入位置之后的数据元素向后移动一位 */
			L->data[k+1]=L->data[k];
	}
	L->data[i-1]=e;          /* 将新元素插入 */
	L->length++;

	return OK;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(SqList *L,int i,ElemType *e) 
{ 
    int k;
    if (L->length==0)               /* 线性表为空 */
		return ERROR;
    if (i<1 || i>L->length)         /* 删除位置不正确 */
        return ERROR;
    *e=L->data[i-1];
    if (i<L->length)                /* 如果删除不是最后位置 */
    {
        for(k=i;k<L->length;k++)/* 将删除位置后继元素前移 */
			L->data[k-1]=L->data[k];
    }
    L->length--;
    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(SqList L)
{
	int i;
    for(i=0;i<L.length;i++)
        visit(L.data[i]);
    printf("\n");
    return OK;
}

void unionL(SqList *La,SqList Lb)
{
	int La_len,Lb_len,i;
	ElemType e;
	La_len=ListLength(*La);
	Lb_len=ListLength(Lb);
	for (i=1;i<=Lb_len;i++)     // 从头遍历Lb
	{
		GetElem(Lb,i,&e);
		if (!LocateElem(*La,e))
			ListInsert(La,++La_len,e);  // 将不存在的元素添加在L末尾
	}
}

int main()
{
    SqList L;
	SqList Lb;
    
    ElemType e;
    Status i;
    int j,k;
    i=InitList(&L);     // 初始化线性表要将地址&L传进去, 函数的参数列表使用*L代表接收的是地址
//    printf("初始化L后：L.length=%d, 初始化是否成功:%d\n", L.length, i);
//    ListTraverse(L);  // 初始化之后i == L.length == 0, 不会执行for循环, 直接输入\n

//    for(j=1;j<=5;j++)
//        i=ListInsert(&L,1,j);   // 1代表表头的位置
//    printf("在L的表头依次插入1～5后：L.data=");
//    ListTraverse(L);
//    printf("L.length=%d \n",L.length);
//    i=ListEmpty(L);
//    printf("L是否空：i=%d(1:是 0:否)\n",i);

//    i=ClearList(&L);
//    printf("清空L后：L.length=%d\n",L.length);
//    i=ListEmpty(L);
//    printf("L是否空：i=%d(1:是 0:否)\n",i);

    for(j=1;j<=10;j++)
        ListInsert(&L,j,j);     // 在表尾插入元素时位置其实应该是L.length, 这里是空表所以直接写j
//    printf("在L的表尾依次插入1～10后：L.data=");
//    ListTraverse(L);
//    printf("L.length=%d \n",L.length);

    ListInsert(&L,1,0);
    printf("在L的表头插入0后：L.data=");
    ListTraverse(L);
//    printf("L.length=%d \n",L.length);

//    printf("e: %d\n", e);     // e初始化后未赋值, 为0, 传入的时候要带着地址&e
//    i = GetElem(L,5,&e);    // 此处如果填写的过大, 返回ERROR(0), 但e未赋值仍为0, 所以打出来的结果不正确, 是0
//    printf("第5个元素的值为：%d\n",e);

//    for(j=3;j<=4;j++)
//    {
//            k=LocateElem(L,j);    // 查找元素对应的位置, 没有返回0
//            if(k)
//                    printf("%d的位置是第%d个元素\n",j,k);
//            else
//                    printf("没有值为%d的元素\n",j);
//    }


//    k=ListLength(L); /* k为表长 */
//    for(j=k+1;j>k-3;j--)    // 删除后3个元素, j=k+1是为了测试异常情况
//    {
//        i=ListDelete(&L,j,&e); /* 删除第j个数据 */
//        if(i==ERROR)
//            printf("删除第%d个数据失败\n",j);
//        else
//            printf("删除第%d个的元素值为：%d\n",j,e);
//    }
//    printf("依次输出L的元素：");
//    ListTraverse(L);

    j=5;
    ListDelete(&L,j,&e); /* 删除第5个数据 */
    printf("删除第%d个的元素值为：%d\n",j,e);
    printf("依次输出L的元素：");
    ListTraverse(L);

	//构造一个有10个数的Lb
	i=InitList(&Lb);
    for(j=6;j<=15;j++)
        i=ListInsert(&Lb,1,j);
    printf("依次输出Lb的元素：");
    ListTraverse(Lb);

	unionL(&L,Lb);      // 要修改L地址处的实际值, 所以传进去的是&L, Lb不用修改
	printf("依次输出合并了Lb的L的元素：");
    ListTraverse(L);

    return 0;
}

