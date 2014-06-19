#ifndef LIST_H
#define LIST_H
#include "Posting.h"
#include <string>
#include <memory>
#include <set>
class List
{
private:
    string term;
    int length;
    shared_ptr<Posting> head;
    shared_ptr<Posting> last;
    shared_ptr<set<string>> otherSet;
public:
    List(string term);
    string getTerm() const;
    int getLength();
    void addPosting(int docId);
    shared_ptr<Posting> getPostings();
    void List::addOther(string other);
    
    shared_ptr<set<string>> List::getOthers();
    int List::getOthersLength();
};
#endif
