#ifndef Tree_H_
#define Tree_H_

#define DEBUG

#include<stack>
#include<iostream>

template<typename Key>
class Tree {// RB tree
public:
    Tree(size_t);
    ~Tree();
#ifdef DEBUG
    void print() const;
#endif
    void insert(Key);
    void remove(const Key&);
private:
    enum class COLOR:char{red, black};
    struct Nod{
        Nod():parent(nullptr), leftChild(&emptyNod), rightChild(&emptyNod),color{COLOR::black}, key{}{}
        Nod(Key k):parent(nullptr), leftChild(&emptyNod), rightChild(&emptyNod),color{COLOR::red}, key{k}{}

        Key key;
        COLOR color;
        Nod* parent;
        Nod* leftChild;
        Nod* rightChild;
    } *root;

    static Nod emptyNod;

    Nod* memoryStart;
    size_t sizeToAllocate;

    Nod* moveMemoryPtr;
    size_t currentSize;// size of Tree
private:
    Nod* grandparent(Nod*);
    Nod* uncle(Nod*);
    Nod* sibling(Nod*);

    void rotateLeft(Nod*);
    void rotateRight(Nod*);

    void grandparendIsNullptr(Nod*);
private://insert things
    bool findThenInsert(Nod*);
    void checkAfterInsert(Nod*);
    //cases
    void insertCase1(Nod*);
    void insertCase2(Nod*);
    void insertCase3(Nod*);


private://erase cases

};
template<typename Key>
typename Tree<Key>::Nod Tree<Key>::emptyNod = Nod();//static field


template<typename Key>
using TNod = typename Tree<Key>::Nod*;


template<typename Key>
using TColor = typename Tree<Key>::COLOR;

#ifdef DEBUG
template<typename Key>
void Tree<Key>::print() const{
    std::stack<Nod *> stack;
    stack.push(root);

    while (stack.size() != 0) {
        Nod *tempNode = stack.top();
        stack.pop();

        std::cout << "key/color:" << tempNode->key << '/';
        if( tempNode->color == COLOR::black)
            std::cout << "black" << std::endl;
        else
            std::cout << "red" << std::endl;

        if (tempNode->rightChild != &emptyNod) {
            stack.push(tempNode->rightChild);
        }
        if (tempNode->leftChild != &emptyNod) {
            stack.push(tempNode->leftChild);
        }

    }
}
#endif

template<typename Key>
Tree<Key>::Tree(size_t size) {
    try {
        sizeToAllocate = size;
        memoryStart  = new Nod[sizeToAllocate];
    } catch (std::bad_alloc &err) {
        std::cerr << err.what() << std::endl;
        sizeToAllocate /= 1.2;
        memoryStart = new Nod[sizeToAllocate];
    }
    currentSize = 0;
    moveMemoryPtr = memoryStart;
    root = nullptr;
}

template<typename Key>
Tree<Key>::~Tree(){
    delete[] memoryStart;
}


template<typename Key>
TNod<Key> Tree<Key>::grandparent(Nod *theNod) {

    if(theNod == nullptr){
        return &emptyNod;//if it's returned, something goes wrong
    }

    if(theNod->parent != nullptr){
        return theNod->parent->parent;
    }else{
        return nullptr;
    }
}

template<typename Key>
TNod<Key> Tree<Key>::uncle(Nod *theNod) {
    Nod* grandPa = grandparent(theNod);
    if(grandPa == &emptyNod){
        return &emptyNod;// something has gone wrong
    }

    if(grandPa == nullptr){
        return nullptr; // there is no grandparent, so that means parent is the root
    }

    if(grandPa->rightChild == theNod->parent){
        return grandPa->leftChild;
    }else{
        return grandPa->rightChild;
    }

}

template<typename Key>
TNod<Key> Tree<Key>::sibling(Nod *theNod) {
    if(theNod->parent != nullptr){
        if(theNod->parent->rightChild == theNod ){
            return theNod->parent->leftChild;
        }else{
            return theNod->parent->rightChild;
        }
    }else{
        return nullptr;
    }
}

template<typename Key>
void Tree<Key>::rotateLeft(Nod * theNod) {

    Nod *rootOfSubtree = theNod->rightChild;

    rootOfSubtree->parent = theNod->parent;
    if (theNod->parent != nullptr) {
        if (theNod->parent->leftChild == theNod) {
            theNod->parent->leftChild = rootOfSubtree;
        } else {
            theNod->parent->rightChild = rootOfSubtree;
        }
    }else{//it's a new root
        root = rootOfSubtree;
    }

    theNod->rightChild = rootOfSubtree->leftChild;
    if (rootOfSubtree->leftChild != &emptyNod) {
        rootOfSubtree->leftChild->parent = theNod;
    }

    theNod->parent = rootOfSubtree;
    rootOfSubtree->leftChild = theNod;
}

template<typename Key>
void Tree<Key>::rotateRight(Nod *theNod) {
    Nod *rootOfSubtree = theNod->leftChild;

    rootOfSubtree->parent = theNod->parent;
    if (theNod->parent != nullptr) {
        if (theNod->parent->leftChild == theNod) {
            theNod->parent->leftChild = rootOfSubtree;
        } else {
            theNod->parent->rightChild = rootOfSubtree;
        }
    }else{//it's a new root
        root = rootOfSubtree;
    }

    theNod->leftChild = rootOfSubtree->rightChild;
    if (rootOfSubtree->rightChild != &emptyNod) {
        rootOfSubtree->rightChild->parent = theNod;
    }

    theNod->parent = rootOfSubtree;
    rootOfSubtree->rightChild = theNod;

}

template<typename Key>
void Tree<Key>::grandparendIsNullptr(Tree::Nod *theNod) {
    if(theNod->parent == nullptr){
        root = theNod;
        theNod->color = COLOR::black;
    }else if(theNod->parent->parent = nullptr){
        theNod->parent->color = COLOR::black;
        root = theNod->parent;
    }
}

template<typename Key>
bool Tree<Key>::findThenInsert(Nod *theNod) {

    if(root == nullptr){
        root = theNod;
        return true;
    }



    std::stack<Nod*> stack;
    stack.push(root);
    while (stack.size() != 0){
        Nod* tempNod = stack.top();
        stack.pop();

        if(tempNod->key == theNod->key){
            return false;
        }

        if(tempNod->key > theNod->key){

            if(tempNod->leftChild == &emptyNod){
                tempNod->leftChild = theNod;
                theNod->parent = tempNod;
                return true;
            }
            stack.push(tempNod->leftChild);
        }else if(tempNod->key < theNod->key){

            if(tempNod->rightChild == &emptyNod){
                tempNod->rightChild = theNod;
                theNod->parent = tempNod;
                return true;
            }

            stack.push(tempNod->rightChild);
        }

    }

}

template<typename Key>
void Tree<Key>::checkAfterInsert(Tree::Nod *theNod) {
    if (theNod->parent == nullptr) {
        theNod->color = COLOR::black;
        return;
    }

    if (theNod->parent->color == COLOR::black) {
        return;
    }


    if (uncle(theNod)->color == COLOR::red) {// if uncle is red, and parent is red!!
        insertCase1(theNod);
    } else { // otherwise uncle is black
        Nod *grandP = grandparent(theNod);
        if ((theNod->parent->rightChild == theNod) && (theNod->parent == grandP->leftChild)) {
            insertCase3(theNod);
            insertCase2(theNod->leftChild);
        } else if ((theNod->parent->leftChild == theNod) && (theNod->parent == grandP->rightChild)) {
            insertCase3(theNod);
            insertCase2(theNod->rightChild);
        }else{
            insertCase2(theNod);
        }
    }
}

template<typename Key>
void Tree<Key>::insertCase1(Nod *theNod) { //if uncle is red
    Nod *uncl = uncle(theNod);
    if(uncl == nullptr){
        grandparendIsNullptr(theNod);
        return;
    }

    theNod->parent->color = COLOR::black;// changing a parent color
    theNod->parent->parent->color = COLOR::red;// for grandparent
    uncl->color = COLOR::black;


    checkAfterInsert(uncl->parent);
}

template<typename Key>
void Tree<Key>::insertCase2(Tree::Nod *theNod) {// rotating
    Nod *grandP = grandparent(theNod);
    if(grandP == nullptr){
        grandparendIsNullptr(theNod);
        return;
    }


    theNod->parent->color = COLOR::black;
    grandP->color = COLOR::red;
    if (theNod->parent == grandP->leftChild) {
        rotateRight(grandP);
    } else if (theNod->parent == grandP->rightChild) {
        rotateLeft(grandP);
    }
}

template<typename Key>
void Tree<Key>::insertCase3(Tree::Nod *theNod) { //small rotating
    Nod *grandP = grandparent(theNod);
    if(grandP == nullptr){
        grandparendIsNullptr(theNod);
        return;
    }

    if ((theNod->parent->rightChild == theNod) && (theNod->parent == grandP->leftChild)) {
        rotateLeft(theNod->parent);
    } else if ((theNod->parent->leftChild == theNod) && (theNod->parent == grandP->rightChild)) {
        rotateRight(theNod->parent);
    }
}

template<typename Key>
void Tree<Key>::insert(Key key) {
    Nod* theNod;
    if(currentSize + 1  <= sizeToAllocate){
        theNod = new(moveMemoryPtr) Nod(key);
        moveMemoryPtr++;
        currentSize++;
    }else{
        std::cerr << "Can't allocate memory, memory of Tree is full" << std::endl;
        return;
    }

    if(findThenInsert(theNod)){
        checkAfterInsert(theNod);
    }else{
#ifdef DEBUG
        std::cout << "Elem exists! " << std::endl;
#endif
        return;
    }





}










#endif //Tree_H_