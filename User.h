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
    char privilege[4];//������ɾ
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
{//����һ����������ʼ��
    L=(UserList)malloc(sizeof(User));
    L->next=NULL;
    L->P=NULL;
}//InitList
Status InitPrivList(PrivList &L)
{//����һ����������ʼ��
    L=(PrivList)malloc(sizeof(Priv));
    L->next=NULL;
}//InitList
UserList UserListInsert(UserList &L,PrivList &e,char *username,char *password)
{//������˳����в���Ԫ��e
    UserList s;
    s=(UserList)malloc(sizeof(User));//�����½ڵ�
    s->P=e;s->next=L->next;//�½ڵ�Ԫ�ظ�ֵΪe,��ָ����һ���ڵ�
    L->next=s;//����Ԫ��֮ǰһ���ڵ�ָ���½ڵ�
    strcpy(s->username,username);
    strcpy(s->password,password);
    return s;
}//ListInsert
PrivList PrivListInsert(PrivList &L,char *tablename,char *privilege)
{//������˳����в���Ԫ��e
    PrivList s;
    s=(PrivList)malloc(sizeof(Priv));//�����½ڵ�
    s->next=L->next;//�½ڵ�Ԫ�ظ�ֵΪe,��ָ����һ���ڵ�
    L->next=s;//����Ԫ��֮ǰһ���ڵ�ָ���½ڵ�
    strcpy(s->tablename,tablename);
    strcpy(s->privilege,privilege);
    return s;
}//ListInsert
Status UserListTravel(UserList &L)
{//��������������
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
