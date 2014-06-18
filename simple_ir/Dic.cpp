#include"Dic.h"
#include<string>
#include<cstring>
#include<iostream>
#include <string>
#include <algorithm>

using namespace std;

Dic::Dic()
{
    this->lists = vector<List>();
    sorted = false;
}

bool compareLists(List list1, List list2)
{
    return (list1.getTerm() < list2.getTerm());
}

List* Dic::getListByTerm(string term)
{
    if(!sorted)
    {
        cout << "Lists not sorted yet!" << endl;
        return NULL;
    }
    List searchFor(term);
    // Binary search
    auto Lists = equal_range(lists.begin(), lists.end(), searchFor, compareLists);
    if(Lists.first != lists.end())
        return &(*Lists.first);
    return NULL;
}

void Dic::addList(string term)
{
    List list(term);
    this->lists.push_back(list);
    sorted = false;
}

void Dic::addList(string term, List list)
{
    this->lists.push_back(list);
    sorted = false;
}


void Dic::sortLists()
{
    sort(lists.begin(), lists.end(), compareLists);
    sorted = true;
}

void Dic::setSorted(bool sorted)
{
    this->sorted = sorted;
}

Dic::list_iterator Dic::begin()
{
    return lists.begin();
}

Dic::list_iterator Dic::end()
{
    return lists.end();
}