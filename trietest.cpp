#include<iostream>
#include<string>
#include<cctype>
#include"header.h"

using namespace std;

#ifdef DEBUG
#include<cstdio>
int main(int argc, char *infilename[]) {
    if(argc > 1) freopen(infilename[1], "r", stdin);
#else
int main(){
#endif
    const string commands[] = {
        "i", "e", "s", "autocomplete", "print", "empty", "clear", "size", "exit"
    };
    const int cmdNum = 9;
    int cmdIndex;
    bool boolRet, isContinue = false;
    string command, parameter;
    Root root;
    do{
        cin >> command;
        for(int i = 0; i < cmdNum; i++)
            if(command == commands[i]){
                cmdIndex = i;
                break;
            }
        cin.get();
        if(cmdIndex < 4) {
            parameter.clear();
            char c;
            while( (c=cin.get())!='\n') {
                parameter.push_back(c);
            }
            try{
                for(int i = 0; i < parameter.length(); i++) {
                    if((!isalpha(parameter[i]) && cmdIndex != 3) || tolower(parameter[i]) != parameter[i]) {
                        throw illegal_exception();
                    }
                }
            }
            catch(illegal_exception &e) {
                cout << e.what() << endl;
                continue;
            }

        }
        switch (cmdIndex)
        {
        case 0: // "i"
            boolRet = root.insertWord(parameter);
            if(boolRet) cout << "success" << endl;
            else cout << "failure" << endl;
            break;
        case 1: // "e"
            boolRet = root.eraseWord(parameter);
            if(boolRet) cout << "success" << endl;
            else cout << "failure" << endl;
            break;
        case 2: // "s"
            boolRet = root.searchWord(parameter);
            if(boolRet) cout << "found " << parameter << endl;
            else cout << "not found " << parameter << endl;
            break;
        case 3: // "autocomplete"
            root.autoComplete(parameter);
            break;
        case 4: // "print"
            root.print();
            break;

        case 5: // "empty"
            boolRet = root.empty();
            if(boolRet) cout << "empty 1" << endl;
            else cout << "empty 0" << endl;
            break;
        case 6: // "clear"
            boolRet = root.clear();
            if(boolRet) cout << "success" << endl;
            else cout << "failure" << endl; 
            break;
        case 7: // "size"
            cout << "number of words is " << root.getSize() << endl;
            break;   
        default: 
            break;
        }
    }while(command != commands[cmdNum - 1]);
    return 0;
}