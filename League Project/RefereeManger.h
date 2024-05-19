//
//  RefereeManger.h
//  C-Project
//
//  Created by Ari Guterman on 07/04/2024.
//

#ifndef RefereeManger_h
#define RefereeManger_h

#include <stdio.h>
#include "Referee.h"

typedef struct {
    Referee** RefereeList;
    int numOfReferees;
}RefereeManger;

void initRefereeManager(RefereeManger* pRefereeManger);
int addRefereeToList(RefereeManger* pRefereeManger);
Referee* findRefereeByID(const RefereeManger* rMan,char* ID);

int loadRefereeArrayFromFile(RefereeManger* pRefereeManger,FILE* pFile);
int saveRefereeArrayToFile(RefereeManger* pRefereeManger,FILE* pFile);
int loadRefereeArrayFromBin(RefereeManger* pRefereeManger,FILE* pFile);
int saveRefereeArrayToBin(RefereeManger* pRefereeManger,FILE* pFile);

void printRefereesArray(const RefereeManger* pRefMan);
void freeRefereeArray(RefereeManger* pRefereeManger);
#endif /* RefereeManger_h */
