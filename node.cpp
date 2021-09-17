#include<iostream>
#include"header.h"

using namespace std;

Node::Node() {
    value = 0;
    isTerminal = true;
    size = 0;
    for(auto i = begin(childs), e = end(childs); i != e; i++)
        *i = nullptr;
}

Node::Node(std::string& str, int index) {
    if(str.length() == 0) {
        Node();
        return;
    }
    for(auto i = begin(childs), e = end(childs); i != e; i++)
        *i = nullptr;

    value = str[index];
    if(index == str.length() - 1){
        isTerminal = true;
        size = 0;
    }
    else {
        childs[str[index + 1] - 'a'] = new Node(str, index + 1);
        size = 1;
        isTerminal = false;
    }
}

Node::~Node() {
    if(size != 0) {
        for(auto i = begin(childs), e = end(childs); i != e; i++) {
            if(*i == nullptr) continue;
            delete *i;
        }
        size = 0;
    }
}

bool Node::addWords(std::string &str, int index) {
    //cout << str << " " << str.length() << endl;
    if(index == str.length() - 1) {
        if(isTerminal == false) isTerminal = true;
        else return false;
    }
    else if(childs[str[index + 1] - 'a'] != nullptr){
        return childs[str[index + 1] - 'a']->addWords(str, index + 1);
    }
    else {
        childs[str[index + 1] - 'a'] = new Node(str, index + 1);
        size += 1;
    }
    return true;
}

bool Node::removeWords(std::string &str, int index) {
    if(index == str.length() - 1) {
        if(isTerminal) {
            isTerminal = false;
            return true;
        }
        else return false;
    }
    if(childs[str[index + 1] - 'a'] == nullptr)
        return false;
    bool ret = childs[str[index + 1] - 'a']->removeWords(str, index + 1);
    if(childs[str[index + 1] - 'a']->getEmpty()) {
        delete childs[str[index + 1] - 'a'];
        childs[str[index + 1] - 'a'] = nullptr;
        size -= 1;
    }
    return ret;
}



Root::Root() {
    for(auto i = begin(childs), e = end(childs); i != e; i++)
        *i = nullptr;
    size = 0;
}

Root::~Root() {
    for(int i = 0, e = 26; i != e; i++) {
        if(childs[i] == nullptr) continue;
        delete childs[i];
        childs[i] = nullptr; 
    }
}


bool Root::insertWord(std::string str){
    if(str.length() == 0) return true;
    if(childs[str[0] - 'a'] == nullptr) {
        childs[str[0] - 'a'] = new Node(str);
        size += 1;
    }
    else {
        bool ret = childs[str[0] - 'a']->addWords(str);
        if(ret) size += 1;
        return ret;
    }
    return true;
}

bool Root::eraseWord(std::string str){
    if(str.length() == 0) return false;
    if(childs[str[0] - 'a'] == nullptr) return false;
    else {
        bool ret = childs[str[0] - 'a']->removeWords(str);
        if(ret) size -= 1;
        return ret;
    }
    return true;
}

bool Root::searchWord(std::string str){
    if(str.length() == 0) return true;
    int i = 1;
    Node *p = childs[str[0] - 'a'];
    do{
        p = p->getChild(str[i++] - 'a');
    } while(p && i < str.length());
    if(i < str.length()) return false;
    if(p == nullptr) return false;
    return p->getTerminal();
}

void Root::print(){
    if(size == 0) return;
    for(int i = 0; i < 26; i++) {
        if(childs[i] == nullptr) continue;
        std::string temp;
        print(childs[i], temp);
    }
    std::cout << std::endl;
}

void Root::print(Node *p, std::string &str) {
    str.push_back(p->getValue());
    if(p->getTerminal()) {
        std::cout << str << " ";
    }

    for(int i = 0; i < 26; i++) {
        if(p->getChild(i) == nullptr) continue;
        print(p->getChild(i), str);
    }

    str.pop_back();
}

void Root::autoComplete(std::string str){
    if(str.length() == 0) return;
    Node *p = childs[str[0] - 'a'];
    int i = 1;
    if(p == nullptr) return;
    while(str[i] != '*' && p) {
        p = p->getChild(str[i++] - 'a');
    }
    if(p && str[i] == '*') {
        std::string temp(str);
        temp.pop_back();
        temp.pop_back();
        print(p, temp);
        cout << endl;
    }
}

int Root::clear(){
    for(int i = 0, e = 26; i != e; i++) {
        if(childs[i] == nullptr) continue;
        delete childs[i];
        childs[i] = nullptr; 
    }
    size = 0;
    return 0;
}