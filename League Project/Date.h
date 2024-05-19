//
//  Date.h
//  C-Project
//
//  Created by Ari Guterman on 30/03/2024.
//

#ifndef Date_h
#define Date_h



typedef struct {
    
    int day;
    int month;
    int year;
    
}Date;

int initDate(Date* pDate);
int checkCorrectDate(const Date* pDate);

int saveDateToFile(const Date* pDate, FILE* pFile);
int readDateFromFile(Date* pDate, FILE* pFile);
int readDateFromBinFile(Date* pDate, FILE* pFile);
int saveDateToBinFile(const Date* pDate, FILE* pFile);

void printDate(const Date* pDate);
int compareByDate(const void* date1,const void* date2);
#endif /* Date_h */
