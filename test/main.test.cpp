#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iterator>
#include <cctype>
#include <unordered_map>

using namespace std;
unordered_map<string, int> strMap;

void countWord(stringstream &ss){
    string strTmp;
    while (ss>>strTmp) {
        unordered_map<string,int>::iterator it = strMap.find(strTmp);
        if(it == strMap.end()){
            strMap.insert(unordered_map<string,int>::value_type(strTmp,1));
        }else{
            strMap[strTmp]++;
        }
    }
}

int main(){
    string strFile,tmp;
    fstream file("input.txt");
    while (getline(file,strFile)) {
        strFile.append(tmp);
        tmp.clear();
    }
    for ( int i = 0;i<strFile.length();i++){
        if(ispunct(strFile[i])){
            strFile[i] = ' ';
        }
    }
    stringstream ss(strFile);
    countWord(ss);
    unordered_map<string,int>::const_iterator it;
    for(it = strMap.begin(); it != strMap.end();++it){
        cout<< it->first<<"="<<it->second<<endl;
    }
    cout<<endl;
    return 0;
}

