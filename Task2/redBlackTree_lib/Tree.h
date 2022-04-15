#ifndef Tree_H_
#define Tree_H_



#include<stack>
#include<iostream>
#include<exception>

template<typename Key>
class Tree {// RB tree
public:
    Tree(size_t);
    ~Tree();

    bool findElem(Key);
    void insert(Key);
    void remove(const Key&);
    Key thelatestRemovedElem{};
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
    Nod* grandparent(Nod*)const;
    Nod* uncle(Nod*)const;
    Nod* sibling(Nod*)const;

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
    Nod* findEraseNod(const Key&);
    Nod* findDelete(Nod*);

    void eraseCase1(Nod*);// theNod is red and have only leafs
    void eraseCase2(Nod*);// theNod have only one leaf

    void eraseCase3(Nod*,bool);//theNod is black and have only leafs

};
template<typename Key>
typename Tree<Key>::Nod Tree<Key>::emptyNod = Nod();//static field


template<typename Key>
using TNod = typename Tree<Key>::Nod*;


template<typename Key>
using TColor = typename Tree<Key>::COLOR;


template<typename Key>
bool Tree<Key>::findElem(Key theKey) {
    if(root == nullptr)
        return false;

    std::stack<Nod*> stack;
    stack.push(root);
    Nod* tempNod;

    while (stack.size() != 0){
        tempNod = stack.top();
        stack.pop();

        if(tempNod == &emptyNod)
            break;

        if(tempNod->key == theKey)
            return true;

        if(tempNod->key > theKey)
            stack.push(tempNod->leftChild);

        if(tempNod->key < theKey)
            stack.push(tempNod->rightChild);
    }
    return false;
}

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
TNod<Key> Tree<Key>::grandparent(Nod *theNod) const {

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
TNod<Key> Tree<Key>::uncle(Nod *theNod) const{
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
TNod<Key> Tree<Key>::sibling(Nod *theNod) const{
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
    return false;

}

template<typename Key>
void Tree<Key>::checkAfterInsert(Tree::Nod *theNod){
    if (theNod->parent == nullptr) {
        theNod->color = COLOR::black;
        root = theNod;
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
        theNod = new(moveMemoryPtr) Nod(key);//TODO alloc
        moveMemoryPtr++;
        currentSize++;
    }else{
        std::cerr << "Can't allocate memory, memory of Tree is full" << std::endl;
        return;
    }

    if(findThenInsert(theNod)){
        checkAfterInsert(theNod);
    }else{
        return;
    }
}

template<typename Key>
TNod<Key> Tree<Key>::findEraseNod(const Key& key){

    std::stack<Nod*> stack;
    stack.push(root);
    Nod* tempNod;

    while (stack.size() != 0){
        tempNod = stack.top();
        stack.pop();

        if(tempNod->key == key){
            return tempNod;
        }

        if(tempNod->key < key){
            if(tempNod->rightChild != &emptyNod)
                stack.push(tempNod->rightChild);
        }else if(tempNod->key > key){
            if(tempNod->leftChild != &emptyNod)
                stack.push(tempNod->leftChild);
        }
    }
    return nullptr;
}

template<typename Key>
TNod<Key> Tree<Key>::findDelete(Nod *theNod) {//find a max element in subtree then swap
    Nod* tempNod = theNod->leftChild;
    while (true){
        if(tempNod->rightChild == &emptyNod){
            theNod->key = tempNod->key;
            return tempNod;
        }
        tempNod = tempNod->rightChild;
    }
}

template<typename Key>
void Tree<Key>::eraseCase1(Nod *theNod) {
    Nod* parent = theNod->parent;

    if(parent->leftChild == theNod){
        parent->leftChild = &emptyNod;
    }else{// parent->rightChild == theNod
        parent->rightChild = &emptyNod;
    }

    //delete theNod;
}

template<typename Key>
void Tree<Key>::eraseCase2(Nod *theNod) {
    if(theNod->rightChild == &emptyNod){
        theNod->key = theNod->leftChild->key;
       // delete theNod->leftChild;
        theNod->leftChild = &emptyNod;
    }else{//theNod->leftChild == &emptyNod
        theNod->key = theNod->rightChild->key;
       // delete theNod->rightChild;
        theNod->rightChild = &emptyNod;
    }
}

template<typename Key>
void Tree<Key>::eraseCase3(Nod *theNod,bool isDeleted) {
    if(theNod->parent == nullptr){
        theNod->color = COLOR::black;
        root = theNod;
        return;
    }


    Nod* parent = theNod->parent;
    Nod* sibl = sibling(theNod);

    if(isDeleted == false){
        if(parent->leftChild == theNod){
            parent->leftChild = &emptyNod;
        }else{
            parent->rightChild = &emptyNod;
        }
    }//TODO

    if(parent->color == COLOR::red){//silbing is only black

        if(sibl->rightChild->color == COLOR::red || sibl->leftChild->color == COLOR::red){//TODO Maybe there is emptyNod problem

            if(parent->leftChild == sibl){
                if(sibl->rightChild->color == COLOR::red){
                    rotateLeft(sibl);
                    rotateRight(parent);
                    parent->color = COLOR::black;
                }else{//if leftChild is red
                    rotateRight(parent);
                }
                return;
            }else{//parent->rightChild == sibl

                if(sibl->leftChild->color == COLOR::red){
                    rotateRight(sibl);
                    rotateLeft(parent);
                    parent->color = COLOR::black;
                }else{//if leftChild is red
                    rotateLeft(parent);
                }
                return;
            }
        }else {//sibl doesn't have a red child
            parent->color = COLOR::black;
            sibl->color = COLOR::red;
        }


    }else{//parent->color == COLOR::black
        Nod* siblRightChild = sibl->rightChild;
        Nod* siblLeftChild = sibl->leftChild;
        if(sibl->color == COLOR::red){
            if(parent->leftChild == sibl){
                if(siblRightChild->leftChild->color == COLOR::red){
                        siblRightChild->leftChild->color = COLOR::black;
                        rotateLeft(sibl);
                        rotateRight(parent);
                }else if(siblRightChild->rightChild->color == COLOR::red){
                    rotateLeft(sibl);
                    rotateRight(parent);
                }else{//doesn't have a red child
                    sibl->color = COLOR::black;
                    siblRightChild->color = COLOR::red;
                    rotateRight(parent);
                }

            }else if(parent->rightChild == sibl){
                if(siblLeftChild->leftChild->color == COLOR::red){
                    rotateRight(sibl);
                    rotateLeft(parent);
                }else if(siblLeftChild->rightChild->color == COLOR::red){
                    siblLeftChild->rightChild->color = COLOR::black;
                    rotateRight(sibl);
                    rotateLeft(parent);
                }else{//doesn't have a red child
                    sibl->color = COLOR::black;
                    siblLeftChild->color = COLOR::red;
                    rotateLeft(parent);
                }
            }

        }else{//sibl->color == COLOR::black
            if(parent->leftChild == sibl){
                if(siblRightChild->color == COLOR::red){
                    siblRightChild->color = COLOR::black;
                    rotateLeft(sibl);
                    rotateRight(parent);
                }else if(siblLeftChild->color == COLOR::red){
                    siblLeftChild->color = COLOR::black;
                    rotateRight(parent);
                }else{//doesn't have a red child
                    sibl->color = COLOR::red;
                    eraseCase3(parent,true);
                }
            }else{//parent->rightChild == sibl
                if(siblLeftChild->color == COLOR::red){
                    siblLeftChild->color = COLOR::black;
                    rotateRight(sibl);
                    rotateLeft(parent);
                }else if(siblRightChild->color == COLOR::red){
                    siblRightChild->color = COLOR::black;
                    rotateLeft(parent);
                }else{//doesn't have a red child
                    sibl->color = COLOR::red;
                    eraseCase3(parent,true);
                }
            }
        }
    }





}

template<typename Key>
void Tree<Key>::remove(const Key &key) {
    if(root == nullptr){
        return;
    }
    Nod* nodToErase = findEraseNod(key);


    if(nodToErase == nullptr){
        return;
    }

    thelatestRemovedElem = nodToErase->key;

    if(nodToErase->parent == nullptr){
        //delete root;
        root = nullptr;//TODO alloc
    }


    if(nodToErase->leftChild != &emptyNod && nodToErase->rightChild != &emptyNod) {
        nodToErase = findDelete(nodToErase);
    }

    if(nodToErase->leftChild == &emptyNod && nodToErase->rightChild == &emptyNod){
        if(nodToErase->color == COLOR::red){
            eraseCase1(nodToErase);
        }else{// nodToErase is black
            eraseCase3(nodToErase,false);
        }
    }else {// nodToErase has one leaf
        eraseCase2(nodToErase);
    }
}



#endif //Tree_H_