
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/iomsg.h>
#include <sys/netmgr.h>
#include <sys/pps.h>
#include <sys/procmgr.h>
#include <signal.h>
#include <ha/ham.h>
#include <errno.h>
#include <pthread.h>
#include "ham-client.h"
#include "ham-monitor.h"
#include "log.h"

extern int ham_client_init(char *file);

static void *Test_Ham_Hbeat(void *arg)
{
	LOGINF("<my-test>carry the pthread of Test_Ham_Hbeat");
	LOGINF("<my-test>Test_Ham_Hbeat tid is %d",gettid());
	int beat=*(int *)arg;
	while(1){
		sleep(beat);
		ham_heartbeat();
		LOGINF("<my-test>%d sencond send a HBEAT",beat);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if(argc>2)
	{
		LOGERR("<my-test>too many argument");
		return EXIT_FAILURE;
	}
	int i=atoi(argv[1]);
	LOGINF("<my-test>choose send hbeat every %ds",i);
	if(procmgr_daemon(EXIT_SUCCESS,PROCMGR_DAEMON_NOCLOSE | PROCMGR_DAEMON_NODEVNULL)==-1)
	{
		LOGERR("<my-test>procmgr_daemon failed");
		return EXIT_FAILURE;
	}
	LOGINF("<my-test>pid:%d",getpid());
	if(!register_ham_self_restart_with_heartbeat("ham-client-test","/TEST/ham-client-test","/emmc/svp/etc/reset-via-mcu.sh",1,2,2000))
	{
		pthread_create(NULL,NULL,Test_Ham_Hbeat,(void *)&i);
	}
	else{
		LOGERR("<my-test>register_ham_self_restart_with_heartbeat failed");
		return EXIT_FAILURE;
	}
	//return EXIT_SUCCESS;
	while(1){
		sleep(2);
	}
}
