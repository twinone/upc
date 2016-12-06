/*
 * A n t l r  S e t s / E r r o r  F i l e  H e a d e r
 *
 * Generated from: lego.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-2001
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 */

#define ANTLR_VERSION	13333
#include "pcctscfg.h"
#include "pccts_stdio.h"

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>


// Uncomment for debugging lines
//#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

// Uncomment for user-warnings (wrongly placed blocks, out of bounds, etc)
//#define WARN
#ifdef WARN
#define W(x) x
#else
#define W(x)
#endif


using namespace std;

// struct to store information about tokens
typedef struct {
  string kind;
  string text;
  int type;
} Attrib;

// function to fill token information (predeclaration)
void zzcr_attr(Attrib *attr, int type, char *text);

// fields for AST nodes
#define AST_FIELDS string kind; string text; int type;
#include "ast.h"

// macro to create a new AST node (and function predeclaration)
#define zzcr_ast(as,attr,ttype,textt) as=createASTnode(attr,ttype,textt)
AST* createASTnode(Attrib* attr,int ttype, char *textt);
#define zzSET_SIZE 4
#include "antlr.h"
#include "ast.h"
#include "tokens.h"
#include "dlgdef.h"
#include "err.h"

ANTLRChar *zztokens[26]={
	/* 00 */	"Invalid",
	/* 01 */	"@",
	/* 02 */	"SPACE",
	/* 03 */	"PRINT",
	/* 04 */	"BOOL",
	/* 05 */	"AND",
	/* 06 */	"MOVE",
	/* 07 */	"FITS",
	/* 08 */	"HEIGHT",
	/* 09 */	"NESW",
	/* 10 */	"GRID",
	/* 11 */	"DEF",
	/* 12 */	"PLACE",
	/* 13 */	"ENDEF",
	/* 14 */	"WHILE",
	/* 15 */	"AT",
	/* 16 */	"CMP",
	/* 17 */	"ASSIG",
	/* 18 */	"LPAREN",
	/* 19 */	"RPAREN",
	/* 20 */	"LSQUARE",
	/* 21 */	"RSQUARE",
	/* 22 */	"COMMA",
	/* 23 */	"PUSH",
	/* 24 */	"INT",
	/* 25 */	"ID"
};
SetWordType zzerr1[4] = {0xc8,0x41,0x0,0x2};
SetWordType zzerr2[4] = {0xca,0x69,0x22,0x2};
SetWordType setwd1[26] = {0x0,0xfb,0x0,0xe4,0x0,0x0,0xe4,
	0xe4,0xe4,0x0,0x0,0xe9,0x0,0xc8,0xe4,
	0x0,0x0,0x0,0x0,0x0,0x0,0xc8,0x0,
	0x0,0x0,0xe4};
SetWordType zzerr3[4] = {0x90,0x1,0x0,0x1};
SetWordType zzerr4[4] = {0x20,0x0,0x9,0x0};
SetWordType setwd2[26] = {0x0,0x7,0x0,0x7,0x0,0xc6,0x7,
	0x7,0x27,0x0,0x0,0x7,0x0,0x7,0x7,
	0x0,0x4,0x0,0x0,0xde,0x0,0x7,0x0,
	0x0,0x20,0x7};
SetWordType zzerr5[4] = {0x0,0x1,0x0,0x1};
SetWordType zzerr6[4] = {0x0,0x10,0x4,0x2};
SetWordType setwd3[26] = {0x0,0xdc,0x0,0xdc,0x0,0x3,0xdc,
	0xdc,0xdc,0x0,0x0,0xdc,0x0,0xdc,0xdc,
	0x10,0x2,0x0,0x20,0x13,0x0,0xdc,0x0,
	0x10,0x0,0xfc};
SetWordType zzerr7[4] = {0xca,0x69,0xa0,0x2};
SetWordType zzerr8[4] = {0x0,0x0,0x4,0x2};
SetWordType setwd4[26] = {0x0,0x7,0x0,0x7,0x0,0x0,0x7,
	0x7,0x7,0x0,0x0,0x7,0x0,0x7,0x7,
	0x0,0x0,0x0,0x0,0x8,0x0,0x7,0x0,
	0x8,0x0,0x7};
