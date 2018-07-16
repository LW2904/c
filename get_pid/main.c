#include <stdio.h>
#include <stdlib.h>

int find_process(const char *ps_name);

int main()
{
	int pid = find_process("osu!.exe");

	printf("%d\n", pid);
}

int find_process(const char *ps_name)
{
    FILE *fp;
    char *cmd=(char*)calloc(1,200);
    sprintf(cmd,"pidof %s",ps_name);
    fp=popen(cmd,"r");
    fread(cmd,1,200,fp);
    fclose(fp);
    return atoi(cmd);
}