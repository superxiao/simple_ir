#include <iostream>
#include "Dic.h"
#include "test.h"


using namespace std;

void testDic()
{
    Dic* dic = new Dic();
    dic->sortLists();
    auto list = dic->getListByTerm("a");
    if(list != NULL)
        cout << "Error!" << endl;
    dic->addList("a");
    dic->sortLists();
    list = dic->getListByTerm("a");
    if(list->getTerm() != "a")
        cout << "Error!" << endl;
    dic->addList("b");
    dic->addList("c");
    dic->sortLists();
    list = dic->getListByTerm("a");
    if(list->getTerm() != "a")
        cout << "Error!" << endl;
    list = dic->getListByTerm("b");
    if(list->getTerm() != "b")
        cout << "Error!" << endl;
    list = dic->getListByTerm("c");
    if(list->getTerm() != "c")
        cout << "Error!" << endl;
    list = dic->getListByTerm("d");
    if(list != NULL)
        cout << "Error!" << endl;
    cout << "If no error, then success!" << endl;
    delete dic;
}

void testList()
{
    List *list = new List("a");
    
    if(list->getTerm() != "a")
        cout << "Error!" << endl;
    if(list->getLength() != 0)
        cout << "Error!" << endl;
    list->addPosting(1);
    list->addPosting(2);
    list->addPosting(3);
    Posting *posting = list->getPostings();
    if(posting->getDocId() != 1)
        cout << "Error!" << endl;
    posting = posting->next;
    if(posting->getDocId() != 2)
        cout << "Error!" << endl;
    posting = posting->next;
    if(posting->getDocId() != 3)
        cout << "Error!" << endl;
    posting = posting->next;
    if(posting != NULL)
        cout << "Error!" << endl;
    if(list->getLength() != 3)
        cout << "Error!" << endl;
    cout << "If no error, then success!" << endl;
}