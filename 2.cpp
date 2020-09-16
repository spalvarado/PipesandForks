#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <fstream>
#include <string>
#include <cstring>
#include <pthread.h>
#define MAX_CHAR 250
using namespace std;



int main(int argc, char *argv[]) {

	string hold;
	string output = "output";
	int fd[2], rc;
	ifstream in;
	char charray[MAX_CHAR];


	if (pipe(fd) == -1) {
		fprintf(stderr, "The Pipe Failed");
	}

	rc = fork();

	if (rc<0) {
		fprintf(stderr, "The Fork has Failed\n");
		exit(-1);
	}
	else if (rc ==0) {
		printf("Child Process pid:%d\n", (int)getpid());
		close(fd[0]);// this closes the reading end of the pipe
		in.open(argv[1]);

		while (!in.eof()) {// reading through file
			getline(in, hold);
			output = output + hold + "\n";
		}
		inputFile.close();
		strcpy(charray,output.c_str());
		write(fd[1], charray, sizeof(charray));
		printf("Child finished writing to pipe pid:%d\n", (int)getpid());
	}else {
		printf("This is the parent process pid:%d\n", (int)getpid());
		wait(NULL);
		close(fd[1]);
		read(fd[0], charray, sizeof(charray));
		printf("Outputting text from pipe pid:%d\n", (int)getpid());
		for (int i = 0; i < MAX_CHAR; i++) {
			cout << charray[i];
		}
	}





}
