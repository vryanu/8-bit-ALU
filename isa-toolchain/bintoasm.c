#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "headers/bintoasm.h"
/*
Create function bintoasm()

Commands in a .txt must be seperated by newline

Proper BIN syntax:
000 ADD   00 REG B
001 SUB   01 REG A
010 MUL   10 MAR
011 DIV   11 ACC
100 MOD
101 AND
110 OR
111 XOR
ART [5 BITS 0] [3 BITS OP]
RAM [2 BITS MOV/SET VAL] [MOV] [LOAD] [STORE] [SET (REQUIRES MOV)] [2 BITS MOV/SET LOC]
*/

bool VAL1, VAL2, MOV, LOAD, STORE, SET, LOC1, LOC2, OP1, OP2, OP3;
char *ctype, *op, *val, *loc;
int cset = 0;

static bool isOn(char val);
static void setVals(const char *binary_str);
static void cmdType(void);
static void setValLoc(void);
static void setOp(void);
static void findValLocOp(const char *num, const char type);

void bintoasm(const char *binary_str, FILE *output)
{
    char command[50] = "";

    setVals(binary_str);
    cmdType();

    if (strcmp(ctype, "END") == 0)
        snprintf(command, sizeof(command), "END");
    else if (MOV && SET)
        snprintf(command, sizeof(command), "SET %s %d", loc, cset);
    else if (MOV)
        snprintf(command, sizeof(command), "MOV %s %s", val, loc);
    else if (LOAD || STORE)
        snprintf(command, sizeof(command), "%s", ctype);
    else
        snprintf(command, sizeof(command), "%s", op);

    fprintf(output, "%s\n", command);
}

static bool isOn(char val)
{
    return val == '1';
}

static void setVals(const char *binary_str)
{
    VAL1 = VAL2 = MOV = LOAD = STORE = SET = LOC1 = LOC2 = OP1 = OP2 = OP3 = false;
    ctype = "";
    op = "";
    val = "";
    loc = "";
    cset = 0;

    if (strcmp(binary_str, "10000000") == 0)
    {
        ctype = "END";
        return;
    }

    VAL1  = isOn(binary_str[0]);
    VAL2  = isOn(binary_str[1]);
    MOV   = isOn(binary_str[2]);
    LOAD  = isOn(binary_str[3]);
    STORE = isOn(binary_str[4]);

    if (MOV)
    {
        SET  = isOn(binary_str[5]);
        LOC1 = isOn(binary_str[6]);
        LOC2 = isOn(binary_str[7]);
    }
    else if (!LOAD && !STORE)
    {
        OP1 = isOn(binary_str[5]);
        OP2 = isOn(binary_str[6]);
        OP3 = isOn(binary_str[7]);
    }
}

static void findValLocOp(const char *num, const char type)
{
    if (type == 'v')
    {
        if (strcmp(num, "00") == 0) val = "REGB";
        else if (strcmp(num, "01") == 0) val = "REGA";
        else if (strcmp(num, "10") == 0) val = "MAR";
        else if (strcmp(num, "11") == 0) val = "ACC";
    }
    else if (type == 'l')
    {
        if (strcmp(num, "00") == 0) loc = "REGB";
        else if (strcmp(num, "01") == 0) loc = "REGA";
        else if (strcmp(num, "10") == 0) loc = "MAR";
        else if (strcmp(num, "11") == 0) loc = "ACC";
    }
    else if (type == 'o')
    {
        if (strcmp(num, "000") == 0) op = "ADD";
        else if (strcmp(num, "001") == 0) op = "SUB";
        else if (strcmp(num, "010") == 0) op = "MUL";
        else if (strcmp(num, "011") == 0) op = "DIV";
        else if (strcmp(num, "100") == 0) op = "MOD";
        else if (strcmp(num, "101") == 0) op = "AND";
        else if (strcmp(num, "110") == 0) op = "OR";
        else if (strcmp(num, "111") == 0) op = "XOR";
    }
}

static void setValLoc(void)
{
    char vstr[3] = "00";
    char vloc[3] = "00";

    vstr[0] = VAL1 ? '1' : '0';
    vstr[1] = VAL2 ? '1' : '0';
    vloc[0] = LOC1 ? '1' : '0';
    vloc[1] = LOC2 ? '1' : '0';

    findValLocOp(vstr, 'v');
    findValLocOp(vloc, 'l');

    cset = (VAL1 ? 2 : 0) + (VAL2 ? 1 : 0);
}

static void setOp(void)
{
    char vop[4] = "000";

    vop[0] = OP1 ? '1' : '0';
    vop[1] = OP2 ? '1' : '0';
    vop[2] = OP3 ? '1' : '0';

    findValLocOp(vop, 'o');
}

static void cmdType(void)
{
    if (strcmp(ctype, "END") == 0)
        return;

    if (MOV)
    {
        ctype = SET ? "SET" : "MOV";
        setValLoc();
    }
    else if (LOAD)
        ctype = "LOAD";
    else if (STORE)
        ctype = "STORE";
    else
        setOp();
}