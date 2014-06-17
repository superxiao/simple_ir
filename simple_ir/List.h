#ifndef LIST_H
#define LIST_H
class List
{
private:
    char name[20];
    double PostingSum;
    Posting* head;
public:
    List(char*);
    List*left;
    List*right;
    char* name();
    double PostingSum();
    bool addTerm(char*);
    Posting* getTerms();
    Posting* has(char*);
};
#endif
