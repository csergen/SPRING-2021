#ifndef __PARSER_H__
#define __PARSER_H__

#include "tokenizer.h"

// GLOBAL PROPERTIES in Parser
static TOKEN s_current_token;
static char *s_current_lexeme;
static int s_current_iter;
static char **s_current_lexemes;
// GLOBAL PROPERTIES in Parser

void next_token()
{
  s_current_lexeme = s_current_lexemes[s_current_iter];
  s_current_token = get_final_token_type(s_current_lexeme);
  s_current_iter++;
}

bool expr_type()
{
  switch (s_current_token)
  {
  case INT:
  case FLOAT:
  case DOUBLE:
  case CHAR:
  case VOID:
    return true;
  }
  return false;
}

bool expr_program_main()
{
  next_token();
  bool temp = expr_type();

  if (temp) 
    next_token();

  if (strcmp(s_current_lexeme, "main") == 0)
  {
    next_token();
    if (s_current_token == LPAR)
    {
      next_token();
      if (s_current_token == RPAR) {
        next_token();
        return true;
      }
      else
        printf("error expected ')' before '%s' token\n%s\n^\n",
              s_current_lexeme, s_current_lexeme);
    }
    else
      printf("error: expected '(...)' before '%s' token\n%s\n^\n",
            s_current_lexeme, s_current_lexeme);
  }
  else
    printf("undefined reference to 'main'\n", s_current_lexeme);

  return false;
}

bool expr_assign()
{
  printf("%s", s_current_lexeme);
  return true;
}

bool expr_if()
{

}

bool expr_for()
{

}

bool expr_while()
{

}

bool expr_sentence()
{
  next_token();

  switch (s_current_token)
  {
  case IF:
    return ( expr_if() ) ? expr_sentence() : false;
  case FOR:
    return ( expr_for() ) ? expr_sentence() : false;
  case WHILE:
    return ( expr_while() ) ? expr_sentence() : false;
  case IDENTIFIER:
  case INT:
  case FLOAT:
  case VOID:
  case CHAR:
  case DOUBLE:
    return ( expr_assign() ) ? expr_sentence() : false;
  }
}

void parse(int size, char **lexemes)
{
  s_current_lexemes = lexemes;
  s_current_iter = 0;
  bool status;
  
  status = expr_program_main();

  if (!status) {
    printf("out: program halted!\n");
    exit(true);
  } else {
    if (s_current_token == LBRACE) {
      status = expr_sentence();
      printf("%d", status);
    } else
      printf("error: lbrace");
  }
}

#endif