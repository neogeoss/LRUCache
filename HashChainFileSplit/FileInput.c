//
//  FileInput.c
//  HashChainFileSplit
//
//  Created by In Chan Hwang on 12/10/14.
//  Copyright (c) 2014 In Chan Hwang. All rights reserved.
//

#include "FileInput.h"


long ReadingFromtheFile(){
    FILE* filePointer;
    
    
    double firstVal;
    double secVal;
    long thirdVal = 0;
    int fourthVal;
    int fifthVal;
    
    char read;
    char* line = NULL;
    int i = 0;
    size_t len = 0;

    
    
    filePointer = fopen("/Users/inchanhwang/Desktop/fin.txt", "r");
    
    
    
    if(filePointer == NULL){
        printf("파일을 열 수 없습니다.\n" );
        exit(1);
    }
    
    while(i<7 && (read = getline(&line, &len, filePointer)) != -1){
        sscanf(line, "%lf %lf %ld %d %d", &firstVal, &secVal, &thirdVal, &fourthVal, &fifthVal);
        printf("%lf %lf %ld %d %d\n", firstVal, secVal, thirdVal, fourthVal, fifthVal);
        i++;
    }
    
    return thirdVal;
}
