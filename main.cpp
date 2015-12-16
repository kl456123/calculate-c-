#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1000
using namespace std;
//char ops[MAXSIZE];
//int nums[MAXSIZE];


typedef struct {
    char data[MAXSIZE];
    int top;
} Stk;

typedef struct{
    double data[MAXSIZE];
    int top;
}StkNums;

Stk *build() {
    Stk *stk;
    stk=(Stk*)malloc(sizeof(Stk));
    stk->top=0;
    return stk;
}
StkNums *buildNums(){
    StkNums *stk;
    stk=(StkNums*)malloc(sizeof(StkNums));
    stk->top=0;
    return stk;
}
bool IsEmpty(Stk *stk) {
    if(stk->top==0){
//            printf("The stack is empty!\n");
        return true;
    }else{
        return false;
    }

}
bool IsEmptyNums(StkNums*stk){
    if(stk->top==0){
//            printf("The stack is empty!\n");
        return true;
    }else{
        return false;
    }
}

bool IsFull(Stk *stk) {
    if(stk->top==MAXSIZE-1){
            printf("It is full\n");
        return true;
    }

    return false;
}

void Pop(Stk *stk) {
    if(IsEmpty(stk)) {
//        printf("The stack is empty!\n");
        return ;
    }
    stk->top--;
    return;
}
void PopNums(StkNums *stk) {
    if(IsEmptyNums(stk)) {
//        printf("The stack is empty!\n");
        return ;
    }
    stk->top--;
    return;
}

void PushChar(char c,Stk *stk) {
    if(IsFull(stk)) {
        printf("The stack is full!\n");
        return ;
    }
    stk->data[stk->top]=c;
    stk->top++;
    return;
}
double PopBack(StkNums*stk){
    if(IsEmptyNums(stk))
        return -1;
    double n=stk->data[stk->top-1];
    PopNums(stk);
//    printf("PopBack:%lf",n);
    return n;
}

void PushNum(double n,StkNums *stk){
    stk->data[stk->top]=n;
    stk->top++;
    return ;
}

double getTop(StkNums *stk){
    return stk->data[stk->top-1];
}
int main() {

    /*init stack*/
    Stk *ops;
    Stk *res;
    StkNums *cal;
    cal=buildNums();
    ops=build();
    res=build();
    freopen("in.txt","r",stdin);
    char c;
    double temp=0;//get tow or over number
    while(~scanf("%c",&c)) {
        if(c==' '||c=='\n')
        continue;
        if(c>='0'&&c<='9') {
            PushChar(c,res);
        } else if(c=='+'||c=='-') {
            if(IsEmpty(ops)) {
                PushChar(c,ops);
            } else {
                if(ops->data[ops->top-1]=='(') {
                    PushChar(c,ops);
                } else {
                    while(!IsEmpty(ops)&&ops->data[ops->top-1]!='(') {
                          PushChar(ops->data[ops->top-1],res);
                            Pop(ops);
                    }
                    PushChar(c,ops);
                }
            }
        } else if(c=='*'||c=='/') {
            if(IsEmpty(ops)) {
                PushChar(c,ops);
            } else {
                if(ops->data[ops->top-1]=='('||ops->data[ops->top-1]=='+'||ops->data[ops->top-1]=='-') {
                    PushChar(c,ops);
                } else {
                    while(!IsEmpty(ops)&&ops->data[ops->top-1]!='('&&ops->data[ops->top-1]!='+'&&ops->data[ops->top-1]!='-') {
                        PushChar(ops->data[ops->top-1],res);
                        Pop(ops);
                    }
                    PushChar(c,ops);
                }
            }
        } else if(c=='(') {
            if(IsEmpty(ops)) {
                PushChar(c,ops);
            } else {
                PushChar(c,ops);
            }
        } else{
            int cot=0;
            while(ops->data[ops->top-1]!='(') {
                PushChar(ops->data[ops->top-1],res);
                Pop(ops);
            }
            Pop(ops);
        }

    }
    while(!IsEmpty(ops)){
        PushChar(ops->data[ops->top-1],res);
        Pop(ops);
    }

//    for(int i=0;i<res->top;i++){
//        printf("%c",res->data[i]);
//    }
    char tmp[MAXSIZE];

    for(int i=0;i<res->top;i++){
        tmp[i]=res->data[i];
    }
//    for(int i=0;i<res->top;i++){
//        printf("%c ",tmp[i]);
//    }
//    puts("");
    int length=res->top;
    int cot=0;
    double a;
    double b;
    while(length>cot){
        char topData=tmp[cot];
        if(topData>='0'&&topData<='9'){
            PushNum(topData-'0',cal);
//            printf("test\n");
//            printf("%d ",cal->data[cal->top-1]);
        }else{
            //printf("%c %c\n",PopBack(cal),PopBack(cal));
//            printf("%lf\n",cal->data[cal->top-1]);
            a=PopBack(cal);
            b=PopBack(cal);
//            printf("PopBack:%lf %lf\n",a,b);
            double ansTemp;
            if(topData=='+'){
                ansTemp=a+b;
            }else if(topData=='-'){
                ansTemp=b-a;
            }else if(topData=='*'){
                ansTemp=a*b;
            }else{
                ansTemp=b/a;
            }
//            printf("PushCal:%lf\n",ansTemp);
            PushNum(ansTemp,cal);
//            printf("TopData%lf\n",cal->data[cal->top-1]);
        }
        cot++;
    }
    double ans=PopBack(cal);
    printf("%lf",ans);
    return 0;
}
