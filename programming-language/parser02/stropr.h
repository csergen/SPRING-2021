#ifndef __STROPR_H__
#define __STROPR_H__

#include <stdlib.h>
#include <string.h>

typedef enum _char_type
{
   DIGIT,
   LETTER,
   OTHER
} CHR_TYPE;

int length(const char *string_)
{
   return (int)strlen(string_);
}

void fit(char *string_)
{
   char *m_fitted_string = string_;

   do
   {
      while ((*m_fitted_string == '\n') ||
            (*m_fitted_string == '\r'))
         m_fitted_string++;
   } while ((*string_++ = *m_fitted_string++));
}

void reverse(char *string_)
{
   char *m_reversed_string = (char*)malloc(sizeof(string_) + 1);

   size_t i = 0;
   for (int m_i = strlen(string_) - 1; m_i >= 0; m_i--)
      m_reversed_string[i++] = string_[m_i];

   memcpy(string_, m_reversed_string, strlen(m_reversed_string) + 1);
   free(m_reversed_string);
}

CHR_TYPE type(char char_)
{
   if (isalpha(char_) != 0 || char_ == '_')
      return LETTER;
   else if (isdigit(char_) != 0)
      return DIGIT;
   else
      return OTHER;
}

void append(char *string_, char char_)
{
   char *m_temp_string = (char*)malloc(sizeof(string_) * sizeof(char_) + 1);

   strcpy(m_temp_string, string_);
   strcat(m_temp_string, &char_);
   memcpy(string_, m_temp_string,
         length(m_temp_string) + length(string_) + 1);

   free(m_temp_string);
}

#endif