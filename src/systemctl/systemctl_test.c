#include "systemctl_test.h"

#include <getopt.h>
#include <locale.h>
#include <unistd.h>

#include "sd-daemon.h"

#include "bus-util.h"
#include "install.h"
#include "main-func.h"
#include "output-mode.h"
#include "pager.h"
#include "parse-argument.h"
#include "path-util.h"
#include "pretty-print.h"
#include "process-util.h"
#include "rlimit-util.h"
#include "sigbus.h"
#include "signal-util.h"
#include "string-table.h"
#include "systemctl-add-dependency.h"
#include "systemctl-cancel-job.h"
#include "systemctl-clean-or-freeze.h"
#include "systemctl-compat-halt.h"
#include "systemctl-compat-runlevel.h"
#include "systemctl-compat-shutdown.h"
#include "systemctl-compat-telinit.h"
#include "systemctl-daemon-reload.h"
#include "systemctl-edit.h"
#include "systemctl-enable.h"
#include "systemctl-is-active.h"
#include "systemctl-is-enabled.h"
#include "systemctl-is-system-running.h"
#include "systemctl-kill.h"
#include "systemctl-list-dependencies.h"
#include "systemctl-list-jobs.h"
#include "systemctl-list-machines.h"
#include "systemctl-list-unit-files.h"
#include "systemctl-list-units.h"
#include "systemctl-log-setting.h"
#include "systemctl-logind.h"
#include "systemctl-mount.h"
#include "systemctl-preset-all.h"
#include "systemctl-reset-failed.h"
#include "systemctl-service-watchdogs.h"
#include "systemctl-set-default.h"
#include "systemctl-set-environment.h"
#include "systemctl-set-property.h"
#include "systemctl-show.h"
#include "systemctl-start-special.h"
#include "systemctl-start-unit.h"
#include "systemctl-switch-root.h"
#include "systemctl-sysv-compat.h"
#include "systemctl-trivial-method.h"
#include "systemctl-util.h"
#include "systemctl.h"
#include "terminal-util.h"
#include "time-util.h"
#include "verbs.h"
#include "virt.h"

typedef struct _file_node{
    char id[50];
    int num;
    struct _file_node* next;
}file_node;

file_node* head=NULL;
static int fp_loc=0;
int num;

static file_node* insert_file_node(char* _id)
{
    file_node *temp=(file_node*)malloc(sizeof(file_node));
    strcpy(temp->id,_id);
    temp->num=1;
    temp->next=NULL;

    return temp;
}

int num_failed_unit(void)
{
    FILE* fp;
    fp=fopen("/var/log/failed_history.txt","r");

    if(!fp)
    {
        printf("Log File Open Error!\n");
        return 0;
    }

    //fseek(fp,fp_loc,0);
    if(head==NULL)
    {
        head=(file_node*)malloc(sizeof(file_node));
        head->num=0;head->next=NULL;
    }

    char time_tmp[20],time_tmp1[20],id_tmp[100],status_tmp[20];
    file_node* tmp;

    fscanf(fp,"%d",&num);

    while(num--)
    {
        fscanf(fp,"%s %s %s %s",id_tmp,time_tmp,time_tmp1,status_tmp);
        for(tmp=head;tmp->next!=NULL;tmp=tmp->next)
            if(!strcmp(tmp->next->id,id_tmp))
            {
                tmp->next->num++;
                break;
            }
        if(tmp->next==NULL)
            tmp->next=insert_file_node(id_tmp);
    }

    printf("Failed Number\tUnit ID\n");
    for(tmp=head->next;tmp!=NULL;)
    {
        printf("%-10d\t%s\n",tmp->num,tmp->id);
        file_node* for_free=tmp;
        tmp=tmp->next;
        free(for_free);
    }
    //fp_loc=ftell(fp);
    free(head);
    fclose(fp);
    return 0;
}

int log_reset(void)
{
    FILE* fp=fopen("/var/log/failed_history.txt","w");

    if(fp)
    {
        fprintf(fp,"0\n");
        fclose(fp);
        printf("Remove /var/log/failed_history.txt success!\n");
    }
    else
        printf("There is no filed called /var/log/failed_history.txt!\n");


    return 0;
}

int systemctl_test(void)
{
    FILE* fp;
    fp=fopen("/var/log/failed_history.txt","r");
    if(!fp)
    {
        printf("File open error!\n");
        return 0;
    }

    printf("Time\t\t\tFailed Status\tUnit ID\n");
    char time_tmp[20],time_tmp1[20],id_tmp[100],status_tmp[20];
    fscanf(fp,"%d",&num);

    while(num--)
    {
        fscanf(fp,"%s %s %s %s",id_tmp,time_tmp,time_tmp1,status_tmp);
        printf("%s %s\t%-10s\t%s\n",time_tmp,time_tmp1,status_tmp,id_tmp);
    }

    fclose(fp);
	return 0;
}
