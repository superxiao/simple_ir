#include<iostream>
#include<string>
#include<fstream>
#include"dic.h"
#include"list.h"
#include"term.h"
using namespace std;
int main(int arc,char** argv)
{
    ifstream in("doc");
    string content("../Reuters/");
    char doc[20];
    for( int i=0;i<10;i++)
    {
        in.getline(doc,20);
        ifstream docs((content+doc).c_str());
        char c;
        docs>>c;
        cout<<doc<<endl;
        cout<<c<<endl;
        docs.close();
        
    }

}
