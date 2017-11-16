#include<iostream>
using namespace std;
typedef struct Node
{
    int data;
    struct Node *next;
}PNode;
PNode* CreateList(int n)//生成长为n的循环链表
{
    PNode* head=NULL;
    PNode *s,*r;
    int i;
    for(i=1;i<=n;i++)
    {
        s=(PNode*)malloc(sizeof(PNode));
        s->data=i;
        s->next=NULL;
        if(head==NULL)
            head=s;
        else
            r->next=s;
        r=s;
    }
    r->next=head;
    return head;
}
void Baoshu(PNode* head,int n,int start,int out)
{
    PNode *p,*q;
    int i;
    p=head;
    for(i=1;i<start;i++)//搜索第k个节点
    {
        q=p;
        p=p->next;
    }
    while(p->next!=p)//开始报数，每次判断链表长度大于等于2
    {
        for(i=1;i<out;i++) //搜索第m个节点
        {
            q=p;
            p=p->next;
        }
        q->next=p->next;  //把第m个节点删除
        free(p);
        p=q->next;
    }
    cout<<p->data<<endl;//输出链表只有1个节点时的节点数据
}
int main()
{
    PNode* h;
    int n,start,out;//n:人数，start：从几开始报数，out：报几出列
    cin>>n>>start>>out;
    h=CreateList(n);
    Baoshu(h,n,start,out);
    return 0;
}