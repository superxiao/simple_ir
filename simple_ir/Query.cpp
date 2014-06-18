#include<iostream>
#include<cstring>
#include<string>
#include <vector>
#include"Query.h"
#include <boost/algorithm/string.hpp>
#include <boost\tokenizer.hpp>
#include <memory>

using namespace std;
using namespace boost;
Query::Query()
{}
const string Query::getName()const
{
    return name;
}
Query::Query(string q)
{
    name = q;
    next=NULL;
}
std::shared_ptr<Query> Query::makeQueryList(string q)
{
    //把一条查询语句a b AND c转化为Query链表
    //每一个query中都是一个单词 a
    to_lower(q);
    int i=0;
    std::shared_ptr<Query> last=NULL;
    std::shared_ptr<Query> head=NULL;
    tokenizer<> tok(q);
    for(tokenizer<>::iterator i=tok.begin(); i!=tok.end();++i) {
        if(head == NULL)
        {
            head = std::shared_ptr<Query>(new Query(*i));
            last = head;
        }
        else
        {
            last->next = std::shared_ptr<Query>(new Query(*i));
            last = last->next;
        }
    }
    return head;
}
