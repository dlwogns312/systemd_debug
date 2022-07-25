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

static int file_cur=0;

typedef struct _file_node{
    char *id;
    int num;
    int fp_loc;
    struct _file_node* next;
}file_node;

file_node* head=0;

/*file_node* insert_file_node(char* _id)
{
    file_node *temp=(file_node*)malloc(sizeof(file_node));
}*/

int systemctl_test(void)
{
    FILE* fp;
    fp=fopen("/var/log/text.txt","r");
    if(!fp)
    {
        printf("File open error!\n");
        return 1;
    }

    char in[200];

    fseek(fp,file_cur,SEEK_SET);
    while(!feof(fp))
    {
        break;
    }

	return 0;
}
