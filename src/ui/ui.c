#include "ui/ui.h"
#include "ui/breakpoint.h"

#include "nemu.h"

#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

uint32_t expr(char *e, bool *success);

int nemu_state = END;

void cpu_exec(uint32_t);
void restart();

/* We use the readline library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

/* This function will be called when you press <C-c>. And it will return to 
 * where you press <C-c>. If you are interesting in how it works, please
 * search for "Unix signal" in the Internet.
 */
static void control_C(int signum) {
	if(nemu_state == RUNNING) {
		nemu_state = INT;
	}
}

void init_signal() {
	/* Register a signal handler. */
	struct sigaction s;
	memset(&s, 0, sizeof(s));
	s.sa_handler = control_C;
	int ret = sigaction(SIGINT, &s, NULL);
	assert(ret == 0);
}

static void cmd_c() {
	if(nemu_state == END) {
		puts("The Program does not start. Use 'r' command to start the program.");
		return;
	}

	nemu_state = RUNNING;
	cpu_exec(-1);
	if(nemu_state != END) { nemu_state = STOP; }
}

static void cmd_r() {
	if(nemu_state != END) { 
		char c;
		while(1) {
			printf("The program is already running. Restart the program? (y or n)");
            fflush(stdout);
			scanf(" %c", &c);
			switch(c) {
				case 'y': goto restart_;
				case 'n': return;
				default: puts("Please answer y or n.");
			}
		}
	}

restart_:
	restart();
	nemu_state = STOP;
	cmd_c();
}

void cmd_si(int n)
{
    if(nemu_state == END) {
        restart();
        nemu_state = STOP;
	}

    cpu_exec(n);
    return;
}

/*  0: r register
*   1: b breakpoint and watch
*/
void cmd_info(uint8_t type)
{
    switch(type) {
    case 0:
        printf("EAX %8x  ECX %8x\n", cpu.eax, cpu.ecx);
        printf("EDX %8x  EBX %8x\n", cpu.edx, cpu.ebx);
        printf("ESP %8x  EBP %8x\n", cpu.esp, cpu.ebp);
        printf("ESI %8x  EDI %8x\n", cpu.esi, cpu.edi);
        break;
    case 1:
        printf("info b \n");
        break;
    default:
        break;
    }
}

void cmd_p( uint32_t addr)
{
    printf("addr %x\n", addr);
    return;
}

void cmd_x(int n, uint32_t addr) 
{
    int i;
    printf("n: %d   addr 0x%x\n", n, addr);
    for (i=0;i<n;i++) {
        printf("0x%8x  ", swaddr_read(addr+i*4, 4));
        if(i%4==4-1&&i) {
            printf("\n");
        }
    }
    if (n%4 != 3)
        printf("\n");
    return;
}

void cmd_b(uint32_t addr)
{
   // need to judge whether has the same breakpoint 
    add_bp(addr);
}

void cmd_d(uint32_t addr)
{   
    del_bp(addr);
}

void main_loop() {
	char *cmd;
	while(1) {
		cmd = rl_gets();
		char *p = strtok(cmd, " ");

		if(p == NULL) { continue; }

		if(strcmp(p, "c") == 0) { cmd_c(); }
		else if(strcmp(p, "r") == 0) { cmd_r(); }
		else if(strcmp(p, "q") == 0) { return; }
        else if(strcmp(p, "si") == 0) { 
            char *p=strtok(NULL, " ");
            cmd_si((p==NULL)?1:atoi(p));
        } else if (strcmp(p, "info") == 0) {
            cmd_info(strtok(NULL, " ")[0] == 'r'?0:1 );
        } else if (strcmp(p, "p") == 0) {
            bool success;
            cmd_p(expr(strtok(NULL, " "), &success));
        } else if (strcmp(p, "x") == 0) {
            char *tmp = strtok(NULL, " ");
            char *tmp1 = tmp+strlen(tmp)+1;
            bool success;
            cmd_x(atoi(tmp), expr(tmp1, &success));
        } else if (strcmp(p, "b") == 0) {
            char *tmp = strtok(NULL, " ");
            if (tmp[0] == '*') {
                cmd_b(0);
            } else {
                // query symbol table 
                ;
            }
        } else if (strcmp(p, "d") == 0) {
            char *tmp = strtok(NULL, " ");
            if (tmp[0] == '*') {
                cmd_d(0);
            } else {
                // query symbol table 
                ;
            }
        }



		/* TODO: Add more commands */

		else { printf("Unknown command '%s'\n", p); }
	}
}
