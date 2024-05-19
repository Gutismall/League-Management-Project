//
//  FighterManger.h
//  C-Project
//
//  Created by Ari Guterman on 07/04/2024.
//

#ifndef FighterManger_h
#define FighterManger_h


#include "Fighter.h"

typedef struct {
    Fighter** FightersList;
    int numOfFighters;
}FighterManger;

void initFighterManager(FighterManger* pFighterMan);
int addFighterToList(FighterManger* pFighterMan);
Fighter* findFighterByID(const FighterManger* fMan,const char* ID);

int loadFightersArrayFromFile(FighterManger* pFighterMan,FILE* pFile);
int saveFightersArrayToFile(FighterManger* pFighterMan,FILE* pFile);
int loadFightersArrayFromBin(FighterManger* pFighterMan,FILE* pFile);
int saveFightersArrayToBin(FighterManger* pFighterMan, FILE* pFile);

void printRanking(const FighterManger* pFighterMan);
void printFightersArray(const FighterManger* pFighterMan);
void freeFighterArray(FighterManger* pFighterMan);

#endif /* FighterManger_h */
