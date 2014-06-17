#include<iostream>
#include<cstring>
#include<string>
#include"List.h"
#include"Posting.h"
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

void List::addPosting(string docId)
{
    // TODO: frequency currently set to 0
    Posting* posting = new Posting(docId, 0);
    if(head == NULL)
    {
        head = posting;
        last = posting;
        length = 1;
    }
    else
    {
        last->next = posting;
        last = last->next;
        length ++;
    }
}

Posting* List::getPostings()
{
    return head;
}



