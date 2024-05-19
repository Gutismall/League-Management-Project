//
//  Event.h
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//

#ifndef Event_h
#define Event_h

#define MAX_EVENT_ID 3

#include "FighterManger.h"
#include "RefereeManger.h"
#include "Arena.h"
#include "Fight.h"
#include "Date.h"
#include "General.h"
#include "list.h"
typedef struct {
    char eventID[MAX_EVENT_ID + 1];
    Arena* eventArena;
    Fight* allFights;
    int numOfFights;
    Date eventDate;
    int ticketPrice;
}Event;

int getEventID(char* ID);
int initEvent(Event* pEvent,const Event* eventArr,int numOfEvents,LIST listOfArenas,const Fight* FightsArr,int sizeOfFightArray);
int addArenaToEvent(Event* pEvent,LIST arenaList);
int addFightToEvent(Event* pEvent,const Fight* fightArr,int sizeOfFightArr);

int loadEventFromFile(Event* pEvent, FighterManger* pFighterMan, RefereeManger* pRefMan, LIST* arenaList, FILE* pFile);
int saveEventToFile(const Event* pEvent,FILE* pFile);
int loadEventFromBin(Event* pEvent, FighterManger* pFighterMan, RefereeManger* pRefMan, LIST* arenaList, FILE* pFile);
int saveEventToBin(Event* pEvent,FILE* pFile);

int compareEventById(const void* event1,const void* event2);
int compareEventByDate(const void* event1,const void* event2);
int compareEventByTicketPrice(const void* event1,const void* event2);

void printEvent(const Event* pEvent);
#endif
