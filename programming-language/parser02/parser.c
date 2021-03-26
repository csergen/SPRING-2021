// sergen cepoglu
// 02190201200
// info.sergencepoglu@gmail.com | 02190201200@ogr.inonu.edu.tr

/*******************************************************************************
PARSERIN TANIMADIGI IFADELER:
(bu ifadeler tanimlanirsa program hata verir ancak dogru bir hata olmaz
   bkz: else if ) bu ifadede program hata verir ancak '(' parantezin olmamasindan degil
   else if ifadesinin bitisik yazilmamasindan dolayi hata verir ve program dogru cikti uretmemis olur ancak,
   elseif ) yapilirsa program '(' parantezin olmamasindan dolayi hata verir ve dogru bir cikti uretmis oluruz.
)

0) fonksiyon tanimi, return ifadeleri, pointer, adres gibi ifadeleri taniyamiyor.
   bkz: a(), return 0;, char *string;, &varaddr gibi

1) noktali sayilari taniyamiyor
   10.0 gibi;

2) declarationda virgul ile ayrilan tanimlamalar:
   bkz: int a, b, c; 
   bkz: int a = 10, b = 10; gibi ifadeleri taniyamiyor.

3) %= tanimiyor.

4) atama isleminde esittirden sonra parantez icine alinan ifadeleri taniyamiyor;
   bkz: a = (a + b) * 10 gibi.
   bkz: if ( (a > 10) && (a < 10) ) gibi.

4) main, if, elseif, else, for, while gibi ifadelerden sonra mutlaka
'{ }' ler gelmelidir yoksa hata verir.
   bkz: if (a > 10)
         a = 0; hatali cikti uretir { } olmak zorundadir.

5) elseif  bitisik yazilmaz ise hata verir.(bkz: else if hata uretecektir)

6) if (burada atama islemi yapilirsa hata verir)
   if (a = 10 gibi)

7) for (<assign>; (burada atama islemi yapilirsa hata verir); <assign>)
   for (int i = 0; i++ gibi veya i = 10 gibi; i++)

8) while (burada atama islemi yapilirsa hata verir)
   while (a++ gibi veya a=10 gibi. sadece logic ifadeleri taniyabiliyor)

9) 0 ile baslayan sayilarda hata uretmiyor:
   bkz: 0100 gibi

10) commentlari tanimiyor


NOT: gcc ile linux uzerinde compile edilirse sorunsuz calisacaktir. windowsda calismiyor.
NOT: kaynak dosyasinin ici bos olursa hata verecektir.
********************************************************************************/

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
   #error "WIN does not supported. (ABORTED)"
#elif defined(__linux__)
   #define OS "LINUX"
#else
   #ifndef OS
      #define NULL
      #pragma message "OS was not recognized"
   #endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

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
   size=lexeme(m_source, m_lexemes);
   parse(size, m_lexemes);

   for (int i = 0; i < size; i++)
      free(m_lexemes[i]);
   free(m_lexemes);

   free(m_source);
   close(m_stream);
}
