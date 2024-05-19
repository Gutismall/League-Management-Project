//
//  Arena.h
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//

#ifndef Arena_h
#define Arena_h

#include "General.h"

typedef struct{
    int arenaID;
    char* name;
    int numOfSeats;
    char* country;
} Arena;

int initArena(Arena* pArena);
int getArenaID(int* ID);

int loadArenaFromFile(Arena* pArena,FILE* pFile);
int saveArenaToFile(const Arena* pArena,FILE* pFile);
int loadArenaFromBinary(Arena* pArena, FILE* pFile);
int saveArenaToBinary(Arena* pArena,FILE* pFile);

int compareArenaById(const void* id1,const void* id2);
void printArena(const Arena* pArena);


#endif /* Arena_h */
