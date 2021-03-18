FROM fedora
RUN dnf update -y
RUN dnf install -y gcc
RUN dnf install -y make
RUN dnf install -y valgrind

COPY . /usr/src/app
WORKDIR /usr/src/app

CMD ["make"]
