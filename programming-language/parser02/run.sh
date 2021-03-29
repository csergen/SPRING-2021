#!/bin/bash

RED='\033[0;31m'
GRN='\033[1;32m'
NC='\033[0m'

if [ $1 == "d" ]
then
   if [ "$EUID " -ne 0 ]
   then 
      echo -e "${RED}[ Run as ROOT :) ]${NC}"
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
else
   BuildDir="cmake-build-debug"

   if [ ! -d $BuildDir ]
   then
      mkdir -p $BuildDir
   fi

   cp test/ -r $BuildDir
   cd $BuildDir
   cmake ..
   make

   Logs=logs
   LogTime="$(date +"%y%m%d%H%M")"
   LogDir=$Logs/log@$LogTime

   if [ ! -d $Logs ]
   then mkdir $Logs
   fi

   if [ ! -d $LogDir ]
   then mkdir $LogDir
   fi 
 
   for item in test/*
   do
      ./Parser $item > "$LogDir/$(basename $item | sed 's/\(.*\)\..*/\1/')@log"
   done

   if [ -d $LogDir ]
   then
      echo -e "${GRN}[ Parsing done. Please checkout '$BuildDir/$LogDir'${NC} ]"
   else
      echo -e "${RED}[ Oops! Something went wrong. Please checkout the 'test' file. ]${NC}"
   fi
   cd ../
fi
