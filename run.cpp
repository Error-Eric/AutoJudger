#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<cstring>
#include<iostream>
#include<unistd.h>
using namespace std;
void help(){

}
#define DATA 0
#define STD 1
#define MY 2
int sysr(string comm){
    //system("stty -echo");
    comm+=" >/dev/null";
    int ans=system(comm.c_str());
    //system("stty echo");
    return ans;
}
string FiName(int Type,bool Suffix){
    switch (Type){
    case DATA:
        if(Suffix)return "data.cpp";
        else return "data";
        break;
    case STD:
        if(Suffix)return "std.cpp";
        else return "std";
        break;
    case MY:
        if(Suffix)return "my.cpp";
        else return "my";
        break;
    default:
        break;
    }
}
void PostErr(string Errinfo){
    printf("\e[31m%s\e[0m\n", Errinfo.c_str());
    //printf("\033[1;31;40m %s\033[0m\n",Errinfo.c_str());
}
void PostAc(){
    printf("\e[33mNo difference found.\e[0m\n");
}
string FiName(int Type){return FiName(Type,1);}
void opI(){
    system("clear");
    puts("[I]initialize");
    string cm="find "+FiName(DATA,1);
    if(sysr(cm.c_str())!=0){
        PostErr("[Error] File \""+FiName(DATA,1)+"\" doesn't exist\n");
        puts("Press any key to continue.");
        getchar();
        return;
    }
    cm="find "+FiName(STD,1);
    if(sysr(cm.c_str())!=0){
        PostErr("[Error] File \""+FiName(STD,1)+"\" doesn't exist\n");
        puts("Press any key to continue.");
        getchar();
        return;
    }
    cm="find "+FiName(MY,1);
    if(sysr(cm.c_str())!=0){
        PostErr("[Error] File \""+FiName(MY,1)+"\" doesn't exist\n");
        puts("Press any key to continue.");
        getchar();
        return;
    }
    cm="g++ "+FiName(DATA,1)+" -o "+FiName(DATA,0);
    if(system(cm.c_str())!=0){PostErr("Complication Error. Please check your data generating program.");getchar();return;}
    cm="g++ "+FiName(STD,1)+" -o "+FiName(STD,0);
    if(system(cm.c_str())!=0){PostErr("Complication Error. Please check your given std.");getchar();return;}
    cm="g++ "+FiName(MY,1)+" -o "+FiName(MY,0);
    if(system(cm.c_str())!=0){PostErr("Complication Error. Please check your own code.");getchar();return;}
    puts("Successfull initialized.Press any key to continue.");
    getchar();
}
bool OPRANSAC=0;
void opR(bool FullEcho){
    if(FullEcho)system("clear");
    if(FullEcho)puts("[R]run");
    string cm="find "+FiName(DATA,0);
    if(sysr(cm.c_str())!=0){
        PostErr("[Error] File \""+FiName(DATA,0)+"\" doesn't exist\n");
        puts("Press any key to continue.");
        getchar();
        return;
    }
    cm="find "+FiName(STD,0);
    if(sysr(cm.c_str())!=0){
        PostErr("[Error] File \""+FiName(STD,0)+"\" doesn't exist\n");
        puts("Press any key to continue.");
        getchar();
        return;
    }
    cm="find "+FiName(MY,0);
    if(sysr(cm.c_str())!=0){
        PostErr("[Error] File \""+FiName(MY,0)+"\" doesn't exist\n");
        puts("Press any key to continue.");
        getchar();
        return;
    }
    if(FullEcho)puts("Running data generating program...");
    cm="./"+FiName(DATA,0)+" >in.txt";
    if(system(cm.c_str())!=0){PostErr("Runtime Error. Please check your data generating program.");getchar();return;}

    if(FullEcho)puts("Running std...");
    cm="./"+FiName(STD,0)+" <in.txt >ans.txt";
    if(system(cm.c_str())!=0){PostErr("Runtime Error. Please check your given std.");getchar();return;}

    if(FullEcho)puts("Running given code...");
    cm="./"+FiName(MY,0)+" <in.txt >out.txt";
    if(system(cm.c_str())!=0){PostErr("Runtime Error. Please check your own code.");getchar();return;}
    
    //usleep(1000);
    cm="diff -b -B out.txt ans.txt";
    if(system(cm.c_str())==0){PostAc();OPRANSAC=1;if(FullEcho)sysr("rm in.txt"),sysr("rm out.txt"),sysr("rm ans.txt");}
    else PostErr("Wa"),OPRANSAC=0;
    if(FullEcho)puts("Press any key to continue...");
}
void opR(){
    opR(1);getchar();
}
void opA(){
    puts("[A]autorun");
    OPRANSAC=1;
    for(register int count=1;count<=100 and OPRANSAC;count++){
        opR(0);
        if(!OPRANSAC)getchar();
    }
}
int main(){
    while(1){
        sysr("stty -echo");
        system("clear");
        puts("Auto Judger for Linux.");
        puts("[I] initiallize. [R] run. [A] autorun. [S] settings. [Q] quit. ");
        sysr("stty raw");
        char op=getchar();
        sysr("stty -raw");
        if(islower(op))op=toupper(op);
        string cm;
        switch (op){
            case 'I':
                opI();
                break;
            case 'R':
                opR();
                break;
            case 'A':
                opA();
                break;
            case 'Q':
                sysr("rm data && rm std && rm my && rm in.txt && rm out.txt && rm ans.txt");
                sysr("clear");
                sysr("stty -raw echo");
                return 0;
                break;
            default:
                break;
        }
    }
}