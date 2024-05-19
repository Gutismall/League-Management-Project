//
//  Fighter.c
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Fighter.h"

int initFighter(Fighter* pFighter){
    getFighterID(pFighter->ID,"Enter Fighter ID : {0000-9999}");
    pFighter->name = getStrExactName("Enter fighters name:");
    pFighter->name[0] = toupper(pFighter->name[0]);
    pFighter->fightersRank = (Rank*)malloc(sizeof(Rank));
    IF_NOT_ALLOC(pFighter->fightersRank)
    initRank(pFighter->fightersRank);
    int input,ok;
    do {
        ok = 0;
        printf("Enter pFighter weight class:\n");
        for (int i = 0 ; i < eNofClasses; i++) {
            printf("%d - %s\n",i + 1,classes[i]);
        }
        scanf("%d",&input);
        input -= 1;
        switch (input) {
            case 0:
                pFighter->fightersClass = eFeather;
                break;
            case 1:
                pFighter->fightersClass = eLight;
                break;
            case 2:
                pFighter->fightersClass = eMid;
                break;
            case 3:
                pFighter->fightersClass = eHeavy;
                break;
            default:
                printf("Wrong Input\n");
                ok = 1;
                break;
        }
    } while (ok != 0);
    return 1;
}
void printFighter(const Fighter* pFighter){
    printf("name - %-20s\t\tID: %s\t\tClass - %s\t\t",pFighter->name,pFighter->ID,classes[pFighter->fightersClass]);
    printRank(pFighter->fightersRank);
    printf("\n");
}
int updateFighterWeightClass(Fighter* pFighter){
    int input;
    printf("Current weight class :%s\n",classes[pFighter->fightersClass]);
    printf("Enter updated weight class:\n");
    do {
        for (int i = 0; i < eNofClasses; i++) {
            printf("%d - %s",i + 1,classes[i]);
            scanf("%d",&input);
        }
    } while (input - 1 > eNofClasses || input - 1 < 0);
    switch (input - 1) {
        case 0:
            pFighter->fightersClass = eFeather;
            break;
        case 1:
            pFighter->fightersClass = eLight;
            break;
        case 2:
            pFighter->fightersClass = eMid;
            break;
        case 3:
            pFighter->fightersClass = eHeavy;
            break;
    }
    return 1;
}
void getFighterID(char* code,char* msg){
    char* temp;
    int check = 1;
    do {
        temp = getStrExactName(msg);
        if (strlen(temp) != FIGHTER_ID_LENGTH) {
            printf("ID must be in range\n");
            check = 0;
            continue;
        }
        for (int i = 0; i < FIGHTER_ID_LENGTH; i++) {
            if (!isdigit(temp[i])) {
                printf("ID must be numbers\n");
                check = 0;
                break;
            }
            else
                check = 1;
        }
    } while (check == 0);
    strcpy(code, temp);
}
int loadFighterFromFile(Fighter* pFighter,FILE* pFile){
    {
        IF_DIDNT_OPEN_FILE(pFile)
        fscanf(pFile,"%s",pFighter->ID);
        fgetc(pFile);
        pFighter->name = readDynStringFromTextFile(pFile);
        pFighter->fightersRank = (Rank*)malloc(sizeof(Rank));
        IF_NOT_ALLOC(pFighter->fightersRank)
        if (!loadRankFromFile(pFighter->fightersRank, pFile))
            return 0;
        fscanf(pFile,"%d",&pFighter->fightersClass);

        return 1;
    }
}
int saveFighterToFile(Fighter* pFighter, FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    fprintf(pFile,"%s\n", pFighter->ID);
    fprintf(pFile,"%s\n", pFighter->name);
    SAVE_OR_OPEN_FILE(saveRankToFile,pFighter->fightersRank,pFile)
    fprintf(pFile,"%d\n",pFighter->fightersClass);
    return 1;
}
int saveFighterToBinFile(Fighter* pFighter, FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    saveClassToBinary(&pFighter->ID,sizeof(pFighter->ID),pFile);
    saveClassToBinary(&pFighter->fightersClass,sizeof(pFighter->fightersClass),pFile);
    int nameLen = strlen(pFighter->name) + 1;
    fwrite(&nameLen, sizeof(int), 1, pFile);
    fwrite(pFighter->name, sizeof(char), nameLen, pFile);
    saveRankToBinaryFileCompressed(pFighter->fightersRank,pFile);
    return 1;
}

int loadFighterFromBinFile(Fighter* pFighter, FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    loadClassFromBinary(&pFighter->ID,sizeof(pFighter->ID),pFile);
    loadClassFromBinary(&pFighter->fightersClass,sizeof(pFighter->fightersClass),pFile);
    int nameLen ;
    loadClassFromBinary(&nameLen,sizeof (int ),pFile);
    pFighter->name = (char*)malloc(sizeof (char) * nameLen);
    IF_NOT_ALLOC(pFighter->name)
    if (!fread(pFighter->name, sizeof(char), nameLen, pFile)){
        return 0;
    }
    pFighter->fightersRank = (Rank*) malloc(sizeof (Rank));
    IF_NOT_ALLOC(pFighter->fightersRank)
    loadRankFromBinaryFileCompressed(pFighter->fightersRank, pFile);
    return 1;
}
int compareByWins(const void* Fighter1,const void* Fighter2){
    const Fighter* cmpFighter1 = *(Fighter**)Fighter1;
    const Fighter* cmpFighter2 = *(Fighter**)Fighter2;
    return  (int )(cmpFighter2->fightersRank->win - cmpFighter1->fightersRank->win);
}
int compareByLooses(const void* Fighter1,const void* Fighter2){
    const Fighter* cmpFighter1 = *(Fighter**)Fighter1;
    const Fighter* cmpFighter2 = *(Fighter**)Fighter2;
    return (int )(cmpFighter2->fightersRank->losses - cmpFighter1->fightersRank->losses);
}
int compareByDraws(const void* Fighter1,const void* Fighter2){
    const Fighter* cmpFighter1 = *(Fighter**)Fighter1;
    const Fighter* cmpFighter2 = *(Fighter**)Fighter2;
    return (int )(cmpFighter2->fightersRank->draw - cmpFighter1->fightersRank->draw);
}
int compareByKnockouts(const void* Fighter1,const void* Fighter2){
    const Fighter* cmpFighter1 = *(Fighter**)Fighter1;
    const Fighter* cmpFighter2 = *(Fighter**)Fighter2;
    return (int )(cmpFighter2->fightersRank->knockout - cmpFighter1->fightersRank->knockout);
}
int compareFighterById(const void* Fighter1,const void* Fighter2){
    const Fighter* cmpFighter1 = (Fighter*)Fighter1;
    const Fighter* cmpFighter2 = (Fighter*)Fighter2;
    return strcmp(cmpFighter1->ID, cmpFighter2->ID);
}
void freeFighter(void* pFighter){
    free((Fighter*)pFighter);
}
