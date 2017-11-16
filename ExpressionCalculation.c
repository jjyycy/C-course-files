#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
char oprset[8]={'+','-','*','/','(',')','#','^'};//符号集
unsigned char table[8][8] =
        {// 运算符优先级表
                //seta1'+' '-' '*' '/' '(' ')' '#' '^' theta2
                /*'+'*/'>','>','<','<','<','>','>','<',
                /*'-'*/'>','>','<','<','<','>','>','<',
                /*'*'*/'>','>','>','>','<','>','>','<',
                /*'/'*/'>','>','>','>','<','>','>','<',
                /*'('*/'<','<','<','<','<','=',' ','<',
                /*')'*/'>','>','>','>',' ','>','>','>',
                /*'#'*/'<','<','<','<','<',' ','=','<',
                /*'^'*/'>','>','>','>','<','>','>','>'
        };
typedef struct Fuhao//存符号的栈
{
    char c;
    struct Fuhao *next;
}fuhao;
typedef struct Shu//存数的栈
{
    int n;
    struct Shu *next;
}shu;
fuhao *Push_fuhao(fuhao *s,char c)//push进符号栈
{
    fuhao *p=(fuhao*)malloc(sizeof(fuhao));
    p->c=c;
    p->next=s;
    return p;
}
shu *Push_shu(shu *s,int n)//push进数栈
{
    shu *p=(shu*)malloc(sizeof(shu));
    p->n=n;
    p->next=s;
    return p;
}
fuhao *Pop_fuhao(fuhao *s)//pop一个符号
{
    fuhao *q=s;
    s=s->next;
    free(q);
    return s;
}
shu *Pop_shu(shu *s)//pop一个数
{
    shu *q=s;
    s=s->next;
    free(q);
    return s;
}

int calculate(int a,unsigned char theta, int b)//运算函数
{
    int tempresult;
    switch(theta)
    {
        case '+': tempresult=a+b; break;
        case '-': tempresult=a-b; break;
        case '*': tempresult=a*b; break;
        case '/': if(b==0)
            {
                printf("Divide 0.\n");tempresult=99;
            }
            else tempresult=a/b;
            break;

        case '^': tempresult=pow(a,b); break;
        default : tempresult=0;
    }
    return tempresult;
}

int judge(char op)//判断是不是符号
{
    int flag=0;
    for (int i=0;i<8; i++)
    {
        if (op==oprset[i])
            flag= 1;
    }
    return flag;
}

int judgeop(char op)//判断是不是加减乘除乘方
{
    int flag=0;
    if (op=='+'||op=='-'||op=='*'||op=='/'||op=='^')
        flag= 1;
    return flag;
}

int findset(char op)//记录是哪个符号
{
    for(int i=0;i<8; i++)
    {
        if (op==oprset[i])
            return i;
    }
}

char priority(char theta1, char theta2)//返回优先级>,<,=
{
    int a,b;
    a=findset(theta1);
    b=findset(theta2);
    return table[a][b];
}

int EvaluateExpression(char* s)
{
    int result;
    fuhao *operation=NULL;//符号栈
    shu *number=NULL;//数栈
    char tempnum[5]={0};
    int Data,a,b;
    char theta,*c,end[]={'#','\0'};
    operation=Push_fuhao(operation,'#');//结尾符#进栈
    c=strcat(s,end);//c是首地址
    int j,left=0,right=0;
    for(j=0;j<strlen(c);j++)
    {
        if(c[j]=='(')
            left++;
        else if(c[j]==')')
            right++;
    }
    while (*c!='#'||operation->c!='#')
    {
        ////////////////////查错//////////////////
        if(!judge(*c)&&(*(c+1))=='(') //数字后面出现左括号
        {
            printf("error.\n");goto w;
        }
        if(!judge(*(c+1))&&(*(c))==')') //数字前面出现右括号
        {
            printf("error.\n");goto w;
        }
        if(*c=='('&&((*(c+1))=='+'||(*(c+1))=='*'||(*(c+1))=='/'||(*(c+1))==')')) //左括号后面出现加、乘、除以及右括号
        {
            printf("error.\n");goto w;
        }
        if(judgeop(*c)&&(judgeop((*(c+1)))||(*(c+1))==')')) //加减乘除后面出现加减乘除及右括号
        {
            printf("error.\n");goto w;
        }
        if(judge(*c)&&(*c)!='#'&&(*(c+1))=='#'&&*c!=')') //表达式末尾出现加减乘除及右括号
        {
            printf("error.\n");goto w;
        }
        if(*c==')'&&(*(c+1))=='(') //右括号后面出现左括号
        {
            printf("error.\n");goto w;
        }
        if(left!=right) //括号不匹配
        {
            printf("error.\n");goto w;
        }
        ////////////////////////////////////////
        if (judge(*c)==0)//数
        {
            end[0]=*c;
            strcat(tempnum,end);
            c++;
            if (judge(*c)==1)
            {
                Data=atoi(tempnum);//字符串转换成int
                number=Push_shu(number, Data);//进数栈
                memset(tempnum,'\0',5*sizeof(char));
            }
        }
        else//符号
        {
            switch (priority(operation->c, *c))
            {
                case '<'://栈顶符号优先级低
                    operation=Push_fuhao(operation, *c);//进栈
                    c++;
                    break;
                case '='://脱括号
                    operation=Pop_fuhao(operation);
                    c++;
                    break;
                case '>'://栈顶符号优先级高
                    theta=operation->c;
                    operation=Pop_fuhao(operation);//出栈
                    b=number->n;number=Pop_shu(number);
                    a=number->n;number=Pop_shu(number);
                    result=calculate(a,theta,b);
                    if (result==99) goto w;
                    else
                        number=Push_shu(number,result);//结果入栈
                    break;
            }
        }
    }
    return number->n;
    w:return 99;//记一个奇怪的数表示它是错的
}

int main()
{
    char s[100];int n,i;
    scanf("%d",&n);
    getchar();
    for (i=1;i<=n;i++)
    {
        gets(s);//录入表达式s
        if(EvaluateExpression(s)!=99)
            printf("%d\n",EvaluateExpression(s));//输出结果
        else;
    }

    return 0;
}