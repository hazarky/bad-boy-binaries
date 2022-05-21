#!/bin/bash

printf "************\nCleaning Up the Binaries\n************\n"

/usr/bin/sudo update-alternatives --remove-all ssh
/usr/bin/sudo update-alternatives --remove-all sudo
/usr/bin/sudo update-alternatives --remove-all passwd
/usr/bin/sudo update-alternatives --remove-all rm