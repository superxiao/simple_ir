#include<iostream>
#include<string>
#include<cstring>
#include"Search.h"
#include"Dic.h"
#include"List.h"
#include"Posting.h"
#include"Query.h"
#include <memory>

using namespace std;

Search::Search(Query query)
{
    q2=query;
    q=&q2;
}

List* Search::exec(shared_ptr<Dic> dic)
{
    return this->getTmpList(q2, dic);
}

List* Search::getTmpList(const Query& tq, shared_ptr<Dic> d)
{
    Query qt=tq;
    Query* q=&qt;
    if(q->next==NULL) 
    {
        List* l=d->getListByTerm(string(q->getName()));
        return l;
    }
    if(q->next->getName() == "or") 
    {
        
        return getOrList(getTmpList(Query(q->getName()), d),getTmpList(*(q->next->next), d));  
    }
    else if(q->next->getName() == "and")
        return getAndList(getTmpList(Query(q->getName()), d),getTmpList(*(q->next->next), d));
    else  
    {
        return getAndList(getTmpList(Query(q->getName()), d),getTmpList(*(q->next), d));
    }
}

List* Search::getOrList(List* r1,List* r2)
{
    shared_ptr<Posting> s1;
    shared_ptr<Posting> s2;
    s1=r1->getPostings();
    s2=r2->getPostings();
    List*  l(new List("r"));
    int i;
    while(s1&&s2)
    {

        if(s1->getDocId() < s2->getDocId())
        {
            l->addPosting(s1->getDocId());
            s1=s1->next;
        }
        else if(s1->getDocId() > s2->getDocId())
        {
            l->addPosting(s2->getDocId());
            s2=s2->next;
        }
        else
        {
            l->addPosting(s1->getDocId());
            s1=s1->next;
            s2=s2->next;
        }
    }
    if(s1==NULL)
    {
        while(s2)
        {
            l->addPosting(s2->getDocId());
            s2=s2->next;
        }
    }
    if(s2==NULL)
    {
        while(s1)
        {
            l->addPosting(s1->getDocId());
            s1=s1->next;
        }
    }
    return l;
}

List* Search::getAndList(List* r1,List*r2)
{
    shared_ptr<Posting> s1;
    shared_ptr<Posting> s2;
    s1=r1->getPostings();
    s2=r2->getPostings();
    List* l(new List("r"));
    while(s1&&s2)
    {
        if(s1->getDocId() < s2->getDocId())
        {
            s1=s1->next;
        }
        else if(s1->getDocId() > s2->getDocId())
            s2=s2->next;
        else
        {
            l->addPosting(s1->getDocId());
            s1=s1->next;
            s2=s2->next;
        }
    }
    return l;
}

