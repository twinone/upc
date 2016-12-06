#header
<<
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
>>

<<
#include <cstdlib>
#include <cmath>

//global structures
AST *root;



// function to fill token information
void zzcr_attr(Attrib *attr, int type, char *text) {
  // Changed from teachers' implementation
  // I don't use kind, it's much easier to switch over type ints
  // and have the text attritubte to be consistent...
  attr->text = text;
  attr->type = type;
}

// function to create a new AST node
AST* createASTnode(Attrib* attr, int type, char* text) {
  AST* as = new AST;
  as->kind = attr->kind;
  as->text = attr->text;
  as->type = attr->type; // We want the type!
  as->right = NULL;
  as->down = NULL;
  return as;
}


/// create a new "list" AST node with one element
AST* createASTlist(AST *child) {
 AST *as=new AST;
 as->kind="list";
 as->right=NULL;
 as->down=child;
 return as;
}

/// get nth child of a tree. Count starts at 0.
/// if no such child, returns NULL
AST* child(AST *a,int n) {
  AST *c=a->down;
  for (int i=0; c!=NULL && i<n; i++) c=c->right;
  return c;
}



/// print AST, recursively, with indentation
void ASTPrintIndent(AST *a,string s)
{
  if (a==NULL) return;

  cout<<a->kind;
  if (a->text!="") cout<<"("<<a->text<<")";
  cout<<endl;

  AST *i = a->down;
  while (i!=NULL && i->right!=NULL) {
    cout<<s+"  \\__";
    ASTPrintIndent(i,s+"  |"+string(i->kind.size()+i->text.size(),' '));
    i=i->right;
  }

  if (i!=NULL) {
      cout<<s+"  \\__";
      ASTPrintIndent(i,s+"   "+string(i->kind.size()+i->text.size(),' '));
      i=i->right;
  }
}

/// print AST
void ASTPrint(AST *a)
{
  while (a!=NULL) {
    cout<<" ";
    ASTPrintIndent(a,"");
    a=a->right;
  }
}


int main() {
  root = NULL;
  ANTLR(parse(&root), stdin);
  ASTPrint(root);
  exec(&root);
}
>>

#lexclass START


// Tokens defined higher have a higher precedence
#token SPACE "[\ \n\t]" << zzskip();>>

#token ASIG  "\:\="
#token EQ    "\="
#token GT    "\<"
#token ADD   "\+|\-"
#token MULT  "\*|\/"
#token INPUT "INPUT"
#token PRINT "PRINT"
#token PUSH  "PUSH"
#token POP   "POP"
#token WHILE "WHILE"
#token DO    "DO"
#token IF    "IF"
#token THEN  "THEN"
#token ELSE  "ELSE"
#token END   "END"
#token OR    "OR"
#token NOT   "NOT"
#token INT   "[0-9]+"
#token ID    "[a-zA-Z][a-zA-Z0-9]*"

exec: parse;
parse: instrs <<#0=createASTlist(_sibling);>>;
instrs: (instr)*;

asig: input|lit;
input: INPUT^ ID;
lit: ID ASIG^ nexpr;

nexpr: nmult (ADD^ nmult)*;
nmult: natom (MULT^ natom)*;
natom: INT|ID;

instr: asig;
//print:;
//read:;
//push:;
//pop:;
//cond:;
//loop:;
//
//instr: print|read|push|pop|cond|loop|asig;
