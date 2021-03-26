# PARSER
[Github](https://github.com/csergen/SPRING-2021/tree/main/programming-language/parser02)

## Step one:
- [Install docker on Linux](https://docs.docker.com/engine/install/)

## Step two:
```console 
  $ sudo run.sh

  or

  $ sudo systemctl start docker
  $ sudo docker build -t parser-img .
  $ sudo docker run -it --rm --name parser parser-img
  $ sudo systemctl stop docker.socket
```

### State Machine Diagram:
![smd](res/sm.png)