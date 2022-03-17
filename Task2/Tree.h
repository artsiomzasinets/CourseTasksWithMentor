//
// Created by artom on 03.03.2022.
//

#ifndef Tree_H_
#define Tree_H_
#include<stack>
#include<iostream>

enum class COLOR:char{red, black};

struct Nod{
    Nod():parent(nullptr),leftChild(nullptr), rightChild(nullptr),color(COLOR::red){}
    Nod(COLOR col):parent(nullptr),leftChild(nullptr), rightChild(nullptr),color(col){}
    Nod* parent;
    Nod* leftChild;
    Nod* rightChild;
    size_t key;
    COLOR color;
};

class Tree {
public:
    Tree(size_t); // number of "Nod" to allocate
    ~Tree();
    void insert(size_t);
    void remove(size_t);
    bool find(size_t) const;
    void printAll()const;

private:// insert cases
    void insertCase1(Nod*);
    void insertCase2(Nod*);
    void insertCase3(Nod*);
private:// remove cases
    void removeCase1(Nod*);//if nod has black color and doesn't have children
    void removeCase2(Nod*);//if nod has red color and doesn't have children
    void removeCase3(Nod*);//if nod has red/black color and has a child
    void removeCase4(Nod*);
    void removeCase5(Nod*);
    void removeCase6(Nod*);
private:
    Nod* grandparent(Nod*);
    Nod* uncle(Nod*);
    Nod* sibling(Nod*);
    bool findAndInsert(Nod*);
    Nod* findElemToRemove(size_t);
    void deleteTheNod(Nod*);
    void checkAfterInsert(Nod*);
    void rotateLeft(Nod*);
    void rotateRight(Nod*);
private:
    Nod* allocatedMemory;// allocated memory for using by "placement new"
    Nod* movePointer; // it's used for pointing to free memory

    Nod* root;
    size_t numberOfNod, currentNumberOfNod;
    static Nod emptyNod;// black leaf
};


#endif //Tree_H_