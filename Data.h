#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#define TURE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define N 100
typedef int Status;

#include <iostream>
#include <cstring>
#include <cstdio>
#include <malloc.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

typedef struct Value
{
    int Sno;
    char Sname[10];
    char Ssex[2];
    int Sage;
    char Sdept[10];
}Value,*ValueList;
typedef struct Data//定义新类型
{
    struct Value *data;
    struct Data *next;
}Data,*DataList;
typedef struct DataName//定义新类型
{
    char DataName[N];
    struct Data *D;
    struct DataName *next;
}DataName,*DataNameList;
Status InitDataNameList(DataNameList &L)
{//建立一个空链表并初始化
    L=(DataNameList)malloc(sizeof(DataName));
    //L->DataName=NULL;
    L->D=NULL;
    L->next=NULL;
}//InitList
Status InitDataList(DataList &L)
{//建立一个空链表并初始化
    L=(DataList)malloc(sizeof(Data));
    L->data=NULL;
    L->next=NULL;
}//InitList
ValueList CreatValue(ValueList &L,int Sno,char *Sname,char *Ssex,int Sage,char *Sdept)
{
    L=(ValueList)malloc(sizeof(Value));
    L->Sno=Sno;L->Sage=Sage;
    strcpy(L->Sname,Sname);
    strcpy(L->Ssex,Ssex);
    strcpy(L->Sdept,Sdept);
    return L;
}
Status output(ValueList &L)
{
    if(L!=NULL)
    cout<<setw(12)<<L->Sno<<setw(12)<<L->Sname<<setw(12)<<L->Ssex<<setw(12)<<L->Sage<<setw(12)<<L->Sdept<<endl;
    return OK;
}
Status DataListTravel(DataList &L)
{//有序单链表遍历输出
    DataList p;
    cout<<setw(12)<<"Sno"<<setw(12)<<"Sname"<<setw(12)<<"Ssex"<<setw(12)<<"Sage"<<setw(12)<<"Sdept"<<endl;
    p=L->next;
    while(p)
    {
        output(p->data);
        p=p->next;
    }
    return OK;
}//ListTravel
Status DataNameListTravel(DataNameList &L)
{//有序单链表遍历输出
    DataNameList p;
    cout<<setw(12)<<"Sno"<<setw(12)<<"Sname"<<setw(12)<<"Ssex"<<setw(12)<<"Sage"<<setw(12)<<"Sdept"<<endl;
    p=L->next;
    while(p)
    {
        output(p->D->data);
        cout<<"......................"<<endl;
        p=p->next;
    }
    return OK;
}//ListTravel
DataList DataListInsert(DataList &L,ValueList &e)
{//在有序顺序表中插入元素e
    DataList s;
    s=(DataList)malloc(sizeof(Data));//建立新节点
    s->data=e;s->next=L->next;//新节点元素赋值为e,并指向下一个节点
    L->next=s;//插入元素之前一个节点指向新节点
    return s;
}//ListInsert
DataNameList DataNameListInsert(DataNameList &L,DataList &e,char *name)
{//在有序顺序表中插入元素e
    DataNameList s;
    s=(DataNameList)malloc(sizeof(DataName));//建立新节点
    strcpy(s->DataName,name);
    s->D=e;s->next=L->next;//新节点元素赋值为e,并指向下一个节点
    L->next=s;//插入元素之前一个节点指向新节点
    return s;
}//ListInsert
Status DataListDelete(DataList &p)
{//在有序单链表L中删除第i个元素，并用e返回其值
    DataList q;
    ValueList s;
    q=p->next;p->next=q->next;s=q->data;q->data=NULL;
    free(s);free(q);//被删除元素的值赋给e，释放被删除的结点
    return OK;
}//ListDelete



#endif // DATA_H_INCLUDED
