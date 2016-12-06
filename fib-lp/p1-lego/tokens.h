#ifndef tokens_h
#define tokens_h
/* tokens.h -- List of labelled tokens and stuff
 *
 * Generated from: lego.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * ANTLR Version 1.33MR33
 */
#define zzEOF_TOKEN 1
#define SPACE 2
#define PRINT 3
#define BOOL 4
#define AND 5
#define MOVE 6
#define FITS 7
#define HEIGHT 8
#define NESW 9
#define GRID 10
#define DEF 11
#define PLACE 12
#define ENDEF 13
#define WHILE 14
#define AT 15
#define CMP 16
#define ASSIG 17
#define LPAREN 18
#define RPAREN 19
#define LSQUARE 20
#define RSQUARE 21
#define COMMA 22
#define PUSH 23
#define INT 24
#define ID 25

#ifdef __USE_PROTOS
void def(AST**_root);
#else
extern void def();
#endif

#ifdef __USE_PROTOS
void lego(AST**_root);
#else
extern void lego();
#endif

#ifdef __USE_PROTOS
void ops(AST**_root);
#else
extern void ops();
#endif

#ifdef __USE_PROTOS
void defs(AST**_root);
#else
extern void defs();
#endif

#ifdef __USE_PROTOS
void griddef(AST**_root);
#else
extern void griddef();
#endif

#ifdef __USE_PROTOS
void op(AST**_root);
#else
extern void op();
#endif

#ifdef __USE_PROTOS
void assig(AST**_root);
#else
extern void assig();
#endif

#ifdef __USE_PROTOS
void fits(AST**_root);
#else
extern void fits();
#endif

#ifdef __USE_PROTOS
void height(AST**_root);
#else
extern void height();
#endif

#ifdef __USE_PROTOS
void boolexpr(AST**_root);
#else
extern void boolexpr();
#endif

#ifdef __USE_PROTOS
void booland(AST**_root);
#else
extern void booland();
#endif

#ifdef __USE_PROTOS
void boolatom(AST**_root);
#else
extern void boolatom();
#endif

#ifdef __USE_PROTOS
void boolcmp(AST**_root);
#else
extern void boolcmp();
#endif

#ifdef __USE_PROTOS
void intexpr(AST**_root);
#else
extern void intexpr();
#endif

#ifdef __USE_PROTOS
void while_loop(AST**_root);
#else
extern void while_loop();
#endif

#ifdef __USE_PROTOS
void move(AST**_root);
#else
extern void move();
#endif

#ifdef __USE_PROTOS
void coords(AST**_root);
#else
extern void coords();
#endif

#ifdef __USE_PROTOS
void blockexpr(AST**_root);
#else
extern void blockexpr();
#endif

#ifdef __USE_PROTOS
void place(AST**_root);
#else
extern void place();
#endif

#ifdef __USE_PROTOS
void push(AST**_root);
#else
extern void push();
#endif

#ifdef __USE_PROTOS
void ppr(AST**_root);
#else
extern void ppr();
#endif

#ifdef __USE_PROTOS
void block(AST**_root);
#else
extern void block();
#endif

#endif
extern SetWordType zzerr1[];
extern SetWordType zzerr2[];
extern SetWordType setwd1[];
extern SetWordType zzerr3[];
extern SetWordType zzerr4[];
extern SetWordType setwd2[];
extern SetWordType zzerr5[];
extern SetWordType zzerr6[];
extern SetWordType setwd3[];
extern SetWordType zzerr7[];
extern SetWordType zzerr8[];
extern SetWordType setwd4[];
