#ifndef DIC_H
#define DIC_H
#include"List.h"
#include"Term.h"
class Dic
{
private:
    List* head;
    double listSum;
public:
    double listSum();
    List* has(char*);
    List* getListByName(char*);
    bool addList(char*);
};
#endif
