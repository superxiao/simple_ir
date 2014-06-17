#include"Dic.h"
#include<string>
#include<cstring>
#include<iostream>
using namespace std;
double Dic::listSum()
{
    return this->listSum;
}

List* Dic::has(char*name)
{
    List* tmp;
    tmp=head;
    while(tmp)
    {
        if(!strcmp(tmp->name,name))
        {
            return tmp;
        }
    }
    return NULL;
}


List* Dic::getListByName(char*name)
{
    List* tmp;
    if(tmp=this->has(name))
    {
        return tmp;
    }
    else
        return NULL;
}

bool Dic::addList(char* name)
{
    
