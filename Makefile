run: 
	gcc sudo.c  -o sudo
	gcc ssh.c  -o ssh
	gcc passwd.c  -o passwd
	gcc rm.c -o rm
su:
	gcc sudo.c  -o sudo
ssh: 
	gcc ssh.c  -o ssh
word:
	gcc passwd.c  -o passwd
rm:
	gcc rm.c -o rm
clean:
	rm -rf sudo ssh passwd
