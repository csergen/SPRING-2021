#ifndef __PARSER_H__
#define __PARSER_H__

#include "tokenizer.h"

// GLOBAL PROPERTIES in Parser
static TOKEN s_current_token;
static char *s_current_lexeme;
static int s_current_iter;
static char **s_current_lexemes;
static int s_size;
// GLOBAL PROPERTIES in Parser

bool sentences();
bool scope();
bool program();
bool sentence();
bool assign();
bool ifstmt();
bool forstmt();
bool whilestmt();
bool expression();
bool conjuction();
bool relation();
bool addition();
bool term();
bool negation();
bool factor();
bool ttype();

void error(char *s)
{
  printf("error: %s\n", s);
  exit(true);
}

void next_token()
{
  if (s_current_iter < s_size)
  {
    s_current_lexeme = s_current_lexemes[s_current_iter];
    s_current_token = get_final_token_type(s_current_lexeme);
    s_current_iter++;
  }
  else
  {
    s_current_token = NIL;
  }
}

bool ifstmt()
{
}

bool forstmt()
{
}

bool whilestmt()
{
}

bool ttype()
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

bool factor()
{
  if (s_current_token == IDENTIFIER || s_current_token == NUMBER)
    next_token();
  else
    error("invalid factor");
}

bool negation()
{
  if (s_current_token == BANG)
    next_token();
  factor();
}

bool term()
{
  negation();

  while (s_current_token == STAR || s_current_token == SLASH)
  {
    next_token();
    negation();
  }
}

bool addition()
{
  term();

  while (s_current_token == PLUS || s_current_token == MINUS)
  {
    next_token();
    term();
  }
}

bool relation()
{
  addition();

  while (s_current_token == LESS || s_current_token == LESSEQUAL ||
         s_current_token == GREATER || s_current_token == GREATEREQUAL ||
         s_current_token == EQEQUAL || s_current_token == NOTEQUAL)
  {
    next_token();
    addition();
  }
}

bool conjuction()
{
  relation();

  while (s_current_token == AND)
  {
    next_token();
    relation();
  }
}

bool expression()
{
  conjuction();

  while (s_current_token == OR)
  {
    next_token();
    conjuction();
  }
}

bool assign()
{
  if (ttype())
    next_token();

  if (s_current_token == SEMI)
    return false;

  if (s_current_token == IDENTIFIER)
  {
    next_token();

    switch (s_current_token)
    {
    case EQUAL:
    case PLUSEQUAL:
    case MINUSEQUAL:
    case STAREQUAL:
    case SLASHEQUAL:
      next_token();
      expression();
    }
  }

  if (s_current_token == SEMI)
    next_token();
  else
    error("expected ';'");
}

bool sentences()
{
  switch (s_current_token)
  {
  case LBRACE:
    scope();
  case INT:
  case FLOAT:
  case DOUBLE:
  case CHAR:
  case VOID:
    assign();
  case IF:
    ifstmt();
  case FOR:
    forstmt();
  case WHILE:
    whilestmt();
  }
}

bool scope()
{
  if (s_current_token == LBRACE)
  {
    while (s_current_token != NIL && s_current_token != RBRACE) {
      next_token();
      sentences();
    }
    if (s_current_token != RBRACE)
      error("expected '}'");
  }
  else
    error("expected '{'");
}

bool program()
{
  if (s_current_token == INT || s_current_token == VOID)
    next_token();

  if (s_current_token == IDENTIFIER && strcmp(s_current_lexeme, "main") == 0)
  {
    next_token();

    if (s_current_token == LPAR)
    {
      next_token();
      if (s_current_token == RPAR)
      {
        next_token();
        scope();
      }
      else
        error("expected ')'");
    }
    else
      error("expected '('");
  }
  else
    error("undefined reference to 'main'");

  return false;
}

void parse(int size, char **lexemes)
{
  s_current_lexemes = lexemes;
  s_current_iter = 0;
  s_size = size;

  next_token();
  program();
}

#endif