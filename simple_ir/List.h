#ifndef LIST_H
#define LIST_H
class List
{
private:
    char name[20];
    double listSum;
    Term* head;
    List*next;
public:
    char* name();
    double listSum();
    bool addTerm(char*);
    Term* getTerms();
};
#endif
