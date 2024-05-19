//
//  Fight.c
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//

#include <stdio.h>
#include "Fight.h"



int initFight(Fight* pFight,const FighterManger* fMan,const RefereeManger* rMan) {
    printFightersArray(fMan);
    printf("\n");

    getFighterID(pFight->Fighters[0].ID, "Enter Fighter ID that you would like to add:");
    if (findFighterByID(fMan, pFight->Fighters[0].ID) == NULL) {
        return 0;
    }
    Fighter* firstFighter = findFighterByID(fMan, pFight->Fighters[0].ID);
    pFight->Fighters[0] = *firstFighter;

    for (int i = 0; i < fMan->numOfFighters; ++i) {
        if (fMan->FightersList[i]->fightersClass == pFight->Fighters[0].fightersClass && strcmp(fMan->FightersList[i]->ID,pFight->Fighters[0].ID) != 0){
            printFighter(fMan->FightersList[i]);
        }
    }
    getFighterID(pFight->Fighters[1].ID, "Enter Fighter ID that you would like to add:");
    if (findFighterByID(fMan, pFight->Fighters[1].ID) == NULL) {
        return 0;
    }
    Fighter* secondFighter = findFighterByID(fMan, pFight->Fighters[1].ID);
    pFight->Fighters[1] = *secondFighter;
    if (strcmp(pFight->Fighters[0].ID,pFight->Fighters[1].ID) == 0) {
        printf("Cant select the same fighter\n");
        return 0;
    }
    if (pFight->Fighters[1].fightersClass != pFight->Fighters[0].fightersClass)
    {
        printf("The fighters must be from the same class weight\n");
        printf("\n");
        return 0;
    }
    printRefereesArray(rMan);
    printf("\n");

    pFight->fightReferee = (Referee*)malloc(sizeof(Referee));
    IF_NOT_ALLOC(pFight->fightReferee)
    getFighterID(pFight->fightReferee->refID, "Enter referee ID that you would like to add:");
    Referee* fightRef = findRefereeByID(rMan, pFight->fightReferee->refID);
    if (fightRef == NULL) {
        return 0;
    }
    pFight->fightReferee = fightRef;
    pFight->winner = -1;
    return 1;
}

void addWinner(Fight* pFight, int pWinner)
{
    int ifKnockout;
    printf("Was this a knockout win ?\n");
    printf("1 - yes\n2 - no\n");
    scanf("%d",&ifKnockout);
    pFight->winner = pWinner;
    if (pWinner == 0){
        updateWinner(pFight->Fighters[pWinner].fightersRank, pFight->Fighters[pWinner + 1].fightersRank, ifKnockout);
    }
    else{
        updateWinner(pFight->Fighters[pWinner].fightersRank, pFight->Fighters[pWinner -1].fightersRank, ifKnockout);
    }

}
void printFight(const Fight* pFight)
{
    printf("%s vs %s\n", pFight->Fighters[0].name, pFight->Fighters[1].name);
}
int loadFightFromFile(Fight* pFight,FighterManger* pFighterMan,RefereeManger* pRefMan ,FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    for (int i = 0; i < MAX_FIGHTERS; i++) {
        char temp[FIGHTER_ID_LENGTH + 1];
        fscanf(pFile, "%s", temp);
        fgetc(pFile);
        Fighter* fighter = findFighterByID(pFighterMan, temp);
        if (fighter != NULL)
            pFight->Fighters[i] = *fighter;
    }
    char tempRef[FIGHTER_ID_LENGTH + 1];
    fscanf(pFile, "%s", tempRef);
    fgetc(pFile);
    pFight->fightReferee = findRefereeByID(pRefMan, tempRef);
    fscanf(pFile,"%d",&pFight->winner);
    return 1;
}
int saveFightsToFile(Fight* pFight, FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    for (int i = 0; i < MAX_FIGHTERS; ++i) {
        fprintf(pFile,"%s\n",pFight->Fighters[i].ID);
    }
    fprintf(pFile,"%s\n",pFight->fightReferee->refID);
    fprintf(pFile,"%d\n",pFight->winner);
    return 1;
}
int saveFightToBinFile(Fight* pFight, FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    for (int i = 0; i < MAX_FIGHTERS; i++)
    {
        fwrite(pFight->Fighters[i].ID, sizeof(char ), FIGHTER_ID_LENGTH + 1,pFile);
    }
    fwrite(pFight->fightReferee->refID, sizeof(char ), FIGHTER_ID_LENGTH + 1,pFile);
    saveClassToBinary(&pFight->winner, sizeof(int ),pFile);
    return 1;
}
int loadFightFromBinFile(Fight* pFight,FighterManger* pFighterMan,RefereeManger* pRefMan, FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    for (int i = 0; i < MAX_FIGHTERS; ++i) {
        char  temp[FIGHTER_ID_LENGTH + 1];
        fread(temp, sizeof(char ),FIGHTER_ID_LENGTH + 1,pFile);
        Fighter* fighter = findFighterByID(pFighterMan, temp);
        if (fighter != NULL)
            pFight->Fighters[i] = *fighter;
    }
    char temp[FIGHTER_ID_LENGTH + 1];
    fread(temp, sizeof(char ),FIGHTER_ID_LENGTH + 1,pFile);
    pFight->fightReferee = findRefereeByID(pRefMan,temp);
    loadClassFromBinary(&pFight->winner, sizeof(int ),pFile);
    return 1;
}

int compareFight(const void* fight1,const void* fight2){
    const Fight * cmpFight1 = (const Fight *)fight1;
    const Fight * cmpFight2 = (const Fight *)fight2;
    if (strcmp(cmpFight1->Fighters[0].ID,cmpFight2->Fighters[0].ID) == 0 && strcmp(cmpFight1->Fighters[1].ID,cmpFight2->Fighters[1].ID) == 0)
        return 0;
    return 1;
}