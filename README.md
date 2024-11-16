League Management Project

Description

The League Management Project is a C-based application designed to manage and simulate the operations of a league, including arenas, fighters, referees, and events. It includes functionalities such as event scheduling, ranking fighters, and organizing fights, providing an efficient system for managing league operations.

Features

	•	Arena Management: Handles creation, updates, and scheduling of arenas for league events.
	•	Fighter Management: Includes functionality to manage fighter details such as rank, wins, and losses.
	•	Referee Management: Manages referees and assigns them to fights.
	•	Event Scheduling: Creates and manages league events and fights.
	•	Ranking System: Updates rankings based on fight results.

Project Structure

The project consists of the following main components:

Source Code Files

	•	Core Modules:
	•	Arena.c/h: Manages arenas for the league.
	•	Fighter.c/h: Handles fighter details and functionalities.
	•	Referee.c/h: Manages referee details and assignments.
	•	Event.c/h: Manages league events and fights.
	•	League.c/h: Main league management system.
	•	Utility Modules:
	•	Date.c/h: Provides date utilities for scheduling.
	•	Rank.c/h: Implements ranking systems for fighters.
	•	list.c/h: Provides linked list functionalities for dynamic data management.
	•	General.c/h: Contains general utility functions.
	•	Manager Modules:
	•	FighterManger.c/h: Handles bulk fighter operations.
	•	RefereeManger.c/h: Manages referees and their roles in the league.
	•	Main Program:
	•	main.c: Entry point of the application.

Data Files

	•	League.bin: Binary data file used for persistent storage of league data.
	•	League.txt: Text-based storage or configuration file for the league.

Headers and Definitions

	•	def.h: Contains macros and definitions used across the project.

How to Compile and Run

Requirements

	•	A C compiler (e.g., GCC)
	•	A terminal or IDE for building and running the project

Compilation

Run the following command in the project directory:

gcc -o league_manager main.c Arena.c Date.c Event.c Fight.c Fighter.c FighterManger.c General.c Rank.c Referee.c RefereeManger.c list.c League.c -I.

Execution

Run the compiled program:

./league_manager

File Overview

Here’s a brief overview of the key files:
	•	main.c: Contains the main logic and controls the flow of the application.
	•	League.c/h: Core module that integrates various components like arenas, events, and fighters.
	•	Fighter.c/h, Referee.c/h, Arena.c/h: Implement individual management for fighters, referees, and arenas.
	•	list.c/h: Provides linked list-based data structures for flexible data storage.

Future Enhancements

	•	Add a GUI to improve user interaction.
	•	Expand the ranking algorithm to consider additional metrics.
	•	Enhance error handling and input validation.
