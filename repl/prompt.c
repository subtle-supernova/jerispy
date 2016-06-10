#include <stdio.h>

//user input buf
static char input[2048];

int main(int argc, char** argv) {
  puts("Jerispy Version 0.0.1");
  puts("Press Ctrl+c to exit\n");

  //Loop for all time
  while(1) {
    fputs("jerispy> ", stdout); //didn't know stdout was a symbol
    fgets(input, 2048, stdin);
    printf("Snark snark: %s Don't need dat snark\n", input);
  }

  return 0;
}
