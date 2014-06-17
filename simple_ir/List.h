#ifndef LIST_H
#define LIST_H
#include "Posting.h"
#include <string>

class List
{
private:
    string term;
    int length;
    Posting* head;
    Posting* last;
public:
    List(string term);
    string getTerm();
    int getLength();
    void addPosting(string docId);
    Posting* getPostings();
};
#endif
