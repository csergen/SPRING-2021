// sergen cepoglu
// 02190201200
// info.sergencepoglu@gmail.com | 02190201200@ogr.inonu.edu.tr

/*******************************************************************************
PARSERIN TANIMADIGI IFADELER:
(bu ifadeler tanimlanirsa program hata verir ancak dogru bir hata olmaz
   bkz: else if ) bu ifadede program hata verir ancak '(' parantezin olmamasindan degil de
   else if ifadesinin bitisik yazilmamasindan dolayi hata verir ve program dogru cikti uretmemis olur ancak
   elseif ) yapilirsa program '(' parantezin olmamasindan dolayi hata verir ve dogru bir cikti uretmis olur.
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

11) for (), for (;;), while() gibi parantezin icinin bos oldugu ifadeleri tanimiyor ( while(1) taniyor )

12) Kaynak dosyasinin ici bos olursa hata verecektir. (Segm. fau.)

NOT: gcc ile linux uzerinde compile edilirse sorunsuz(60-50%) calisacaktir. (windows'ta (MINGW) calismiyor karakter hatasi veriyor.)
NOT: Programin hatasiz cikti verebilmesi icin DOCKER kullanilabilir.
   ! Dockerfile icindeki  CMD ["./parser", "KAYNAKDOSYASI"] KAYNAKDOSYASI yerine test edilecek test dosyasinin yolu
   verilebilir. (AYNI DIZINDE veya AYNI DIZIN ICINDEKI DOSYALARIN ALTINDA OLMAK SARTIYLA)

   $ sudo run.sh                                   // build and run

      or

   $ sudo systemctl start docker                   // start docker
   $ sudo docker build . -t parser-img             // build image (-t is tag)
   $ docker run -it --rm --name parser parser-img  // run docker image
   $ sudo systemctl stop docker.socket             // stop docker
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
   char *temp_source = malloc(strlen(m_source));
   strcpy(temp_source, m_source);

   fit(m_source);

   char **m_lexemes = malloc(sizeof(char*) * length(m_source));
   for (int i = 0; i < length(m_source); i++)
      m_lexemes[i] = calloc(0x100, sizeof(char));


   /* kelimelestirilmis halini gormek icin commentlari kaldiriniz.
   for (int i = 0; i < size; i++) 
      printf("%s, ", m_lexemes[i]);
   */

   printf("%s", temp_source);

   int size;
   parse(size=lexeme(m_source, m_lexemes), m_lexemes);
   printf("\nParsing Successfull!");

   for (int i = 0; i < size; i++)
      free(m_lexemes[i]);
   free(m_lexemes);

   free(temp_source);
   free(m_source);
   close(m_stream);
}
