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
 as->kind="seq";
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
void print(AST *a);
// print with parentheses or not if it's a leaf
void ppl(AST *a) {
  cout << "("; print(a); cout << ")";
}

void printBexpr(AST *a);

void ppb(AST *a) {
  cout << "("; printBexpr(a); cout << ")";
}

void printBexpr(AST *a) {
  if (a->type == OR||a->type == AND) {
    cout << (a->type == OR ? "OR" : "AND") << " ";
    ppb(a->down); cout << " ";
    ppb(a->down->right);
  }
  else if (a->type == NOT) {
    cout << "NOT" << " ";
    ppb(a->down);
  }
  else if (a->type == BOP) {
    cout << (a->text == ">" ? "Gt" : "Eq") << " ";
    ppb(a->down); cout << " ";
    ppb(a->down->right);
  }
  else if (a->type == ID) { cout << "Var "<< '"' << a->text << '"'; }
  else if (a->type == INT) { cout << "Const " << a->text; }
  else if (a->type == ADD) {
    cout << (a->text=="+"?"Plus":"Minus") << " ";
    cout << "("; printBexpr(a->down);        cout << ") ";
    cout << "("; printBexpr(a->down->right); cout << ")";
  }
  else if (a->type == MULT) {
    cout << "Times ";
    cout << "("; printBexpr(a->down);        cout << ") ";
    cout << "("; printBexpr(a->down->right); cout << ")";
  }
}
/// print AST, recursively, with indentation
void print(AST *a) {
  if (a==NULL) return;
  if (a->kind == "seq") {
    cout << "Seq [";
    AST *i = a->down;
    while (i != NULL) {
      print(i);
      if (i->right != NULL) cout << ", ";
      i = i->right;
    }
    cout << "]";
  }
  else if (a->type == ASSIGN) {
    cout << "Assign " << '"' << a->down->text << '"';
    cout << " ";
    cout << "(";
    printBexpr(a->down->right);
    cout << ")";
  }
  else if (a->type == ID) { cout << "Var "<< '"' << a->text << '"'; }
  else if (a->type == INT) { cout << "Const " << a->text; }
  else if (a->type == PRINT) { cout << "Print " << '"' << a->down->text << '"'; }
  else if (a->type == INPUT) { cout << "Input " << '"' << a->down->text << '"'; }
  else if (a->type == EMPTY) { cout << "Empty " << '"' << a->down->text << '"'; }
  else if (a->type == POP) { cout << "Pop " << '"' << a->down->text << "\" \"" << a->down->right->text << '"'; }
  else if (a->type == SIZE) { cout << "Size " << '"' << a->down->text << "\" \"" << a->down->right->text << '"'; }
  else if (a->type == PUSH) {
    cout << "Push " << '"' << a->down->text << '"' << " ";
    cout << "(";
    printBexpr(a->down->right);
    cout << ")";
  }
  else if (a->type == IF) {
    cout << "Cond ";
    cout << "("; printBexpr(a->down); cout << ") "; // bool
    if (a->down->right == NULL) cout << "(Seq []) ";
    else { cout << "("; print(a->down->right); cout << ") "; }
    if (a->down->right->right == NULL) cout << "(Seq [])";
    else { cout << "("; print(a->down->right->right); cout << ")"; }
  }
  else if (a->type == WHILE) {
    cout << "Loop ";
    cout << "("; printBexpr(a->down); cout << ") "; // bool
    if (a->down->right == NULL) cout << "(Seq [])";
    else { cout << "("; print(a->down->right); cout << ")"; }
  }
}
/// print AST
void ASTPrint2(AST *a)
{

  cout <<  endl << endl;
  cout << "(";
  while (a!=NULL) {
    print(a);
    a=a->right;
  }
  cout << ")";

  cout <<  endl << endl;

  //cout << endl << ")" << endl;
}


int main(int argc, char **argv) {
  ANTLR(parse(&root), stdin);
  if (argc == 1)
    ASTPrint(root);
  ASTPrint2(root);
}
>>

#lexclass START

// Tokens defined higher have a higher precedence
#token SPACE "[\ \n\t]" << zzskip();>>

#token ASSIGN  "\:\="
#token BOP    "\=|\>"
#token ADD   "\+|\-"
#token MULT  "\*"
#token INPUT "INPUT"
#token EMPTY "EMPTY"
#token PRINT "PRINT"
#token SIZE "SIZE"
#token PUSH  "PUSH"
#token POP   "POP"
#token WHILE "WHILE"
#token DO    "DO"
#token IF    "IF"
#token THEN  "THEN"
#token ELSE  "ELSE"
#token END   "END"
#token OR    "OR"
#token AND   "AND"
#token NOT   "NOT"
#token INT   "[0-9]+"
#token ID    "[a-zA-Z][a-zA-Z0-9]*"

exec: parse;
parse: seq;
seq: (command)* <<#0=createASTlist(_sibling);>>;

asig: input|empty|lit|size;
empty: EMPTY^ ID;
input: INPUT^ ID;
lit: ID ASSIGN^ nexpr;
size: SIZE^ ID ID;

nexpr: nfact (ADD^ nfact)*;
nfact: natom (MULT^ natom)*;
natom: INT|ID;

print: PRINT^ ID;


/////////////////////////
cond: IF^ bexpr cond_then cond_else END!;
// Note that it's allowed,
// like in regular programming languages,
// to have an empty ifs
cond_then: (THEN! seq|);
cond_else: (ELSE! seq|);

loop: WHILE^ bexpr DO! seq END!;

bexpr: band (OR^ band)*;
band: batom2 (AND^ batom2)*;
batom2: batom|NOT^ batom2;
batom: (nexpr BOP^ nexpr)|"true"|"false";

push: PUSH^ ID nexpr;
pop: POP^ ID ID;

command: asig|print|cond|loop|push|pop;
