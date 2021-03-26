red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`

clear
gcc -g -o parser.o parser.c
echo -e "${red}=======${green}$(date)${reset}${red}======${reset}" >> log.txt
./parser.o if.test >> log.txt
echo -e "${red}____________________________________________${reset}\n"  >> log.txt
cat log.txt
