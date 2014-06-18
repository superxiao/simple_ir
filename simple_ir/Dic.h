#ifndef DIC_H
#define DIC_H
#include"List.h"
#include"Posting.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Dic
{
private:
    vector<List> lists;
    bool sorted;
public:
    Dic();
    shared_ptr<List> getListByTerm(string term);
    typedef vector<List>::iterator list_iterator;
    void addList(string term);
    void addList(string term, List list);
    void setSorted(bool);
    list_iterator begin();
    list_iterator end();
    void sortLists();
};
#endif
