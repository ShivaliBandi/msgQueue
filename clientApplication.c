#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>

struct my_msg_st
{
	long int my_msg_type;
	char text[BUFSIZ];
};

int main()
{
	int running = 1;
	int msgid;
	struct my_msg_st data;
	long int msg_to_recieve = 0;

	msgid = msgget((key_t)1234, 0666);

	while(running)
	{
		msgrcv(msgid, (void *)&data, BUFSIZ, msg_to_recieve, 0);
		printf("\n\nRecieved Data:-\n %s", data.text);

		if(strncmp(data.text, "end", 3) == 0)
		{
			running = 0;
		}
	}
	exit(EXIT_SUCCESS);
}