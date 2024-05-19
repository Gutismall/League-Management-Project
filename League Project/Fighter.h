//
//  Fighter.h
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//

#ifndef Fighter_h
#define Fighter_h
#define FIGHTER_ID_LENGTH 4

#include "General.h"
#include "Rank.h"


typedef enum {eFeather,eLight,eMid,eHeavy,eNofClasses}weightClass;
static const char* classes[eNofClasses] = {"Feather weight","Light weight","Middle weight","Heavy weight"};


typedef struct {
    char ID[FIGHTER_ID_LENGTH + 1];
    char* name;
    Rank* fightersRank;
    weightClass fightersClass;
}Fighter;

void getFighterID(char* code,char* msg);
int initFighter(Fighter* pFighter);
int updateFighterRank(Fighter* pFighter);
int updateFighterWeightClass(Fighter* pFighter);


int loadFighterFromFile(Fighter* pFighter,FILE* pFile);
int saveFighterToFile(Fighter* pFighter,FILE* pFile);
int loadFighterFromBinFile(Fighter* pFighter, FILE* pFile);
int saveFighterToBinFile(Fighter* pFighter, FILE* pFile);



void printFighter(const Fighter* pFighter);
void freeFighter(void* pFighter);

int compareByWins(const void* Fighter1,const void* Fighter2);
int compareByLooses(const void* Fighter1,const void* Fighter2);
int compareByDraws(const void* Fighter1,const void* Fighter2);
int compareByKnockouts(const void* Fighter1,const void* Fighter2);
int compareFighterById(const void* Fighter1,const void* Fighter2);
#endif /* Fighter_h */
