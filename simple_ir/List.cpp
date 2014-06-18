#include<iostream>
#include<cstring>
#include<string>
#include"List.h"
#include"Posting.h"
#include <memory>

using namespace std;

List::List(string term)
{
    this->length = 0;
    head=NULL;
    last = NULL;
    this->term = term;
}

string List::getTerm() const
{
    return term;
}


int List::getLength()
{
    return length;
}

void List::addPosting(int docId)
{
    // Assume docId are added in increasing order
    // TODO: frequency currently set to 0
    shared_ptr<Posting> posting(new Posting(docId, 0));
    if(head == NULL)
    {
        head = posting;
        last = posting;
        length = 1;
    }
    else
    {
        // Because docId are added in increasing order we only need to asure
        // last docId in list doesn't equal to the one we are adding.
        if(last->getDocId() != docId)
        {
            last->next = posting;
            last = last->next;
            length ++;
        }
    }
}

shared_ptr<Posting> List::getPostings()
{
    return head;
}



