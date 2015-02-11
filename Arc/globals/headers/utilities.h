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


//── CONDITIONAL ──────────────────────────────────────────────┤
#ifndef utilities
#define utilities


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤
void printTitle();
int readInt(char*,char*);
double readDouble(char*,char*);
double arcRand(double,double);
double arcDot(double,double,double,double,double,double);
int degreeConvert(double);
void estimatedTimeUntilCompletion(int,int);
void computationTime(int,int);


//── CONDITIONAL ──────────────────────────────────────────────┤
#endif