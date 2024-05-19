//
//  Arena.c
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "Arena.h"

int initArena(Arena* pArena){
    pArena->arenaID = rand() % (9999-1111 + 1) + 1111;
    pArena->name = getStrExactName("Enter arena name:");
    do {
        printf("Enter the number of sits in the arena:\t");
        scanf("%d",&pArena->numOfSeats);
    } while (pArena->numOfSeats < 0);
    pArena->country =  getStrExactName("Enter arena location:");
    return 1;
}
int loadArenaFromFile(Arena* pArena,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    pArena->name = readDynStringFromTextFile(pFile);
    fscanf(pFile, "%d",&pArena->arenaID);
    fgetc(pFile);
    fscanf(pFile, "%d",&pArena->numOfSeats);
    fgetc(pFile);
    pArena->country = readDynStringFromTextFile(pFile);
    return 1;
}
int saveArenaToFile(const Arena* pArena,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    fprintf(pFile, "%s\n",pArena->name);
    fprintf(pFile, "%d\n",pArena->arenaID);
    fprintf(pFile, "%d\n",pArena->numOfSeats);
    fprintf(pFile, "%s\n",pArena->country);
    return 1;
}
int loadArenaFromBinary(Arena* pArena, FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    loadClassFromBinary(&pArena->arenaID, sizeof(int), pFile);
    loadClassFromBinary(&pArena->numOfSeats, sizeof(int), pFile);

    int nameLen, countryLen;
    loadClassFromBinary(&nameLen, sizeof(int), pFile);
    pArena->name = (char*)malloc(nameLen * sizeof(char));
    IF_NOT_ALLOC(pArena->name)
    if(!fread(pArena->name, sizeof(char), nameLen, pFile))
        return 0;

    loadClassFromBinary(&countryLen, sizeof(int), pFile);
    pArena->country = (char*)malloc(countryLen * sizeof(char));
    IF_NOT_ALLOC(pArena->country)
    if (!fread(pArena->country, sizeof(char), countryLen, pFile))
        return 0;
    return 1;
}
int saveArenaToBinary(Arena* pArena,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    saveClassToBinary(&pArena->arenaID, sizeof(int ),pFile);
    saveClassToBinary(&pArena->numOfSeats, sizeof(int ),pFile);

    int nameLen = strlen(pArena->name) + 1;
    saveClassToBinary(&nameLen, sizeof(int ),pFile);

    if (!fwrite(pArena->name, sizeof(char), nameLen, pFile))
        return 0;

    int countryLen = strlen(pArena->country) + 1;
    saveClassToBinary(&countryLen, sizeof(int), pFile);
    if (!fwrite(pArena->country, sizeof(char), countryLen, pFile))
        return 0;
    return 1;
}
void printArena(const Arena* pArena){
    printf("name - %-30s \t\t(ID: %d)\t\tnumber of sits - %5d\t\t location: %5s\n", pArena->name, pArena->arenaID, pArena->numOfSeats, pArena->country);
}
int compareArenaById(const void* id1,const void* id2){
    Arena* arena1 = (Arena*)id1;
    Arena* arena2 = (Arena*)id2;
    return (arena1->arenaID - arena2->arenaID);
}
int getArenaID(int* ID){
    int input,check = 0;
    do {
        printf("Enter arena ID : ");
        scanf("%d",&input);
        if (input > 9999 || input < 1111) {
            printf("ID invalid\n");
            continue;
        }
        check = 1;
    } while (!check);
    *ID = input;
    return 1;
}
