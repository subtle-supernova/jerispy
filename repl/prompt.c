#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
//leave me and my unix beard alone

char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

void add_history(char* unused) {}
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char** argv) {
  puts("Jerispy Version 0.0.1");
  puts("Press Ctrl+c to exit\n");

  //Loop for all time
  while(1) {
    //fputs("jerispy> ", stdout); //didn't know stdout was a symbol
    //readline prompt
    char* input = readline("jerispy> ");
    //add to readline's history
    add_history(input);
    //fgets(input, 2048, stdin);
    printf("Snark snark: %s Don't need dat snark\n", input);
    //Oh snap. I guess this is why we threw in stdlib.
    free(input);
  }

  return 0;
}
