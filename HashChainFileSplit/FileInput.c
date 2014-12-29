//
//  FileInput.c
//  HashChainFileSplit
//
//  Created by In Chan Hwang on 12/10/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//

#include "FileInput.h"



List ReadingFromtheFile(long maxLineRead){
    /*FILE* filePointer;
    
    List aNewNodeList = NULL;
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
        Node* aNode = CreateNodeLRU(sectorNo);
        //aNewNodeList =
        AppendNodeFileCircularLinkedList(&aNewNodeList, aNode);
        
     //  printf("\r Time in MilliSec: %lf . Sector No. reading : %ld. Sectors in operation at the moment: %d", timeInMilliSec, sectorNo, noOfSectorsForOperation);
        //printf("\r%ld",  sectorNo);
        //clrscr();
        i++;
        if(i%1000 == 0){
            printf("\r Time in MilliSec: %lf . Sector No. reading : %ld. Sectors in operation at the moment: %d", timeInMilliSec, sectorNo, noOfSectorsForOperation);
        }
    }
    printf("\r Time in MilliSec: %lf . Sector No. reading : %ld. Sectors in operation at the moment: %d", timeInMilliSec, sectorNo, noOfSectorsForOperation);
    
    return aNewNodeList;*/
    return NULL;
}

ElementType nodeCount(List nodeName){
    ElementType nodeLength = GetNodeCountLRU(nodeName);
    return nodeLength;
}
