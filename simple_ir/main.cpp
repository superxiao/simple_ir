#include <iostream>
#include <boost/filesystem.hpp>
#include <sstream>
#include "TokenReader.h"
#include "Dic.h"
#include "test.h"
#include "IndexConstructor.h"
#include "IndexPersister.h"
#include "Query.h"
#include "Search.h"
#include "TwoGramIndexer.h"

using namespace std;
using namespace boost::filesystem;

void printSomeFileContent(string file)
{
    ifstream stream("../Reuters/" + file + ".html");
    char buffer[100] = {0};
    stream.read(buffer, 99);
    cout << "\"" << buffer << "...." << "\"" << endl << endl;
}

int main(int argc, char** argv)
{
    //testDic();
    cout << "Usage:\n" << "construct <folder>: construct index\n" 
        << "s <search string>: search string from index\n" << endl;
    string line;
    shared_ptr<Dic> dic = NULL;
    shared_ptr<Dic> twoGramIndex = NULL;
    IndexPersister store;
    while(true)
    {
        cout << ">>";
        getline(cin, line);
        stringstream stream(line);
        string token;
        stream >> token;
        if(token == "construct")
        {
            string folder;
            stream >> folder;
            IndexConstructor constructor;
            if(!exists(folder))
            {
                cout << "Folder doesn't exist." << endl;
                continue;
            }
            dic = constructor.constructIndex(folder, 0);
            store.saveIndexToFile(dic, "term", "postings");
        }
        else if(token == "s")
        {
            if(dic == NULL)
            {
                if(!exists("term") || !exists("postings"))
                {
                    cout << "Construct index first!" << endl;
                    continue;
                }
                dic = store.readIndexFromFile("term", "postings");
            }
            string queryStr;
            getline(stream, queryStr);
            cout << "Search for query " << queryStr << endl;
            auto query = Query::makeQueryList(queryStr);
            Search search(*query);
            if(twoGramIndex == NULL)
            {
                cout << "Reading 2-gram index from disk.." << endl;
                twoGramIndex = TwoGramIndexer::readIndexFromFile("2gram_terms", "2gram_postings");
            }
            auto list = search.exec(dic, twoGramIndex);
            if(list != NULL)
            {
                shared_ptr<Posting> posting = list->getPostings();
                while(posting != NULL)
                {
                    cout << posting->getDocId() << ".html" << endl;
                    stringstream stream;
                    stream << posting->getDocId();
                    string fileName;
                    stream >> fileName;
                    printSomeFileContent(fileName);
                    posting = posting->next;
                }
            }
            else
            {
                cout << "Not found!" << endl;
            }
        }
        else
        {
            cout << "Invalid command." << endl;
        }
    }

    int i;
    cin >> i;
    return 0;
}