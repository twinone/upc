#header
<<
#include <string>
#include <iostream>
using namespace std;

// struct to store information about tokens
typedef struct {
  string kind;
  string text;
} Attrib;

// function to fill token information (predeclaration)
void zzcr_attr(Attrib *attr, int type, char *text);

// fields for AST nodes
#define AST_FIELDS string kind; string text;
#include "ast.h"

// macro to create a new AST node (and function predeclaration)
#define zzcr_ast(as,attr,ttype,textt) as=createASTnode(attr,ttype,textt)
AST* createASTnode(Attrib* attr, int ttype, char *textt);
>>

<<
#include <cstdlib>
#include <cmath>
#include <map>

map<string, int> vars;

// function to fill token information
void zzcr_attr(Attrib *attr, int type, char *text) {
  if (type == NUM) {
    attr->kind = "intconst";
    attr->text = text;
  }
  else {
    attr->kind = text;
    attr->text = "";
  }
}

// function to create a new AST node
AST* createASTnode(Attrib* attr, int type, char* text) {
  AST* as = new AST;
  as->kind = attr->kind; 
  as->text = attr->text;
  as->right = NULL; 
  as->down = NULL;
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

int evaluate(AST *a, bool &err) {
	if (a == NULL) return 0;
	else if (a->kind == "intconst")
		return atoi(a->text.c_str());
	else if (a->kind == "+")
		return evaluate(child(a,0), err) + evaluate(child(a,1), err);
	else if (a->kind == "-")
		return evaluate(child(a,0), err) - evaluate(child(a,1), err);
	else if (a->kind == "*")
		return evaluate(child(a,0), err) * evaluate(child(a,1), err);
	else if (a->kind == "/")
		return evaluate(child(a,0), err) / evaluate(child(a,1), err);
	else { // variable
		map<string,int>::iterator it = vars.find(a->kind);
		if (it == vars.end()) {
			cerr << "error: '" << a->kind << "' undeclared" << endl;
			err = true;
			return 0;
		}
		return it->second;
	}
}

void execute(AST *a) {
	if (a == NULL) return;
	if (a->kind == ":=") {
		bool err;
		int res = evaluate(child(a,1), err);
		if (!err) vars[child(a,0)->kind] = res;
		else return;
	}
	else if (a->kind == "write") {
		bool err;
		int res = evaluate(child(a,0), err);
		if (!err) cout << res << endl;
		else return;
	}
	execute(a->right);
}

int main() {
	AST *root = NULL;
	ANTLR(prog(&root), stdin);
	cout << "==================== AST =======================" << endl;
	ASTPrint(root);
	cout << "===============  EXECUTION  ====================" << endl;
	execute(root);
}

>>


#lexclass START
#token NUM "[0-9]+"
#token PLUS "\+|\-"
#token TIMES "\*|\/"
#token LPAREN "\("
#token RPAREN "\)"
#token OP "\+|\-|\*|\/"
#token SPACE "[\ \n]" << zzskip(); >>

#token WRITE "write"
#token ID "[a-zA-Z]"
#token ASIG ":="


prog: (instr)* "@"!;
instr: (ID ASIG^ expr | WRITE^ expr);

expr: term (PLUS^ term)*;
term: base (TIMES^ base)*;
par: LPAREN! expr RPAREN!;
base: par|NUM|ID;
