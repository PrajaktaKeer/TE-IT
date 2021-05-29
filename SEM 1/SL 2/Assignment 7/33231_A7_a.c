/*Implementation of Full duplex communication between parent and child processes. Parent
process writes a pathname of a file (the contents of the file are desired) on one pipe to be
read by child process and child process writes the contents of the file on second pipe to be
read by parent process and displays on standard output.*/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
void child(int,int);
void parent(int,int);
void main()
{
	int pipe1[2], pipe2[2], fd, len, n;
	char buff[10];
	pid_t pid;
	pipe(pipe1); 
	pipe(pipe2); 
	
	pid=fork(); 

	if(pid == 0)
	{
		close(pipe1[1]);
		close(pipe2[0]);
		//closing ends that aren't in use
		n = read(pipe1[0], buff, 10);//Step 3
		//Handle the Error
		buff[n]='\0';
		fd = open(buff, O_RDONLY);
		while((n = read(fd ,buff,10)) > 0) //Step 5
		write(pipe2[1], buff, n);
		close(fd);
	}
	else //first, goes to parent
	{
		close(pipe1[0]);
		close(pipe2[1]);
		//Parent Writing pathname to file
		printf("Enter the path name : "); //Step 4
		fgets(buff,10,stdin);
		len = strlen(buff);
		if(buff[len-1]=='\n')
		len--;
		write(pipe1[1], buff, len);//Step 4
		//Handle the Error
		printf("The contents of file : \n");
		while((n = read(pipe2[0],buff,10)) > 0)//Step 6
		write(STDOUT_FILENO,buff,n);//Step 7
		printf("\n");
	}
}