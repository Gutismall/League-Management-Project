//
//  Referee.h
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//

#ifndef Referee_h
#define Referee_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Fighter.h"

typedef struct{
    char refID[FIGHTER_ID_LENGTH + 1];
    char* name;
    int yearsOfExperience;
} Referee;


int initReferee(Referee* pRef);
void printRef(const Referee* pRef);
int saveRefereeToFile(Referee* pReferee, FILE* pFile);
int loadRefereeFromFile(Referee* pReferee, FILE* pFile);
int saveRefereeToBinFile(Referee* pRef, FILE* pFile);
int loadRefereeFromBinFile(Referee* pRef, FILE* pFile);
int compareRefereeById(const void* referee1,const void* referee2);
void freeReferee(Referee * pRef);


#endif /* Referee_h */
