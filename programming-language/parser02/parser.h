/* GRAMMAR
<program>: [int | void] main () <scope>

<sentences>: { <sentence> }

<sentence>: 
  <scope>       |
  <assign>      |
  <ifstmt>      |
  <forstmt>     |
  <whilestmt>   |

<type>:
  int | float | double | char | void

<id>: _a-Z
<number>: 0-9

<scope>: '{' <sentences> '}'

<assign>:
  [<type>] <id> ( = | += | -= | *= | /= ) <expression>

{* <conj> || <conj> || <conj> || ... *}
<expression>: <conj> { || <conj> }

{* <relation> && <relation> && <relation> && ... *}
<conj>: <relation> { && <relation> }

{* <addition> < <addition> <= <addition> > <addition> >= <addition> == <addition> != <addition>  .... *}
<relation>: <addition> { [ < | <= | > | >= | == | != ] addition}

{* <term> + <term> - <term> ..... *}
<addition>: <term> { (+ | -) <term> }

{* <negation> * <negation> / <negation> .... *}
<term>: <negation> { (* | /) <negation> }

{* !a | !0 *}
<negation>: ! <factor>

<factor>: <id> | <number> | <quote> | <dquote> 

<ifstmt>: if ({ <expression> }) <scope>
          { elseif ( { <expression> } ) <scope> }
          [ else <scope> ]

<forstmt>: for ([<assign>]; [<expression>]; [<assign>]) <scope>

<whilestmt>: while ( [<expression>] ) <scope>
*/

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

void sentences();
void scope();
void program();
void sentence();
void assign();
void ifstmt();
void forstmt();
void whilestmt();
void expression();
void conjuction();
void relation();
void addition();
void term();
void negation();
void factor();
bool ttype();

void error(char *s)
{
  printf("error: %s ....%s\n%s\n^\n", s, s_current_lexeme, s_current_lexeme);
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
    memset(s_current_lexeme, 0, sizeof(s_current_lexeme) + 1);
    s_current_lexeme = NULL;
  }
}

void ifstmt()
{
  if (s_current_token == IF)
  {
    next_token();
    if (s_current_token == LPAR)
    {
      next_token();
      expression();

      if (s_current_token != RPAR)
        error("expected ')'");
      next_token();
      scope();
    }
  }

  if (s_current_token == ELSEIF)
  {
    next_token();
    if (s_current_token == LPAR)
    {
      next_token();
      expression();

      if (s_current_token != RPAR)
        error("expected ')'");
      next_token();
      scope();
      ifstmt();
    }
  }

  if (s_current_token == ELSE)
  {
    next_token();
    scope();

    if (s_current_token == ELSE)
      error("unexpected definition");
  }
}

void forstmt()
{
  if (s_current_token == FOR)
  {
    next_token();

    if (s_current_token == LPAR)
    {
      next_token();
      assign();
      if (s_current_token == SEMI)
      {
        next_token();
        expression();
        if (s_current_token == SEMI)
        {
          next_token();
          assign();

          if (s_current_token == RPAR) {
            next_token();
            scope();
          } else
              error("expected ')'");
        } else
            error("expected ';'");
      } else
          error("expected ';'");
    } else
        error("expected '('");
  } else
    error("unexpected definition");
}

void whilestmt()
{
  if (s_current_token == WHILE) {
    next_token();
    if (s_current_token == LPAR) {
      next_token();
      expression();
      if (s_current_token == RPAR) {
        next_token();
        scope();
      }
      else
        error("expected ')'");
    } else 
        error("expected '('");
  } else
      error("unexpected definition");
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

void factor()
{
  if (s_current_token == IDENTIFIER || s_current_token == NUMBER)
    next_token();
  else if (s_current_token == QUOTE)
  {
    next_token();
    factor();

    if (s_current_token != QUOTE)
      error("missing terminating ' character");
    next_token();
  }
  else if (s_current_token == DQUOTE)
  {
    next_token();
    factor();

    if (s_current_token != DQUOTE)
      error("missing terminating \" character");
    next_token();
  }
  else
    error("invalid factor");
}

void negation()
{
  if (s_current_token == BANG)
    next_token();
  if (s_current_token == MINUS)
    next_token();
  factor();
}

void term()
{
  negation();

  while (s_current_token == STAR || s_current_token == SLASH || s_current_token == PERCENT)
  {
    next_token();
    negation();
  }
}

void addition()
{
  term();

  while (s_current_token == PLUS || s_current_token == MINUS)
  {
    next_token();
    term();
  }
}

void relation()
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

void conjuction()
{
  relation();

  while (s_current_token == AND)
  {
    next_token();
    relation();
  }
}

void expression()
{
  conjuction();

  while (s_current_token == OR)
  {
    next_token();
    conjuction();
  }
}

void assign()
{
  if (ttype())
    next_token();

  if (s_current_token == IDENTIFIER)
  {
    next_token();

    if (s_current_token == INCREASE || s_current_token == DECREASE)
      next_token();
    else
    {
      switch (s_current_token)
      {
      case EQUAL:
      case PLUSEQUAL:
      case MINUSEQUAL:
      case STAREQUAL:
      case SLASHEQUAL:
      case PERCENTEQUAL:
        next_token();
        expression();
        break;
      }
    }
  }
}

void sentences()
{
  while (s_current_token != RBRACE && s_current_token != NIL)
  {
    switch (s_current_token)
    {
    case LBRACE:
      scope();
      break;
    case INT:
    case FLOAT:
    case DOUBLE:
    case CHAR:
    case VOID:
    case QUOTE:
    case DQUOTE:
    case IDENTIFIER:
      assign();
      if (s_current_token != SEMI)
        error("expected ';'");
      next_token();
      break;
    case IF:
      ifstmt();
      break;
    case FOR:
      forstmt();
      break;
    case WHILE:
      whilestmt();
      break;
    case PRINTF:
      break;
    case SCANF:
      break;
    }
  }
}

void scope()
{
  if (s_current_token == LBRACE)
  {
    next_token();
    sentences();
    if (s_current_token != RBRACE)
      error("expected '}'");
    next_token();
  }
  else
    error("expected '{'");
}

void program()
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

        if (s_current_token != NIL)
        {
          error("out of scope");
        }
      }
      else
        error("expected ')'");
    }
    else
      error("expected '('");
  }
  else
    error("undefined reference to 'main'");
}

void parse(int size, char **lexemes)
{
  s_current_lexemes = lexemes;
  s_current_iter = 0;
  s_size = size;

  next_token();
  program();

  free(s_current_lexeme);
}

#endif