#pragma once
#ifndef __ALFRED_H__
#define __ALFRED_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/************************* FILE *************************/
FILE *alfred_open(const char *const, const char *const);
bool alfred_close(FILE *const);
bool alfred_write(FILE *const, const char *const);
char *alfred_read(FILE *const);

/************************* STRING *************************/
typedef enum _char_type
{
   DIGIT,
   LETTER,
   OTHER
} CHR_TYPE;

int alfred_length(const char *);
void alfred_fit(char *);
void alfred_reverse(char *);
CHR_TYPE alfred_type(char);
void alfred_append(char *, char);

/************************* TOKENIZER *************************/
typedef enum _token_name
{
   NUMBER,
   IDENTIFIER,
   LPAR,
   RPAR,
   LSQB,
   RSQB,
   COLON,
   COMMA,
   SEMI,
   PLUS,
   MINUS,
   STAR,
   SLASH,
   BSLASH,
   AMPER,
   LESS,
   GREATER,
   EQUAL,
   DOT,
   PERCENT,
   LBRACE,
   RBRACE,
   PIPE,
   QUOTE,
   DQUOTE,
   NIL
} TOKEN;

void alfred_lexeme(char *);

/************************* INPUT/OUTPUT *************************/
FILE *alfred_open(const char *const file_path_,
                  const char *const file_mode_)
{
   return fopen(file_path_, file_mode_);
}

bool alfred_close(FILE *const stream_)
{
   bool status = true;

   if (stream_ != NULL)
      status = (fclose(stream_) == 0) ? true : false;
   else
      printf("File is already closed\n");

   return status;
}

bool alfred_write(FILE *const stream_, const char *const text_)
{
   if (stream_ == NULL)
   {
      printf("File is not opened\n");
      return false;
   }

   fprintf(stream_, "%s", text_);

   return true;
}

char *alfred_read(FILE *const stream_)
{
   char *m_destination = malloc(sizeof(char) * 1e6);
   char m_line;
   int m_line_counter = 0;

   while ((m_line = fgetc(stream_)) != EOF)
      m_destination[m_line_counter++] = m_line;

   if (strlen(m_destination) == 0)
   {
      free(m_destination);
      return 0;
   }

   return m_destination;
}
/************************* INPUT/OUTPUT *************************/

/************************* STRING *************************/
int alfred_length(const char *string_)
{
   return (int)strlen(string_);
}

void alfred_fit(char *string_)
{
   char *m_fitted_string = string_;

   do
   {
      while ((*m_fitted_string == '\n') ||
             (*m_fitted_string == '\r'))
         m_fitted_string++;
   } while ((*string_++ = *m_fitted_string++));
}

void alfred_reverse(char *string_)
{
   char *m_reversed_string = malloc(sizeof(string_) + 1);

   size_t i = 0;
   for (int m_i = strlen(string_) - 1; m_i >= 0; m_i--)
      m_reversed_string[i++] = string_[m_i];

   memcpy(string_, m_reversed_string, strlen(m_reversed_string) + 1);
   free(m_reversed_string);
}

CHR_TYPE alfred_type(char char_)
{
   if (isalpha(char_) != 0 || char_ == '_')
      return LETTER;
   else if (isdigit(char_) != 0)
      return DIGIT;
   else
      return OTHER;
}

void alfred_append(char *string_, char char_)
{
   char *m_temp_string = malloc(sizeof(string_) * sizeof(char_) + 1);

   strcpy(m_temp_string, string_);
   strcat(m_temp_string, &char_);
   memcpy(string_, m_temp_string,
          alfred_length(m_temp_string) + alfred_length(string_) + 1);

   free(m_temp_string);
}
/************************* STRING *************************/

/************************* TOKENIZER *************************/
static TOKEN alfred_get_token_type(char char_)
{
   CHR_TYPE m_char_type = alfred_type(char_);
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
      case ':':
         return COLON;
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

static void s_alfred_getchar(char *string_, int *iter_, char *current_char_, TOKEN *token_type_)
{
   *current_char_ = string_[(*iter_)++];
   *token_type_ = alfred_get_token_type(*current_char_);
}

static void s_alfred_addchar(char *lexeme_, char *m_current_char)
{
   alfred_append(lexeme_, *m_current_char);
}

void alfred_lexeme(char *string_)
{
   char *m_lexeme = malloc(sizeof(char) * 0x90);
   char m_current_char;
   TOKEN m_token_type;

   int m_iterator = 0;

   s_alfred_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
   while (m_iterator <= alfred_length(string_))
   {
      switch (m_token_type)
      {
      case IDENTIFIER:
         s_alfred_addchar(m_lexeme, &m_current_char);
         s_alfred_getchar(string_, &m_iterator, &m_current_char, &m_token_type);

         while (m_token_type == IDENTIFIER || m_token_type == NUMBER)
         {
            s_alfred_addchar(m_lexeme, &m_current_char);
            s_alfred_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
         }
         break;
      case NUMBER:
         s_alfred_addchar(m_lexeme, &m_current_char);
         s_alfred_getchar(string_, &m_iterator, &m_current_char, &m_token_type);

         while (m_token_type == NUMBER)
         {
            s_alfred_addchar(m_lexeme, &m_current_char);
            s_alfred_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
         }
         break;
      case LPAR:
      case RPAR:
      case LSQB:
      case RSQB:
      case COLON:
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
         s_alfred_addchar(m_lexeme, &m_current_char);
         TOKEN temp_type = m_token_type;
         s_alfred_getchar(string_, &m_iterator, &m_current_char, &m_token_type);

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
               s_alfred_addchar(m_lexeme, &m_current_char);
               s_alfred_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
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
               s_alfred_addchar(m_lexeme, &m_current_char);
               s_alfred_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
            }
            break;
         case BSLASH:
            switch (m_current_char)
            {
            case 'n':
            case 't':
            case 'r':
               s_alfred_addchar(m_lexeme, &m_current_char);
               s_alfred_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
            }
            break;
         case AMPER:
            switch (m_token_type)
            {
            case AMPER:
               s_alfred_addchar(m_lexeme, &m_current_char);
               s_alfred_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
            }
            break;
            break;
         case PIPE:
            switch (m_token_type)
            {
            case PIPE:
               s_alfred_addchar(m_lexeme, &m_current_char);
               s_alfred_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
            }
            break;
         }
         break;
         break;
      }

      if (alfred_length(m_lexeme) > 0)
         printf("%s, ", m_lexeme);
      memset(m_lexeme, 0, sizeof(m_lexeme) + 1);

      if (m_token_type == NIL)
         s_alfred_getchar(string_, &m_iterator, &m_current_char, &m_token_type);
   }

   free(m_lexeme);
}
/************************* TOKENIZER *************************/

/************************* PARSER *************************/

/************************* PARSER *************************/

#endif // __ALFRED_H_
