run: 
	gcc sudo.c -Wall -Werror -o sudo
	gcc ssh.c -Wall -Werror -o ssh
	gcc passwd.c -Wall -Werror -o passwd
su:
	gcc sudo.c -Wall -Werror -o sudo
ssh: 
	gcc ssh.c -Wall -Werror -o ssh
word:
	gcc passwd.c -Wall -Werror -o passwd
clean:
	rm -rf sudo ssh passwd
