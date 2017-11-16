#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int a[4][4];
void play(int y[4])
{
       int k,s=0,note=0;
       for(k=3;k>=0;k--)
       {
          if(y[k]!=0)
          {
              if(s==0||(y[k]!=y[4-s]&&s!=0)||(y[k]==y[4-s]&&note==1))
              {
                 y[3-s]=y[k];
                 s=s+1;
                 note=0;
              }
              else if(note==0)
			  {
			     y[4-s] = 2*y[4-s];
			     note=1;
			  }
          }
       }
       for(k=0;k<4-s;k++) y[k]=0;
}
void turn(int x[4])
{
     int s;
     s = x[0];
     x[0]=x[3];
     x[3]=s;
     s=x[1];
     x[1]=x[2];
     x[2]=s;
}
void Add(int LOC)
{
    int i,j;
    i=LOC/4;
    if(LOC%4!=0) j=LOC%4-1;
    else
	{
      j=3;
	  i=i-1;
    }
    while(a[i][j]!=0)
    {
        if(j<3) j=j+1;
        else
		{
		   i=i+1;
		   j=0;
	    }
	    if(i==3&&j==3)
	    {
	    	i=0;
	    	j=0;
	    }
    }
    if(j==3) a[i][j]=4;
    else     a[i][j]=2;
}
main()
{
      int c[100],d[4],i,j,k,m;
      char b[100],L;
      for(i=0;i<4;i++)
      {
         for(j=0;j<4;j++)
         {
             scanf("%d",&a[i][j]);
             }
      }
      gets(b);  gets(b);
      m = (strlen(b)+1)/2;
      for(i=0;i<m;i++) scanf("%d",&c[i]);
      for(i=0;i<m;i++)
      {
         L=b[2*i];
         switch(L)
         {
            case 'd': for(j=0;j<4;j++)  play(a[j]);
                      break;
            case 'a': for(j=0;j<4;j++)
                      {
                          turn(a[j]);
                          play(a[j]);
                          turn(a[j]);
                      }
                      break;
            case 's': for(j=0;j<4;j++)
                      {
                          for(k=0;k<4;k++) d[k]=a[k][j];
                          play(d);
                          for(k=0;k<4;k++) a[k][j]=d[k];
                      }
                      break;
            case 'w': for(j=0;j<4;j++)
                      {
                          for(k=0;k<4;k++) d[k]=a[k][j];
                          {
                              turn(d);
                              play(d);
                              turn(d);
                          }
                          for(k=0;k<4;k++) a[k][j]=d[k];
                      }
                      break;
         }
         Add(c[i]);
      }
      for(i=0;i<4;i++)
      {
         for(j=0;j<4;j++)
         {
             if(i==3&&j==3) printf("%d\n",a[i][j]);
             else           printf("%d ",a[i][j]);
             }
      }
      system ("pause");
      return 0;
}