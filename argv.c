#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	printf("argc:%d\targv[0]:%s\n",argc,argv[0]);
	int i=1;
	while(i<argc)
	{
		printf("%s\t",argv[i]);
		i++;
	}
	printf("\n");
	return 0;
}
