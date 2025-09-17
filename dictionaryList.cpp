#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include "dictionaryList.h"
using namespace std;

Node::Node(const int& keyA, const Datum& datumA, Node *nextA)
: keyM(keyA), datumM(datumA), nextM(nextA)
{
}

DictionaryList::DictionaryList()
: sizeM(0), headM(0), cursorM(0)
{
}

int DictionaryList::size() const
{
    return sizeM;
}

int DictionaryList::cursor_ok() const
{
    return cursorM != 0;
}

const int& DictionaryList::cursor_key() const
{
    assert(cursor_ok());
    return cursorM->keyM;
}

const Datum& DictionaryList::cursor_datum() const
{
    assert(cursor_ok());
    return cursorM->datumM;
}

void DictionaryList::insert(const int& keyA, const string& datumA)
{
    // Add new node at head?
    if (headM == 0 || keyA < headM->keyM) {
        headM = new Node(keyA, datumA, headM);
        sizeM++;
    }
    
    // Overwrite datum at head?
    else if (keyA == headM->keyM)
        headM->datumM = datumA;
    
    // Have to search ...
    else {
        
        //POINT ONE
        
        // if key is found in list, just overwrite data;
        for (Node *p = headM; p !=0; p = p->nextM)
        {
            if(keyA == p->keyM)
            {
                p->datumM = datumA;
                return;
            }
        }
        
        //OK, find place to insert new node ...
        Node *p = headM ->nextM;
        Node *prev = headM;
        
        while(p !=0 && keyA >p->keyM)
        {
            prev = p;
            p = p->nextM;
        }
        
        prev->nextM = new Node(keyA, datumA, p);
        sizeM++;
    }
    cursorM = NULL;
    
}

void DictionaryList::remove(const int& keyA)
{
    if (headM == 0 || keyA < headM -> keyM)
        return;
    
    Node *doomed_node = 0;
    
    if (keyA == headM-> keyM) {
        doomed_node = headM;
        headM = headM->nextM;
        
        // POINT TWO
    }
    else {
        Node *before = headM;
        Node *maybe_doomed = headM->nextM;
        while(maybe_doomed != 0 && keyA > maybe_doomed-> keyM) {
            before = maybe_doomed;
            maybe_doomed = maybe_doomed->nextM;
        }
        
        if (maybe_doomed != 0 && maybe_doomed->keyM == keyA) {
            doomed_node = maybe_doomed;
            before->nextM = maybe_doomed->nextM;
        }
        
        
    }
    if(doomed_node == cursorM)
        cursorM = 0;
    
    delete doomed_node;           // Does nothing if doomed_node == 0.
    sizeM--;
}

void DictionaryList::go_to_first()
{
    cursorM = headM;
}

void DictionaryList::step_fwd()
{
    assert(cursor_ok());
    cursorM = cursorM->nextM;
}



// The following functions are supposed to be completed by the stuents, as part
// of the exercise B. the given code for this fucntion are just place-holders
// in order to allow successful linking when you're esting insert and remove.
// Replace them with the definitions that work.

DictionaryList::DictionaryList(const DictionaryList& source)
{
    if (source.headM == nullptr){
        headM = nullptr;
    }
    headM = new Node(source.headM->keyM,source.headM->datumM, source.headM->nextM);
    Node *newTail = headM;
    Node *orgNext = source.headM->nextM;

    while(orgNext != nullptr){
        newTail->nextM = new Node(orgNext->keyM, orgNext->datumM, orgNext->nextM); 
        orgNext = orgNext->nextM;
        newTail = newTail->nextM;
    }
}

DictionaryList& DictionaryList::operator =(const DictionaryList& rhs)
{
    if (this == &rhs){
        return *this;
    }
    while(this->headM != nullptr){
        Node *next = this->headM->nextM;
        delete this->headM;
        this->headM = next; 
    }
    if(rhs.headM == nullptr){
        return;
    }
    
    while(rhs.headM != nullptr){
        new Node *
    }

    // if (rhs.headM == nullptr){
    //     headM = nullptr;
    //     return;
    // }
    // delete all nodes in 
    // headM = new Node(rhs.headM->keyM,rhs.headM->datumM, rhs.headM->nextM);
    // Node *newTail = headM;
    // Node *orgNext = rhs.headM->nextM;

    // while(orgNext != nullptr){
    //     newTail->nextM = new Node(orgNext->keyM, orgNext->datumM, orgNext->nextM); 
    //     orgNext = orgNext->nextM;
    //     newTail = newTail->nextM;
    // }
    // return *this;
}

DictionaryList::~DictionaryList()
{
    while(headM){
        Node *next = headM -> nextM;
        delete headM;
        headM = next;
    }
}

void DictionaryList::find(const int& keyA)
{
    // Students should replace these messages with proper code.
    cout << "\nDon't know how to find " << keyA << " (or any other key).\n";
    cout << "... so exit is being called.\n";
    exit(1);
}

void DictionaryList::make_empty()
{
    // Students should replace these messages with proper code.
    // cout << "\nWARNING: call to the function make_empty failed, because it is not properly implemented.";
    // cout << " Students should fix it and remove this warning." << endl;

}
