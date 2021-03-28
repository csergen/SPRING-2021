#!/bin/bash

if [ "$EUID " -ne 0 ]
  then echo "run as root :)"
  exit
fi

DockerContainer="parser"
DockerImage="$DockerContainer-img"
DockerStatus=`sudo systemctl is-active docker`
DockerBuildArgs="--no-cache -t $DockerImage ."
DockerRunArgs="-it --rm --name $DockerContainer $DockerImage"

$sudo systemctl start docker

$sudo docker build $DockerBuildArgs
$sudo docker run $DockerRunArgs
$sudo systemctl stop docker.socket