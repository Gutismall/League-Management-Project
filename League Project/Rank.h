//
//  Rank.h
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//

#ifndef Rank_h
#define Rank_h

typedef unsigned char BYTE;

typedef struct{
    
    unsigned int win; //0-50
    unsigned int losses; //0-50
    unsigned int draw; //0-50
    unsigned int knockout; //0-50
    
} Rank;

void printRank(Rank* pRank);
void initRank(Rank* pRank);
void getCorrectRank(Rank* pRank,char* input);
void updateWinner(Rank * winnersRank,Rank* loosersRank,int ifKnockout);
int saveRankToBinaryFileCompressed(Rank* pRank,FILE* pFile);
int loadRankFromBinaryFileCompressed(Rank* pRank, FILE* pFile);
int saveRankToFile(Rank* pRank,FILE* pFile);
int loadRankFromFile(Rank* pRank,FILE* pFile);

#endif /* Rank_h */
