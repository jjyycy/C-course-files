#include <stdio.h>
#include <malloc.h>

typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

BiTree Create()//层次建立二叉树
{
    BiTNode *Queue[50];//定义队列
    int num=0,front=1,rear=0,count=1;//初始化队列
    BiTNode *Troot,*T;
    Troot=NULL;
    scanf(" %d",&num);
    while(count<=15)//输入15个数
    {
        T=NULL;
        if(num!=0)
        {
            T=(BiTNode *)malloc(sizeof(BiTNode));
            T->data=num;
            T->lchild=NULL;
            T->rchild=NULL;
        }
        count++;
        rear++;
        Queue[rear]=T;//新结点地址入队
        if(rear==1) Troot=T;//若rear=1，是根结点，用root指向它
        else
        {
            if(T&&Queue[front])//当前结点及其双亲结点都不为空
                if(rear%2==0) //rear为偶，左孩子
                    Queue[front]->lchild=T;
                else//rear为奇，右孩子
                    Queue[front]->rchild=T;
                if(rear%2==1)//rear为奇，两个孩子已处理完
                    front++;
        }
        scanf(" %d",&num);
    }
    return Troot;
}

void zhongxu(BiTree T)//中序遍历二叉树
{
   if(T)
   {
   zhongxu(T->lchild);
   printf("%d ",T->data);
   zhongxu(T->rchild);
   }
}

int main()
{
    BiTNode *tree;
    tree=Create();
    zhongxu(tree);
    printf("\n");
    return 0;
}