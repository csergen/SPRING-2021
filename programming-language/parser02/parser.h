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
<relation>: <addition> { ( < | <= | > | >= | == | != ) <addition> }

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

<stringstmt>: " { <factor> }"

<iostmt>: printf | scanf ([<stringstmt> {, <id> }]);
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

static void sentences();
static void scope();
static void program();
static void assign();
static void ifstmt();
static void forstmt();
static void stringstmt();
static void iostmt();
static void whilestmt();
static void expression();
static void conjuction();
static void relation();
static void addition();
static void term();
static void negation();
static void factor();
static bool ttype();
static void parse();


void error(char *s)
{
  printf(RED"\n\nout: oops, something went wrong 🤔 %s ~~~%s\n%s\n^\n\n" RESET, s, s_current_lexeme, s_current_lexeme);
  exit(true);
}

static void 
next_token()
{
  if (s_current_iter < s_size)
  {
    s_current_lexeme = s_current_lexemes[s_current_iter];
    if (length(s_current_lexeme) == 1) {
      s_current_token = get_token_type(*s_current_lexeme);
    } else
      s_current_token = get_string_token_type(s_current_lexeme);
    s_current_iter++;
  }
  else
  {
    s_current_token = NIL;
    s_current_lexeme = NULL;
  }
}

/* 
  <stringstmt>: " { <factor> | <format> }"
*/
static void
stringstmt()
{
  if (s_current_token == DQUOTE)
  {
    next_token();
    while (s_current_token != DQUOTE) {
      if (s_current_token == DQUOTE)
        break;
      factor();
    }
    next_token();
  }
}


/* 
  <iostmt>: printf (<stringstmt> {, <id> });
*/
static void
iostmt()
{
  if (s_current_token == PRINTF || s_current_token == SCANF) 
  {
    next_token();
    if (s_current_token == LPAR)
    {
      next_token();
      stringstmt();

      while (s_current_token == COMMA) {
        next_token();
        factor();
      }

      if (s_current_token != RPAR)
        error("expected ')'");
      next_token();
    }
  }
}

/* <ifstmt>: if ({ <expression> }) <scope>
          { elseif ( { <expression> } ) <scope> }
          [ else <scope> ] */
static void 
ifstmt()
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

/* <forstmt>: for ([<assign>]; [<expression>]; [<assign>]) <scope> */
static void 
forstmt()
{     assign();

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

/* <whilestmt>: while ( [<expression>] ) <scope> */
static void
whilestmt()
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

/* <type>: int | float | double | char | void */
static bool
ttype()
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

/* <factor>: <id> | <number> | <quote> | <dquote> */
static void
factor()
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
  } else if (s_current_token == FORMATINT || s_current_token == FORMATCHAR || s_current_token == FORMATFLOAT || s_current_token == FORMATSTRING) {
      next_token();
  }
  else
    error("invalid factor");
}

/* {* !a | !0 *}
   <negation>: ! <factor> */
static void 
negation()
{
  if (s_current_token == BANG)
    next_token();
  if (s_current_token == MINUS)
    next_token();
  factor();
}

/* {* <negation> * <negation> / <negation> .... *}
   <term>: <negation> { (* | /) <negation> } */
static void
term()
{
  negation();

  while (s_current_token == STAR || s_current_token == SLASH || s_current_token == PERCENT)
  {
    next_token();
    negation();
  }
}

/* {* <term> + <term> - <term> ..... *}
   <addition>: <term> { (+ | -) <term> } */
static void 
addition()
{
  term();

  while (s_current_token == PLUS || s_current_token == MINUS)
  {
    next_token();
    term();
  }
}

/* {* <addition> < <addition> <= <addition> > <addition> >= <addition> == <addition> != <addition>  .... *}
   <relation>: <addition> { ( < | <= | > | >= | == | != ) <addition> } */
static void 
relation()
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

/* {* <relation> && <relation> && <relation> && ... *}
   <conj>: <relation> { && <relation> } */
static void 
conjuction()
{
  relation();

  while (s_current_token == AND)
  {
    next_token();
    relation();
  }
}

/* 
  {* <conj> || <conj> || <conj> || ... *}
  <expression>: <conj> { || <conj> } */
static void 
expression()
{
  conjuction();

  while (s_current_token == OR)
  {
    next_token();
    conjuction();
  }
}

/* <assign>: [<type>] <id> ( = | += | -= | *= | /= ) <expression> */
static void 
assign()
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

/* <sentences>: { <sentence> } 

<sentence>: 
  <scope>       |
  <assign>      |
  <ifstmt>      |
  <forstmt>     |
  <whilestmt>   |
*/
static void 
sentences()
{
  while (s_current_token != RBRACE && s_current_token != NIL)
  {
    switch (s_current_token)
    {
    case LPAR:
    case RPAR:
      error("unexpected character");
      break;
    case SEMI:
      next_token();
      break;
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
      if (s_current_token == SEMI)
        error("unexpected character");
      break;
    case NUMBER:
      next_token();
      if (s_current_token != SEMI)
        error("expected ';'");
      break;
    case IF:
      ifstmt();
      break;
    case ELSEIF:
    case ELSE:
      error("unexpected definition");
    case FOR:
      forstmt();
      break;
    case WHILE:
      whilestmt();
      break;
    case PRINTF:
    case SCANF:
      iostmt();
      if (s_current_token != SEMI) 
        error("expected ';'");
      next_token();
      break;
    }
  }
}

/* <scope>: '{' <sentences> '}' */
static void 
scope()
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

/* <program>: [int | void] main () <scope> */
static void 
program()
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

static void 
parse(int size, char **lexemes)
{
  s_current_lexemes = lexemes;
  s_current_iter = 0;
  s_size = size;

  next_token();
  program();

  free(s_current_lexeme);
}

#endif
