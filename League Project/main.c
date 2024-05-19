//
//  main.c
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//

#include <stdio.h>
#include <time.h>
#include "League.h"

int main(void) {
    srand(time(NULL));
    League newLeague;
    int fileInput,ok = 0;

    do {
        printf("Welcome from what file type would you like to use\n");
        printf("1) Binary file\n");
        printf("2) Text file\n");
        scanf("%d",&fileInput);
        switch (fileInput) {
            case 1:
                if (!LoadLeagueFromBin(&newLeague,LEAGUE_BIN_NAME)){
                    printf("File does not exist starting system from user\n");
                    initLeague(&newLeague);
                }
                ok = 1;
                break;
            case 2:
                if (!LoadLeagueFromFile(&newLeague, LEAGUE_TXT_NAME)){
                    printf("File does not exist starting system from user\n");
                    initLeague(&newLeague);
                }
                ok = 1;
                break;
            default:
                WRONG_INDEX;
                break;
        }
    } while (!ok);
    int input;
    do {
        printf("Please select your option:\n");
        printf("1 - Add fighter to league \t2 - Add Referee to league \n");
        printf("3 - Add new fight \t\t4 - Add new arena \n");
        printf("5 - Add new event \t\t6 - Print rankings \n");
        printf("7 - Print league \t\t8 - Sort events \n");
        printf("9 - Find events \t\t10 - Select winner to fight \n");
        printf("-1 - Exit \n");
        scanf("%d",&input);
        switch (input) {
            case 1:
                addFighterToList(newLeague.FighterMan);
                break;
            case 2:
                addRefereeToList(newLeague.RefMan);
                break;
            case 3:
                addFight(&newLeague);
                break;
            case 4:
                addArena(&newLeague);
                break;
            case 5:
                addEvent(&newLeague);
                break;
            case 6:
                printRanking(newLeague.FighterMan);
                break;
            case 7:
                printLeague(&newLeague);
                break;
            case 8:
                sortEvents(&newLeague);
                break;
            case 9:
                FindEvent(&newLeague);
                break;
            case 10:
                selectWinner(&newLeague);
                break;
            default:
                if (input == -1) {
                    break;
                }
                WRONG_INDEX
                break;
        }
    } while (input != -1);
    if (!saveLeagueToFile(&newLeague))
        printf("Error in saving file\n");
    if (!saveLeagueToBin(&newLeague))
        printf("Error in saving bin file");
    freeLeague(&newLeague);
}
