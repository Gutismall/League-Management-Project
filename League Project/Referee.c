//
//  Referee.c
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//

#include "Referee.h"

int initReferee(Referee* pRef){
    getFighterID(pRef->refID, "Enter referee ID: {0000-9999}\t");
    pRef->name = getStrExactName("Enter referees name:");
    printf("Enter years of experience:\t");
    scanf("%d", &(pRef->yearsOfExperience));
    return 1;
}
void printRef(const Referee* pRef){
    printf("name - %-10s\t\tID - %s\t\tYears of Experience - %d\n",pRef->name,pRef->refID,pRef->yearsOfExperience);
}
int saveRefereeToFile(Referee* pReferee, FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    fprintf(pFile,"%s\n",pReferee->refID);
    fprintf(pFile,"%s\n",pReferee->name);
    fprintf(pFile,"%d\n",pReferee->yearsOfExperience);
    return 1;
}
int loadRefereeFromFile(Referee* pReferee, FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    fscanf(pFile, "%s", pReferee->refID);
    fgetc(pFile);
    pReferee->name = readDynStringFromTextFile(pFile);
    fscanf(pFile, "%d", &pReferee->yearsOfExperience);
    return 1;
}
int saveRefereeToBinFile(Referee* pRef, FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    saveClassToBinary(pRef->refID,sizeof (pRef->refID),pFile);
    int nameLength = strlen(pRef->name) + 1;
    fwrite(&nameLength, sizeof(nameLength), 1, pFile) ;
    fwrite(pRef->name, sizeof(char), nameLength, pFile);
    saveClassToBinary(&pRef->yearsOfExperience,sizeof(pRef->yearsOfExperience),pFile);
    return 1;
}
int loadRefereeFromBinFile(Referee* pRef, FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    loadClassFromBinary(pRef->refID,sizeof(pRef->refID),pFile);
    int nameLength;
    fread(&nameLength, sizeof(nameLength), 1, pFile);
    pRef->name = (char*)malloc(nameLength * sizeof(char));
    IF_NOT_ALLOC(pRef->name)
    fread(pRef->name, sizeof(char), nameLength, pFile);
    pRef->name[nameLength] = '\0';
    fread(&(pRef->yearsOfExperience), sizeof(pRef->yearsOfExperience), 1, pFile);
    
    return 1;
}
int compareRefereeById(const void* referee1,const void* referee2){
    const Referee* cmpRef1 = (Referee*)referee1;
    const Referee* cmpRef2 = (Referee*)referee2;
    return strcmp(cmpRef1->refID, cmpRef2->refID);
}
void freeReferee(Referee * pRef){
    free(pRef);
}
