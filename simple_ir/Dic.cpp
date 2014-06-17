#include"Dic.h"
#include<string>
#include<cstring>
#include<iostream>
#include <string>

using namespace std;

Dic::Dic()
{
    this->lists = vector<List>();
}

List* Dic::getListByTerm(string term)
{
    // Should only allow this operation when we have the list sorted by term.
    // In that case we can do a binary search.
    // Currently we do a linear search.
    for(vector<List>::iterator list = lists.begin(); list != lists.end(); list++)
    {
        if(list->getTerm() == term)
        {
            return &(*list);
        }
    }
    return NULL;
}

void Dic::addList(string term)
{
    List list(term);
    this->lists.push_back(list);
}