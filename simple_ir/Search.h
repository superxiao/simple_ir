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
    unique_ptr<List> getOrList(unique_ptr<List>,unique_ptr<List>);
    unique_ptr<List> getAndList(unique_ptr<List>,unique_ptr<List>);
    unique_ptr<List> getTmpList(Query& tq, shared_ptr<Dic>& d, shared_ptr<Dic>& twoGram);
    unique_ptr<List> PromptForWildcardSearchAndReturnResultsIfContinue(vector<string>& words, string& stringPart, shared_ptr<Dic>& d, shared_ptr<Dic>& twoGram);
public:
    Search(Query);
    unique_ptr<List> exec(shared_ptr<Dic> dic, shared_ptr<Dic> twoGram);
};
#endif



