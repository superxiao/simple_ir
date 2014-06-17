#ifndef DIC_H
#define DIC_H
#include"List.h"
#include"Posting.h"
#include <string>
#include <vector>

using namespace std;

class Dic
{
private:
    vector<List> lists;
public:
    Dic();
    List* getListByTerm(string term);
    void addList(string term);
};
#endif
