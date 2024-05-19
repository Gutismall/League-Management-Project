//
//  League.h
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//

#ifndef League_h
#define League_h

#include "FighterManger.h"
#include "RefereeManger.h"
#include "Fight.h"
#include "Event.h"
#include "list.h"
#define LEAGUE_TXT_NAME "League.txt"
#define LEAGUE_BIN_NAME "League.bin"

typedef enum {eByID,eByDate,eByTicketprice,eNotSorted,eNofSorted}TypeOfSort;
static const char* EventSort[eNofSorted]
        = { "ID", "Date", "Ticket price","Not sorted" };

typedef struct{
    TypeOfSort eventSort;
    FighterManger* FighterMan;
    RefereeManger* RefMan;
    Fight* listOfFights;
    int numOfFights;
    Event* listOfEvents;
    int numOfEvents;
    LIST listOfArena;
    int numOFArenas;
    
} League;

int initLeague(League* pLeague);
int addEvent(League* pLeague);
int addArena(League* pLeague);
int addFight(League* pLeague);
int FindEvent(League* pLeague);
void selectWinner(League* pLeague);
void sortEvents(League* pLeague);

int LoadLeagueFromFile(League* pLeague, char* fileName);
int saveLeagueToFile(League* pLeague);
int LoadLeagueFromBin(League* pLeague, char* fileName);
int saveLeagueToBin(League* pLeague);


void freeLeague(League* pLeague);
void printLeague(const League* pLeague);





#endif /* League_h */
