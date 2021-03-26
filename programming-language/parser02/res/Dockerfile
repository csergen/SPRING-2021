FROM ubuntu
RUN apt-get update -y
RUN apt-get install -y gcc

COPY . /usr/src/app
WORKDIR /usr/src/app

CMD ["gcc", "parser.c"]
CMD ["/bin/bash", "run.sh"]
