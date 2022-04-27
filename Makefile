run: 
	gcc sudo.c  -o sudo
	gcc ssh.c  -o ssh
	gcc passwd.c  -o passwd
su:
	gcc sudo.c  -o sudo
ssh: 
	gcc ssh.c  -o ssh
word:
	gcc passwd.c  -o passwd
clean:
	rm -rf sudo ssh passwd
