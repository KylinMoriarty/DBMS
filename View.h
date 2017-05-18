#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED
#define TURE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define N 100

#include <iostream>
#include <cstring>
#include <cstdio>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

typedef int Status;

typedef struct ViewAttr
{
    char name[N][N];
    char type[N][N];
}ViewAttr,*ViewAttrList;
typedef struct View
{
    char name[N];
    int len;
    struct ViewAttr *address;
    struct View *next;
}View,*ViewList;
Status InitViewList(ViewList &L)
{
    L=(ViewList)malloc(sizeof(View));
    L->next=NULL;
}//InitList
ViewAttrList CreatView(ViewAttrList &L)
{
    L=(ViewAttrList)malloc(sizeof(ViewAttr));
    return L;
}
Status OutView(ViewList &p)
{
    int len=p->len;
        cout<<"View Name:"<<p->name<<endl;
        cout<<"View Information:"<<endl;
        for(int i=0;i<len;i++)
        {
            cout<<p->address->name[i]<<" "<<p->address->type[i]<<endl;
        }
    return OK;
}//ListTravel
Status ViewListTravel(ViewList &L)
{
    ViewList p;
    p=L->next;
    int len=p->len;
    while(p)
    {
        cout<<"View Name:"<<p->name<<endl;
        cout<<"View Information:"<<endl;
        for(int i=0;i<len;i++)
        {
            cout<<p->address->name[i]<<" "<<p->address->type[i]<<endl;
        }
        p=p->next;
        if(p)
        len=p->len;
    }
    return OK;
}//ListTravel
ViewList ViewListInsert(ViewList &L,ViewAttrList &e)
{
    ViewList s;
    s=(ViewList)malloc(sizeof(View));//建立新节点
    s->address=e;s->next=L->next;
    L->next=s;
    return s;
}//ListInsert
Status ViewListDelete(ViewList &L,char *key)
{
    ViewList p,q;
    ViewAttrList s;
    p=L;
    while(p->next&&strcmp(p->next->name,key))
    {
        p=p->next;
    }//遍历单链表，p为删除位置
    q=p->next;p->next=q->next;s=q->address;
    free(q);free(s);//被删除元素的值赋给e，释放被删除的结点
    return OK;
}//ListDelete

#endif // VIEW_H_INCLUDED
