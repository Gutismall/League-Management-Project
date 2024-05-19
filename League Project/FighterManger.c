//
//  FighterManger.c
//  C-Project
//
//  Created by Ari Guterman on 07/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FighterManger.h"

void initFighterManager(FighterManger* pFighterMan){
    pFighterMan->FightersList = NULL;
    pFighterMan->numOfFighters = 0;
    
}
int addFighterToList(FighterManger* pFighterMan){
    Fighter* newFighter = (Fighter*)malloc(sizeof(Fighter));
    IF_NOT_ALLOC(newFighter)
    IF_NOT_INIT(initFighter,newFighter)
    for (int i = 0; i < pFighterMan->numOfFighters; i++) {
        if (!compareFighterById(pFighterMan->FightersList[i], newFighter)) {
            printf("This ID exists\n\n");
            return 0;
        }
    }
    pFighterMan->FightersList = (Fighter**)realloc(pFighterMan->FightersList, sizeof(Fighter*) * (pFighterMan->numOfFighters + 1));
    IF_NOT_ALLOC(pFighterMan->FightersList)
    pFighterMan->FightersList[pFighterMan->numOfFighters] = newFighter;
    pFighterMan->numOfFighters++;
    return 1;
}
void printFightersArray(const FighterManger* pFighterMan) {
    printf("Fighters:\n");
    if (pFighterMan->numOfFighters == 0) {
        printf("No fighters yet\n\n");
    }
    else {
        for (int i = 0; i < pFighterMan->numOfFighters; i++) {
            printFighter(pFighterMan->FightersList[i]);
        }
    }
    printf("\n");
}
void printRanking(const FighterManger* pFighterMan){
    if (!pFighterMan->numOfFighters) {
        printf("No Fighters yet\n");
        return;
    }
    int input;
    do {
        printf("how would you like to sort the ranking ?\n1 - By wins\n2 - By looses\n3 - By draws\n4 - By knockouts\n");
        scanf("%d",&input);
        printf("\n");
    } while (input < 0 || input > 4);
    switch (input) {
        case 1:
            qsort(pFighterMan->FightersList, pFighterMan->numOfFighters, sizeof(Fighter*), compareByWins);
            break;
        case 2:
            qsort(pFighterMan->FightersList, pFighterMan->numOfFighters, sizeof(Fighter*), compareByLooses);
            break;
        case 3:
            qsort(pFighterMan->FightersList, pFighterMan->numOfFighters, sizeof(Fighter*), compareByDraws);
            break;
        case 4:
            qsort(pFighterMan->FightersList, pFighterMan->numOfFighters, sizeof(Fighter*), compareByKnockouts);
            break;
    }
    for (int i = 0 ; i < pFighterMan->numOfFighters; i++) {
        printf("%s: ",pFighterMan->FightersList[i]->name);
        printRank(pFighterMan->FightersList[i]->fightersRank);
        printf("\n");
    }
    printf("\n");
}
void freeFighterArray(FighterManger* pFighterMan){
    for (int i = 0; i < pFighterMan->numOfFighters; i++) {
        free(pFighterMan->FightersList[i]);
    }
}
Fighter* findFighterByID(const FighterManger* fMan,const char* ID){
    Fighter* search = (Fighter*)calloc(sizeof(Fighter),1);
    IF_NOT_ALLOC(search)
    strcpy(search->ID,ID);
    for (int i = 0; i < fMan->numOfFighters; i++) {
        if (compareFighterById(fMan->FightersList[i], search) == 0) {
            return fMan->FightersList[i];
        }
    }
    printf("Fighter no found\n");
    return NULL;
}
int loadFightersArrayFromBin(FighterManger* pFighterMan,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    int numOfFighters;
    loadClassFromBinary(&numOfFighters,sizeof (int ),pFile);
    pFighterMan->numOfFighters = numOfFighters;
    pFighterMan->FightersList = (Fighter**) malloc(sizeof (Fighter*) * numOfFighters);
    IF_NOT_ALLOC(pFighterMan->FightersList)
    for (int i = 0; i < pFighterMan->numOfFighters; ++i) {
        pFighterMan->FightersList[i] = (Fighter*) malloc(sizeof (Fighter));
        IF_NOT_ALLOC(pFighterMan->FightersList[i])
        SAVE_OR_OPEN_FILE(loadFighterFromBinFile,pFighterMan->FightersList[i],pFile)
    }
    return 1;
}
int saveFightersArrayToBin(FighterManger* pFighterMan, FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    saveClassToBinary(&pFighterMan->numOfFighters,sizeof(int ),pFile );
    for (int i = 0; i < pFighterMan->numOfFighters; ++i) {
        SAVE_OR_OPEN_FILE(saveFighterToBinFile,pFighterMan->FightersList[i],pFile)
    }
    return 1;
}
int loadFightersArrayFromFile(FighterManger* pFightersMan,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    fscanf(pFile, "%d",&pFightersMan->numOfFighters);
    fgetc(pFile);
    pFightersMan->FightersList = (Fighter**)calloc(pFightersMan->numOfFighters, sizeof(Fighter*));
    IF_NOT_ALLOC(pFightersMan->FightersList)
    for (int i = 0; i < pFightersMan->numOfFighters; i++) {
        pFightersMan->FightersList[i] = (Fighter*)malloc(sizeof(Fighter));
        IF_NOT_ALLOC(pFightersMan->FightersList[i])
        SAVE_OR_OPEN_FILE(loadFighterFromFile,pFightersMan->FightersList[i],pFile)
    }
    return 1;
}
int saveFightersArrayToFile(FighterManger* pFighterMan,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    fprintf(pFile, "%d",pFighterMan->numOfFighters);
    fputs("\n", pFile);
    for (int i = 0; i < pFighterMan->numOfFighters; i++) {
        SAVE_OR_OPEN_FILE(saveFighterToFile,pFighterMan->FightersList[i],pFile)
    }
    return 1;
}