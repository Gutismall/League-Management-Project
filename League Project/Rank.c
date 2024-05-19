//
//  Rank.c
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Rank.h"
#include "General.h"

void initRank(Rank* pRank){
    pRank->win = 0;
    pRank->losses = 0;
    pRank->draw = 0;
    pRank->knockout = 0;
}
void getCorrectRank(Rank* pRank,char* input){
    
    pRank->win = atoi(strtok(input, "/"));
    pRank->losses = atoi(strtok(NULL, "/"));
    pRank->draw = atoi(strtok(NULL, "/"));
    pRank->knockout = atoi(strtok(NULL, "/"));
}
void updateWinner(Rank * winnersRank,Rank* loosersRank,int ifKnockout){
    winnersRank->win++;
    if(ifKnockout == 1)
        winnersRank->knockout++;
    loosersRank->losses++;
}
void printRank(Rank* pRank){
    printf("current rank : %d/%d/%d/%d", pRank->win, pRank->draw, pRank->losses, pRank->knockout);
}

int saveRankToBinaryFileCompressed(Rank* pRank,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    BYTE data[3];
    data[0] = (pRank->knockout << 2) | (pRank->losses >> 4);
    data[1] = ((pRank->losses & 0x0F) << 4) | (pRank->draw >> 2);
    data[2] = ((pRank->draw & 0x03) << 6) | pRank->win;
    if(fwrite(data, sizeof(BYTE), 3, pFile) != 3)
        return 0;
    return 1;
}

int loadRankFromBinaryFileCompressed(Rank* pRank, FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    BYTE data[3];
    if(fread(data, sizeof(BYTE), 3, pFile) != 3)
        return 0;
    pRank->knockout = (data[0] >> 2) & 0x3F;
    pRank->losses = ((data[0] & 0x03) << 4) | ((data[1] >> 4) & 0x0F);
    pRank->draw = ((data[1] & 0x0F) << 2) | ((data[2] >> 6) & 0x03);
    pRank->win = data[2] & 0x3F;
    
    return 1;
}
int saveRankToFile(Rank* pRank,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    fprintf(pFile, "%u/%u/%u/%u\n", pRank->win, pRank->draw, pRank->losses, pRank->knockout);
    return 1;
}
int loadRankFromFile(Rank* pRank,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    char temp[255];
    fscanf(pFile, "%s",temp);
    getCorrectRank(pRank, temp);
    return 1;
}
