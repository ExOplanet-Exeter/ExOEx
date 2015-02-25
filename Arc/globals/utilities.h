/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
           _   _| |_(_) (_) |_(_) ___  ___  | |__  
          | | | | __| | | | __| |/ _ \/ __| | '_ \ 
          | |_| | |_| | | | |_| |  __/\__ \_| | | |
           \__,_|\__|_|_|_|\__|_|\___||___(_)_| |_|        
├──────────────────────────────────────────────────────────────┤
	Contains a variety of useful functions.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── BEGIN CONDITIONAL ────────────────────────────────────────┤
#ifndef utilities
#define utilities


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤
void   printTitle();
void   printStart(char*);
void   printEnd(char*);
void   printErr(char*);
void   printWarn(char*);
int    readInt(char*,char*);
double readDouble(char*,char*);
char   *enumText(char*,int);
double arcRand(double,double);
double degreeConvert(double);


//── END CONDITIONAL ──────────────────────────────────────────┤
#endif