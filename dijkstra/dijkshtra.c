#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define max 20000
int d[max];
int q[max];
int use;
/* node type declaration */
typedef struct nodetype1{
    int vertex;
    int weight1;
    int weight2;
    struct nodetype1 *next;
}gnode;
void creategraph(gnode *adj[],int n){
 int i;
 for(i=0;i<n;i++)
    adj[i]=NULL;
}
void inputgraph(gnode *adj[],int n,int x,int y,int z,int r){
  gnode *ptr,*temp;
  temp=NULL;
  ptr=(gnode*)malloc(sizeof(gnode));
  ptr->vertex=y;
  ptr->weight1=z;
  ptr->weight2=r;
  ptr->next=NULL;
  if(adj[x]==NULL)
    adj[x]=ptr;
  else{
    temp=adj[x];
    adj[x]=ptr;
    ptr->next=temp;
  }
}
void printgraph(gnode *adj[],int n){
    int i;
    gnode *temp,*ptr;
    printf("Representation is as\n node->adjacent node-weight\n");
    for(i=0;i<n;i++){
        ptr=adj[i];
        printf("(%d)",i);
        while(ptr!=NULL){
            printf("->%d-%d-%d",ptr->vertex,ptr->weight1,ptr->weight2);
            ptr=ptr->next;
        }
        printf("\n");
    }
}
void initialize(gnode *adj[],int n,int s){
    int i;
    for(i=0;i<n;i++)
        d[i]=99999;
    d[s]=0;
    use=1;
}
int isempty(int n){
    int i,flag=1;
    for(i=0;i<n;i++){
        if(q[i]!=-1){
            flag=0;
            break;
        }
        else
            flag=1;
    }
    return flag;
}
int extractmin(int q[],int n){
    int min,i,temp;
    min=9999;
    for(i=0;i<n;i++){
    if(q[i]!=-1){
        if(d[q[i]]<min){
            temp=q[i];
            min=d[q[i]];
        }
    }
    }
    q[temp]=-1;
    return temp;
}
void relax(int u,int v,int w,int r,int use){
    int a,b;
        a=d[u]+w;
        b=d[u]+r;
        if(d[v]>a || d[v]>b){
        if(a>b || use==0)
            d[v]=a;
        else
        {
            d[v]=b;
            use--;
        }
        }
}
void dijkshtra(gnode *adj[],int n,int s){
    int i,u,a=n;
    gnode *ptr;
    initialize(adj,n,s);
    for(i=0;i<n;i++){
        q[i]=i;
    }
    while(isempty(n)!=1){
        u=extractmin(q,n);
        ptr=adj[u];
        use=1;
        while(ptr!=NULL){
            relax(u,ptr->vertex,ptr->weight1,ptr->weight2,use);
            ptr=ptr->next;
        }
    }
}
/* main function */
int main(){
    gnode *adj1[max];
    int n,i,x,y,z,s,t,j,r,des;
    long int e;
    //printf("Enter the no of test cases:\n");
    scanf("%d",&t);
    for(j=0;j<t;j++){
        printf("Enter the no of nodes:\n");
        scanf("%d",&n);
        printf("Enter the no of edges:\n");
        scanf("%d",&e);
        creategraph(adj1,n);
        //srand(time(NULL));
        //printf("Enter the vertices in which edge exists and their corresponding weight:\n");
        for(i=0;i<e;i++){
            x=1+rand()%n;
            y=1+rand()%n;
            z=1+rand()%6;
            r=1+rand()%200;
            if(x!=y){
            inputgraph(adj1,n,x-1,y-1,z,r);
            inputgraph(adj1,n,y-1,x-1,z,r);
            }
            //inputgraph(adj1,n,x-1,y-1,r);
            //inputgraph(adj1,n,y-1,x-1,r);
        }
        printgraph(adj1,n);
        printf("Enter the source vertex:\n");
        scanf("%d",&s);
        printf("Enter the destination vertex:\n");
        scanf("%d",&des);
        dijkshtra(adj1,n,s-1);
        if(d[des-1]==99999)
            printf("-1");
        else
         printf("%d",d[des-1]);
         printf("\n");
    }
    return 0;
}
