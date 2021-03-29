FROM gcc

RUN apt-get update && apt-get install -y cmake

COPY . /usr/src/parser
RUN mkdir "mkdir cmake-build-debug"
WORKDIR ./usr/src/parser/cmake-build-debug
RUN cmake ..
RUN make

CMD ["./Parser", "../test/general.test"]
