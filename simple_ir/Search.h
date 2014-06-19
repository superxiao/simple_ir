#ifndef SEARCH_H
#define SEARCH_H
#include "Query.h"
#include "List.h"
#include <memory>
#include "Dic.h"
/*
*search用一条查询语句进行初始化，然后执行。
*/

class Search
{
    Query* q;
    Query q2;
    List* getOrList(List*,List*);
    List* getAndList(List*,List*);
    List* getTmpList(const Query& tq, shared_ptr<Dic> d, shared_ptr<Dic> twoGram);
public:
    Search(Query);
    List* exec(shared_ptr<Dic> dic, shared_ptr<Dic> twoGram);
};
#endif



