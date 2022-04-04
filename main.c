#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>


void writeLog(char* message, int iter_counter, FILE* log){

	fprintf(log, "%s %d\n", "iter counter = ",iter_counter);
	int i;
	for(i = 0; i < iter_counter; i++){
		fprintf(log, "%d - %s\n", i, message);
		sleep(1);
	}
	fprintf(log, "%s\n", "_________________");
}

void makeFork(char* message, int n_proc, int n_iter, FILE* log){
	
	int i;
	for(i = 0; i < n_proc; ++i){
		int new_pid = fork();
		if (new_pid == 0){
			writeLog(message, n_iter*(i+1), log);
			break;
		}
		else{
			if(i+1 == n_iter){
				wait(0);
			}
		}
	}
}



int main (int argc, char** argv){
	FILE* log;
	if ((log = fopen("/home/grush/Documents/log.txt", "w")) == NULL){
    		return 0;
  	}
	
	char* message = (char*) argv[1];
	int n_proc = (int)* argv[2];
	int n_iter = (int)* argv[3];
	
	makeFork(message,n_proc-48,n_iter-48, log);
		
	fclose(log);
	return 0;
}
