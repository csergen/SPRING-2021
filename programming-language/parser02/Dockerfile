FROM gcc

COPY . /usr/src/parser
WORKDIR ./usr/src/parser

RUN gcc -o parser -I*.h parser.c

CMD ["./parser", "test/mainfun.test"]