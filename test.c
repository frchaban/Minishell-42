#include <stdio.h>
#include <unistd.h>

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/errno.h>
#include <sys/types.h>


#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>

#define   MAX_COUNT  200
#define   BUF_SIZE   100



int main(void)
{
    int     fd[2], nbytes;
    pid_t   childpid;
    char    string[] = "Hello, world!\n";
    char    readbuffer[80];

    pipe(fd);

    if((childpid = fork()) == -1)
    {
            perror("fork");
            exit(1);
    }

    if(childpid == 0)
    {
            
            close(fd[0]);

            
            write(fd[1], "from parent", (strlen(string)+1));
            exit(0);
    }
    else
    {
            
            close(fd[1]);

            
            nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
            printf("Received string: %s", readbuffer);
    }

    return(0);
}

