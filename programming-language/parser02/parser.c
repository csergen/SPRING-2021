// sergen cepoglu
// 02190201200
// info.sergencepoglu@gmail.com | 02190201200@ogr.inonu.edu.tr

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "fileopr.h"
#include "stropr.h"
#include "tokenizer.h"
#include "parser.h"

int main(int argc, char **argv)
{
   char *m_file_path = malloc(sizeof(char) + 1);

   if (argc > 1)
      m_file_path = argv[1];
   else
   {
      printf("Enter file path: ");
      scanf("%s", m_file_path);

      if (strlen(m_file_path) <= 0)
      {
         free(m_file_path);
         printf("File path does not exist!\n");
         exit(true);
      }
   }

   FILE *m_stream = open(m_file_path, "r");
   char *m_source = read(m_stream);

   fit(m_source);

   char **m_lexemes = malloc(sizeof(char*) * length(m_source));
   for (int i = 0; i < length(m_source); i++)
      m_lexemes[i] = calloc(0x100, sizeof(char));

   int size;
   parse((size=lexeme(m_source, m_lexemes)), m_lexemes);

   for (int i = 0; i < size; i++)
      free(m_lexemes[i]);
   free(m_lexemes);

   free(m_source);
   close(m_stream);
}
