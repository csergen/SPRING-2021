#ifndef __FILEOPR_H__
#define __FILEOPR_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

FILE *open(const char *const file_path_,
      const char *const file_mode_)
{
   return fopen(file_path_, file_mode_);
}

bool close(FILE *const stream_)
{
   bool status = true;

   if (stream_ != NULL)
      status = (fclose(stream_) == 0) ? true : false;
   else
      printf("File is already closed\n");

   return status;
}

bool write(FILE *const stream_, const char *const text_)
{
   if (stream_ == NULL)
   {
      printf("File is not opened\n");
      return false;
   }

   fprintf(stream_, "%s", text_);

   return true;
}

char *read(FILE *const stream_)
{
   char *m_destination = malloc(sizeof(char)*0xF4240); // max 1 Mb
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

#endif