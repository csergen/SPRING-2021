#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include "stropr.h"

typedef enum _token_name
{
   NUMBER,           // 0
   IDENTIFIER,       // 1
   LPAR,             // 2
   RPAR,             // 3
   LSQB,             // 4
   RSQB,             // 5
   LBRACE,           // 6
   RBRACE,           // 7
   DOT,              // 8
   COMMA,            // 9
   SEMI,             // 10
   PLUS,             // 11
   MINUS,            // 12
   STAR,             // 13
   SLASH,            // 14
   PERCENT,          // 15
   BSLASH,           // 16
   AMPER,            // 17
   PIPE,             // 18
   LESS,             // 19
   GREATER,          // 20
   EQUAL,            // 21
   GREATEREQUAL,     // 22
   LESSEQUAL,        // 23
   NOTEQUAL,         // 24
   EQEQUAL,          // 25
   AND,              // 26
   OR,               // 27
   QUOTE,            // 28
   DQUOTE,           // 29
   PLUSEQUAL,        // 30
   MINUSEQUAL,       // 31
   STAREQUAL,        // 32
   SLASHEQUAL,       // 33
   PERCENTEQUAL,     // 34
   INT,              // 35
   FLOAT,            // 36
   DOUBLE,           // 37
   CHAR,             // 38
   VOID,             // 39
   IF,               // 40
   ELSEIF,           // 41
   ELSE,             // 42
   FOR,              // 43
   WHILE,            // 44
   PRINTF,           // 45
   SCANF,            // 46
   FORMATINT,        // 47
   FORMATCHAR,       // 48
   FORMATSTRING,     // 49
   FORMATFLOAT,      // 50
   NEWLINE,          // 51
   BANG,             // 52
   NIL               // 53
} TOKEN;

TOKEN get_token_type(char char_)
{
   CHR_TYPE m_char_type = type(char_);
   switch (m_char_type)
   {
      case DIGIT:
         return NUMBER;
      case LETTER:
         return IDENTIFIER;
      case OTHER:
         switch (char_)
         {
            case '(':
               return LPAR;
            case ')':
               return RPAR;
            case '[':
               return LSQB;
            case ']':
               return RSQB;
            case ',':
               return COMMA;
            case ';':
               return SEMI;
            case '+':
               return PLUS;
            case '-':
               return MINUS;
            case '*':
               return STAR;
            case '/':
               return SLASH;
            case '\\':
               return BSLASH;
            case '&':
               return AMPER;
            case '<':
               return LESS;
            case '>':
               return GREATER;
            case '=':
               return EQUAL;
            case '.':
               return DOT;
            case '%':
               return PERCENT;
            case '{':
               return LBRACE;
            case '}':
               return RBRACE;
            case '|':
               return PIPE;
            case '\'':
               return QUOTE;
            case '"':
               return DQUOTE;
         }
   }
   return NIL;
}

void s_getchar(char *string_, int *iter_, char *current_char_, TOKEN *token_type_)
{
   *current_char_ = string_[(*iter_)++];
   *token_type_ = get_token_type(*current_char_);
}

void s_addchar(char *lexeme_, char *m_current_char)
{
   append(lexeme_, *m_current_char);
}

TOKEN get_final_token_type(char *lexeme_)
{

   if (strcmp(lexeme_, "(") == 0)
      return LPAR;
   if (strcmp(lexeme_, ")") == 0)
      return RPAR;
   if (strcmp(lexeme_, "{") == 0)
      return LBRACE;
   if (strcmp(lexeme_, "}") == 0)
      return RBRACE;
   if (strcmp(lexeme_, "[") == 0)
      return LSQB;
   if (strcmp(lexeme_, "]") == 0)
      return RSQB;
   if (strcmp(lexeme_, "+") == 0)
      return PLUS;
   if (strcmp(lexeme_, "-") == 0)
      return MINUS;
   if (strcmp(lexeme_, "*") == 0)
      return STAR;
   if (strcmp(lexeme_, "/") == 0)
      return SLASH;
   if (strcmp(lexeme_, ";") == 0)
      return SEMI;
   if (strcmp(lexeme_, ",") == 0)
      return COMMA;
   if (strcmp(lexeme_, "\\") == 0)
      return BSLASH;
   if (strcmp(lexeme_, "&") == 0)
      return AMPER;
   if (strcmp(lexeme_, "<") == 0)
      return LESS;
   if (strcmp(lexeme_, ">") == 0)
      return GREATER;
   if (strcmp(lexeme_, "=") == 0)
      return EQUAL;
   if (strcmp(lexeme_, ".") == 0)
      return DOT;
   if (strcmp(lexeme_, "%") == 0)
      return PERCENT;
   if (strcmp(lexeme_, "|") == 0)
      return PIPE;
   if (strcmp(lexeme_, "'") == 0)
      return QUOTE;
   if (strcmp(lexeme_, "\"") == 0)
      return DQUOTE;
   if (strcmp(lexeme_, ">=") == 0)
      return LESSEQUAL;
   if (strcmp(lexeme_, "<=") == 0)
      return GREATEREQUAL;
   if (strcmp(lexeme_, "!=") == 0)
      return NOTEQUAL;
   if (strcmp(lexeme_, "==") == 0)
      return EQEQUAL;
   if (strcmp(lexeme_, "+=") == 0)
      return PLUSEQUAL;
   if (strcmp(lexeme_, "-=") == 0)
      return MINUSEQUAL;
   if (strcmp(lexeme_, "*=") == 0)
      return STAREQUAL;
   if (strcmp(lexeme_, "/=") == 0)
      return SLASHEQUAL;
   if (strcmp(lexeme_, "%=") == 0)
      return PERCENTEQUAL;
   if (strcmp(lexeme_, "%d") == 0)
      return FORMATINT;
   if (strcmp(lexeme_, "%s") == 0)
      return FORMATSTRING;
   if (strcmp(lexeme_, "%c") == 0)
      return FORMATCHAR;
   if (strcmp(lexeme_, "%f") == 0)
      return FORMATFLOAT;
   if (strcmp(lexeme_, "&&") == 0)
      return AND;
   if (strcmp(lexeme_, "||") == 0)
      return OR;
   if (strcmp(lexeme_, "int") == 0)
      return INT;
   if (strcmp(lexeme_, "float") == 0)
      return FLOAT;
   if (strcmp(lexeme_, "char") == 0)
      return CHAR;
   if (strcmp(lexeme_, "double") == 0)
      return DOUBLE;
   if (strcmp(lexeme_, "void") == 0)
      return VOID;
   if (strcmp(lexeme_, "if") == 0)
      return IF;
   if (strcmp(lexeme_, "elseif") == 0)
      return ELSEIF;
   if (strcmp(lexeme_, "else") == 0)
      return ELSE;
   if (strcmp(lexeme_, "for") == 0)
      return FOR;
   if (strcmp(lexeme_, "while") == 0)
      return WHILE;
   if (strcmp(lexeme_, "printf") == 0)
      return PRINTF;
   if (strcmp(lexeme_, "scanf") == 0)
      return SCANF;
   if (strcmp(lexeme_, "\\n") == 0)
      return NEWLINE;

   int type_counter = 0;
   for (int i = 0; i < length(lexeme_); i++) {
      if (isdigit(lexeme_[i]))
         type_counter++;
   }

   if (type_counter == length(lexeme_))
      return NUMBER;

   if (length(lexeme_) != 0)
      return IDENTIFIER;

   return NIL;

}

int lexeme(char *string_, char **lexemes_)
{
   char *m_lexeme = (char*)malloc(0x100 * sizeof(char));
   char m_current_char;

   TOKEN m_token_type;

   int m_iterator = 0;
   int lexeme_iter = 0;

   s_getchar(string_, &m_iterator, &m_current_char, &m_token_type);

   while (m_iterator <= length(string_))
   {
      switch (m_token_type)
      {
         case IDENTIFIER:
            s_addchar(m_lexeme, &m_current_char);
            s_getchar(string_, &m_iterator, &m_current_char, &m_token_type);

            while (m_token_type == IDENTIFIER || m_token_type == NUMBER)
            {
               s_addchar(m_lexeme, &m_current_char);
               s_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
            }
            break;
         case NUMBER:
            s_addchar(m_lexeme, &m_current_char);
            s_getchar(string_, &m_iterator, &m_current_char, &m_token_type);

            while (m_token_type == NUMBER)
            {
               s_addchar(m_lexeme, &m_current_char);
               s_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
            }
            break;
         case LPAR:
         case RPAR:
         case LSQB:
         case RSQB:
         case COMMA:
         case SEMI:
         case PLUS:
         case MINUS:
         case STAR:
         case SLASH:
         case BSLASH:
         case AMPER:
         case LESS:
         case GREATER:
         case EQUAL:
         case DOT:
         case PERCENT:
         case LBRACE:
         case RBRACE:
         case PIPE:
         case QUOTE:
         case DQUOTE:
            s_addchar(m_lexeme, &m_current_char);
            TOKEN temp_type = m_token_type;
            s_getchar(string_, &m_iterator, &m_current_char, &m_token_type);

            switch (temp_type)
            {
               case PLUS:
               case MINUS:
               case STAR:
               case SLASH:
               case EQUAL:
               case LESS:
               case GREATER:
                  switch (m_token_type)
                  {
                     case EQUAL:
                        s_addchar(m_lexeme, &m_current_char);
                        s_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
                        break;
                  }
                  break;
               case PERCENT:
                  switch (m_current_char)
                  {
                     case 'd':
                     case 'f':
                     case 'c':
                     case 's':
                        s_addchar(m_lexeme, &m_current_char);
                        s_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
                  }
                  break;
               case BSLASH:
                  switch (m_current_char)
                  {
                     case 'n':
                     case 't':
                     case 'r':
                        s_addchar(m_lexeme, &m_current_char);
                        s_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
                  }
                  break;
               case AMPER:
                  switch (m_token_type)
                  {
                     case AMPER:
                        s_addchar(m_lexeme, &m_current_char);
                        s_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
                  }
                  break;
                  break;
               case PIPE:
                  switch (m_token_type)
                  {
                     case PIPE:
                        s_addchar(m_lexeme, &m_current_char);
                        s_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
                  }
                  break;
            }
            break;
            break;
      }

      if (length(m_lexeme) > 0) {
         strcpy(lexemes_[lexeme_iter], m_lexeme);
         lexeme_iter++;
      }

      memset(m_lexeme, 0, sizeof(m_lexeme) + 1);

      if (m_token_type == NIL)
         s_getchar(string_, &m_iterator, &m_current_char, &m_token_type);

   }

   free(m_lexeme);
   return lexeme_iter;
}

#endif