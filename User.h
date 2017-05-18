#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

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

typedef struct Priv
{
    char tablename[N];
    char privilege[4];//查增改删
    struct Priv *next;
}Priv,*PrivList;
typedef struct User
{
    char username[N];
    char password[N];
    struct Priv *P;
    struct User *next;
}User,*UserList;
Status InitUserList(UserList &L)
{//建立一个空链表并初始化
    L=(UserList)malloc(sizeof(User));
    L->next=NULL;
    L->P=NULL;
}//InitList
Status InitPrivList(PrivList &L)
{//建立一个空链表并初始化
    L=(PrivList)malloc(sizeof(Priv));
    L->next=NULL;
}//InitList
UserList UserListInsert(UserList &L,PrivList &e,char *username,char *password)
{//在有序顺序表中插入元素e
    UserList s;
    s=(UserList)malloc(sizeof(User));//建立新节点
    s->P=e;s->next=L->next;//新节点元素赋值为e,并指向下一个节点
    L->next=s;//插入元素之前一个节点指向新节点
    strcpy(s->username,username);
    strcpy(s->password,password);
    return s;
}//ListInsert
PrivList PrivListInsert(PrivList &L,char *tablename,char *privilege)
{//在有序顺序表中插入元素e
    PrivList s;
    s=(PrivList)malloc(sizeof(Priv));//建立新节点
    s->next=L->next;//新节点元素赋值为e,并指向下一个节点
    L->next=s;//插入元素之前一个节点指向新节点
    strcpy(s->tablename,tablename);
    strcpy(s->privilege,privilege);
    return s;
}//ListInsert
Status UserListTravel(UserList &L)
{//有序单链表遍历输出
    UserList U;
    PrivList P;
    U=L->next;

    while(U)
    {
        //P=U->P->next
        P=U->P->next;;
        cout<<"Username:"<<U->username<<";Password:"<<U->password<<endl;
        while(P)
        {
            cout<<"Tablename:"<<P->tablename<<endl;
            if(P->privilege[0]=='1') cout<<"select ";
            if(P->privilege[1]=='1') cout<<"insert ";
            if(P->privilege[2]=='1') cout<<"update ";
            if(P->privilege[3]=='1') cout<<"delete ";
            cout<<endl;
            P=P->next;
        }
        U=U->next;
    }
    return OK;
}//ListTravel

#endif // USER_H_INCLUDED
