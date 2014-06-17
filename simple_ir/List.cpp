#include<iostream>
#include<cstring>
#include<string>
#include"List.h"
#include"Posting.h"
using namespace std;
List::List(char*n)
{
    PostingSum=0;
    head=NULL;
    strcpy(name,n);
    left=NULL;
    right=NULL;
}

char* List::name()
{
    return name;
}

Posting* has(char*name)
{
    Posting* tmp;
    tmp=head;
    if(head==NULL)
        return NULL;
    while(tmp)
    {
        if(!strcmp(tmp->name,name))
            return tmp;
        tmp=tmp->next;
    }
    return NULL;
}

double List::PostingSum()
{
    return PostingSum;
}

bool List::addTerm(char* name)
{
    Posting* tmp;
    if(tmp=this->has(name))
    {
        tmp->fq++;
    }
    else
    {
        //如果在链接表中没有记录或者记录应该在head之前
        if(head==NULL||strcmp(head->name,name)>0)
        {
            tmp=new Posting(name);
            tmp->next=head;
            head=tmp;
            return true;
        }
        tmp=head;
        while(tmp)
        {
            //如果不是最后一条记录
            if(tmp->next)
            {
                if(strcmp(tmp->next->name,name)>0)
                {
                    Posting*t=new Posting(name);
                    t->next=tmp->next;
                    tmp->next=t;
                    return true;
                }
                else
                {
                    tmp=tmp->next;
                }
            }
            else    //是最后一条记录
            {
                if(strcmp(tmp->name,name)<0)
                {
                    Posting*t=new Posting(name);
                    tmp->next=t;
                    return true;
                }
                else
                {
                    Posting*t=new Posting(name);
                    tmp->next=t;
                    return true;
                }
            }
        }
    }
}



Posting* List::getTerms()
{
    return head;
}

        

