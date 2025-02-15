// sergen cepoglu

/*******************************************************************************
PARSERIN TANIMADIGI IFADELER:
(bu ifadeler tanimlanirsa program hata verir ancak dogru bir hata olmaz
   bkz: else if ) bu ifadede program hata verir ancak '(' parantezin olmamasindan degil de
   else if ifadesinin bitisik yazilmamasindan dolayi hata verir ve program dogru cikti uretmemis olur ancak
   elseif ) yapilirsa program '(' parantezin olmamasindan dolayi hata verir ve dogru bir cikti uretmis olur.
)

0) fonksiyon tanimi, return ifadeleri, pointer, adress gibi ifadeleri taniyamiyor.
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

5) elseif  bitisik yazilmaz ise elseif i tanimaz. 
   bkz: else if (a < 10) hata uretecektir

6) if ( ' burada atama islemi yapilirsa hata verir' )
   if (a = 10) gibi

7) for (<assign>; (burada atama islemi yapilirsa hata verir); <assign>)
   for (int i = 0; ' i++ gibi veya i = 10 gibi' ; i++)

8) while (burada atama islemi yapilirsa hata verir)
   while (a++ gibi veya a=10 gibi) sadece logic ifadeleri taniyabiliyor

9) 0 ile baslayan sayilarda hata uretmiyor:
   bkz: 0100 gibi

10) commentlari tanimiyor

11) for (), for (;;), while() gibi parantezin icinin bos oldugu ifadeleri tanimiyor ( while(1) taniyor )

12) Kaynak dosyasinin ici bos olursa hata verecektir. (Segm. fau.)

13) ':' karakterini tanimiyor.

14) printf/scanf icinde %d %s %c %f gibi ifadelerin disinda %e, %f, %x, ... gibi ifadeleri
   tanimiyor.
   bkz: printf("%t") gibi

15) string icinde !, <=, if, ,, for, *, + gibi ifadeleri tanimiyor.
      sadece identifier veya number veya format ifadeleri olmak zorunda.
      "hello world 00123123" calisir ancak 
      "hello world!" calismaz.
      "hello world: " calismaz.
      "hello world = 10 " calismaz. vb.

NOT: gcc ile linux uzerinde compile edilirse (veya cmake veya docker ile) dogru calisacaktir. (windows'ta (MINGW) calismiyor, karakterler dogru calismiyor.)
   bkz: README.md

********************************************************************************/

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#error "WIN does not supported. (ABORTED)"
#elif defined(__linux__)
#define OS "LINUX"
#else
#ifndef OS
#error "OS was not recognized. (ABORTED)"
#endif
#endif

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define RESET "\x1B[0m"

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
         printf(RED "File does not exist!\n" RESET);
         exit(true);
      }
   }

   FILE *m_stream = open(m_file_path, "r");
   char *m_source = read(m_stream);

   printf("%s\n", m_source);

   char **m_lexemes = malloc(sizeof(char *) * length(m_source));
   for (int i = 0; i < length(m_source); i++)
      m_lexemes[i] = calloc(0x100, sizeof(char));

   int size;
   size = lexeme(m_source, m_lexemes);

   printf(GRN "\n\n[Out]: Voilà. The Lexeme process is successful!\n\n" RESET);
   for (int i = 0; i < size; i++)
   {
      printf(" %s ", m_lexemes[i]);
   }

   parse(size, m_lexemes);
   printf(GRN "\n\n\n[Out]: Voilà. The Parsing process is successful! An Error was not found!\n\n" RESET);

   for (int i = 0; i < size; i++)
      free(m_lexemes[i]);
   free(m_lexemes);

   free(m_source);
   close(m_stream);
}
