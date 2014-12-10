//
//  LinkedList.c
//  HashChainFileSplit
//
//  Created by In Chan Hwang on 12/8/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//

#include "LinkedList.h"

Node* CreateNode(ElementType newData, ElementType newKey){
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    newNode->value = newData;
    newNode->key = newKey;
    newNode->prevNode = NULL;
    newNode->nextNode = NULL;
    newNode->lruNode = NULL;
    
    return newNode;
}

Node* CreateNodeLRU(ElementType newData){
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    newNode->value = newData;
    newNode->key = newData;
    newNode->prevNode = NULL;
    newNode->nextNode = NULL;
    newNode->lruNode = NULL;
    
    return newNode;
}



void DestroyNode(Node* node){
    free(node);
}




int LookUpFunctionForValue(Node* head, int numInput){
    int foundOrNot = 0;
    int indexNum = -1;
    int valueReturned = 0;
    for(int i=0; i<GetNodeCount(head); i++){
        int numData = GetNodeAt(head, i)->key;
        if(numInput == numData){
            indexNum = i;
            foundOrNot = 1;
            valueReturned = GetNodeAt(head,i)->value;
        }
    }
    
    return valueReturned;
    //returns a number when it is present, but returns 0 when it is not found
    
}




int LookUpFunctionForIndexNum(Node* head, int numInput){
    int foundOrNot = 0;
    int indexNum = -1;
    int valueReturned = 0;
    for(int i=0; i<GetNodeCount(head); i++){
        int numData = GetNodeAt(head, i)->key;
        if(numInput == numData){
            indexNum = i;
            foundOrNot = 1;
            valueReturned = GetNodeAt(head,i)->value;
        }
    }
    
    return indexNum;
    //returns -1 when it is present, but returns 0 when it is not found
    
}





void RemoveNode(Node** head, Node* remove){
    //if the head is identical to the one to remove
    if(*head == remove){
        
        
        //head points to the address of the next node
        *head = remove->nextNode;
        
        //if the head still exists,
        if((*head) != NULL)//Null is assigned because the previous node does not exist.
            (*head)->prevNode = NULL;
        
        
        remove->prevNode = NULL;
        remove->nextNode = NULL;
        
    } else {
        Node* temp = remove;
        //If the node to remove still has the previous node address
        if(remove->prevNode != NULL)//The previous node is connected with the next node
            remove->prevNode->nextNode = temp->nextNode;
        //if the node to remove still has the next node address
        if(remove->nextNode != NULL)//the next node address and the previous node address are connected together.
            remove->nextNode->prevNode = remove->prevNode;
        remove->prevNode = NULL;
        remove->nextNode = NULL;
    }
}


//Node searching
Node* GetNodeAt(Node* head, int location){
    Node* current = head;
    
    while(current != NULL && (--location) >= 0){
        current = current->nextNode;
    }
    return current;
}

//Count nodes
int GetNodeCount(Node* head){
    int count = 0;
    Node* current = head;
    
    while(current != NULL){
        current = current->nextNode;
        count++;
    }
    return count;
}



void AppendNode(Node** head, Node* newNode){
    if(*head == NULL)
        *head = newNode;
    else {
        Node* tail = *head;
        while(tail->nextNode != NULL)
            tail = tail->nextNode;
        
        tail->nextNode = newNode;
        //The current tail node is pointed by the preNode of the new node.
        newNode->prevNode = tail;
    }
}

List LRUOperationForAsingleBuffer(List thList, ElementType Key, ElementType result, int indexForTheResult, int MAX_HORIZANTAL_CACHE_SIZE){
    
    List newProcessedList = thList;
    if(result == 0){
        Node* newNode = CreateNode(Key, Key);
        AppendNode(&newProcessedList, newNode);
        
        if(GetNodeCount(newProcessedList)>MAX_HORIZANTAL_CACHE_SIZE){
            Node* theLastNodeToRemove = GetNodeAt(newProcessedList, 0);
            RemoveNode(&newProcessedList, theLastNodeToRemove);
            
            DestroyNode(theLastNodeToRemove);
        }
        
        
    } else {
        RemoveNode(&newProcessedList, GetNodeAt(newProcessedList, indexForTheResult));
        
        Node* newNode = CreateNode(Key, Key);
        AppendNode(&newProcessedList, newNode);
    }
    return newProcessedList;
}

void AppendNodeLRU(Node** Head, Node* NewNode){
    if((*Head) == NULL){
        *Head = NewNode;
    } else {
        Node* Tail = (*Head);
        while(Tail->lruNode != NULL){
            Tail = Tail->lruNode;
        }
        Tail->lruNode = NewNode;
        Tail->prevNode=NULL;
        Tail->nextNode=NULL;
    }
    
    
    
}

void RemoveNodeLRU(Node** Head, Node* Remove){
    if(*Head == Remove){
        Remove->nextNode =NULL;
        Remove->prevNode =NULL;
        *Head = Remove->lruNode;
    } else {
        Node* Current = *Head;
        while(Current != NULL && Current->lruNode != Remove){
            Current = Current->lruNode;
        }
        if(Current != NULL)
            Current->lruNode = Remove->lruNode;
        
        Remove->nextNode =NULL;
        Remove->prevNode =NULL;
    }
}

Node* GetNodeAtLRU(Node* Head, int Location){
    Node* Current = Head;
    while(Current != NULL && (--Location) >= 0) {
        Current = Current->lruNode;
    }
    return Current;
}


int GetNodeCountLRU(Node* Head){
    int Count = 0;
    Node* Current = Head;
    
    while(Current != NULL){
        Current = Current->lruNode;
        Count++;
    }
    return Count;
}

int LookUpFunctionForIndexNumLRU(Node* head, int numInput){
    int foundOrNot = 0;
    int indexNum = -1;
    int valueReturned = 0;
    for(int i=0; i<GetNodeCountLRU(head); i++){
        int numData = GetNodeAtLRU(head, i)->key;
        if(numInput == numData){
            indexNum = i;
            foundOrNot = 1;
            valueReturned = GetNodeAtLRU(head,i)->value;
        }
    }
    
    return indexNum;
    //returns -1 when it is present, but returns 0 when it is not found
    
}


Node* inputToLRULine(Node* list, int submittingNum){
    
    List newList = list;
    int numToSubmit = submittingNum;
    
    //printf("a generated number moving into the cache is %d\n ", numToSubmit);
    Node* newNode = NULL;
    Node* firstNode = NULL;
    //int cacheElementCount = sizeof(numbersInCache)/sizeof(int);
    
    int indexNumForOperation = LookUpFunctionForIndexNumLRU(list, numToSubmit);//returns an index number, -1 is returned when it cannot find any.
    if(indexNumForOperation == -1 ){
        
        List newNodeToLRU = CreateNodeLRU(numToSubmit);
        
        firstNode = GetNodeAtLRU(list, 0);
        
        RemoveNodeLRU(&newList, firstNode);
        
        AppendNodeLRU(&newList, newNodeToLRU);
        DestroyNode(firstNode);
        DestroyNode(newNodeToLRU);
        
        
        //When the number of nodes exceeds the cache size, it deletes the very first node to maintain its maximum capacity.
        
    } else {
        
        RemoveNodeLRU(&newList, GetNodeAtLRU(list, indexNumForOperation));
        newNode = CreateNode(numToSubmit, numToSubmit);
        AppendNodeLRU(&newList, newNode);
    }
    return newList;
}

int HashLRUNodeRemovalOperation(Node** thList, ElementType Key){
    //List newProcessedList = thList;
    int indicator = 0; //Nothing in the Hash.
    List oneToRemove = NULL;
    int nodeLength = GetNodeCount(*thList);
    for(int i = 0; i<nodeLength; i++){
        if(Key == GetNodeAt(*thList, i)->key){
            oneToRemove = GetNodeAt(*thList,i);
            indicator = 1;
        }
    }
    
    RemoveNode(thList, oneToRemove);
    
    return indicator;
}
