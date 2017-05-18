#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

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

typedef struct TableAttr
{
    char name[N][N];    //����
    char type[N][N];     //����
    char condition[N][N];//���� ���� Ψһ �ǿ�
}TableAttr,*TableAttrList;
typedef struct Table
{
    char name[N];   //������
    int len;        //����
    struct TableAttr *address;  //��ַ
    struct Table *next;
}Table,*TableList;
Status InitTableList(TableList &L)
{//InitList
    L=(TableList)malloc(sizeof(Table));
    L->next=NULL;
}
TableAttrList CreatTable(TableAttrList &L)
{
    L=(TableAttrList)malloc(sizeof(TableAttr));
    return L;
}
Status OutTable(TableList &p)
{//ListTravel
    int len=p->len;
        cout<<"Table Name:"<<p->name<<endl;
        cout<<"Table Information:"<<endl;
        for(int i=0;i<len;i++)
        {
            cout<<p->address->name[i]<<" "<<p->address->type[i]<<" ";
            if(p->address->condition[i][0]=='1')
                cout<<"����"<<" ";
            if(p->address->condition[i][1]=='1')
                cout<<"����"<<" ";
            if(p->address->condition[i][2]=='1')
                cout<<"����Ϊ��"<<" ";
            if(p->address->condition[i][3]=='1')
                cout<<"Ψһ"<<" ";
            cout<<endl;
        }
    return OK;
}
Status TableListTravel(TableList &L)
{
    TableList p;
    p=L->next;
    int len=p->len;
    while(p)
    {
        cout<<"Table Name:"<<p->name<<endl;
        cout<<"Table Information:"<<endl;
        for(int i=0;i<len;i++)
        {
            cout<<p->address->name[i]<<" "<<p->address->type[i]<<" ";
            if(p->address->condition[i][0]=='1')
                cout<<"����"<<" ";
            if(p->address->condition[i][1]=='1')
                cout<<"����"<<" ";
            if(p->address->condition[i][2]=='1')
                cout<<"����Ϊ��"<<" ";
            if(p->address->condition[i][3]=='1')
                cout<<"Ψһ"<<" ";
            cout<<endl;
        }
        p=p->next;
        if(p)
        len=p->len;
    }
    return OK;
}//ListTravel
TableList TableListInsert(TableList &L,TableAttrList &e)
{//ListInsert
    TableList s;
    s=(TableList)malloc(sizeof(Table));//�����½ڵ�
    s->address=e;s->next=L->next;
    L->next=s;
    return s;
}
Status TableListDelete(TableList &L,char *key)
{//ListDelete
    TableList p,q;
    TableAttrList s;
    p=L;
    while(p->next&&strcmp(p->next->name,key))
    {
        p=p->next;
    }//����������pΪɾ��λ��
    q=p->next;p->next=q->next;s=q->address;
    free(q);free(s);
    return OK;
}


#endif // TABLE_H_INCLUDED
