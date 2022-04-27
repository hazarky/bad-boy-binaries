#include <pwd.h>
#include <stdio.h>


int main () {
    struct passwd *p = getpwuid(getuid()); 
    printf("The user name is %s", p->pw_name);
    return 0;
}