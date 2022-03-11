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


Nod *Tree::grandparent(Nod *theNod) {
    if (theNod != nullptr && theNod->parent != nullptr) {
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
}

void Tree::check(Nod *nodToInsert) {//checking if everything is ok, Is it tree correct

    if (nodToInsert->parent == nullptr) {
        nodToInsert->parent->color = COLOR::black;
        return;
    }

    if (nodToInsert->parent->color == COLOR::black) {
        return;
    }


    if (uncle(nodToInsert)->color == COLOR::red) {// if uncle is red, and parent is red!!
        insertCase1(nodToInsert);
    } else { // otherwise uncle is black

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
    Nod *nodToInsert = nullptr;
    if (currentNumberOfNod + 1 < numberOfNod) {//checking for range
        nodToInsert = new(movePointer) Nod();// create red node to insert
        nodToInsert->key = theKey;
        nodToInsert->rightChild = nodToInsert->leftChild = &emptyNod;
        movePointer += 1;
        currentNumberOfNod++;
    } else {
        return;// if it's impossible to create a node
    }


    if (findAndInsert(
            nodToInsert)) {// if it's possible  the function inserts "nodToInsert" but if something goes wrong it returns "false"
        check(nodToInsert);

    } else {
        return;
    }


}


void Tree::insertCase1(Nod *insertedNod) {

    Nod *tempNod = insertedNod;// firstly it's for "insertedNod" then it'll be using for grandparents


    Nod *uncl = uncle(insertedNod);

    insertedNod->parent->color = COLOR::black;// changing a parent color
    insertedNod->parent->parent->color = COLOR::red;// for grandparent
    uncl->color = COLOR::black;

    tempNod = uncl->parent;

    check(insertedNod);


}

void Tree::insertCase2(Nod *) { // for rotating

}

void Tree::insertCase3(Nod *) {

}


void Tree::remove(size_t theKey) {

}








