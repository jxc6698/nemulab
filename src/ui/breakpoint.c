#include "ui/breakpoint.h"

#include "nemu.h"

#define NR_BP 32

static BP bp_pool[NR_BP];
static BP *head, *free_;
static uint32_t bp_index;

void init_bp_pool() {
	int i;
	for(i = 0; i < NR_BP - 1; i ++) {
		bp_pool[i].NO = i;
		bp_pool[i].next = &bp_pool[i + 1];
	}
    bp_pool[i].NO = i;
	bp_pool[i].next = NULL;

	head = NULL;
	free_ = bp_pool;
    bp_index = 0;
}

/* TODO: Implement the function of breakpoint */
void add_bp(uint32_t addr)
{
	uint8_t cmd = swaddr_read(addr, 1);
	if (cmd == INT3_CODE)
		return ;
    BP *cur=NULL;
    if (!free_) {
        printf("breakpoint already have 32\n");
        return;
    }
    if (!head) {
        head = free_;
        free_ = free_->next;
        head->next = NULL;
        cur = head;
    } else {
        cur = head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = free_;
        cur = cur->next;
        free_ = free_->next;
        cur->next = NULL;
    }

    cur->NO = bp_index;
    bp_index ++;
    cur->addr = addr;
    cur->ins_f_bit = cmd;
	swaddr_write(addr, 1, INT3_CODE);

    return;
}

void del_bp(uint32_t index)
{
    BP *cur = head, *prev=NULL;
    while (cur) {
        if (cur->NO==index)
            break;
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL)
        printf("no breakpoint index %d\n", index);
    else {
        if (!prev) {
            head = head->next;
            cur->next = free_;
            free_ = cur;
        } else {
            prev->next = cur->next;
            cur->next = free_;
            free_ = cur;
        }
    }
}

void show_bp(int index) {
    BP *cur=NULL;
    cur = head;
    while (cur) {
		if (index==-1 || index==cur->NO)
			printf("index : %d address %x\n", cur->NO, cur->addr);
        cur = cur->next;
    }
}

int recover_bp(swaddr_t addr)
{
    BP *cur=NULL;
    cur = head;
    while (cur) {
		if (cur->addr == addr) {
			swaddr_write(addr, 1, cur->ins_f_bit);
			return cur->NO;
		}
        cur = cur->next;
    }
	return -1;
}

void reset_bp(swaddr_t addr)
{
	swaddr_write(addr, 1, INT3_CODE);
}
