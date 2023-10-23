/* The following code is modified by Mahesh(MXA220203) and Mugil(MXK230014) 
** User program to generate graph data
*/
#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

void spin()
{
    int i = 0;
    int j = 0;
    int k = 0;
	for(i = 0; i < 50; ++i) {
        for(j = 0; j < 10000000; ++j) {
            k = j % 10;
            k = k + 1;
        }
	}
}

int
main(int argc, char *argv[])
{
    struct pstat st;

    int tickets[] = {100,200,300};
    int ticks[3];
    int pid[3];

    int i;
    for(i=0; i<3; i++) {
        pid[i] = fork();
        if (pid[i] == 0) { //child process
            settickets(tickets[i]);
            for(;;)      //spin forever
                spin();   
        }
    }

    //generate data for 100 iterations
    int j;
    for (j=1; j<=100; j++) {
        getpinfo(&st);
        for(i = 0; i < NPROC; i++)
        {
            if(st.pid[i] == pid[0])
                ticks[0] = st.ticks[i];
            else if (st.pid[i] == pid[1])
                ticks[1] = st.ticks[i];
            else if (st.pid[i] == pid[2])
                ticks[2] =  st.ticks[i];
        }
        printf(1,"Iteration %d\n", j);
        for(i = 0; i < 3; i++) {
            printf(1, "i: %d | pid: %d | tickets: %d | ticks: %d\n", i, pid[i], tickets[i], ticks[i]);
        }
        printf(1,"\n");
    }

    //After generating the data, kill the childs
    int k;
    for(k=0; k<3; k++)
        kill(pid[k]);
    while (wait() > 0);
    exit();
}
/* End of code added */