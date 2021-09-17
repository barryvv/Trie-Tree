#ifndef HEADER__H__
#define HEADER__H__
#include<string>
#include<exception>

class Node{
private:
    char value;
    bool isTerminal;
    int size; // child of node
    Node *childs[26];
public:
    Node();
    Node(std::string& str, int index = 0);
    ~Node();

    bool getEmpty() {return size == 0;}
    bool getTerminal() {return isTerminal;}
    Node *getChild(int i) {return childs[i];}
    char getValue() {return value;}
    bool addWords(std::string &str, int index = 0);
    bool removeWords(std::string &str, int index = 0);
};

class Root {
private:
    Node *childs[26];
    int size;

public:
    Root();
    ~Root();
    bool insertWord(std::string str);
    bool eraseWord(std::string str);
    bool searchWord(std::string str); // return true if word in the tree
    void print();
    void print(Node *p, std::string &str);
    void autoComplete(std::string str);
    bool empty() {return size == 0;}
    int clear();
    int getSize() {return size;}
};

class illegal_exception{
private:
    std::string message{"illegal argument"};
public:
    illegal_exception(){}
    std::string what(){return message;}
};


#endif