#include"Dic.h"
#include<string>
#include<cstring>
#include<iostream>
using namespace std;
Dic::Dic()
{
    this->head=NULL;
    this->listSum=0;
}
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
        tmp=tmp->next(name);
    }
    return NULL;
}


List* Dic::getListByName(char*name)
{
    List* tmp;
    if(tmp=this->has(name))
        return tmp;
    else
        return NULL;
}

bool Dic::addList(char* name)
{
   
   head=this->insert(head,name);
   listSum++;
}

//插入到二叉树中，返回插入后的根节点
List*  Dic::insert(List* list,char* name)
{
   if(list==NULL)
       return  new List(name);
    else
    {   //二叉树结构的字典
        //找到要插入的地方，然后把新的词项插入进去;
       if(strcmp(list->name,name)>0)
            list->left=insert(list->left,name);
        else
            list->right=insert(list->right,name);
    }
    return head;
}

    
    
