#include "stdio.h"    
#include "stdlib.h"   

#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status; 

typedef int SElemType; /* SElemType类型根据实际情况而定，这里假设为int */


/* 两栈共享空间结构 */
typedef struct 
{
        SElemType data[MAXSIZE];
        int top1;	/* 栈1栈顶指针 */
        int top2;	/* 栈2栈顶指针 */
}SqDoubleStack;


Status visit(SElemType c)
{
        printf("%d ",c);
        return OK;
}

/*  构造一个空栈S */
Status InitStack(SqDoubleStack *S)
{ 
        S->top1=-1;
        S->top2=MAXSIZE;        // 栈2第一个元素从MAXSIZE-1开始
        return OK;
}

/* 把S置为空栈 */
Status ClearStack(SqDoubleStack *S)
{ 
        S->top1=-1;
        S->top2=MAXSIZE;
        return OK;
}

/* 若栈S为空栈，则返回TRUE，否则返回FALSE */
Status StackEmpty(SqDoubleStack S)
{ 
        if (S.top1==-1 && S.top2==MAXSIZE)      // 两个都为空栈
                return TRUE;
        else
                return FALSE;
}

/* 返回S的元素个数，即栈的长度 */
int StackLength(SqDoubleStack S)
{ 
        return (S.top1+1)+(MAXSIZE-S.top2);     // 栈2如(MAXSIZE-1) - (MAXSIZE-3) + 1 = 3, 其中S.top2==MAXSIZE-3
}

/* 插入元素e为新的栈顶元素 */
Status Push(SqDoubleStack *S,SElemType e,int stackNumber)
{
        if (S->top1+1==S->top2)	/* 栈已满，不能再push新元素了 */
                return ERROR;	
        if (stackNumber==1)			/* 栈1有元素进栈 */
                S->data[++S->top1]=e; /* 若是栈1则先top1+1自增后再给数组元素赋值。S->top1从-1开始加 */
        else if (stackNumber==2)	/* 栈2有元素进栈 */
                S->data[--S->top2]=e; /* 若是栈2则先top2-1自减后再给数组元素赋值。S->top2从MAXSIZE=20开始减 */
        return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(SqDoubleStack *S,SElemType *e,int stackNumber)
{ 
        if (stackNumber==1) 
        {
                if (S->top1==-1) 
                        return ERROR; /* 说明栈1已经是空栈，溢出 */
                *e=S->data[S->top1--]; /* 将栈1的栈顶元素出栈, 先取值再自减 */
        }
        else if (stackNumber==2)
        { 
                if (S->top2==MAXSIZE) 
                        return ERROR; /* 说明栈2已经是空栈，溢出 */
                *e=S->data[S->top2++]; /* 将栈2的栈顶元素出栈, 先取值再自增, 注意栈2的栈顶是远离MAXSIZE-1那一侧的 */
        }
        return OK;
}

Status StackTraverse(SqDoubleStack S)
{
        int i;
        i=0;
        while(i<=S.top1)
        {
                visit(S.data[i++]);
        }
        i=S.top2;   // 从S.top2处开始取值, S.top2能取到
        while(i<MAXSIZE)
        {
                visit(S.data[i++]);
        }
        printf("\n");
        return OK;
}

int main()
{
        int j;
        SqDoubleStack s;
        int e;
        if(InitStack(&s)==OK)
        {
                for(j=1;j<=5;j++)
                        Push(&s,j,1);
                for(j=MAXSIZE;j>=MAXSIZE-2;j--)
                        Push(&s,j,2);
        }

        printf("栈中元素依次为：");
        StackTraverse(s);

        printf("当前栈中元素有%d个\n",StackLength(s));

        Pop(&s,&e,2);
        printf("弹出的栈顶元素 e=%d\n",e);
        printf("栈空否：%d(1:空 0:否)\n",StackEmpty(s));

        for(j=6;j<=MAXSIZE-2;j++)   // 又把18压回去了, 不过是压到栈1
                Push(&s,j,1);

        printf("栈中元素依次为：");
        StackTraverse(s);

        printf("栈满否：%d(0:满 1:否)\n",Push(&s,100,1));     // 栈满则push不进去, 返回ERROR==0

        
        ClearStack(&s);     // 清空栈跟清空顺序表一样, 只是重置指针
        printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(s));
        
        return 0;
}