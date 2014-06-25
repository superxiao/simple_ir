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

unique_ptr<List> Search::exec(shared_ptr<Dic> dic, shared_ptr<Dic> twoGram)
{
    return this->getTmpList(q2, dic, twoGram);
}

static string removePrefixCharacter(string in, char c)
{
    auto itr = in.begin();
    for(; itr != in.end()&&*itr == c; itr++);
    return in.substr(itr-in.begin());
}

static string removePostfixCharacter(string in, char c)
{
    auto itr = in.end() - 1;
    for(; itr >= in.begin()&&*itr == c; itr--);
    return in.substr(0, itr-in.begin() + 1);
}

unique_ptr<List> Search::PromptForWildcardSearchAndReturnResultsIfContinue(vector<string>& words, string& stringPart, shared_ptr<Dic>& d, shared_ptr<Dic>& twoGram)
{
    
    if(words.size() == 0)
        return NULL;
    cout << "Using 2-gram index, found " << words.size() << " terms. They are:" << endl;
    for(auto itr = words.begin(); itr!=words.end() && itr - words.begin() < 100; itr++)
    {
        cout << *itr << " ";
    }
    if(words.end()-words.begin() > 100)
        cout << "...";
    cout << endl;
    cout << "Wildcard search may take longer time than single terms. Continue?[y/n]";
    string s;
    getline(cin, s);
    if(s != "y" && s != "Y")
        return NULL;

    string query = words[0];
    for(auto itr = words.begin() + 1; itr!=words.end(); itr++)
        query = query + " or " + *itr;
    auto q = Query::makeQueryList(query);
    return getTmpList(*q, d, twoGram);
}

unique_ptr<List> Search::getTmpList(Query& tq, shared_ptr<Dic>& d, shared_ptr<Dic>& twoGram)
{
    Query* q=&tq;
    if(q->next==NULL) 
    {
        if(starts_with(q->getName(), "*"))
        {
            string removed = removePrefixCharacter(q->getName(), '*');
            auto words = TwoGramIndexer::searchForPostfix(twoGram, removed);
            return PromptForWildcardSearchAndReturnResultsIfContinue(words, removed, d, twoGram);
        }
        else if(ends_with(q->getName(), "*"))
        {
            string removed = removePostfixCharacter(q->getName(), '*');
            auto words = TwoGramIndexer::searchForPrefix(twoGram, removed);
            return PromptForWildcardSearchAndReturnResultsIfContinue(words, removed, d, twoGram);
        }
        unique_ptr<List> l=d->getListByTerm(string(q->getName()));
        return l;
    }
    if(q->next->getName() == "or") 
    {
        if(q->next->next != NULL)
            return getOrList(getTmpList(Query(q->getName()), d, twoGram),getTmpList(*(q->next->next), d, twoGram));  
        else return getTmpList(Query(q->getName()), d, twoGram);
    }
    else if(q->next->getName() == "and")
    {
        if(q->next->next != NULL)
            return getAndList(getTmpList(Query(q->getName()), d, twoGram),getTmpList(*(q->next->next), d, twoGram));
        else return getTmpList(Query(q->getName()), d, twoGram);
    }
    else  
    {
        if(q->next != NULL)
            return getAndList(getTmpList(Query(q->getName()), d, twoGram),getTmpList(*(q->next), d, twoGram));
        else return getTmpList(Query(q->getName()), d, twoGram);
    }
}

unique_ptr<List> Search::getOrList(unique_ptr<List> r1,unique_ptr<List> r2)
{
    shared_ptr<Posting> s1;
    shared_ptr<Posting> s2;
    s1=r1->getPostings();
    s2=r2->getPostings();
    if(r1 == NULL)
        return unique_ptr<List>(new List(*r2));
    else if(r2 == NULL)
        return unique_ptr<List>(new List(*r1));
    unique_ptr<List>  l(new List("r"));
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

unique_ptr<List> Search::getAndList(unique_ptr<List> r1,unique_ptr<List> r2)
{
    shared_ptr<Posting> s1;
    shared_ptr<Posting> s2;
    if(r1 == NULL || r2 == NULL)
        return NULL;
    s1=r1->getPostings();
    s2=r2->getPostings();
    unique_ptr<List> l(new List("r"));
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

