//
//  League.c
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "League.h"

int initLeague(League* pLeague){
    pLeague->FighterMan = (FighterManger*)malloc(sizeof(FighterManger));
    IF_NOT_ALLOC(pLeague->FighterMan)
    initFighterManager(pLeague->FighterMan);
    pLeague->RefMan = (RefereeManger*)malloc(sizeof(RefereeManger));
    IF_NOT_ALLOC(pLeague->FighterMan)
    initRefereeManager(pLeague->RefMan);

    pLeague->listOfEvents = NULL;
    pLeague->listOfFights = NULL;
    if(!L_init(&pLeague->listOfArena)){
        return 0;
    }
    pLeague->numOfFights = 0;
    pLeague->numOfEvents = 0;
    pLeague->numOFArenas = 0;
    return 1;
}

int addEvent(League* pLeague){
    if (pLeague->numOfFights == 0) {
        printf("Cant add event without fights\n");
        return 0;
    }
    if (pLeague->numOFArenas == 0) {
        printf("Cant add event without arenas\n");
        return 0;
    }
    Event* newEvent = (Event*)malloc(sizeof(Event));
    IF_NOT_ALLOC(newEvent)
    if(!initEvent(newEvent,pLeague->listOfEvents,pLeague->numOfEvents,pLeague->listOfArena,pLeague->listOfFights,pLeague->numOfFights)){
        free(newEvent);
        return 0;
    }
    pLeague->listOfEvents = (Event*)realloc(pLeague->listOfEvents, sizeof(Event) * (pLeague->numOfEvents + 1));
    IF_NOT_ALLOC(pLeague->listOfEvents)
    pLeague->listOfEvents[pLeague->numOfEvents] = *newEvent;
    pLeague->numOfEvents++;
    pLeague->eventSort = eNotSorted;
    return 1;
}
int addArena(League* pLeague){
    Arena* newArena = (Arena*)malloc(sizeof(Arena));
    IF_NOT_ALLOC(newArena)
    IF_NOT_INIT(initArena,newArena)
    if (L_find(pLeague->listOfArena.head.next, newArena, compareArenaById)) {
        printf("\nThis ID already exists\n\n");
        free(newArena);
        return 0;
    }
    L_insert(&pLeague->listOfArena.head, newArena);
    pLeague->numOFArenas++;
    return 1;
}
int addFight(League* pLeague){
    if (pLeague->FighterMan->numOfFighters < 2) {
        printf("\nCant add fight without enough fighters\n\n");
        return 0;
    }
    if (pLeague->RefMan->numOfReferees == 0) {
        printf("\nCant add fight without referees\n\n");
        return 0;
    }


    Fight* newFight = (Fight*)malloc(sizeof(Fight));
    IF_NOT_ALLOC(newFight)
    if (!initFight(newFight,pLeague->FighterMan,pLeague->RefMan)) {
        return 0;
    }
    if (generalCompareFunction(pLeague->listOfFights, sizeof(Fight),pLeague->numOfFights,compareFight,newFight)){
        printf("This fight already exist\n");
        free(newFight);
        return 0;
    }
    pLeague->listOfFights = (Fight*)realloc(pLeague->listOfFights, (pLeague->numOfFights + 1) * sizeof(Fight));
    IF_NOT_ALLOC(pLeague->listOfFights)
    pLeague->listOfFights[pLeague->numOfFights] = *newFight;
    pLeague->numOfFights++;
    return 1;
}
void printLeague(const League* pLeague){
    printFightersArray(pLeague->FighterMan);
    printRefereesArray(pLeague->RefMan);
    printf("Arenas:\n");
    if (pLeague->listOfArena.head.next == NULL) {
        printf("No arenas yet\n\n");
    }
    else
        L_print(&pLeague->listOfArena);
    printf("\n");
    printf("Fights:\n");
    if (pLeague->numOfFights == 0) {
        printf("No fights yet\n\n");
    }
    else
    {
        for (int i = 0; i < pLeague->numOfFights; i++)
        {
            printf("Fight %d - ",i + 1);
            printFight(&pLeague->listOfFights[i]);
            printf("\n");
        }
    }
    printf("Events:\n");
    if (pLeague->numOfEvents == 0) {
        printf("No events yet\n\n");
    }
    else{
        for (int i = 0; i < pLeague->numOfEvents; i++) {
            printEvent(&pLeague->listOfEvents[i]);
        }
    }
}
void sortEvents(League* pLeague) {
    if (pLeague->numOfEvents < 1) {
        printf("Not enough events yet\n\n");
        return;
    }
    int choice;
    printf("\nHow would you like to sort the list?\n");
    do {
        for (int i = 0; i < eNofSorted - 1; i++) {
            printf("%d - %s\n", i + 1, EventSort[i]);
        }
        scanf("%d", &choice);
    } while (choice < 1 || choice > 3);
    switch (choice) {
        case 1:
            qsort(pLeague->listOfEvents, pLeague->numOfEvents, sizeof(Event), compareEventById);
            pLeague->eventSort = eByID;
            break;
        case 2:
            qsort(pLeague->listOfEvents, pLeague->numOfEvents, sizeof(Event ), compareEventByDate);
            pLeague->eventSort = eByDate;
            break;
        case 3:
            qsort(pLeague->listOfEvents, pLeague->numOfEvents, sizeof(Event ), compareEventByTicketPrice);
            pLeague->eventSort = eByTicketprice;
            break;

    }
}
int FindEvent(League* pLeague){
    if (!pLeague->numOfEvents) {
        printf("No events yet\n");
        return 0;
    }
    Event* found = NULL;
    Event* search = (Event*)malloc(sizeof(Event));
    IF_NOT_ALLOC(search)
    switch (pLeague->eventSort) {
        case eByID:
            printf("Event id:\t");
            getEventID(search->eventID);
            if (bsearch(search, pLeague->listOfEvents, pLeague->numOfEvents, sizeof(Event), compareEventById)) {
                found = bsearch(search, pLeague->listOfEvents, pLeague->numOfEvents, sizeof(Event), compareEventById);
            }
            break;
        case eByDate:
            printf("Date:\t");
            initDate(&search->eventDate);
            if (bsearch(search, pLeague->listOfEvents, pLeague->numOfEvents, sizeof(Event), compareEventByDate)) {
                found = bsearch(search, pLeague->listOfEvents, pLeague->numOfEvents, sizeof(Event), compareEventByDate);
            }
            break;
        case eByTicketprice:
            printf("Ticket price:\t");
            scanf("%d",&search->ticketPrice);
            if (bsearch(search, pLeague->listOfEvents, pLeague->numOfEvents, sizeof(Event), compareEventByTicketPrice)) {
                found = bsearch(search, pLeague->listOfEvents, pLeague->numOfEvents, sizeof(Event), compareEventByTicketPrice);
            }
            break;
        case eNotSorted:
            printf("Sort event list first\n");
            return 0;
    }
    if (found == NULL) {
        printf("Event not found\n");
        return 0;
    }
    else{
        printEvent(found);
        return 1;
    }
}
int LoadLeagueFromFile(League* pLeague, char* fileName){
    FILE* pFile = fopen(fileName, "r");
    IF_DIDNT_OPEN_FILE(pFile)
    pLeague->FighterMan = (FighterManger*)malloc(sizeof(FighterManger));
    IF_NOT_ALLOC(pLeague->FighterMan)
    SAVE_OR_OPEN_FILE(loadFightersArrayFromFile,pLeague->FighterMan,pFile)
    pLeague->RefMan = (RefereeManger*)malloc(sizeof(RefereeManger));
    IF_NOT_ALLOC(pLeague->RefMan)
    SAVE_OR_OPEN_FILE(loadRefereeArrayFromFile,pLeague->RefMan,pFile)
    if (!L_init(&pLeague->listOfArena)) {
        return 0;
    }
    fscanf(pFile, "%d",&pLeague->numOFArenas);
    if (pLeague->numOFArenas != 0) {
        NODE* nTemp = &pLeague->listOfArena.head;
        for (int i = 0; i < pLeague->numOFArenas; i++) {
            Arena* newArena = (Arena*)malloc(sizeof(Arena));
            IF_NOT_ALLOC(newArena)
            loadArenaFromFile(newArena,pFile);
            L_insert(nTemp, newArena);
            nTemp = nTemp->next;
        }
    }
    fscanf(pFile, "%d",&pLeague->numOfFights);
    fgetc(pFile);
    pLeague->listOfFights = (Fight*)calloc(pLeague->numOfFights, sizeof(Fight));
    IF_NOT_ALLOC(pLeague->listOfFights)
    if (pLeague->numOfFights != 0) {
        for (int i = 0; i < pLeague->numOfFights; i++) {
            if (!loadFightFromFile(&pLeague->listOfFights[i], pLeague->FighterMan, pLeague->RefMan, pFile)) {
                return 0;
            }
        }
    }
    fscanf(pFile, "%d",&pLeague->numOfEvents);
    pLeague->listOfEvents = (Event*)calloc(pLeague->numOfEvents, sizeof(Event));
    IF_NOT_ALLOC(pLeague->listOfEvents)
    if (pLeague->numOfEvents != 0) {
        for (int i = 0; i < pLeague->numOfEvents; i++) {
            if (!loadEventFromFile(&pLeague->listOfEvents[i],pLeague->FighterMan,pLeague->RefMan,&pLeague->listOfArena,pFile)) {
                return 0;
            }
        }
    }
    pLeague->eventSort = eNotSorted;
    fclose(pFile);
    return 1;
}
int saveLeagueToFile(League *pLeague) {
    FILE *pFile;
    pFile = fopen(LEAGUE_TXT_NAME, "w");
    IF_DIDNT_OPEN_FILE(pFile)
    SAVE_OR_OPEN_FILE(saveFightersArrayToFile,pLeague->FighterMan,pFile)
    SAVE_OR_OPEN_FILE(saveRefereeArrayToFile,pLeague->RefMan,pFile)
    fprintf(pFile, "%d\n", pLeague->numOFArenas);
    if (pLeague->numOFArenas != 0) {
        NODE *temp = pLeague->listOfArena.head.next;
        while (temp != NULL) {
            SAVE_OR_OPEN_FILE(saveArenaToFile,temp->key,pFile)
            temp = temp->next;
        }
    }
    fprintf(pFile, "%d\n", pLeague->numOfFights);
    if (pLeague->numOfFights != 0) {
        for (int i = 0; i < pLeague->numOfFights; i++) {
            SAVE_OR_OPEN_FILE(saveFightsToFile,&pLeague->listOfFights[i],pFile)
        }
    }
    fprintf(pFile, "%d\n", pLeague->numOfEvents);
    if (pLeague->numOfEvents != 0) {
        for (int i = 0; i < pLeague->numOfEvents; i++) {
            SAVE_OR_OPEN_FILE(saveEventToFile,&pLeague->listOfEvents[i],pFile)
        }
    }
    fclose(pFile);
    return 1;
}
int saveLeagueToBin(League* pLeague){
    FILE* pFile = fopen(LEAGUE_BIN_NAME, "wb");
    IF_DIDNT_OPEN_FILE(pFile)
    SAVE_OR_OPEN_FILE(saveFightersArrayToBin, pLeague->FighterMan, pFile)
    SAVE_OR_OPEN_FILE(saveRefereeArrayToBin,pLeague->RefMan,pFile)
    saveClassToBinary(&pLeague->numOFArenas, sizeof(int ),pFile);
    NODE* temp = pLeague->listOfArena.head.next;
    while (temp != NULL){
        SAVE_OR_OPEN_FILE(saveArenaToBinary,temp->key,pFile)
        temp = temp->next;
    }
    saveClassToBinary(&pLeague->numOfFights,sizeof (int ),pFile);
    for (int i = 0; i < pLeague->numOfFights; ++i) {
        SAVE_OR_OPEN_FILE(saveFightToBinFile,&pLeague->listOfFights[i],pFile)
    }
    saveClassToBinary(&pLeague->numOfEvents,sizeof (int ),pFile);
    for (int i = 0; i < pLeague->numOfEvents; ++i) {
        SAVE_OR_OPEN_FILE(saveEventToBin,&pLeague->listOfEvents[i],pFile)
    }
    fclose(pFile);
    return 1;
}
int LoadLeagueFromBin(League* pLeague, char* fileName){
    FILE* pFile = fopen(fileName,"rb");
    IF_DIDNT_OPEN_FILE(pFile)
    pLeague->FighterMan = (FighterManger*)malloc(sizeof(FighterManger));
    initFighterManager(pLeague->FighterMan);
    SAVE_OR_OPEN_FILE(loadFightersArrayFromBin, pLeague->FighterMan, pFile)
    pLeague->RefMan = (RefereeManger*)malloc(sizeof(RefereeManger));
    initRefereeManager(pLeague->RefMan);
    SAVE_OR_OPEN_FILE(loadRefereeArrayFromBin,pLeague->RefMan,pFile)
    loadClassFromBinary(&pLeague->numOFArenas,sizeof (int ),pFile);
    if (!L_init(&pLeague->listOfArena)){
        return 0;
    }
    NODE* temp = &pLeague->listOfArena.head;
    for (int i = 0; i < pLeague->numOFArenas; ++i) {
        Arena* newArena = (Arena*) malloc(sizeof (Arena));
        IF_NOT_ALLOC(newArena)
        SAVE_OR_OPEN_FILE(loadArenaFromBinary,newArena,pFile)
        L_insert(temp,newArena);
        temp = temp->next;
    }
    loadClassFromBinary(&pLeague->numOfFights,sizeof (int ),pFile);
    pLeague->listOfFights = (Fight*) calloc(pLeague->numOfFights,sizeof (Fight));
    IF_NOT_ALLOC(pLeague->listOfFights)
    for (int i = 0; i < pLeague->numOfFights; ++i) {
        if (!loadFightFromBinFile(&pLeague->listOfFights[i],pLeague->FighterMan,pLeague->RefMan,pFile)){
            return 0;
        }
    }
    loadClassFromBinary(&pLeague->numOfEvents,sizeof (int ),pFile);
    pLeague->listOfEvents = (Event*) calloc(pLeague->numOfEvents,sizeof(Event));
    IF_NOT_ALLOC(pLeague->listOfEvents)
    for (int i = 0; i < pLeague->numOfEvents; ++i) {
        if (!loadEventFromBin(&pLeague->listOfEvents[i],pLeague->FighterMan,pLeague->RefMan,&pLeague->listOfArena,pFile))
            return 0;
    }
    pLeague->eventSort = eNotSorted;
    fclose(pFile);
    return 1;
}
void freeLeague(League* pLeague){
    freeFighterArray(pLeague->FighterMan);
    freeRefereeArray(pLeague->RefMan);
    if (pLeague->numOfEvents != 0) {
        free(pLeague->listOfEvents);
    }
    if (pLeague->numOFArenas) {
        L_free(&pLeague->listOfArena);
    }
    if (pLeague->numOfFights) {
        free(pLeague->listOfFights);
    }
}
void selectWinner(League* pLeague){
    if (pLeague->numOfEvents == 0){
        printf("No events yet\n");
        return;
    }
    int eventSelect;
    printf("Please select event\n");
    for (int i = 0; i < pLeague->numOfEvents; ++i) {
        printf("%d)",i + 1);
        printf("UFC%s\n",pLeague->listOfEvents[i].eventID);
    }
    scanf("%d",&eventSelect);
    eventSelect-=1;
    if (eventSelect < 0 || eventSelect > pLeague->numOfEvents){
        WRONG_INDEX
        return;
    }
    int winnerselect;
    for(int i = 0;i < pLeague->numOfFights ;i++){
        printf("Who is the winner for this fight ?\n");
        printf("1)%s\n",pLeague->listOfEvents[eventSelect].allFights[i].Fighters[0].name);
        printf("2)%s\n",pLeague->listOfEvents[eventSelect].allFights[i].Fighters[1].name);
        scanf("%d",&winnerselect);
        switch (winnerselect) {
            case 1:
                addWinner(&pLeague->listOfEvents[eventSelect].allFights[i],0);
                break;
            case 2:
                addWinner(&pLeague->listOfEvents[eventSelect].allFights[i],1);
                break;
            default:
                WRONG_INDEX
                break;
        }

    }
}
