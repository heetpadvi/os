#include<stdio.h>
#include<pthread.h>
int a[3][3]={ {1,2,3},{4,5,6},{7,8,9}};
int b[3][3]={{1,2,3},{4,5,6},{7,8,9}};
int c[3][3];
void *multi(void *arg)
{
int i,j,k;
for(i=0;i<3;i++)
{
for(j=0;j<3;j++)
{
c[i][j]=0;
for(k=0;k<3;k++)
{
c[i][j]+=a[i][k] * b[k][j];
}
}
}
}
int main()
{
pthread_t arr[10];
for(int i=0;i<10;i++)
{
int *p;
pthread_create(&arr[i],NULL,multi,(void*)(p));
}
for(int i=0;i<3;i++)
{
pthread_join(arr[i],NULL);
}
printf("matrix multipllication is :- ");
for(int i=0;i<3;i++)
{
for(int j=0;j<3;j++)
{
printf("%d\t",c[i][j]);
}
printf("\n");
}
}
