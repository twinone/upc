#header
<<
#include <string>
#include <iostream>
using namespace std;

// struct to store information about tokens
typedef struct {
  string kind;
  string text;
  int type;
} Attrib;

typedef struct {
  int type;
  bool boolval;
  int intval;
} Variable;

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

map<string, Variable> vars;

// function to fill token information
void zzcr_attr(Attrib *attr, int type, char *text) {
  attr->text = text;

  if (type == NUM) attr->kind = "intconst";
  else if (type == BOOL) attr->kind = "boolconst";
  else if (type == TIMES || type == PLUS) attr->kind = "arit";
  else if (type == CMP) attr->kind = "cmp";

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

Variable evaluate(AST *a, bool &err) {
	Variable res;
	if (a == NULL) return res;
  string k = a->kind;
  string t = a->text;
	if (k == "intconst") {
		res.type = NUM;
		res.intval = atoi(a->text.c_str());
		return res;
	}
	if (k == "boolconst") {
		res.type = BOOL;
		res.boolval = a->text == "true";
		return res;
	}
	if (k == "arit") {
		res.type = NUM;
		Variable l = evaluate(child(a,0), err);
		Variable r = evaluate(child(a,1), err);
		if (l.type != NUM || r.type != NUM) { cerr << "operand " << k << " expects two values of type NUM" << endl; err = true; return res; }
		if (t == "+") res.intval = l.intval + r.intval;
		if (t == "-") res.intval = l.intval - r.intval;
		if (t == "*") res.intval = l.intval * r.intval;
		if (t == "/") res.intval = l.intval / r.intval;
		return res;
	}
	if (k == "cmp") {
		res.type = BOOL;
		Variable l = evaluate(child(a,0), err);
		Variable r = evaluate(child(a,1), err);
		if (l.type != NUM || r.type != NUM) { cerr << "operand " << k << " expects two values of type NUM" << endl; err = true; return res; }
  	if (t == "==") res.boolval = l.intval == r.intval;
		if (t == "<") res.boolval = l.intval < r.intval;
		if (t == "<=") res.boolval = l.intval <= r.intval;
		if (t == ">") res.boolval = l.intval > r.intval;
		if (t == ">=") res.boolval = l.intval >= r.intval;
		return res;
	}
	else { // variable
		map<string,Variable>::iterator it = vars.find(a->kind);
		if (it == vars.end()) {
			cerr << "error: '" << a->kind << "' undeclared" << endl;
			err = true;
			return res;
		}
		return it->second;
	}
}

AST *nextif(AST *a) {
  while (a->kind != "elif" && a->kind != "else" && a->kind != "fi") a = a->right;
  return a;
}

void execute(AST *a) {
	if (a == NULL) return;
  bool err;
  string k = a->kind;
  //cout << "kind " << k << endl;

  // Handled by if internally
  if (k == "elif" || k == "else" || k == "fi") return;

  // Handled by while internally
  if (k == "done") return;

	if (k == ":=") {
		Variable res = evaluate(child(a,1), err);
    if (err) return;
		vars[child(a,0)->kind] = res;
	}
	else if (k == "write") {
		Variable res = evaluate(child(a,0), err);
    if (err) return;
		if(res.type == NUM) cout << res.intval << endl;
		if(res.type == BOOL) cout << (res.boolval ? "true" : "false") << endl;
	}
  else if (k == "if") {
    Variable cond = evaluate(a->down, err);
    if (err) return;
    if (cond.type != BOOL) {
      cerr << "expected boolean expression at if" << endl;
      return;
    }
    // if true:
    if (cond.boolval) {
        execute(a->down->right);
    }
    // if false:
    else {
      AST *node = nextif(a->down);
      while (node->kind != "fi") {
        if (node->kind == "else") {
          execute(node->right);
          break;
        }
        if (node->kind == "elif") {
          cond = evaluate(node->right, err);
          if (err) return;
          if (cond.type != BOOL) {
            cerr << "expected boolean expression at elif" << endl;
            return;
          }
          // if true:
          if (cond.boolval) {
              execute(node->right->right);
              break;
          } else {
            node = node->right; // skip this elif block
          }
        }
        node = nextif(node);
      }
    }
  } else if (k == "while") {
    while (true) {
      Variable cond = evaluate(a->down, err);
      if (err) return;
      if (cond.type != BOOL) {
        cerr << "expected boolean expression at while" << endl;
        return;
      }
      // if true:
      if (!cond.boolval) break;
      execute(a->down->right);
    }
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
#token BOOL "true|false"

#token PLUS "\+|\-"
#token TIMES "\*|\/"
#token CMP "(\=\=)|(\<)|(\<\=)|(\>)|(\>\=)"

#token IF "if"
#token THEN "then"
#token ELIF "elif"
#token ELSE "else"
#token FI "fi"

#token WHILE "while"
#token DO "do"
#token DONE "done"

#token LPAREN "\("
#token RPAREN "\)"
#token SPACE "[\ \n]" << zzskip(); >>

#token WRITE "write"
#token ID "[a-zA-Z]"
#token ASIG ":="

prog: (instr)* "@"!;
instr: (ID ASIG^ expr | WRITE^ expr) | cond | loop;
loop: WHILE^ expr DO! (instr)* DONE;
cond: IF^ expr THEN! (instr)* (ELIF expr THEN! (instr)*)* (ELSE (instr)*|) FI;

expr: cmp;
cmp: arit (CMP^ arit)*;
arit: term (PLUS^ term)*;
term: base (TIMES^ base)*;
par: LPAREN! cmp RPAREN!;
base: par|NUM|ID|BOOL;
