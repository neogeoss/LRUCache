//
//  main.c
//  HashChainFileSplit
//
//  Created by In Chan Hwang on 12/8/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//

#include "HashChaining.h"
#include <time.h>
#include <malloc/malloc.h>

#define MAX_HORIZANTAL_CACHE_SIZE 10
#define MAX_CACHE_SIZE 29

/*int plainKeys1 [] =  {11, 21, 31, 41, 51};
int plainKeys2 [] =  {12, 22, 32, 42, 52};
int plainKeys3 [] =  {13, 23, 33, 43, 53};
int plainKeys4 [] =  {14, 24, 34, 44, 54};
int plainKeys5 [] =  {15, 25, 35, 45, 55};*/

int plainKeys1 [] =  {11, 21, 31, 41, 51};
int plainKeys2 [] =  {12, 22, 32, 42, 52};
int plainKeys3 [] =  {13, 23, 33, 43, 53};
int plainKeys4 [] =  {14, 24, 34, 44, 54};
int plainKeys5 [] =  {15, 25, 35, 45, 55};


int inputKeys [] = {14, 44, 64, 74, 63, 73, 83, 42, 12};

int inputKeysn [] = {14, 44, 64, 74, 13, 15, 84, 61 , 51};

//int inputKeysn1 [] = {51};

List DummyDataFiller(int dataArray [], HashTable* HT , int actualLoopPeriod, List Lrulist){
    Node* newNode = NULL;
    Node* LRUNode = NULL;
    int loopPeriod = actualLoopPeriod;
    for(int i = 0; i<loopPeriod;i++){
        newNode = CreateNode(dataArray[i], dataArray[i]);
        LRUNode = CreateNodeLRU(dataArray[i]);
        //newNode = CreateNode(randomValue, randomKey);
        AppendNodeIntoAHashTable(HT, newNode);
        AppendNodeLRU(&Lrulist, LRUNode);
        
    }
    
    return Lrulist;
    
}

void ActualDataFiller(HashTable* HT, int integer){
    Node* newNode = NULL;
    newNode = CreateNode(integer, integer);
    AppendNodeIntoAHashTable(HT, newNode);
    DestroyNode(newNode);
}

void DisplayList(Node* List){
    int listSize = GetNodeCountLRU(List);
    Node* current = NULL;
    for(int i = 0; i<listSize; i++){
        current = GetNodeAtLRU(List, i);
        printf(" %d ", current->value);
    }
    printf("\n");
    
}

int main(int argc, const char * argv[]) {
    
  /*  int hitCounter=0;
    
    int numberOfAccessAttempts = 10;*/
    int tableSize = 5;
  //  int contentsIntheCache = 100;
    
    
    
    //time_t t = time(NULL);
    //struct tm tm = *localtime(&t);
    
    
    List aSampleList = NULL;
    
   // srand(time(NULL));
    
    Node* LRUOperationTemp = NULL;
    
    Node* newNode = NULL;
    
    HashTable* HT = CreateHashTable(tableSize);
    
    Node* lruList = NULL;
    
    
    lruList = DummyDataFiller(plainKeys1, HT, sizeof(plainKeys1)/sizeof(int), lruList);
    lruList = DummyDataFiller(plainKeys2, HT, sizeof(plainKeys2)/sizeof(int), lruList);
    lruList = DummyDataFiller(plainKeys3, HT, sizeof(plainKeys3)/sizeof(int), lruList);
    lruList = DummyDataFiller(plainKeys4, HT, sizeof(plainKeys4)/sizeof(int), lruList);
    lruList = DummyDataFiller(plainKeys5, HT, sizeof(plainKeys5)/sizeof(int), lruList);
    
    printf("Initial Hash Entries\n");
    
    for(int i = 0; i<tableSize; i++){
        aSampleList = GetAHorizontalSetofListData(HT, i);
        printf("Hash Entry  %d: ", i);
        for(int j = 0; j<GetNodeCount(aSampleList); j++){
            Node* aNode = GetNodeAt(aSampleList, j);
            printf("  %d ", aNode->value);
            
        }
        printf("\n");
    }
    
    printf("\n");
    
    
    
    printf("input values :  ");
    
    printf("\n\nThe list of total LRU input: ");
    DisplayList(lruList);
    
    
    for(int i = 0; i<sizeof(inputKeysn)/sizeof(int); i++){
        int keyInput = inputKeysn[i];
        printf("%d  ", keyInput);
        Node* KeyNodeForLRUandHash = CreateNodeLRU(keyInput);
        
        
        AppendNodeLRU(&lruList, KeyNodeForLRUandHash);
        ElementType returnedValue = RetriveAHashValue(HT, keyInput);
        if(returnedValue != 0){
            DeleteANodeFromtheHash(HT, keyInput);
            AppendNodeIntoAHashTable(HT, KeyNodeForLRUandHash);
            RemoveNodeLRU(&lruList, KeyNodeForLRUandHash);
            AppendNodeLRU(&lruList, KeyNodeForLRUandHash);
        } else {
            AppendNodeIntoAHashTable(HT, KeyNodeForLRUandHash);
            
            if(GetNodeCountLRU(lruList)>MAX_CACHE_SIZE){
                LRUOperationTemp = GetNodeAtLRU(lruList, 0);
                DeleteANodeFromtheHash(HT, LRUOperationTemp->key);
                RemoveNodeLRU(&lruList, LRUOperationTemp);
            }
        }
    }
   /* for(int i = 0; i<sizeof(inputKeysn)/sizeof(int); i++){
        int randomKey = inputKeysn[i];
        printf("%d  ", randomKey);
        Node* randomKeyNode = CreateNodeLRU(randomKey);
        //printf("Key:%d, Value:%d", keysforNumbers[i], getValueFromHashTable(HT, keysforNumbers[i]));
        //lruList = inputToLRULine(lruList, randomKey);
        AppendNodeLRU(&lruList, randomKeyNode);
        ElementType returnedValue = RetriveAHashValue(HT, randomKey);
        if(returnedValue != 0) {
            //printf("%d  ", getValueFromHashTable(HT, randomKey));
            DeleteANodeFromtheHash(HT, randomKey);
            AppendNodeIntoAHashTable(HT, randomKeyNode);
            hitCounter++;
            if(hitCounter%7 == 0){
                printf("\n");
            }
            
            
        }  else {
                AppendNodeIntoAHashTable(HT, randomKeyNode);
                Node* firstNode = GetNodeAtLRU(lruList, 0);
                DeleteANodeFromtheHash(HT, firstNode->key);
                RemoveNodeLRU(&lruList, firstNode);
                DestroyNode(firstNode);
        }
    }*/
        


   // lruList = inputToLRULine(lruList, 63);
    
    printf("\n\nThe list of modified LRU input: ");
    DisplayList(lruList);
    
    printf("\n\n");
    
    printf("Contents Changed After the Inputs\n");
    
    printf("\n");
    
    for(int i = 0; i<tableSize; i++){
        aSampleList = GetAHorizontalSetofListData(HT, i);
        printf("Hash Entry  %d: ", i);
        for(int j = 0; j<GetNodeCount(aSampleList); j++){
            Node* aNode = GetNodeAt(aSampleList, j);
            printf("  %d ", aNode->value);
            
        }
        printf("\n");
    }

    
    
    
    
    /*printf("Initial Hash Tables\n");
    
    for(int i = 0; i<tableSize; i++){
        aSampleList = GetAHorizontalSetofListData(HT, i);
        printf("Hash Table  %d: ", i);
        for(int j = 0; j<GetNodeCount(aSampleList); j++){
            Node* aNode = GetNodeAt(aSampleList, j);
            printf("  %d ", aNode->value);
            
        }
        printf("\n");
    }
    
    printf("\n");
    
    
    printf("input value :  ");
    while(tm.tm_mday<9){
        int randomKey = rand()%10000;
        printf("%d  ", randomKey);
        
        if(GetValueFromHashTable(HT, randomKey) != 0) {
            
            hitCounter++;
            if(hitCounter%7 == 0){
                printf("\n");
            }
        }
        
    }
    
    printf("Table Changed After the Inputs\n");
    
    printf("\n");
    
    for(int i = 0; i<tableSize; i++){
        aSampleList = GetAHorizontalSetofListData(HT, i);
        printf("Hash Table  %d: ", i);
        for(int j = 0; j<GetNodeCount(aSampleList); j++){
            Node* aNode = GetNodeAt(aSampleList, j);
            printf("  %d ", aNode->value);
            
        }
        printf("\n");
    }*/
    DestroyHashTable(HT); 
    
    
}