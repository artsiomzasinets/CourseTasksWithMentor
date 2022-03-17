//
// Created by artom on 03.03.2022.
//

#include "Tree.h"


Nod Tree::emptyNod = Nod(COLOR::black);


Tree::Tree(size_t number) {
    try {
        currentNumberOfNod = 0;
        numberOfNod = number;
        allocatedMemory = new Nod[numberOfNod];
        movePointer = allocatedMemory;
        root = nullptr;
    } catch (std::bad_alloc &err) {
        std::cerr << err.what() << std::endl;

        numberOfNod /= 1.2;
        allocatedMemory = new Nod[numberOfNod];
        movePointer = allocatedMemory;
        root = nullptr;
    }

}

Tree::~Tree() {
    delete[] allocatedMemory;
}

void Tree::printAll() const {
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


Nod *Tree::grandparent(Nod *theNod) {
    if (theNod != &emptyNod && theNod->parent != nullptr) {
        return theNod->parent->parent;
    } else {
        return nullptr;
    }
}

Nod *Tree::uncle(Nod *theNod) {
    Nod *grandP = grandparent(theNod);
    if (grandP == nullptr) {
        return nullptr;
    } else if (theNod->parent == grandP->leftChild) {
        return grandP->rightChild;
    } else {
        return grandP->leftChild;
    }
}

Nod* Tree::sibling(Nod *theNod) {
    if(theNod->parent->leftChild == theNod){
        return theNod->parent->rightChild;
    }else{
        return  theNod->parent->leftChild;
    }
}


bool Tree::find(size_t theKey) const {
    std::stack<Nod *> stack;
    stack.push(root);

    while (stack.size() != 0) {
        Nod *tempNode = stack.top();
        stack.pop();


        if (theKey == tempNode->key) {
            return true;
        }

        if (tempNode->rightChild != &emptyNod) {
            stack.push(tempNode->rightChild);
        }
        if (tempNode->leftChild != &emptyNod) {
            stack.push(tempNode->leftChild);
        }

    }
    return false;
}

bool Tree::findAndInsert(Nod *theNod) {
    std::stack<Nod *> stack;
    stack.push(root);


    while (stack.size() != 0) {

        Nod *tempNod = stack.top();
        stack.pop();


        if (theNod->key == tempNod->key) {
            return false;
        } else if (theNod->key < tempNod->key) {
            if (tempNod->leftChild == &emptyNod) {
                tempNod->leftChild = theNod;
                theNod->parent = tempNod;
                return true;
            }
            stack.push(tempNod->leftChild);

        } else if (theNod->key > tempNod->key) {
            if (tempNod->rightChild == &emptyNod) {
                tempNod->rightChild = theNod;
                theNod->parent = tempNod;
                return true;
            }
            stack.push(tempNod->rightChild);
        }
    }
    return false;
}


void Tree::rotateLeft(Nod *insertedNod) {
    Nod *rootOfSubtree = insertedNod->rightChild;

    rootOfSubtree->parent = insertedNod->parent;
    if (insertedNod->parent != nullptr) {
        if (insertedNod->parent->leftChild == insertedNod) {
            insertedNod->parent->leftChild = rootOfSubtree;
        } else {
            insertedNod->parent->rightChild = rootOfSubtree;
        }
    }else{//it's a new root
        root = rootOfSubtree;
    }

    insertedNod->rightChild = rootOfSubtree->leftChild;
    if (rootOfSubtree->leftChild !=
        nullptr) {
        rootOfSubtree->leftChild->parent = insertedNod;
    }

    insertedNod->parent = rootOfSubtree;
    rootOfSubtree->leftChild = insertedNod;

}

void Tree::rotateRight(Nod *insertedNod) {
    Nod *rootOfSubtree = insertedNod->leftChild;

    rootOfSubtree->parent = insertedNod->parent;
    if (insertedNod->parent != nullptr) {
        if (insertedNod->parent->leftChild == insertedNod) {
            insertedNod->parent->leftChild = rootOfSubtree;
        } else {
            insertedNod->parent->rightChild = rootOfSubtree;
        }
    }else{//it's a new root
        root = rootOfSubtree;
    }

    insertedNod->leftChild = rootOfSubtree->rightChild;
    if (rootOfSubtree->rightChild !=
        nullptr) {
        rootOfSubtree->rightChild->parent = insertedNod;
    }

    insertedNod->parent = rootOfSubtree;
    rootOfSubtree->rightChild = insertedNod;

}


void Tree::checkAfterInsert(Nod *nodToInsert) {//checking if everything is ok, Is it tree correct

    if (nodToInsert->parent == nullptr) {
        nodToInsert->color = COLOR::black;
        return;
    }

    if (nodToInsert->parent->color == COLOR::black) {
        return;
    }


    if (uncle(nodToInsert)->color == COLOR::red) {// if uncle is red, and parent is red!!
        insertCase1(nodToInsert);
    } else { // otherwise uncle is black
            Nod *grandP = grandparent(nodToInsert);
            if ((nodToInsert->parent->rightChild == nodToInsert) && (nodToInsert->parent == grandP->leftChild)) {
                insertCase3(nodToInsert);
                insertCase2(nodToInsert->leftChild);
            } else if ((nodToInsert->parent->leftChild == nodToInsert) && (nodToInsert->parent == grandP->rightChild)) {
                insertCase3(nodToInsert);
                insertCase2(nodToInsert->rightChild);
            }else{
                insertCase2(nodToInsert);
            }

    }
}

void Tree::insert(size_t theKey) {

    //create the root!
    if (root == nullptr) {
        if (currentNumberOfNod + 1 < numberOfNod) {//checking for range
            root = new(movePointer) Nod(COLOR::black);// using placement new
            movePointer += 1;
            currentNumberOfNod++;
        } else {
            return;
        }
        root->leftChild = root->rightChild = &emptyNod;
        root->key = theKey;
        return;
    }



    // if root exists it's found a leaf to insert
    Nod *nodToInsert;
    if (currentNumberOfNod + 1 < numberOfNod) {//checking for range
        nodToInsert = new(movePointer) Nod();// create red node to insert
        nodToInsert->key = theKey;
        nodToInsert->rightChild = nodToInsert->leftChild = &emptyNod;
        movePointer += 1;
        currentNumberOfNod++;
    } else {
        return;// if it's impossible to create a node
    }


    if (findAndInsert(nodToInsert)) {// if it's possible  the function inserts "nodToInsert"
        // but if something goes wrong it returns "false"
        checkAfterInsert(nodToInsert);
    } else {
        return;
    }


}


void Tree::insertCase1(Nod *insertedNod) {

    Nod *uncl = uncle(insertedNod);

    insertedNod->parent->color = COLOR::black;// changing a parent color
    insertedNod->parent->parent->color = COLOR::red;// for grandparent
    uncl->color = COLOR::black;


    checkAfterInsert(uncl->parent);


}

void Tree::insertCase2(Nod *insertedNod) { // for rotating
    Nod *grandP = grandparent(insertedNod);

    insertedNod->parent->color = COLOR::black;
    grandP->color = COLOR::red;
    if ((insertedNod->parent->leftChild == insertedNod) && (insertedNod->parent == grandP->leftChild)) {
        rotateRight(grandP);
    } else if ((insertedNod->parent->rightChild == insertedNod) && (insertedNod->parent == grandP->rightChild)) {
        rotateLeft(grandP);
    }
}

void Tree::insertCase3(Nod *insertedNod) {// for small rotating
    Nod *grandP = grandparent(insertedNod);
    if ((insertedNod->parent->rightChild == insertedNod) && (insertedNod->parent == grandP->leftChild)) {
        rotateLeft(insertedNod->parent);
    } else if ((insertedNod->parent->leftChild == insertedNod) && (insertedNod->parent == grandP->rightChild)) {
        rotateRight(insertedNod->parent);
    }
}


void Tree::remove(size_t theKey) {
    Nod* nodToRemove = findElemToRemove(theKey);
    if(nodToRemove != nullptr){
        deleteTheNod(nodToRemove);
    }else{
        std::cout << "Element is not found" << std::endl;
    }
}



void Tree::removeCase2(Nod *theNod) {
    if(theNod->parent->leftChild == theNod)
        theNod->parent->leftChild = &emptyNod;
    else
        theNod->parent->rightChild = &emptyNod;
}

void Tree::removeCase3(Nod *theNod) {
    Nod* child = theNod->leftChild == &emptyNod ? theNod->rightChild : theNod->leftChild;

    if(theNod->parent->leftChild == theNod)
        theNod->parent->leftChild = child;
    else
        theNod->parent->rightChild = child;

    child->color = COLOR::black;
    child->leftChild = child->rightChild = &emptyNod;
}

void Tree::removeCase1(Nod * theNod) {
    Nod* grandP = grandparent(theNod);
    Nod* uncl = uncle(theNod);

    if(theNod->parent->leftChild == theNod)
        theNod->parent->leftChild = &emptyNod;
    else
        theNod->parent->rightChild = &emptyNod;

    if(grandP->color == COLOR::red){

        if ((theNod->parent->rightChild == theNod) && (theNod->parent == grandP->leftChild)) {

            if(uncl->rightChild->color == COLOR::red){
                rotateLeft(uncl);
                rotateRight(grandP);
            }else if(uncl->leftChild->color == COLOR::red){
                rotateRight(grandP);
            }else{// if uncle doesn't have red child
                uncl->color = COLOR::red;
                grandP->color = COLOR::black;
            }

        } else if ((theNod->parent->leftChild == theNod) && (theNod->parent == grandP->rightChild)) {
            if(uncl->leftChild->color == COLOR::red){
                rotateRight(uncl);
                rotateLeft(grandP);
            }else if(uncl->rightChild->color == COLOR::red){
                rotateLeft(grandP);
            }else{// if uncle doesn't have red child
                uncl->color = COLOR::red;
                grandP->color = COLOR::black;
            }
        }



    }else{//if grandparent has black color

        if(uncl->color == COLOR::red){

            if(uncl->rightChild->color == COLOR::black){

            }

        }else{//uncle is black

        }

    }


}

void Tree::removeCase4(Nod *theNod) {

}

void Tree::removeCase5(Nod *theNod) {

}

void Tree::removeCase6(Nod *theNod) {

}

Nod *Tree::findElemToRemove(size_t theKey) {
    std::stack<Nod*> stack;
    stack.push(root);

    Nod* tempPtr;
    while (stack.size() != 0){
        tempPtr = stack.top();
        stack.pop();

        if(tempPtr->key == theKey){
            return tempPtr;
        }

        if(tempPtr->leftChild != &emptyNod)
            stack.push(tempPtr->leftChild);
        if(tempPtr->rightChild != &emptyNod)
            stack.push(tempPtr->rightChild);

    }

    return nullptr;
}

void Tree::deleteTheNod(Nod *theNod) {
    if((theNod->leftChild == &emptyNod) && (theNod-> rightChild == &emptyNod)){

        if(theNod->parent == nullptr){
            root = nullptr;
        }

        if(theNod->color == COLOR::red){
            removeCase2(theNod);
        }else{
            removeCase1(theNod);
        }
    }else if((theNod->leftChild != &emptyNod) && (theNod-> rightChild != &emptyNod)){// find the max elem in leftchild
        std::stack<Nod*> stack;
        stack.push(theNod->leftChild);
        Nod* tempPtr;
        while (stack.size() != 0){
            tempPtr = stack.top();
            stack.pop();

            if(tempPtr->rightChild == &emptyNod){
                theNod->key = tempPtr->key;
                deleteTheNod(tempPtr);
                break;
            }
            stack.push(tempPtr->rightChild);
        }
    }else{//if nod has a child
        removeCase3(theNod);
    }

}












