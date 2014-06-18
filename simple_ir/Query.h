#ifndef QUERY_H
#define QUERY_H
#include <string>
#include <memory>
using namespace std;
class Query
{
    string name;
public:
    Query();
    Query(string);
    std::shared_ptr<Query> next;
   const string getName()const;
    static std::shared_ptr<Query> makeQueryList(string);
};
#endif
