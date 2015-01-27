#include "common.h"
#include "cpu/reg.h"
#include "memory.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>

enum {
	NOTYPE = 256, EQ, NUM, REG,
    /* * operator: *0x100000  */
    RESTORE

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// 0 white space
	{"\\+", '+'},					// 1 plus
	{"==", EQ},						// 2 equal
    {"-", '-'},                     // 3 minus
    {"\\*", '*'},                   // 4 multiply/parse
    {"/", '/'},                     // 5 div
    {"\\(", '('},                   // 6 left
    {"\\)", ')'},                   // 7 right
    {"\\.", '.'},                   // 8 Dominant operator
    {"(0x)?[0-9]+", NUM},           // 9 num
    {"\\$E((AX)|(BX)|(CX)|(DX)|(SP)|(BP)|(SI)|(EI))", REG}
                                    // 10 registers 
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			test(0, "regex compilation failed: %s\n%s\n", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				Log("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);

				position += substr_len;


				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */

				switch(rules[i].token_type) {
                    case NOTYPE:
                        break;
                    case '.':
                        tokens[nr_token].type = '.';
                        nr_token++;
                        break;
                    case '+':
                        tokens[nr_token].type = '+';
                        nr_token++;
                        break;
                    case '-':
                        tokens[nr_token].type = '-';
                        nr_token++;
                        break;
                    case '*':
                        if(nr_token ==0 || tokens[nr_token-1].type == '(' 
                            || tokens[nr_token-1].type == '+'
                            || tokens[nr_token-1].type == '-'
                            || tokens[nr_token-1].type == '*'
                            || tokens[nr_token-1].type == '/'
                            || tokens[nr_token-1].type == EQ) {
                            tokens[nr_token].type = RESTORE;
                        }
                        else
                            tokens[nr_token].type = '*';
                        nr_token++;
                        break;
                    case '/':
                        tokens[nr_token].type = '/';
                        nr_token++;
                        break;
                    case '(':
                        tokens[nr_token].type = '(';
                        nr_token++;
                        break;
                    case ')':
                        tokens[nr_token].type = ')';
                        nr_token++;
                        break;
                    case NUM: 
                        tokens[nr_token].type = NUM;
                        strncpy(tokens[nr_token].str, substr_start, substr_len+1);
                        nr_token++;
                        break;
                    case EQ:
                        tokens[nr_token].type = EQ;
                        nr_token++;
                        break;
                    case REG:
                        tokens[nr_token].type = REG;
                        strncpy(tokens[nr_token].str, substr_start, substr_len+1);
                        nr_token++;
                        break;
					default: assert(0);
				}

				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}

static uint32_t cpu_reg(char *reg)
{
    if(reg[2] == 'A')
        return cpu.eax;
    else if (reg[2] == 'C')
        return cpu.ecx;
    else if (reg[2] == 'D' && reg[3] == 'X')
        return cpu.edx;
    else if (reg[2] == 'B' && reg[3] == 'X')
        return cpu.ebx;
    else if (reg[2] == 'S' && reg[3] == 'P')
        return cpu.esp;
    else if (reg[2] == 'B' && reg[3] == 'P')
        return cpu.ebp;
    else if (reg[2] == 'S' && reg[3] == 'I')
        return cpu.esi;
    else if (reg[2] == 'D' && reg[3] == 'I')
        return cpu.edi;
    printf("error : input reg is %s", reg);

    return 0;
}

static int64_t expr_exp(int s, int e, bool *success) {
    int i=0;
    uint32_t value;
    /* parenthesis depth */
    int depth=0, split=-1;
    if (s > e) {
        *success = false;
        return 0;
    } else if (s == e) {
        if (tokens[s].type == NUM) {
            *success = true;
            if (!strncmp(tokens[s].str, "0X", 2) || 
                 !strncmp(tokens[s].str, "0x", 2) )
                sscanf(tokens[s].str, "%x", &value);
            else
                value = atoll(tokens[s].str);
            return value;
        } else if(tokens[s].type == REG) {
            *success = true;
            return cpu_reg(tokens[s].str);
        }
        printf("error : s==e = %d, not handled type %d\n", s, tokens[s].type);
        *success = false;
        return 0;
    } else if (tokens[s].type == '(' && tokens[e].type == ')') {
        return expr_exp(s+1,e-1, success);
    }
    /*  priority 1 +-  2 * /  3 *(restore) 4 .  */
    for (i=e;i >= s;i --) {
        if (tokens[i].type == NUM)
            ;
        else if (tokens[i].type == REG)
            ;
        else if (tokens[i].type == EQ)
            ;
        else if (tokens[i].type == '(')
            depth ++;
        else if (tokens[i].type == ')')
            depth --;
        else if (depth) {
            ;/* just continue */
        } else if (tokens[i].type == '+') {
            split = i;
            break;
        } else if (tokens[i].type == '-') {
            split = i;
            break;
        } else if (tokens[i].type == '*') {
            if(split == -1 || tokens[split].type == '.' 
                || tokens[split].type == RESTORE) 
                split = i;
        } else if (tokens[i].type == '/') {
            if(split == -1 || tokens[split].type == '.'
                || tokens[split].type == RESTORE) 
                split = i;
        } else if (tokens[i].type == RESTORE) {
            if(split == -1 || tokens[split].type == '.')
                split = i;
        } else if (tokens[i].type == '.') {
            if(split == -1)
                split = i;
            printf("new not handle . operator\n");
        }

        /* others ignore */
    }
    if(split == -1) {
        printf("can not handle between index %d %d\n", s, e);
        *success = false;
        return 0;
    }
    int64_t tmpl = (s!=split)?expr_exp(s,split-1,success):0;
    if(!*success)
        return 0;
    int64_t tmpr = expr_exp(split+1,e,success);
    if(!*success)
        return 0;
    switch(tokens[split].type) {
        case '+':
            return tmpl+tmpr;
        case '-':
            return tmpl-tmpr;
        case '*':  
            return tmpl*tmpr;
        case '/':
            if (tmpr == 0) {
                *success = false;
                return 0;
            }
            return tmpl/tmpr;
        case RESTORE:
        /* *0x10000 in fault 4 bytes */
            return swaddr_read(tmpr, 4);
        default:
            printf("unhandled token %d\n", tokens[i].type);
            *success = false;
            return 0;
    }
}

uint32_t expr(char *e, bool *success) {
    uint32_t ret;
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
    
	/* TODO: Implement code to evaluate the expression. */
    *success = true;
    ret = expr_exp(0, nr_token-1, success);
    if(!*success)
        printf("error while expr expression\n");

    return ret;
}

