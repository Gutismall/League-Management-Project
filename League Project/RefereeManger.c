//
//  RefereeManger.c
//  C-Project
//
//  Created by Ari Guterman on 07/04/2024.
//

#include "RefereeManger.h"

void initRefereeManager(RefereeManger* pRefereeManger){
    pRefereeManger->RefereeList = NULL;
    pRefereeManger->numOfReferees = 0;
}
void printRefereesArray(const RefereeManger* pRefMan) {
    printf("Referees:\n");
    if (pRefMan->numOfReferees == 0) {
        printf("No referees yet\n\n");
    }
    else {
        for (int i = 0; i < pRefMan->numOfReferees; i++) {
            printRef(pRefMan->RefereeList[i]);
        }
    }
    printf("\n");
}

int addRefereeToList(RefereeManger* pRefereeManger){
    Referee* newReferee = (Referee*)malloc(sizeof(Referee));
    IF_NOT_ALLOC(newReferee)
    IF_NOT_INIT(initReferee,newReferee)
    pRefereeManger->RefereeList = (Referee**)realloc(pRefereeManger->RefereeList, sizeof(Referee*) * (pRefereeManger->numOfReferees + 1));
    IF_NOT_ALLOC(pRefereeManger->RefereeList)
    pRefereeManger->RefereeList[pRefereeManger->numOfReferees] = newReferee;
    pRefereeManger->numOfReferees++;
    return 1;
}
int loadRefereeArrayFromFile(RefereeManger* pRefereeManger,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)

    fscanf(pFile, "%d",&pRefereeManger->numOfReferees);
    pRefereeManger->RefereeList = (Referee**)calloc(pRefereeManger->numOfReferees, sizeof(Referee*));
    IF_NOT_ALLOC(pRefereeManger->RefereeList)
    for (int i = 0; i < pRefereeManger->numOfReferees; i++) {
        pRefereeManger->RefereeList[i] = (Referee*)malloc(sizeof(Referee));
        IF_NOT_ALLOC(pRefereeManger->RefereeList[i])
        SAVE_OR_OPEN_FILE(loadRefereeFromFile,pRefereeManger->RefereeList[i],pFile)
    }
    return 1;
}
int saveRefereeArrayToFile(RefereeManger* pRefereeManger,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    fprintf(pFile, "%d\n",pRefereeManger->numOfReferees);
    for (int i = 0; i < pRefereeManger->numOfReferees; i++) {
        SAVE_OR_OPEN_FILE(saveRefereeToFile,pRefereeManger->RefereeList[i],pFile)
    }
    return 1;
}
void freeRefereeArray(RefereeManger* pRefereeManger){
    for (int i = 0; i < pRefereeManger->numOfReferees; i++) {
        free(pRefereeManger->RefereeList[i]);
    }
    free(pRefereeManger->RefereeList);
}
Referee* findRefereeByID(const RefereeManger* rMan,char* ID){
    Referee* search = (Referee*)malloc(sizeof(Referee));
    IF_NOT_ALLOC(search)
    strcpy(search->refID,ID);
    for (int i = 0; i < rMan->numOfReferees; i++) {
        if (compareRefereeById(rMan->RefereeList[i], search) == 0) {
            return rMan->RefereeList[i];
        }
    }
    printf("Referee no found\n");
    return NULL;
}
int loadRefereeArrayFromBin(RefereeManger* pRefereeManger,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    int numOfReferees;
    loadClassFromBinary(&numOfReferees,sizeof (int ),pFile);
    pRefereeManger->numOfReferees = numOfReferees;
    pRefereeManger->RefereeList = (Referee **) calloc(numOfReferees,sizeof (Referee *));
    IF_NOT_ALLOC(pRefereeManger->RefereeList)
    for (int i = 0; i < pRefereeManger->numOfReferees; i++) {
        pRefereeManger->RefereeList[i] = (Referee *) malloc(sizeof (Referee));
        IF_NOT_ALLOC(pRefereeManger->RefereeList[i])
        SAVE_OR_OPEN_FILE(loadRefereeFromBinFile,pRefereeManger->RefereeList[i],pFile)
    }
    return 1;
}
int saveRefereeArrayToBin(RefereeManger* pRefereeManger,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    saveClassToBinary(&pRefereeManger->numOfReferees,sizeof(int ),pFile );
    for (int i = 0; i < pRefereeManger->numOfReferees; ++i) {
        SAVE_OR_OPEN_FILE(saveRefereeToBinFile,pRefereeManger->RefereeList[i],pFile)
    }
    return 1;
}