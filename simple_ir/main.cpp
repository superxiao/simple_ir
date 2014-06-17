#include <iostream>
#include "TokenReader.h"
#include "Dic.h"
#include "test.h"
#include "IndexConstructor.h"
using namespace std;



int main(int argc, char** argv)
{
    //testDic();
    IndexConstructor constructor("../Reuters", 100);
    auto dic = constructor.constructIndex();
    string term("commercial");
    cout << "Search for term " << term << endl;
    auto list = dic->getListByTerm(term);
    Posting* posting = list->getPostings();
    while(posting != NULL)
    {
        cout << posting->getDocId() << endl;
        posting = posting->next;
    }
    //TokenReader::readAndLowerTokensFromFile("../Reuters/10.html");

    int i;
    cin >> i;
    return 0;
}