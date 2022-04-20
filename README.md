# bad-boy-binaries
Malicious C binaries that are immitations of popular binaries
![main image](img/binaries.gif)

## Repository structure Structure
- ssh.c
- sudo.c 
- passwd.c
- junkmybinary.sh
### ssh.c 
This is binary that impersonates the Secure Shell binary on a linux system. The script sends the password information that was input by the victim to a target harvesting server.
To specifically compile ssh
```
make ssh
```
### sudo.c 
This is a binary that impersonates the sudo binary on a linux system. the script sends the password information that was given by the victim to a target harvesting server.
To specifically compile sudo
```
make sudo
```
### passwd.c
This is a binary that impersonates the passwd binary on a linux system. the script sends the password information that given by the victim to a target harvesting server.
To specifically compile passwd
```
make passwd
```

### junkmybinary.sh
This is based on a basic ofuscation technique where you append characters at the end of a binary. This makes it a little more difficult for basic reverse engineering techniques.
To run the script
```
  ./junkmybinary.sh [malicious-binary] [text-file-to-append]
```
