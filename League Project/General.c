//
//  General.c
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "General.h"

char* getStrExactName(const char* msg)
{
    char* str;
    char temp[MAX_STR_LEN];
    printf("%s\t", msg);
    myGets(temp, MAX_STR_LEN, stdin);

    str = getDynStr(temp);
    return str;
}

char* getDynStr(char* str)
{
    char* theStr;
    theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
    if (!theStr)
        return NULL;

    strcpy(theStr, str);
    return theStr;
}



char*  myGets(char* buffer, int size, FILE* source)
{
    char* ok;
    if (buffer != NULL && size > 0)
    {
        do {
            ok = fgets(buffer, size, source);
        } while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
        if (ok)
        {
            char* back = buffer + strlen(buffer);
            //trim end spaces
            while ((buffer < back) && (isspace(*--back)));
            *(back + 1) = '\0';
            return buffer;
        }
        buffer[0] = '\0';
    }
    return NULL;
}
int loadClassFromBinary(void* val,size_t size,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    if(fread(val, size, 1, pFile) != 1)
        return 0;
    return 1;
}
int saveClassToBinary(void* val,size_t size,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    if(fwrite(val, size, 1, pFile) != 1)
        return 0;
    return 1;
}
char* readDynStringFromTextFile(FILE* fp)
{
    char temp[MAX_STR_LEN];
    myGets(temp, sizeof(temp), fp);
    return getDynStr(temp);
}
int generalCompareFunction(const void *array,const size_t size,const size_t count, int func(const void *,const void *),const void* cmpVal) {
    unsigned char *arr = (unsigned char *)array;
    for (size_t i = 0; i < count; i++) {
        if (func(cmpVal,arr + i * size) == 0)
            return 1;
    }
    return 0;
}