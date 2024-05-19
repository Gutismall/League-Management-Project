//
//  Event.c
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Event.h"




int initEvent(Event* pEvent,const Event* eventArr,const int numOfEvents,const LIST listOfArenas,const Fight* FightsArr,const int sizeOfFightArray){
    int check;
    do {
        check = 1;
        if (!getEventID(pEvent->eventID))
            return 0;
        if (generalCompareFunction(eventArr, sizeof(Event),numOfEvents,compareEventById,pEvent)){
                printf("This event ID is already taken\n");
                check = 0;
        }
    } while (check == 0);
    if (!initDate(&pEvent->eventDate)) {
        printf("Invalid date\n");
        return 0;
    }
    if ( generalCompareFunction(eventArr, sizeof(Event), numOfEvents, compareEventByDate,pEvent)){
        printf("There is an event on this date already\n");
        return 0;
    }

    pEvent->eventArena = NULL;
    if(!addArenaToEvent(pEvent, listOfArenas)){
        printf("Arena not found\n");
        return 0;
    }
    int input;
    do {
        printf("How many fights are in this event ?\n");
        scanf("%d",&input);
        if (input < 1 || input > sizeOfFightArray) {
            printf("Invalid number of fights\n");
        }
    } while (input < 1 || input > sizeOfFightArray);
    do {
        if (!addFightToEvent(pEvent, FightsArr, sizeOfFightArray)) {
            continue;
        }
        input--;
    } while (input != 0);
    printf("Enter the ticket price for this event\t");
    scanf("%d",&pEvent->ticketPrice);
    return 1;
    
}
int loadEventFromFile(Event* pEvent,FighterManger* pFighterMan,RefereeManger* pRefMan,LIST* arenaList,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    fscanf(pFile, "%s",pEvent->eventID);
    fgetc(pFile);
    Arena* findArena = (Arena*)malloc(sizeof(Arena));
    IF_NOT_ALLOC(findArena)
    fscanf(pFile, "%d",&findArena->arenaID);
    fgetc(pFile);
    pEvent->eventArena = L_find(arenaList->head.next, findArena, compareArenaById)->key;
    
    fscanf(pFile, "%d",&pEvent->numOfFights);
    fgetc(pFile);
    pEvent->allFights = (Fight*)calloc(pEvent->numOfFights, sizeof(Fight));
    IF_NOT_ALLOC(pEvent->allFights)
    for (int i = 0; i  < pEvent->numOfFights; i++) {
        loadFightFromFile(&pEvent->allFights[i], pFighterMan,pRefMan,pFile);
    }
    readDateFromFile(&pEvent->eventDate,pFile);
    fscanf(pFile, "%d",&pEvent->ticketPrice);
    fgetc(pFile);
    return 1;
}
int saveEventToFile(const Event* pEvent,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    fprintf(pFile, "%s\n",pEvent->eventID);
    fprintf(pFile, "%d\n",pEvent->eventArena->arenaID);
    fprintf(pFile, "%d\n",pEvent->numOfFights);
    for (int i = 0; i < pEvent->numOfFights; i++) {
        if(!saveFightsToFile(&pEvent->allFights[i], pFile))
            return 0;
    }
    if(!saveDateToFile(&pEvent->eventDate,pFile))
        return 0;
    fprintf(pFile, "%d\n",pEvent->ticketPrice);
    return 1;
}
int loadEventFromBin(Event* pEvent, FighterManger* pFighterMan, RefereeManger* pRefMan, LIST* arenaList, FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    fread(pEvent->eventID,sizeof (char ),MAX_EVENT_ID + 1,pFile);
    Arena* findArena = (Arena*) malloc(sizeof(Arena));
    IF_NOT_ALLOC(findArena)
    loadClassFromBinary(&findArena->arenaID, sizeof(int ),pFile);
    pEvent->eventArena = L_find(arenaList->head.next, findArena, compareArenaById)->key;
    loadClassFromBinary(&pEvent->numOfFights, sizeof(int ),pFile);
    pEvent->allFights = (Fight*) calloc(pEvent->numOfFights,sizeof (Fight));
    IF_NOT_ALLOC(pEvent->allFights)
    for (int i = 0; i < pEvent->numOfFights; ++i) {
        if (!loadFightFromBinFile(&pEvent->allFights[i],pFighterMan,pRefMan,pFile))
            return 0;
    }
    SAVE_OR_OPEN_FILE(readDateFromBinFile,&pEvent->eventDate,pFile)
    loadClassFromBinary(&pEvent->ticketPrice, sizeof(int ),pFile);
    return 1;
}
int saveEventToBin(Event* pEvent,FILE* pFile){
    IF_DIDNT_OPEN_FILE(pFile)
    fwrite(pEvent->eventID, sizeof(char ),MAX_EVENT_ID + 1,pFile);
    saveClassToBinary(&pEvent->eventArena->arenaID, sizeof(int ),pFile);
    saveClassToBinary(&pEvent->numOfFights, sizeof(int ),pFile);
    for (int i = 0; i < pEvent->numOfFights; ++i) {
        SAVE_OR_OPEN_FILE(saveFightToBinFile,&pEvent->allFights[i],pFile)
    }
    SAVE_OR_OPEN_FILE(saveDateToBinFile,&pEvent->eventDate,pFile)
    saveClassToBinary(&pEvent->ticketPrice, sizeof(int ),pFile);
    return 1;
}
int getEventID(char* ID){
    char* temp = getStrExactName("Enter event ID - 3 numbers");
    if (strlen(temp) != MAX_EVENT_ID) {
        printf("Event ID must be %d\n",MAX_EVENT_ID);
        return 0;
    }
    for (int i = 0; i < MAX_EVENT_ID; i++) {
        if (!isdigit(temp[i])) {
            printf("ID must be numbers\n");
            return 0;
        }
    }
    strcpy(ID, temp);
    return 1;
}
int addArenaToEvent(Event* pEvent,const LIST arenaList){
    int tempID;
    NODE* search = arenaList.head.next;
    
    printf("Pick arena for the event:\n");
    L_print(&arenaList);
    getArenaID(&tempID);
    
    while (search != NULL) {
        if (search->key->arenaID == tempID) {
            pEvent->eventArena = search->key;
            return 1;
        }
        search = search->next;
    }
    return 0;
}
void printEvent(const Event* pEvent){
    printf("UFC%s\n",pEvent->eventID);
    printArena(pEvent->eventArena);
    printf("Ticket Price: %d\n",pEvent->ticketPrice);
    for (int i = 0; i < pEvent->numOfFights; i++) {
        printf("Fight %d:", i+ 1);
        printFight(&pEvent->allFights[i]);
        switch (pEvent->allFights[i].winner) {
            case -1:
                break;
            case 0:
                printf("Winner of fight : %s\n",pEvent->allFights[i].Fighters[0].name);
                break;
            case 1:
                printf("Winner of fight : %s\n",pEvent->allFights[i].Fighters[1].name);
                break;
        }
    }
    printDate(&pEvent->eventDate);
    printf("\n");
}
int addFightToEvent(Event* pEvent,const Fight* fightArr,const int sizeOfFightArr){
    int input;
    printf("Select the fight you want to add:\n");
    for (int i = 0; i < sizeOfFightArr; i++) {
        printf("%d) ", i + 1);
        printFight(&fightArr[i]);
    }
    scanf("%d", &input);
    input -= 1;
    if (input < 0 || input >= sizeOfFightArr) {
        WRONG_INDEX
        return 0;
    }
    if (generalCompareFunction(pEvent->allFights, sizeof(Fight),pEvent->numOfFights,compareFight,&fightArr[input])){
        printf("\n\nThis fight already in this event\n");
        return 0;
    }
    pEvent->allFights = (Fight*) realloc(pEvent->allFights,(pEvent->numOfFights + 1) * sizeof(Fight));
    IF_NOT_ALLOC(pEvent->allFights)
    pEvent->allFights[pEvent->numOfFights] = fightArr[input];
    pEvent->numOfFights++;
    return 1;
}
int compareEventById(const void* event1,const void* event2){
    const Event* cmpEvent1 = (const Event*)event1;
    const Event* cmpEvent2 = (const Event*)event2;
    return strcmp(cmpEvent1->eventID, cmpEvent2->eventID);
}
int compareEventByDate(const void* event1,const void* event2){
    const Event* cmpEvent1 = (const Event*)event1;
    const Event* cmpEvent2 = (const Event*)event2;
    return compareByDate(&cmpEvent1->eventDate, &cmpEvent2->eventDate);
}
int compareEventByTicketPrice(const void* event1,const void* event2){
    const Event* cmpEvent1 = (const Event*)event1;
    const Event* cmpEvent2 = (const Event*)event2;
    return cmpEvent1->ticketPrice - cmpEvent2->ticketPrice;
}