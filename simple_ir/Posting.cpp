#include<iostream>
#include<cstring>
#include<string>
#include"Posting.h"
using namespace std;
Posting::Posting(char*n)
{
    strcpy(name,n);
    fq=1;
    next=NULL;
}
double Posting::freq()
{
    return fq;
}
char* Posting::name()
{
    return name;
}
