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
#include "FileInput.h"

#define MAX_HORIZANTAL_CACHE_SIZE 10
#define MAX_CACHE_BLOCKS 15
#define HASH_ENTRY_SIZE 5

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

int inputValues [] = {1, 3, 44, 33, 23, 56, 3 , 54 , 21, 33, 81, 82, 74, 91, 61, 56,11, 21};
int inputValues1 [] = { 9, 99, 69};
int diskAccessValues [] = {1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0};

//int inputKeysn1 [] = {51};

List DummyDataFiller(int dataArray [], int statusArray[], HashTable* HT , int actualLoopPeriod, List Lrulist){
    Node* newNode = NULL;
    Node* LRUNode = NULL;
    int loopPeriod = actualLoopPeriod;
    for(int i = 0; i<loopPeriod;i++){
        newNode = CreateNode(dataArray[i], dataArray[i]);
        LRUNode = CreateNodeLRU(dataArray[i], statusArray[i]);
        //newNode = CreateNode(randomValue, randomKey);
        AppendNodeIntoAHashTable(HT, newNode);
        AppendNodeLRU(&Lrulist, LRUNode);
        
    }
    
    return Lrulist;
    
}

/*void RandomDataFill(HashTable* HT, ElementType inputValue, Node** Lrulist){
    Node* newNode = NULL;
    Node* LRUNode = NULL;
    newNode = CreateNode(inputValue, inputValue);
    LRUNode = CreateNodeLRU(inputValue);
    AppendNodeIntoAHashTable(HT, newNode);
    AppendNodeLRU(Lrulist, LRUNode);
}*/

void FileDataFill(HashTable* HT, Node** Lrulist){
    FILE* filePointer;
    
    //List aNewNodeList = NULL;
    // List lastNodeContainer = NULL;
    
    double timeInMilliSec=0;
    double deviceIDNo=0;
    long sectorNo = 0;
    int noOfSectorsForOperation =0;
    int readOrWrite=0;
    
    char read;
    char* line = NULL;
    int i = 0;
    size_t len = 0;
    
    
    
    filePointer = fopen("/Users/inchanhwang/Desktop/fin.txt", "r");
    
    
    
    if(filePointer == NULL){
        printf("파일을 열 수 없습니다.\n" );
        exit(1);
    }
    
    while((read = getline(&line, &len, filePointer)) != -1){
        sscanf(line, "%lf %lf %ld %d %d", &timeInMilliSec, &deviceIDNo, &sectorNo, &noOfSectorsForOperation, &readOrWrite);
        // printf("%lf %lf %ld %d %d\n", firstVal, secVal, thirdVal, fourthVal, fifthVal);
        Node* aNode = CreateNodeLRU(sectorNo, sectorNo);
        Node* aHashNode = CreateNode(sectorNo, sectorNo);
        //aNewNodeList =
        //AppendNodeFileCircularLinkedList(Lrulist, aNode);
        AppendNodeIntoAHashTable(HT, aHashNode);
        AppendNodeLRU(Lrulist, aNode);
        
        //  printf("\r Time in MilliSec: %lf . Sector No. reading : %ld. Sectors in operation at the moment: %d", timeInMilliSec, sectorNo, noOfSectorsForOperation);
        //printf("\r%ld",  sectorNo);
        //clrscr();
        i++;
        if(i%1000 == 0){
            printf("\r Time in MilliSec: %lf . Sector No. reading : %ld. Sectors in operation at the moment: %d", timeInMilliSec, sectorNo, noOfSectorsForOperation);
        }
    }
    printf("\r Time in MilliSec: %lf . Sector No. reading : %ld. Sectors in operation at the moment: %d", timeInMilliSec, sectorNo, noOfSectorsForOperation);
    
    //return aNewNodeList;
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
        printf(" %ld ", current->value);
    }
    printf("\n");
    
}

void DisplayDiskAccessStatusToo(Node* List){
    int listSize = GetNodeCountLRU(List);
    Node* current = NULL;
    for(int i = 0; i<listSize; i++){
        current = GetNodeAtLRU(List, i);
        printf(" %ld ", current->value);
    }
    printf("\n\nRead Write Status\n");
    for(int i = 0; i<listSize; i++){
        current = GetNodeAtLRU(List, i);
        printf(" %ld ", current->key);
    }
    printf("\n");
    
}


void DisplayHashEntries(int tableSize, HashTable* HT){
    printf("\n");
    Node* aSampleList = NULL;
    for(int i = 0; i<tableSize; i++){
        aSampleList = GetAHorizontalSetofListData(HT, i);
        printf("Hash Entry  %d: ", i);
        for(int j = 0; j<GetNodeCount(aSampleList); j++){
            Node* aNode = GetNodeAt(aSampleList, j);
            printf("  %ld ", aNode->value);
            
        }
        printf("\n");
    }
    
}

void FileReadingExperimentalChecker(HashTable* HT, Node* lruList){
    ElementType aValueToFind = 47862992;
    Node* aNode = CreateNodeLRU(aValueToFind, aValueToFind);
    if(RetriveAHashValue(HT, aValueToFind) == aValueToFind){
        
        Node* aNodeToRemove = GetNodeAt(lruList,LookUpFunctionForIndexNum(lruList, aValueToFind));
        RemoveNodeLRU(&lruList, aNodeToRemove);
        AppendNodeLRU(&lruList, aNode);
        printf("\nIt is a value in the hash. LRU operation has been done with it.\n");
    } else {
        Node* firstNode = GetNodeAt(lruList, 0);
        AppendNodeLRU(&lruList, aNode);
        RemoveNodeLRU(&lruList, firstNode);
        printf("\nNo such a value found in the hash, It is a new value, having been added to the LRU. ");
        
    }
}


void FillingData(HashTable* HT, Node** lruList, int inputValues [], int theLength, int TableSize){
    
    Node* newNode = NULL;
    Node* LRUNode = NULL;
    int loopPeriod = theLength;
    for(int i = 0; i<loopPeriod;i++){
        
        newNode = CreateNode(inputValues[i], inputValues[i]);
        LRUNode = CreateNodeLRU(inputValues[i], inputValues[i]);
        //newNode = CreateNode(randomValue, randomKey);
        
        if(RetriveAHashValue(HT, inputValues[i]) != inputValues[i]){
         AppendNodeIntoAHashTable(HT, newNode);
         AppendNodeLRU(lruList, LRUNode);
        
            if(hashNodeCounter(HT, TableSize)> MAX_CACHE_BLOCKS){
               Node* firstNode = GetNodeAtLRU(*lruList, 0);
                RemoveNodeLRU(lruList, firstNode);
                
                DeleteANodeFromtheHash(HT, firstNode->key);
            }
            
        } else {
            DeleteANodeFromtheHash(HT, inputValues[i]);
            
            ElementType index = LookUpFunctionForIndexNum(*lruList, inputValues[i]);
            Node* aNode = GetNodeAtLRU(*lruList, index);
            RemoveNodeLRU(lruList, aNode);
            
            if((*lruList)->value == aNode->value){
                (*lruList) = NULL;
            }
            
            AppendNodeIntoAHashTable(HT, CreateNode(inputValues[i], inputValues[i]));
            AppendNodeLRU(lruList, aNode);
            
            //RemoveNodeLRU(&lruList, inputValues[i]);
        }
        
    
    
   
    }
}

void displayInitialInputs(int inputs [], int lengthOfInputs){
    printf("\nHere is a list of inputs : ");
    for(int i = 0; i < lengthOfInputs; i++){
        printf(" %d ", inputs [i]);
    }
}

int main(int argc, const char * argv[]) {
    
  /*  int hitCounter=0;
    
    int numberOfAccessAttempts = 10;*/
    int tableSize = HASH_ENTRY_SIZE;
  //  int contentsIntheCache = 100;
    
    
    
    //time_t t = time(NULL);
    //struct tm tm = *localtime(&t);
    
    
    List aSampleList = NULL;
    
    srand(time(NULL));
    
    Node* LRUOperationTemp = NULL;
    
    Node* newNode = NULL;
    
    HashTable* HT = CreateHashTable(tableSize);
    
    Node* lruList = NULL;
    
    //FileDataFill(HT, &lruList);
    displayInitialInputs(inputValues, sizeof(inputValues)/sizeof(int));
    FillingData(HT, &lruList, inputValues, sizeof(inputValues)/sizeof(int), tableSize);
    DisplayHashEntries(tableSize, HT);
    printf("\nLRU List!\n");
    DisplayDiskAccessStatusToo(lruList);
    
    printf(" %ld ",RetriveAHashValue(HT, 5));
    /*DeleteANodeFromtheHash(HT, 1);
    DisplayHashEntries(tableSize, HT);*/
    
  /* lruList = DummyDataFiller(inputValues, diskAccessValues, HT, sizeof(inputValues)/sizeof(int), lruList);
    DisplayHashEntries(tableSize, HT);
    printf("\n %ld ",hashNodeCounter(HT, tableSize));*/
    //DisplayHashEntries(tableSize, HT);
    //printf("\n %ld", RetriveAHashValue(HT, 15));
    //DeleteANodeFromtheHash(HT, 7);
    //DisplayHashEntries(tableSize, HT);
    //FileDataFill(HT, &lruList);
   // FillingData(HT, lruList, inputValues, sizeof(inputValues)/sizeof(int), tableSize);
    //printf("\nFile reading has been complete!\n");
    //DisplayHashEntries(tableSize, HT);
    
    /*printf("\nHash Entries!\n");
    DisplayHashEntries(tableSize, HT);
    
    
    
    printf("\nLRU List!\n");
    DisplayDiskAccessStatusToo(lruList);*/
   /* ElementType aValueToFind = 47862992;
    Node* aNode = CreateNodeLRU(aValueToFind);
    if(RetriveAHashValue(HT, aValueToFind) == aValueToFind){
        
        Node* aNodeToRemove = GetNodeAt(lruList,LookUpFunctionForIndexNum(lruList, aValueToFind));
        RemoveNodeLRU(&lruList, aNodeToRemove);
        AppendNodeLRU(&lruList, aNode);
        printf("\nIt is a value in the hash. LRU operation has been done with it.\n");
    } else {
        Node* firstNode = GetNodeAt(lruList, 0);
        AppendNodeLRU(&lruList, aNode);
        RemoveNodeLRU(&lruList, firstNode);
        printf("\nNo such a value found in the hash, It is a new value, having been added to the LRU. ");
        
    }*/
    
    
    /*for(int i = 0; i<100; i++){
        RandomDataFill(HT, rand()%100, &lruList);
    }*/
    
    /*lruList = DummyDataFiller(plainKeys1, HT, sizeof(plainKeys1)/sizeof(int), lruList);
    lruList = DummyDataFiller(plainKeys2, HT, sizeof(plainKeys2)/sizeof(int), lruList);
    lruList = DummyDataFiller(plainKeys3, HT, sizeof(plainKeys3)/sizeof(int), lruList);
    lruList = DummyDataFiller(plainKeys4, HT, sizeof(plainKeys4)/sizeof(int), lruList);
    lruList = DummyDataFiller(plainKeys5, HT, sizeof(plainKeys5)/sizeof(int), lruList);*/
    /*
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
    }*/
    
    //TheOne I used
     
     
     
     
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
    /*
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
     */
    
    
    
    
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