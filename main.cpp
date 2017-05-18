#define TURE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define N 100
#define MAX 1000

#include <iostream>
#include <cstring>
#include <cstdio>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <conio.h>
#include <sstream>
#include <io.h>
#include "View.h"
#include "Data.h"
#include "Index.h"
#include "Table.h"
#include "User.h"

using namespace std;

ViewList V;
TableList T;
DataNameList DN;
//DataList D;
IndexNameList I;
UserList U;
UserList NowUser;
char username[N];
char sql[MAX],sqltmp[MAX];

int AddView()//(ViewList &V)
{
    //View
    ViewAttrList VA,VA2;
    ViewList Vtemp;

    char viewattrname[N][N]={"name","sex"};
    char viewattrtype[N][N]={"char[10]","char[2]"};
    char viewname[N]="student";

    //int viewlen=2;
    int viewlen=0;
    CreatView(VA);
    //CreatView(VA2);
    for(int i=0;i<viewlen;i++)
    {
        strcpy(VA->name[i],viewattrname[i]);
        strcpy(VA->type[i],viewattrtype[i]);
        //strcpy(VA2->name[i],viewattrname[i]);
        //strcpy(VA2->type[i],viewattrtype[i]);
    }

    Vtemp=ViewListInsert(V,VA);
    strcpy(Vtemp->name,viewname);
    Vtemp->len=viewlen;
    //Vtemp=ViewListInsert(V,VA2);
    //strcpy(Vtemp->name,viewname);
    //Vtemp->len=viewlen;

    //ViewListTravel(V);
    return 0;
}
int AddTable()//(TableList &T)
{
    //Table

    TableAttrList TA,TA2;
    TableList Ttemp;
    IndexNameList Itemp;

    char Tableattrname[N][N]={"Sno","Sname","Ssex","Sage","Sdept"};
    char Tableattrtype[N][N]={"int","char[10]","char[2]","int","char[10]"};
    char Tableattrcondition[N][N]={"1011","0010","0010","0010","0100"};
    char Tablename[N]="student";
    char Indexname[N]="student";

    int Tablelen=5;
    CreatTable(TA);
    //CreatTable(TA2);
    InitIndexNameList(I);
    IndexNameListInsert(I,Indexname);

    for(int i=0;i<Tablelen;i++)
    {
        strcpy(TA->name[i],Tableattrname[i]);
        strcpy(TA->type[i],Tableattrtype[i]);
        strcpy(TA->condition[i],Tableattrcondition[i]);
        //strcpy(TA2->name[i],Tableattrname[i]);
        //strcpy(TA2->type[i],Tableattrtype[i]);
        //strcpy(TA2->condition[i],Tableattrcondition[i]);
    }

    Ttemp=TableListInsert(T,TA);
    strcpy(Ttemp->name,Tablename);
    Ttemp->len=Tablelen;

    //Ttemp=TableListInsert(T,TA2);
    //strcpy(Ttemp->name,Tablename);
    //Ttemp->len=Tablelen;

    //TableListTravel(T);

    return 0;

}
int AddData()//(DataList &D)
{
    char DataName[N]={"student"};
    ValueList VA;
    DataList D;
    InitDataList(D);
    DataNameListInsert(DN,D,DataName);
    DataList Dtemp;


    char SnameValue[N][N]={"wangqilin","qiwenkai","sunchonggao","songzhenhua"};
    char SsexValue[N][N]={"m","m","m","w"};
    char SdeptValue[N][N]={"is","is","cs","cs"};
    int SnoValue[N]={10,11,12,13};
    int SageValue[N]={21,22,21,20};

    for(int i=0;i<4;i++)
    {
        CreatValue(VA,SnoValue[i],SnameValue[i],SsexValue[i],SageValue[i],SdeptValue[i]);
        Dtemp=DataListInsert(D,VA);
        InsertINDEX(I->next->I,Dtemp);
        if(i==0)
        DN->D=Dtemp;//保留初值
    }

    //DataNameList DNtemp=DN->next;
    //while(DNtemp)
    //{
      //  if(strcmp(DNtemp->DataName,"student")==0)
      //  {DataListTravel(DNtemp->D);}
      //  DNtemp=DNtemp->next;
    //}
    //cout<<endl<<endl;

    //InOrderTraerse(I->I);

    return 0;
}
int AddUser()
{
    UserList Utemp;
    PrivList P;
    char username[N][N]={"kylin1","kylin2","kylin3","kylin4"};
    char password[N][N]={"1","2","3","4"};
    char tablename[N]={"student"};
    char privilege[N][N]={"1111","1110","1100","1000"};//查增改删

    for(int i=0;i<4;i++)
    {
        InitPrivList(P);
        Utemp=UserListInsert(U,P,username[i],password[i]);
        PrivListInsert(Utemp->P,tablename,privilege[i]);
    }

   // UserListTravel(U);

    return 0;
}

int login()
{

    char password[N];
    int right=0;
    UserList UP;
    while(right==0)
    {
        cout<<"please input username:";
        gets(username);
        cout<<"please input password:";
        gets(password);
        UP=U->next;
        while(UP)
        {
            if(strcmp(username,UP->username)==0&&strcmp(password,UP->password)==0)
            {
                right=1;
                NowUser=UP;
                break;
            }
            UP=UP->next;
        }
        if(right==1) {cout<<"登录成功"<<endl;break;}
        else {cout<<"用户名或密码错误,请重新输入!"<<endl;}
    }
    return right;
}
void lower(char *s)                   //将输入的大写字母转化为小写字母
{
    int len = strlen(s);
    for(int i = 0; i < len; ++i)
    {
        if(s[i] >= 65 && s[i] <= 90) s[i] += 32;
    }
}
int read()                              //读入SQL语句，并进行格式化分离单词，以分号结束，ESC退出整个程序
{
    char c;
    int i;
    cout<<"请输入命令:";
    for(i = 0; c = getch(); i++)
    {
        if(c == 27)
            exit(0);            //ESC退出
        if(c == 8)                      //退格
        {
            if(sqltmp[i-1]==0)
            i -= 2;i -= 2;
            if(i < -1)
                i = -1;
            system("cls");
            cout<<"请输入命令:";
            for(int j = 0; j <= i; j++)
            {
                if(sqltmp[j] == 13)
                    cout<<endl;
                if(sqltmp[j] != 0)
                cout<<sqltmp[j];
            }
            continue;
        }
        sqltmp[i] = c;
        if(c==13) cout<<endl;
        else cout<<c;
        if(c == ';') break;
        if(c == 13)    sql[i] = ' ';
        else if(c == '(' || c == ')' || c == '\'' || c == '\n') sql[i] = ' ';
        else if(c == ','||c == '='|| c== '<'||c == '>')
        {
            sql[i] = ' ';
            sql[i + 1] = c;
            sql[i + 2] = ' ';
            sqltmp[i+1] = 0;
            sqltmp[i+2] = 0;
            i += 2;
        }
        else  sql[i] = c;
    }
    sql[i] = 0;
    cout<<endl;
    lower(sql);
    //cout<<sql;
    return 0;
}
int help_fun()
{
    char tmp[N];
    stringstream ss(sql);
    ss>>tmp;ss>>tmp;
    if(strcmp(tmp,"database")==0)
    {
        IndexNameList IN=I->next;
        cout<<endl;
        ViewListTravel(V);
        DataList D;
        DN=DN->next;
        D=DN->D;
        if(D!=NULL)
        DataListTravel(D);
        cout<<endl;
        TableListTravel(T);
        cout<<endl;
        //InitDataList(D);

        cout<<endl;
        while(IN)
        {
            cout<<"Indxename:"<<IN->name<<endl;
            InOrderTraerse(IN->I);
            IN=IN->next;
        }
    }
    else if(strcmp(tmp,"table")==0)
    {
        TableList TL=T->next;
        ss>>tmp;
        while(TL&&strcmp(tmp,TL->name)!=0)
        {
            TL=TL->next;
        }
        if(TL) OutTable(TL);
        else cout<<"not found!"<<endl;
    }
    else if(strcmp(tmp,"view")==0)
    {
        ViewList VL=V->next;
        ss>>tmp;
        while(VL&&strcmp(tmp,VL->name)!=0)
        {
            VL=VL->next;
        }
        if(VL) {OutView(VL);

        DataList D;
        DN=DN->next;
        D=DN->D;
        if(D!=NULL)
        DataListTravel(D);
        cout<<endl;

        }
        else cout<<"not found!"<<endl;
    }
    else if(strcmp(tmp,"index")==0)
    {
        IndexNameList IL=I->next;
        ss>>tmp;
        while(IL&&strcmp(tmp,IL->name)!=0)
        {
            IL=IL->next;
        }
        if(IL) {cout<<"Indxename:"<<IL->name<<endl;InOrderTraerse(IL->I);}
        else cout<<"not found!"<<endl;
    }
    else if(strcmp(tmp,"users")==0)
    {
        if(U) UserListTravel(U);
        else cout<<"not found!"<<endl;
    }
    else cout<<"输入错误!请输入database或index或view或table"<<endl;
    return 0;
}
int grant_fun()
{
    char tmp[N],NowUP[N];
    UserList Utemp;
    PrivList Ptemp;
    stringstream ss(sql);
    ss>>tmp;
    if(0 == strcmp(tmp,"grant"))
    {
        char g[N]={"0000"};
        char gname[N],guser[N];
        Utemp=U->next;
        ss>>tmp;
        while(strcmp(tmp,"on")!=0)
        {
            if(strcmp(tmp,"select")==0) g[0]='1';
            if(strcmp(tmp,"insert")==0) g[1]='1';
            if(strcmp(tmp,"update")==0) g[2]='1';
            if(strcmp(tmp,"delete")==0) g[3]='1';
            ss>>tmp;
        }
        //cout<<g;
        ss>>tmp;ss>>gname;ss>>tmp;ss>>guser;//to
        //cout<<gname<<"   "<<guser<<"   "<<endl;

        Ptemp=NowUser->P->next;
        while(Ptemp&&strcmp(Ptemp->tablename,gname)!=0){Ptemp=Ptemp->next;}
        if(Ptemp) strcpy(NowUP,Ptemp->privilege);
        //cout<<NowUP<<endl;
        if(NowUP[0]=='1'&&g[0]=='1') g[0]=='1';
        if(NowUP[1]=='1'&&g[1]=='1') g[1]=='1';
        if(NowUP[2]=='1'&&g[2]=='1') g[2]=='1';
        if(NowUP[3]=='1'&&g[3]=='1') g[3]=='1';
        //cout<<g;

        while(Utemp&&strcmp(Utemp->username,guser)!=0){Utemp=Utemp->next;}
        Ptemp=Utemp->P->next;
        while(Ptemp&&strcmp(Ptemp->tablename,gname)!=0){Ptemp=Ptemp->next;}
        if(g[0]=='1') Ptemp->privilege[0]='1';
        if(g[1]=='1') Ptemp->privilege[1]='1';
        if(g[2]=='1') Ptemp->privilege[2]='1';
        if(g[3]=='1') Ptemp->privilege[3]='1';

        cout<<endl;
        cout<<"用户 "<<guser<<" 已获得对 "<<gname<<" 的 ";
        if(g[0]=='1') cout<<"select ";
        if(g[1]=='1') cout<<"insert ";
        if(g[2]=='1') cout<<"update ";
        if(g[3]=='1') cout<<"delete ";
        cout<<"权限"<<endl<<endl;;

    }
    else
    {
        char r[N]={"1111"};
        char rname[N],ruser[N];
        Utemp=U->next;
        ss>>tmp;
        while(strcmp(tmp,"on")!=0)
        {
            if(strcmp(tmp,"select")==0) r[0]='0';
            if(strcmp(tmp,"insert")==0) r[1]='0';
            if(strcmp(tmp,"update")==0) r[2]='0';
            if(strcmp(tmp,"delete")==0) r[3]='0';
            ss>>tmp;
        }
        ss>>tmp;ss>>rname;ss>>tmp;ss>>ruser;

        Ptemp=NowUser->P->next;
        while(Ptemp&&strcmp(Ptemp->tablename,rname)!=0){Ptemp=Ptemp->next;}
        if(Ptemp) strcpy(NowUP,Ptemp->privilege);
        if(NowUP[0]=='1'&&r[0]=='0') r[0]=='0';
        if(NowUP[1]=='1'&&r[1]=='0') r[1]=='0';
        if(NowUP[2]=='1'&&r[2]=='0') r[2]=='0';
        if(NowUP[3]=='1'&&r[3]=='0') r[3]=='0';

        while(Utemp&&strcmp(Utemp->username,ruser)!=0){Utemp=Utemp->next;}
        Ptemp=Utemp->P->next;
        while(Ptemp&&strcmp(Ptemp->tablename,rname)!=0){Ptemp=Ptemp->next;}
        if(r[0]=='0') Ptemp->privilege[0]='0';
        if(r[1]=='0') Ptemp->privilege[1]='0';
        if(r[2]=='0') Ptemp->privilege[2]='0';
        if(r[3]=='0') Ptemp->privilege[3]='0';

        cout<<endl;
        cout<<"已移除用户 "<<ruser<<" 对 "<<rname<<" 的 ";
        if(r[0]=='0') cout<<"select ";
        if(r[1]=='0') cout<<"insert ";
        if(r[2]=='0') cout<<"update ";
        if(r[3]=='0') cout<<"delete ";
        cout<<"权限"<<endl<<endl;
    }
    //UserListTravel(U);
    return 0;
}
int insert_fun()
{
    PrivList Ptemp;
    Ptemp=NowUser->P->next;

    DataNameList DNtemp=DN->next;
    DataList D,Dtemp,DD;
    ValueList VA;

    char tmp[N],Tname[N];
    char SnameValue[N],SsexValue[N],SdeptValue[N];
    int SnoValue,SageValue;
    stringstream ss(sql);
    ss>>tmp;ss>>tmp;ss>>Tname;ss>>tmp;//insert into student values

    while(Ptemp&&strcmp(Ptemp->tablename,Tname)!=0){Ptemp=Ptemp->next;}
    if(Ptemp&&Ptemp->privilege[1]=='1')
    {
        while(DNtemp&&strcmp(DNtemp->DataName,Tname)!=0){DNtemp=DNtemp->next;}
        D=DNtemp->D;
        if(strcmp(Tname,"student")==0)
        {
            ss>>SnoValue;ss>>tmp;    //sno ,
            ss>>SnameValue;ss>>tmp;   //sname ,
            ss>>SsexValue;ss>>tmp;   //ssex ,
            ss>>SageValue;ss>>tmp;   //sage ,
            ss>>SdeptValue;         //sdept
            CreatValue(VA,SnoValue,SnameValue,SsexValue,SageValue,SdeptValue);

            DD=DN->D;
            int t=0;
            while(DD) {if(DD->data->Sno==SnoValue) {t=1;break;}DD=DD->next;}
            if(t==0)
            {Dtemp=DataListInsert(D,VA);
            InsertINDEX(I->next->I,Dtemp);
            cout<<"成功插入了一个元组!"<<endl;
            }
            else
            {
                cout<<"主键必须唯一，请重新输入"<<endl;
            }
        }

        //DataListTravel(DNtemp->D);
    }

    else{cout<<"您没有对该表的插入权限!"<<endl;}
    return 0;
}
int update_fun()
{
    PrivList Ptemp;
    Ptemp=NowUser->P->next;

    DataNameList DNtemp=DN->next;
    DataList D,Dtemp;
    ValueList VA;

    char tmp[N],Tname[N],Aname[N],SAname[N];
    char SnameValue[N],SsexValue[N],SdeptValue[N];
    int SnoValue,SageValue;
    char CSname[N],CSsex[N],CSdept[N];
    int CSno,CSage;
    stringstream ss(sql);
    ss>>tmp;ss>>Tname;


    while(Ptemp&&strcmp(Ptemp->tablename,Tname)!=0){Ptemp=Ptemp->next;}
    if(Ptemp&&Ptemp->privilege[2]=='1')
    {
        while(DNtemp&&strcmp(DNtemp->DataName,Tname)!=0){DNtemp=DNtemp->next;}
        D=DNtemp->D;
        //DataListTravel(DNtemp->D);
        if(strcmp(Tname,"student")==0)
        {
            int i=0;
            ss>>tmp;ss>>Aname;ss>>tmp;//ss>>Avalue;//待更新
            if(strcmp(Aname,"sno")==0) ss>>CSno;
            else if(strcmp(Aname,"sname")==0) ss>>CSname;
            else if(strcmp(Aname,"ssex")==0) ss>>CSsex;
            else if(strcmp(Aname,"sage")==0) ss>>CSage;
            else if(strcmp(Aname,"sdept")==0) ss>>CSdept;
            ss>>tmp;ss>>SAname;
            if(strcmp(SAname,"sno")==0)
            {
                ss>>tmp;ss>>SnoValue;//条件
                D=D->next;
                while(D)
                {

                    if(D->data->Sno==SnoValue)
                    {
                        i++;
                        if(strcmp(Aname,"sno")==0) D->data->Sno=CSno;
                        else if(strcmp(Aname,"sname")==0) strcpy(D->data->Sname,CSname);
                        else if(strcmp(Aname,"ssex")==0) strcpy(D->data->Ssex,CSsex);
                        else if(strcmp(Aname,"sage")==0) D->data->Sage=CSage;
                        else if(strcmp(Aname,"sdept")==0) strcpy(D->data->Sdept,CSdept);
                        //if(strcmp(Aname,"sdept")==0) strcpy(D->data->Sdept,CSdept);
                    }
                    D=D->next;
                }


            }
            else if(strcmp(SAname,"sname")==0)
            {
                ss>>tmp;ss>>SnameValue;//条件
                D=D->next;
                while(D)
                {

                    if(strcmp(D->data->Sname,SnameValue)==0)
                    {
                        i++;
                        if(strcmp(Aname,"sno")==0) D->data->Sno=CSno;
                        else if(strcmp(Aname,"sname")==0) strcpy(D->data->Sname,CSname);
                        else if(strcmp(Aname,"ssex")==0) strcpy(D->data->Ssex,CSsex);
                        else if(strcmp(Aname,"sage")==0) D->data->Sage=CSage;
                        else if(strcmp(Aname,"sdept")==0) strcpy(D->data->Sdept,CSdept);
                        //if(strcmp(Aname,"sdept")==0) strcpy(D->data->Sdept,CSdept);
                    }
                    D=D->next;
                }

            }
             else if(strcmp(SAname,"ssex")==0)
            {
                ss>>tmp;ss>>SsexValue;//条件
                D=D->next;
                while(D)
                {

                    if(strcmp(D->data->Ssex,SsexValue)==0)
                    {
                        i++;
                        if(strcmp(Aname,"sno")==0) D->data->Sno=CSno;
                        else if(strcmp(Aname,"sname")==0) strcpy(D->data->Sname,CSname);
                        else if(strcmp(Aname,"ssex")==0) strcpy(D->data->Ssex,CSsex);
                        else if(strcmp(Aname,"sage")==0) D->data->Sage=CSage;
                        else if(strcmp(Aname,"sdept")==0) strcpy(D->data->Sdept,CSdept);
                        //if(strcmp(Aname,"sdept")==0) strcpy(D->data->Sdept,CSdept);
                    }
                    D=D->next;
                }

            }
             else if(strcmp(SAname,"sage")==0)
            {
                ss>>tmp;ss>>SageValue;//条件
                D=D->next;
                while(D)
                {

                    if(D->data->Sage==SageValue)
                    {
                        i++;
                        if(strcmp(Aname,"sno")==0) D->data->Sno=CSno;
                        else if(strcmp(Aname,"sname")==0) strcpy(D->data->Sname,CSname);
                        else if(strcmp(Aname,"ssex")==0) strcpy(D->data->Ssex,CSsex);
                        else if(strcmp(Aname,"sage")==0) D->data->Sage=CSage;
                        else if(strcmp(Aname,"sdept")==0) strcpy(D->data->Sdept,CSdept);
                        //if(strcmp(Aname,"sdept")==0) strcpy(D->data->Sdept,CSdept);
                    }
                    D=D->next;
                }

            }
             else if(strcmp(SAname,"sdept")==0)
            {
                ss>>tmp;ss>>SdeptValue;//条件
                D=D->next;
                while(D)
                {

                    if(strcmp(D->data->Sdept,SdeptValue)==0)
                    {
                        i++;
                        if(strcmp(Aname,"sno")==0) D->data->Sno=CSno;
                        else if(strcmp(Aname,"sname")==0) strcpy(D->data->Sname,CSname);
                        else if(strcmp(Aname,"ssex")==0) strcpy(D->data->Ssex,CSsex);
                        else if(strcmp(Aname,"sage")==0) D->data->Sage=CSage;
                        else if(strcmp(Aname,"sdept")==0) strcpy(D->data->Sdept,CSdept);
                        //if(strcmp(Aname,"sdept")==0) strcpy(D->data->Sdept,CSdept);
                    }
                    D=D->next;
                }

            }
            cout<<"修改了"<<i<<"条记录!"<<endl;
        }
        //DataListTravel(DNtemp->D);
    }
    else{cout<<"您没有对该表的更新权限!"<<endl;}
    return 0;
}
int delete_fun()
{
    PrivList Ptemp;
    Ptemp=NowUser->P->next;

    DataNameList DNtemp=DN->next;
    DataList D,Dtemp;
    ValueList VA;

    char tmp[N],Tname[N],Aname[N],SAname[N];
    char SnameValue[N],SsexValue[N],SdeptValue[N];
    int SnoValue,SageValue;
    stringstream ss(sql);
    ss>>tmp;ss>>tmp;ss>>Tname;  //delete from student

    while(Ptemp&&strcmp(Ptemp->tablename,Tname)!=0){Ptemp=Ptemp->next;}   //找出此表权限
    if(Ptemp&&Ptemp->privilege[3]=='1')
    {
        while(DNtemp&&strcmp(DNtemp->DataName,Tname)!=0){DNtemp=DNtemp->next;} //找出此表数据
        D=DNtemp->D;
        //DataListTravel(DNtemp->D);
        if(strcmp(Tname,"student")==0)
        {
            int i=0;
            ss>>tmp;ss>>SAname;//ss>>tmp;//ss>>Avalue;//待更新      //where sno
            //cout<<SAname;
            if(strcmp(SAname,"sno")==0)
            {
                ss>>tmp;ss>>SnoValue;//条件  = 10
                //D=D->next;
                while(D&&D->next)
                {
                    int b=0;
                    if(D->next->data->Sno==SnoValue)
                    {
                        i++;
                        DataListDelete(D);
                        b=1;
                    }
                    if(b==0)
                    D=D->next;
                }

            }
            else if(strcmp(SAname,"sname")==0)
            {
                ss>>tmp;ss>>SnameValue;//条件
                //D=D->next;
                while(D&&D->next)
                {
                    int b=0;
                    if(strcmp(D->next->data->Sname,SnameValue)==0)
                    {
                        i++;
                        DataListDelete(D);
                        b=1;
                    }
                    if(b==0)
                    D=D->next;
                }

            }
             else if(strcmp(SAname,"ssex")==0)
            {
                ss>>tmp;ss>>SsexValue;//条件
                //D=D->next;
                while(D&&D->next)
                {
                    int b=0;
                    if(strcmp(D->next->data->Ssex,SsexValue)==0)
                    {
                        i++;
                        DataListDelete(D);
                        b=1;
                    }
                    if(b==0)
                    D=D->next;
                }

            }
             else if(strcmp(SAname,"sage")==0)
            {
                ss>>tmp;ss>>SageValue;//条件
                //D=D->next;
                while(D&&D->next)
                {
                    int b=0;
                    if(D->next->data->Sage==SageValue)
                    {
                        i++;
                        DataListDelete(D);
                        b=1;
                    }
                    if(b==0)
                    D=D->next;
                }

            }
             else if(strcmp(SAname,"sdept")==0)
            {
                ss>>tmp;ss>>SdeptValue;//条件
                //D=D->next;
                while(D&&D->next)
                {
                    int b=0;
                    if(strcmp(D->next->data->Sdept,SdeptValue)==0)
                    {
                        i++;
                        DataListDelete(D);
                        b=1;
                    }
                    if(b==0)
                    D=D->next;
                }
            }
            cout<<"删除了"<<i<<"条记录!"<<endl;
        }
        //DataListTravel(DNtemp->D);
    }
    else{cout<<"您没有对该表的删除权限!"<<endl;}
    return 0;
}
int select_fun()
{
    PrivList Ptemp;
    Ptemp=NowUser->P->next;
    DataNameList DNtemp=DN->next;
    DataList D,Dtemp;
    ValueList VA;
    char tmp[N],Tname[N],Aname[N],SAname[N];

    stringstream ss(sql);
    ss>>tmp;ss>>Aname;ss>>tmp;ss>>Tname;

    while(Ptemp&&strcmp(Ptemp->tablename,Tname)!=0){Ptemp=Ptemp->next;}
    if(Ptemp&&Ptemp->privilege[0]=='1')
    {
        while(DNtemp&&strcmp(DNtemp->DataName,Tname)!=0){DNtemp=DNtemp->next;}
        DN=DN->next;
        D=DN->D;
        if(strcmp(Aname,"*")==0)
       {
           if(D!=NULL)
        DataListTravel(D);
        cout<<endl;
       }
        //DataListTravel(DNtemp->D);
//            if(strcmp(Aname,"sno")==0)
//            {//条件
//                while(D)
//                {
//                    cout<<D->data->Sno<<endl;
//                    D=D->next;
//                }
//
//            }
//            else if(strcmp(Aname,"sname")==0)
//            {
//                while(D)
//                {
//                    cout<<D->data->Sname<<endl;
//                    D=D->next;
//                }
//
//            }
//             else if(strcmp(Aname,"ssex")==0)
//            {
//                while(D)
//                {
//                    cout<<D->data->Ssex<<endl;
//                    D=D->next;
//                }
//            }
//             else if(strcmp(Aname,"sage")==0)
//            {
//                while(D)
//                {
//                    cout<<D->data->Sage<<endl;
//                    D=D->next;
//                }
//
//            }
//             else if(strcmp(Aname,"sdept")==0)
//            {
//                while(D)
//                {
//                    cout<<D->data->Sdept<<endl;
//                    D=D->next;
//                }
//
//            }
            //cout<<"修改了"<<i<<"条记录!"<<endl;
        }
        //DataListTravel(DNtemp->D);
    else{cout<<"您没有对该表的查询权限!"<<endl;}
    return 0;
}
int create_fun()
{
    PrivList Ptemp;
    Ptemp=NowUser->P->next;

    TableAttrList TA;
    TableList Ttemp;
    IndexNameList Itemp;

    char Tname[N],Tattrname[N],Tattrtype[N],Tattrcondition[N];
    char tmp[N];
    stringstream ss(sql);
    ss>>tmp;ss>>tmp;ss>>Tname;ss>>tmp;//create table student
    strcpy(Ptemp->tablename,Tname);
    for(int k=0;k<4;k++)
    Ptemp->privilege[k]==NowUser->P->privilege[k];

    int j=0;
    CreatTable(TA);
    InitIndexNameList(I);
    IndexNameListInsert(I,Tname);
    for(int i=0;i<5;i++)
    {
        ss>>Tattrname;ss>>Tattrtype;ss>>Tattrcondition;
        strcpy(TA->name[i],Tattrname);
        strcpy(TA->type[i],Tattrtype);
        strcpy(TA->condition[i],Tattrcondition);
        j++;
        //cout<<"+++++++++"<<endl;
    }
    int Tablelen=j;
    Ttemp=TableListInsert(T,TA);
    strcpy(Ttemp->name,Tname);
    Ttemp->len=Tablelen;
    cout<<"成功建成表"<<Tname<<endl;
    return 0;
}
int main()
{
    char tmp[N];
    InitViewList(V);
    AddView();//(V);
    InitTableList(T);
    AddTable();//(T);
    InitDataNameList(DN);
    AddData();//(D);
    InitUserList(U);
    AddUser();


    login();
    cout<<"按任意键继续......"<<endl;
    getchar();
    system("cls");

    while(1)
    {
        read();
        stringstream str_s(sql);
        str_s>>tmp;
        if( 0 == strcmp(tmp,"help"))
        help_fun();
        else if((0 == strcmp(tmp,"grant"))||(0 == strcmp(tmp,"revoke")))
        grant_fun();
        else if(0 == strcmp(tmp,"insert"))
        insert_fun();
        else if(0 == strcmp(tmp,"update"))
        update_fun();
        else if(0 == strcmp(tmp,"delete"))
        delete_fun();
        else if(0 == strcmp(tmp,"select"))
        select_fun();
        else if(0 == strcmp(tmp,"create"))
        create_fun();
        else if(0 == strcmp(tmp,"exit"))
        exit(0);
        cout<<"按任意键继续......"<<endl;
        getchar();
        system("cls");
    }

    return 0;
}
