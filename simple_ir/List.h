#ifndef LIST_H
#define LIST_H
#include "Posting.h"
#include <string>
#include <memory>

class List
{
private:
    string term;
    int length;
    shared_ptr<Posting> head;
    shared_ptr<Posting> last;
public:
    List(string term);
    string getTerm() const;
    int getLength();
    void addPosting(int docId);
    shared_ptr<Posting> getPostings();
};
#endif
