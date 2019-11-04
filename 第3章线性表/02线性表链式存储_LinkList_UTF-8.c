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

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */


Status visit(ElemType c)
{
    printf("%d ",c);
    return OK;
}

typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node;
typedef struct Node *LinkList; /* 定义LinkList */

/* 初始化链表 */
Status InitList(LinkList *L) 
{ 
    *L=(LinkList)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */
    if(!(*L)) /* 存储分配失败 */
        return ERROR;
    (*L)->next=NULL; /* 指针域为空 */

    return OK;
}

/* 初始条件：链表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(LinkList L)
{ 
    if(L->next)
        return FALSE;
    else
        return TRUE;
}

/* 初始条件：链表L已存在。操作结果：将L重置为空表 */
Status ClearList(LinkList *L)
{ 
	LinkList p,q;
	p=(*L)->next;           /*  p指向第一个结点 */
	while(p)                /*  没到表尾 */
	{
		q=p->next;
		free(p);
		p=q;
	}
	(*L)->next=NULL;        /* 头结点指针域为空 */
	return OK;
}

/* 初始条件：链表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(LinkList L)
{
    int i=0;
    LinkList p=L->next; /* p指向第一个结点 */
    while(p)                        
    {
        i++;
        p=p->next;
    }
    return i;
}

/* 初始条件：链表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值 */
Status GetElem(LinkList L,int i,ElemType *e)
{
	int j;
	LinkList p;		/* 声明一结点p */
	p = L->next;		/* 让p指向链表L的第一个结点 */
	j = 1;		/*  j为计数器 */
	while (p && j<i)  /* p不为空或者计数器j还没有等于i时，循环继续 */
	{   
		p = p->next;  /* 让p指向下一个结点 */
		++j;
	}
	if ( !p || j>i ) 
		return ERROR;  /*  第i个元素不存在 */
	*e = p->data;   /*  取第i个元素的数据 */
	return OK;
}

/* 初始条件：链表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
int LocateElem(LinkList L,ElemType e)
{
    int i=0;
    LinkList p=L->next;
    while(p)
    {
        i++;
        if(p->data==e) /* 找到这样的数据元素 */
            return i;
        p=p->next;
    }

    return 0;
}


/* 初始条件：链表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1, 插入后的元素位置是i */
Status ListInsert(LinkList *L,int i,ElemType e)
{ 
	int j;
	LinkList p,s;
	p = *L;   
	j = 1;
	while (p && j < i)     /* 寻找第i个结点 */
	{
		p = p->next;    // 如果是最后一个节点后(i==12)插入, p指向最后一个节点, p->next==NULL, j==i, 跳出循环
		++j;
	} 
	if (!p || j > i) 
		return ERROR;   /* 第i个元素不存在 */
	s = (LinkList)malloc(sizeof(Node));  /*  生成新结点(C语言标准函数) */
	s->data = e;  
	s->next = p->next;      /* 将p的后继结点赋值给s的后继  */
	p->next = s;          /* 将s赋值给p的后继 */
	return OK;
}

/* 初始条件：链表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(LinkList *L,int i,ElemType *e) 
{ 
	int j;
	LinkList p,q;
	p = *L;
	j = 1;
	while (p->next && j < i)	/* 遍历寻找第i个元素 */
	{
        p = p->next;
        ++j;
	}
	if (!(p->next) || j > i) 
	    return ERROR;           /* 第i个元素不存在 */
	q = p->next;
	p->next = q->next;			/* 将q的后继赋值给p的后继, 即p->next = p->next->next */
	*e = q->data;               /* 将q结点中的数据给e */
	free(q);                    /* 让系统回收此结点，释放内存 */
	return OK;
}

/* 初始条件：链表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(LinkList L)
{
    LinkList p=L->next;
    while(p)
    {
        visit(p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（头插法） */
void CreateListHead(LinkList *L, int n) 
{
	LinkList p;
	int i;
	srand(time(0));                         /* 初始化随机数种子 */
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;                      /*  先建立一个带头结点的单链表 */
	for (i=0; i<n; i++) 
	{
		p = (LinkList)malloc(sizeof(Node)); /*  生成新结点 */
		p->data = rand()%100+1;             /*  随机生成100以内的数字 */
		p->next = (*L)->next;    
		(*L)->next = p;						/*  插入到表头 */
	}
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法） */
void CreateListTail(LinkList *L, int n) 
{
	LinkList p,r;
	int i;
	srand(time(0));                      /* 初始化随机数种子 */
	*L = (LinkList)malloc(sizeof(Node)); /* L为整个线性表 */
	r=*L;                                /* r为指向尾部的结点 */
	for (i=0; i<n; i++) 
	{
		p = (Node *)malloc(sizeof(Node)); /*  生成新结点 */
		p->data = rand()%100+1;           /*  随机生成100以内的数字 */
		r->next=p;                        /* 将表尾终端结点的指针指向新结点 */
		r = p;                            /* 将当前的新结点定义为表尾终端结点 */
	}
	r->next = NULL;                       /* 表示当前链表结束 */
}

Status InitList_1(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(Node));    // 传进来的*L是结构体声明时候的内存地址
    if(!(*L))
        return ERROR;
    (*L)->next = NULL;
    return OK;
}

int ListLength_1(LinkList L)
{
    LinkList p = L->next;
    int i=0;
    while(p)
    {
        p = p->next;
        i++;
    }
    return i;
}

Status ListInsert_1(LinkList *L, int i, ElemType e)
{
    LinkList p, s;
    p = (*L);   // 插入删除节点时p要初始化为头结点, 因为要考虑空表的可能
    int j = 1;
    while(p && j < i)   // 当p下一个是空的时候代表到了最后一个节点, 此时跳出循环
    {
        p = p->next;
        j++;
    }
    if (!p || j > i)    // 此处防止i过大p为空, 或i<1 while不执行, 抛出异常
        return ERROR;
    s = (LinkList)malloc(sizeof(Node));
    s->data = e;
    s->next = p->next;  // i==1的情况从头结点后面插入s节点, 所以p初始化为L的头结点
    p->next = s;
    return OK;
}

Status ListTraverse_1(LinkList L)
{
    LinkList p = L->next;
    int i = 1;
    while(p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

Status ClearList_1(LinkList *L)
{
    LinkList p = (*L)->next;
    LinkList q;
    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    // 在上面free了5个节点后, *L各节点的数据为0(头节点), 0(第一个节点)和4个随机地址, 最后一个节点的next才为NULL(p==NULL跳出循环)
    // 所以第一个节点仍可以访问, 将头节点的next设为NULL后才算真正的清空了链表
    // TODO: 为什么第一个节点释放后值是0?
    (*L)->next = NULL;
    return OK;
}

Status GetElem_1(LinkList L, int i, ElemType *e)
{
    LinkList p = L->next;
    int j = 1;
    while(p && j < i)
    {
        p = p->next;
        j++;
    }
    if(!p || j > i)
        return ERROR;
    *e = p->data;
    return OK;
}

int LocateElem_1(LinkList L, ElemType e)
{
    LinkList p = L->next;
    int i = 1;
    while(p)
    {
        if(p->data == e)
            return i;   // if后面跟return的话就不用写else了, 因为如果符合会直接退出函数
        p = p->next;
        i++;
    }
    return 0;
}

Status ListDelete_1(LinkList *L, int j, ElemType *e)
{
    LinkList p = (*L);
    LinkList s;
    int i = 1;
    // 这里遍历条件用p->next是因为p->next->next不能不存在(NULL的后继, 但可以为NULL), 最多遍历到倒数第二个节点
    while((p->next) && i < j)
    {
        p = p->next;
        i++;
    }
    if(!(p->next) || i > j)
        return ERROR;
    s = p->next;
    p->next = s->next;
    *e = s->data;
    free(s);
    return OK;
}

int main()
{        
    LinkList L;
    ElemType e;
    Status i;
    int j,k;
    i=InitList_1(&L);     // 初始化链表要分配内存
//    printf("初始化L后：ListLength(L)=%d\n",ListLength_1(L));
//    for(j=1;j<=5;j++)
//        i=ListInsert_1(&L,1,j);
//    i=ListInsert_1(&L,7,6);     // 在范围外插入会忽略
//    printf("在L的表头依次插入1～5后：L.data=");
//    ListTraverse_1(L);
//    printf("ListLength(L)=%d\n",ListLength_1(L));
//    i=ListEmpty(L);
//    printf("L是否空：i=%d(1:是 0:否)\n",i);

//    i=ClearList_1(&L);
//    printf("清空L后：ListLength(L)=%d\n",ListLength(L));
//    i=ListEmpty(L);
//    printf("L是否空：i=%d(1:是 0:否)\n",i);

    for(j=1;j<=10;j++)
            ListInsert(&L,j,j);
//    printf("在L的表尾依次插入1～10后：L.data=");
//    ListTraverse(L);
//    printf("ListLength(L)=%d \n",ListLength(L));

    ListInsert(&L,11,11);
//    printf("在L的表头插入0后：L.data=");
    ListTraverse(L);
//    printf("ListLength(L)=%d \n",ListLength(L));

//    GetElem_1(L,5,&e);  // 此处把实参&e地址传进去, 就可以直接修改e变量, 不再需要返回e, 节省内存
//    printf("第5个元素的值为：%d\n",e);
//    for(j=9;j<=11;j++)
//    {
//            k=LocateElem_1(L,j);
//            if(k)
//                    printf("%d是第%d个元素\n",j,k);
//            else
//                    printf("没有值为%d的元素\n",j);
//    }


//    k=ListLength(L); /* k为表长 */
//    for(j=k+1;j>=k;j--)
//    {
//            i=ListDelete_1(&L,j,&e); /* 删除第j个数据 */
//            if(i==ERROR)
//                    printf("删除第%d个数据失败\n",j);
//            else
//                    printf("删除第%d个的元素值为：%d\n",j,e);
//    }
//    printf("依次输出L的元素：");
//    ListTraverse(L);
//
//    j=5;
//    ListDelete(&L,j,&e); /* 删除第5个数据 */
//    printf("删除第%d个的元素值为：%d\n",j,e);
//    printf("依次输出L的元素：");
//    ListTraverse(L);

    i=ClearList(&L);
    printf("\n清空L后：ListLength(L)=%d\n",ListLength(L));
    CreateListHead(&L,20);
    printf("整体创建L的元素(头插法)：");
    ListTraverse(L);

//    i=ClearList(&L);
//    printf("\n删除L后：ListLength(L)=%d\n",ListLength(L));
//    CreateListTail(&L,20);
//    printf("整体创建L的元素(尾插法)：");
//    ListTraverse(L);


    return 0;
}

