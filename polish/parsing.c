#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"


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
  //MPC
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Jerispy = mpc_new("jerispy");

  mpca_lang(MPCA_LANG_DEFAULT,
        "number : /-?[0-9]+/ ; \
        operator : '+' | '-' | '*' | '/' ; \
        expr : <number> | '(' <operator> <expr>+ ')' ; \
        jerispy : /^/ <operator> <expr>+ /$/ ; \
      ",
      Number, Operator, Expr, Jerispy);
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
    //printf("Snark snark: %s Don't need dat snark\n", input);
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Jerispy, &r)) {
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
    //Oh snap. I guess this is why we threw in stdlib.
    free(input);
  }

  //MPC cleanup
  mpc_cleanup(4, Number, Operator, Expr, Jerispy);
  return 0;
}
