#include<iostream>
#include<string>
#include<cstring>
#include"Search.h"
#include"Dic.h"
#include"List.h"
#include"Posting.h"
#include"Query.h"
#include <memory>
#include <boost\algorithm\string\predicate.hpp>
#include "TwoGramIndexer.h"

using namespace std;
using namespace boost;

Search::Search(Query query)
{
    q2=query;
    q=&q2;
}

List* Search::exec(shared_ptr<Dic> dic, shared_ptr<Dic> twoGram)
{
    return this->getTmpList(q2, dic, twoGram);
}

static string removePrefixCharacter(string in, char c)
{
    auto itr = in.begin();
    for(; itr != in.end()&&*itr != c; itr++);
    return in.substr(itr-in.begin());
}

static string removePostfixCharacter(string in, char c)
{
    auto itr = in.end() - 1;
    for(; itr >= in.begin()&&*itr != c; itr--);
    return in.substr(0, itr-in.begin());
}

List* Search::getTmpList(const Query& tq, shared_ptr<Dic> d, shared_ptr<Dic> twoGram)
{
    Query qt=tq;
    Query* q=&qt;
    if(q->next==NULL) 
    {
        if(starts_with(q->getName(), "*"))
        {
            string removed = removePrefixCharacter(q->getName(), '*');
            auto words = TwoGramIndexer::searchForPrefix(twoGram, removed);
        }
        else if(ends_with(q->getName(), "*"))
        {
            string removed = removePostfixCharacter(q->getName(), '*');
            auto words = TwoGramIndexer::searchForPrefix(twoGram, removed);
        }
        List* l=d->getListByTerm(string(q->getName()));
        return l;
    }
    if(q->next->getName() == "or") 
    {
        
        return getOrList(getTmpList(Query(q->getName()), d, twoGram),getTmpList(*(q->next->next), d, twoGram));  
    }
    else if(q->next->getName() == "and")
        return getAndList(getTmpList(Query(q->getName()), d, twoGram),getTmpList(*(q->next->next), d, twoGram));
    else  
    {
        return getAndList(getTmpList(Query(q->getName()), d, twoGram),getTmpList(*(q->next), d, twoGram));
    }
}

List* Search::getOrList(List* r1,List* r2)
{
    shared_ptr<Posting> s1;
    shared_ptr<Posting> s2;
    s1=r1->getPostings();
    s2=r2->getPostings();
    if(r1 == NULL)
        return r2;
    else if(r2 == NULL)
        return r1;
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
    if(r1 == NULL || r2 == NULL)
        return NULL;
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

