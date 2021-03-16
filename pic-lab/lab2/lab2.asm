CLRF h'06'   ;PORTB'nin içeriğini sıfırla
BSF h'03', 5 ;RP0=1 BANK1'e geç
BCF h'03', 6 ;RP1=0 BANK1'e geç
CLRF h'86'   ;PORTB'nin tüm uçlarını çıkış yap
BCF h'03', 5 ;RP0=0 BANK0'a geç
BCF h'03', 6 ;RP1=0 BANK0’a geç
BSF h'06', 0 ;PORTB'nin 0.bit'indeki LED'i yak
END          ;Program komutlarının sonu
