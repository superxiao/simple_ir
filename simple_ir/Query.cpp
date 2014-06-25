#include<iostream>
#include<cstring>
#include<string>
#include <vector>
#include"Query.h"
#include <boost/algorithm/string.hpp>
#include <boost\tokenizer.hpp>
#include <memory>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;
Query::Query()
{}
string& Query::getName()
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
    std::shared_ptr<Query> last=NULL;
    std::shared_ptr<Query> head=NULL;
    
    boost::regex re("[\\s\\]\\[!\"#$%&'\\(\\)+,./:;<=>?@\\^_`{|}~-]+");
    boost::sregex_token_iterator i(q.begin(), q.end(), re, -1);
    boost::sregex_token_iterator j;

    for(; i!=j;++i) {
        if((*i) == "")
            continue;
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
