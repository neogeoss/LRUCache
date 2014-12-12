//
//  LinkedList.h
//  HashChainFileSplit
//
//  Created by In Chan Hwang on 12/8/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h


#include <stdio.h>
#include "HashChaining.h"
#include "DataTypes.h"

Node* CreateNode(ElementType newData, ElementType key);
void DestroyNode(Node* node);
int LookUpFunctionForValue(Node* head, int numInput);
int LookUpFunctionForIndexNum(Node* head, int numInput);
void RemoveNode(Node** head, Node* remove);
Node* GetNodeAt(Node* head, int location);
int GetNodeCount(Node* head);
void AppendNode(Node** head, Node* newNode);
List LRUOperationForAsingleBuffer(List theList, ElementType Key, ElementType result, int indexForTheResult, int MAX_HORIZANTAL_CACHE_SIZE);
void AppendNodeLRU(Node** Head, Node* NewNode);
void RemoveNodeLRU(Node** Head, Node* Remove);
Node* GetNodeAtLRU(Node* Head, int Location);
int GetNodeCountLRU(Node* Head);
void AppendNodeFileCircularLinkedList(Node** Head, Node* NewNode);

Node* inputToLRULine(Node* list, int submittingNum);
Node* CreateNodeLRU(ElementType newData);

#endif /* defined(__HashChainFileSplit__LinkedList__) */
