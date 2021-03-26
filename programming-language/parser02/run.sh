if [ "$EUID" -ne 0 ]
  then echo "run as root"
  exit
fi

PROGRAM="parser"
PROGRAM_IMAGE="$PROGRAM-img"

sudo systemctl start docker
sudo docker build -t $PROGRAM_IMAGE .
sudo docker run -it --rm --name $PROGRAM $PROGRAM_IMAGE
sudo systemctl stop docker.socket
