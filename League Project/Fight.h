//
//  Fight.h
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//

#ifndef Fight_h
#define Fight_h
#define MAX_FIGHTERS 2

#include "FighterManger.h"
#include "RefereeManger.h"

typedef struct{
    Fighter Fighters[MAX_FIGHTERS];
    Referee* fightReferee;
    int winner;
    
} Fight;

int initFight(Fight* pFight,const FighterManger* fMan,const RefereeManger* rMan);
void addWinner(Fight* pFight, int pWinner);
void changeReferee(Fight* pFight, Referee* newReferee);

int loadFightFromFile(Fight* pFight, FighterManger* pFighterMan, RefereeManger* pRefMan, FILE* pFile);
int saveFightsToFile(Fight* pFight,FILE* pFile);
int loadFightFromBinFile(Fight* pFight,FighterManger* pFighterMan,RefereeManger* pRefMan, FILE* pFile);
int saveFightToBinFile(Fight* pFight,FILE* pFile);

int compareFight(const void* fight1,const void* fight2);
void freeFight(Fight* pFight);
void printFight(const Fight* pFight);
#endif /* Fight_h */
