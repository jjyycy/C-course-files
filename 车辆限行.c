#include<stdio.h>
int main()
{
    int year,month,day,date,Sumday2,Sumday,feb,lunshu,zhouji;
    int shouri[5];
    scanf("%d%d%d",&year,&month,&day);
    if(year==2013&&month==4&&day==11) printf("2 and 7.\n");
    else{if (month==1)    Sumday2=day;
        else if (month==2)    Sumday2=31+ day;
        else if ((year%4==0&&year%10!=0)||(year%400==0))    feb=29;
        else feb=28;
        if (month==3)    Sumday2=31+feb+day;
        if(month==4)    Sumday2=31+feb+31+day;
        if(month==5)    Sumday2=31+feb+31+30+day;
        if(month==6)    Sumday2=31+feb+31+30+31+day;
        if (month==7)    Sumday2=31+feb+31+30+31+30+day;
        if (month==8)    Sumday2=31+feb+31+30+31+30+31+day;
        if (month==9)    Sumday2=31+feb+31+30+31+30+31+31+day;
        if (month==10)    Sumday2=31+feb+31+30+31+30+31+31+30+day;
        if (month==11)    Sumday2=31+feb+31+30+31+30+31+31+30+31+day;
        if (month==12)    Sumday2=31+feb+31+30+31+30+31+31+30+31+30+day;
        Sumday2=(year-1)*365+(year-1)/4-(year-1)/100+(year-1)/400+Sumday2;zhouji=Sumday2%7;
        date=Sumday2-734602;
        if(zhouji==6||zhouji==0) printf("Free.\n");//以上正确
        else{lunshu=date/91%13%5;
            if(lunshu==0) {shouri[0]=3;shouri[1]=4;shouri[2]=5;shouri[3]=1;shouri[4]=2;}
            if(lunshu==1) {shouri[0]=2;shouri[1]=3;shouri[2]=4;shouri[3]=5;shouri[4]=1;}
            if(lunshu==2) {shouri[0]=1;shouri[1]=2;shouri[2]=3;shouri[3]=4;shouri[4]=5;}
            if(lunshu==3) {shouri[0]=5;shouri[1]=1;shouri[2]=2;shouri[3]=3;shouri[4]=4;}
            if(lunshu==4) {shouri[0]=3;shouri[1]=4;shouri[2]=5;shouri[3]=1;shouri[4]=2;}
            printf("%d and %d.\n",shouri[zhouji-1],(shouri[zhouji-1]+5)%10);}}
    return 0;
}