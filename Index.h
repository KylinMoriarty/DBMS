#ifndef INDEX_H_INCLUDED
#define INDEX_H_INCLUDED

#define TURE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define N 100
typedef int Status;
typedef int TElemType;

#include <iostream>
#include <cstring>
#include <cstdio>
#include <malloc.h>
#include <stdlib.h>
#include "Data.h"
using namespace std;

typedef struct Index
{
    TElemType data;
    struct Data *address;
    struct Index *lchild,*rchild;
}Index,*IndexTree;
typedef struct IndexName
{
    char name[N];
    struct Index *I;//左右孩纸指针
    struct IndexName *next;
}IndexName,*IndexNameList;
void InOrderTraerse(IndexTree &T)
{//中序遍历
    if(T)
    {
        InOrderTraerse(T->lchild);
        cout<<"Sno:"<<T->data<<";"<<"address:"<<T->address<<endl;
        InOrderTraerse(T->rchild);
    }
}
Status SearchINDEX(IndexTree T,TElemType key,IndexTree f,IndexTree &p)
{
    if(!T){p=f;return FALSE;}
    else if(T->data==key) {p=T;return TURE;}
    else if((T->data)>key) return SearchINDEX(T->lchild,key,T,p);
    else return SearchINDEX(T->rchild,key,T,p);

}
Status InsertINDEX(IndexTree &T,DataList &D)
{
    IndexTree p,s;
    if(!SearchINDEX(T,D->data->Sno,NULL,p))
    {
        s=(IndexTree)malloc(sizeof(Index));
        (s->data)=(D->data->Sno);s->lchild=NULL;s->rchild=NULL;
        s->address=D;
        if(!p) T=s;
        else if((p->data)>(D->data->Sno)) p->lchild=s;
        else p->rchild=s;
        return TURE;
    }
    else return FALSE;
}
Status InitIndexNameList(IndexNameList &L)
{
    L=(IndexNameList)malloc(sizeof(IndexName));
    L->next=NULL;
    L->I=NULL;
}//InitList
IndexNameList IndexNameListInsert(IndexNameList &L,char *name)
{
    IndexNameList s;
    s=(IndexNameList)malloc(sizeof(IndexName));//建立新节点
    strcpy(s->name,name);
    s->I=NULL;s->next=L->next;
    L->next=s;
    return s;
}//ListInsert

#endif // INDEX_H_INCLUDED
