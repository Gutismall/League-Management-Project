//
//  Date.c
//  C-Project
//
//  Created by Ari Guterman on 30/03/2024.
//

#include <stdio.h>

#include "Date.h"
#include "General.h"

int initDate(Date* pDate)
{
    printf("Enter day: ");
    scanf("%d", &pDate->day);
    printf("Enter month: ");
    scanf("%d", &pDate->month);
    printf("Enter year: ");
    scanf("%d", &pDate->year);
    return checkCorrectDate(pDate);
}

int checkCorrectDate(const Date* pDate) {
    int maxDays;

    if (pDate->month < 1 || pDate->month > 12)
        return 0;

    switch (pDate->month) {
    case 2:
        maxDays = (pDate->year % 4 == 0 && (pDate->year % 100 != 0 || pDate->year % 400 == 0)) ? 29 : 28;
        if (pDate->day < 1 || pDate->day > maxDays)
            return 0;
        break;
    case 4: case 6: case 9: case 11:
        maxDays = 30;
        if (pDate->day < 1 || pDate->day > maxDays)
            return 0;
        break;
    default:
        maxDays = 31;
        if (pDate->day < 1 || pDate->day > maxDays)
            return 0;
        break;
    }

    return 1;
}
void printDate(const Date* pDate)
{
    printf("%02d/%02d/%04d\n", pDate->day, pDate->month, pDate->year);
}

int saveDateToFile(const Date* pDate, FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    fprintf(pFile, "%d\n", pDate->day);
    fprintf(pFile, "%d\n", pDate->month);
    fprintf(pFile, "%d\n", pDate->year);
    return 1;
}

int readDateFromFile(Date* pDate, FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    fscanf(pFile, "%d",&pDate->day);
    fgetc(pFile);
    fscanf(pFile, "%d",&pDate->month);
    fgetc(pFile);
    fscanf(pFile, "%d",&pDate->year);
    fgetc(pFile);
    return 1;
}

int readDateFromBinFile(Date* pDate, FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    fread(pDate, sizeof(Date), 1, pFile);
    return 1;
}

int saveDateToBinFile(const Date* pDate, FILE* pFile)
{
    IF_DIDNT_OPEN_FILE(pFile)
    if(!fwrite(pDate, sizeof(Date), 1, pFile))
        return 0;
    return 1;
}
int compareByDate(const void* date1,const void* date2){
    const Date* cmpDate1 = (const Date*)date1;
    const Date* cmpDate2 = (const Date*)date2;
    int temp1 = cmpDate1->year + cmpDate1->month + cmpDate1->day;
    int temp2 = cmpDate2->year + cmpDate2->month + cmpDate2->day;
    return temp1 - temp2;
}
