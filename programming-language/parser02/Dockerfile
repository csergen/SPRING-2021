FROM gcc

COPY . /usr/src/parser
WORKDIR ./usr/src/parser

RUN gcc -o parser parser.c

CMD ["./parser", "test/general.test"]