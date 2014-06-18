#include <iostream>
#include "TokenReader.h"
#include "Dic.h"
#include "test.h"
#include "IndexConstructor.h"
#include "IndexPersister.h"
#include "Query.h"
#include "Search.h"
using namespace std;



int main(int argc, char** argv)
{
    //testDic();
    IndexConstructor constructor;
   // auto dic = constructor.constructIndex("../Reuters", 0);

    IndexPersister store;
    //store.saveIndexToFile(dic, "../term", "../postings");
    auto dic = store.readIndexFromFile("../term", "../postings");

    string term("commercial OR reason");
    cout << "Search for term " << term << endl;
    auto query = Query::makeQueryList(term);
    Search search(*query);
    auto list = search.exec(dic);
    if(list != NULL)
    {
        shared_ptr<Posting> posting = list->getPostings();
        while(posting != NULL)
        {
            cout << posting->getDocId() << endl;
            posting = posting->next;
        }
    }
    else
    {
        cout << "Not found!" << endl;
    }
    //TokenReader::readAndLowerTokensFromFile("../Reuters/10.html");

    int i;
    cin >> i;
    return 0;
}