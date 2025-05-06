#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_PROC 10
#define COMM_ARG_LIM 5
#define PID_BUF_LEN 32

void itoa(pid_t pid, char* buffer) {
    if(buffer == NULL) {
        perror("cannot allocate buffer");
        exit(1);
    }
    sprintf(buffer, "%d", pid);
}

int main(int argc, char* argv[]) {

    pid_t pids[NUM_PROC]; // array stores process id

    char* commands[NUM_PROC][COMM_ARG_LIM] = { // testing commands
        {"/bin/ls", NULL}, // lists contents 
        {"/bin/echo","hello Jay", NULL}, // prints given message
        {"/bin/mkdir", "testdir", NULL}, // creates directory
        {"/bin/ip","a", NULL}, // show network interfaces
        {"/bin/id", NULL}, // show user, group ids
        {"/bin/date", NULL}, // show current date
        {"/bin/touch", "test.txt", NULL}, // create empty file
        {"/bin/head", "-n1", "create_childs.c", NULL}, // prints contents of target file from top
        {"/bin/tail","-n1", "create_childs.c", NULL}, // prints contents fo target file from bottom
        {"/bin/uptime", NULL} // prints active time
    };

    pid_t pid; // temporary storage for process id
    for(int i = 0; i < NUM_PROC; i++) {
        pid = fork(); // creates child process
        if(pid < 0) { // if fork() returns -1, 
            perror("fork() error"); // terminates program with -1
            exit(-1);
        }
        else if(pid == 0) { // if it is child process, 
            char buffer[PID_BUF_LEN];
            itoa(getpid(), buffer); // function that converts long(or int) type pid to char*
            printf("Process number %s created\n", buffer); // prints current process's id
            execvp(commands[i][0], commands[i]); // execute target command
            perror("execl() error"); // otherwise, prints error message
            exit(1); // terminates with abnormal status
        }
        else {
            pids[i] = pid; // if parent process, save child's pid
        }
    }

    int status; 
    for(int i = 0;  i < NUM_PROC; i++) { // wait for each child process to be terminated
        waitpid(pids[i], &status, 0);
        if(WIFEXITED(status)) { // if process terminated normally,
            printf("process %d exited normally\n", pids[i]); // prints message that certain process terminated normally
        }
        else if(WIFSIGNALED(status)) { // if process not terminated normally, 
            printf("process %d abnormally terminated with status %d\n", pids[i], status); // prints message that certain process terminated abnormally. 
        }
    }

    return 0;
}