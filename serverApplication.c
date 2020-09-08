#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>

#define MAX_TEXT 512

struct my_msg_st
{
	long int my_msg_type;
	char text[MAX_TEXT];
};

int main()
{
	int running = 1;
	int msgid;
	struct my_msg_st data;
	char buffer[BUFSIZ];

	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	if(msgid == -1)
	{
		printf("\n\nFailed to create");
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		printf("\n\nEnter Some Text('end' to terminate): ");
		fgets(buffer, BUFSIZ, stdin);
		data.my_msg_type = 1;
		strcpy(data.text, buffer);

		if(msgsnd(msgid, (void *)&data, MAX_TEXT, 0) == -1)
		{
			printf("\n\nmsgnd failed");
			exit(EXIT_FAILURE);
		}

		if(strncmp(buffer, "end", 3) == 0)
		{
			running = 0;
		}
	}
	exit(EXIT_SUCCESS);
}