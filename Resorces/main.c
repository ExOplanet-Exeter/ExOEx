#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 512

int main(int argc, char *argv[]){

  // Create string for path and copy PWD to it.
  char path[MAX_PATH_LENGTH];
  strcpy(path,getenv("PWD"));
  int pathLength;

  // Remove anything past /ExOEx/
  for(int i=0; i<MAX_PATH_LENGTH; i++){
    if((path[i-4] == 'E') && (path[i-3] == 'x') && (path[i-2] == 'O') && (path[i-1] == 'E') && (path[i] = 'x')){
      pathLength = i+2;
      break;
    }    
  }
  
  
  // Open file and print path directory of ExOEx into it.
  FILE *file = fopen("path.txt","w");
  
  if (file == NULL){
    printf("ERROR! Could not open path.txt.\n");
    exit(1);
  }
  
  for(int j=0; j<pathLength; j++){
    fprintf(file,"%c",path[j]);
  }
  
  fclose(file);
  
  return 0;
}
