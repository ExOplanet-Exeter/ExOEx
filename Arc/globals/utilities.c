/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
			| |_ ___ _ __ ___  _ __ | | __ _| |_ ___   ___ 
			| __/ _ \ '_ ` _ \| '_ \| |/ _` | __/ _ \ / __|
			| ||  __/ | | | | | |_) | | (_| | ||  __/| (__ 
			 \__\___|_| |_| |_| .__/|_|\__,_|\__\___(_)___|
									|_|           
├──────────────────────────────────────────────────────────────┤
	Short description of script in here.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── INCLUDES ─────────────────────────────────────────────────┤
#include "global.h"


//─── COMPLETED FUNCTIONS ─────────────────────────────────────┤
// Prints the title of ExOEx to the terminal.
void printTitle(){
	
	printf(ARED
	"\n╦═════════════════════════════════════╦═════════════════"
		"═══════╦\n" AYELLOW
	    "║oooooooooooo               .oooooo.  ║oooooooooooo       "
	    "     ║ \n" AGREEN
		"║`888'     `8              d8P'  `Y8b ║`888'     `8       "
		"     ║ \n" ACYAN
		"║ 888         oooo    ooo 888      888║ 888         oooo  "
		"  ooo║ \n" ABLUE
		"║ 888oooo8     `88b..8P'  888      888║ 888oooo8     `88b."
		".8P' ║ \n" AMAGENTA
		"║ 888    \"       Y888'    888      888║ 888    \"       Y"
		"888'   ║\n" ARED
		"║ 888       o  .o8\"'88b   `88b    d88'║ 888       o  .o8"
		"\"'88b  ║\n" AYELLOW
		"║o888ooooood8 o88'   888o  `Y8bood8P' ║o888ooooood8 o88'  "
		" 888o║\n" AGREEN
		"╩═════════════════════════════════════╩═══════════════════"
		"═════╩\n\n"
	ARESET);
	
	return;
}

// Informs user code section has started.
void printStart(char *word){
	
	printf(ACYAN);
	printf(word);
	printf(" running:\n" ARESET);
	
	return;
}

// Informs user code section has finished.
void printEnd(char *word){
	
	printf(AGREEN);
	printf(word);
	printf(" complete.\n" ARESET);
	
	return;
}