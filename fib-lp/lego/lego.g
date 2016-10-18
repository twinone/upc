#header
<<
#include <string>
#include <iostream>
#include <map>
#include <vector>

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

#define WARN
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
  attr->text = text;
  attr->type = type;

// This is bullshit
/*  if (type == ID) attr->kind = "id";

  else {
    attr->kind = text;
    attr->text = "";
  }
*/
}

// function to create a new AST node
AST* createASTnode(Attrib* attr, int type, char* text) {
  AST* as = new AST;
  as->kind = attr->kind;
  as->text = attr->text;
  as->type = attr->type; // We want this
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

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


typedef struct Block {
  // global coordinates of block
	int x; int y;
  // dimensions of block
	int w; int h;
	// Blocks stacked on top of this one
	vector<Block*> blocks;
	// The block below this one
	Block* parent;
} Block;

vector<Block*> allBlocks;
map<string, AST*> functions;
map<string, Block*> blocks;
Block grid;

inline int toInt(AST *a) { return atoi(a->text.c_str()); }

inline int getdx(AST *a) {
  string s = a->down->right->text;
  int num = toInt(a->down->right->right);
	if (s == "NORTH"||s == "SOUTH") return 0;
	return (s == "EAST" ? 1 : -1) * num;
}

inline int getdy(AST *a) {
  string s = a->down->right->text;
  int num = toInt(a->down->right->right);
	if (s == "EAST"||s == "WEST") return 0;
	return (s == "SOUTH" ? 1 : -1) * num;
}


void initGrid(AST *a) {
	grid.x = 0;
	grid.y = 0;
	grid.w = toInt(a->down);
	grid.h = toInt(a->down->right);
	D(cerr << "Initialized grid of " << grid.w << "x" << grid.h << endl;)
}

void processDefs(AST *a) {
	a = a->down;
	while (a != NULL) {
		D(cerr<<"READ DEF "<<a->down->text<<endl;)
//		D(ASTPrint(a->down->right);)
		functions.insert(std::pair<string,AST*>(a->down->text,a->down->right));
		a = a->right;
	}
}



Block *processPlace(AST *a) {
	Block *b;
  b = new Block;
  allBlocks.push_back(b);

	AST *size = a->down;
	AST *coords = size->right;

	b->x = toInt(coords->down) -1;
	b->y = toInt(coords->down->right) -1;

	b->w = toInt(size->down);
	b->h = toInt(size->down->right);

	grid.blocks.push_back(b);
	b->parent = &grid;

	return b;
}


void processAssig(AST *a) {
	string name = a->down->text;
	Block *b = new Block;
  a = a->down->right;
	switch (a->type) {
		case PLACE: b = processPlace(a); break;
	}
	blocks.insert(std::pair<string,Block*>(name, b));
}

// Returns true if you can place a wxh block at (x, y)
// on Block b
bool canPlace(Block *b, int x, int y, int w, int h) {

}


// Move moves the block and everything above it
void processMove(AST *a) {
	string name = a->down->text;
	Block *b = blocks[name];
	if (b == NULL) {
		W(cout << "warning: ignoring instruction: block " << name << " undefined" << endl;)
		return;
	}
	string nesw = a->down->right->text;
  int num = toInt(a->down->right->right);
	int newX = b->x + getdx(a);
	int newY = b->y + getdy(a);
  b->x = newX; b->y = newY;

  Block bbb = *grid.blocks[0];
}

void exec(AST *a) {
	a = a->down;
	while (a != NULL) {
		switch (a->type) {
			case ASSIG: processAssig(a); break;
			case MOVE: processMove(a); break;
		}
		a = a->right;
	}
}

// Returns true if (x,y) is inside the block (in parent's coordinate system)
inline bool contains(Block *b, int x, int y) {
  return x >= b->x && y >= b->y && x < b->x+b->w && y < b->y+b->h;
}
// Returns the height at the specified position
int heightAt(Block *b, int x, int y) {
  int n = 0;
  for (int i = 0; i < b->blocks.size(); i++) {
    Block bb = *b->blocks[i];
    if (contains(&bb, x,y)) {
      n += heightAt(&bb, x, y) + 1;
      break;
    }
  }
  return n;
}

// Debug function to print a block's heights
void printBlock(Block *b, bool fancy) {
#ifdef DEBUG
	if (fancy) cout << "+";
	if (fancy)  for (int i = 0; i < b->w*2-1; i++) cout << (i%2==0?"-":"+");
	if (fancy)  cout << "+" << endl;

	for (int i = 0; i < b->h; i++) {
		for (int j = 0; j < b->w; j++) {
			if (fancy) cout << "|";
      cout << heightAt(&grid, j, i);
      if (!fancy) cout << " ";
		}
		if (fancy) cout << "|" << endl;
		if (fancy) cout << "+";
		if (fancy) for (int i = 0; i < b->w*2-1; i++) cout << (i%2==0?"-":"+");
		if (fancy) cout << "+";
    cout << endl;
	}
#endif
}

int main() {
  root = NULL;
  ANTLR(lego(&root), stdin);
  initGrid(root->down);
  processDefs(root->down->right->right);
  exec(root->down->right);
  ASTPrint(root);
  printBlock(&grid, false);
}
>>

#lexclass START


// Tokens defined higher have a higher precedence
#token SPACE "[\ \n\t]" << zzskip();>>
#token BOOL "true|false" // placeholder
#token AND "AND"
#token MOVE "MOVE"
#token FITS "FITS"
#token HEIGHT "HEIGHT"
#token NESW "NORTH|EAST|SOUTH|WEST"
#token GRID "Grid|GRID"
#token DEF "DEF"
#token PLACE "PLACE"
#token ENDEF "ENDEF|ENDDEF"
#token WHILE "WHILE"
#token AT "AT"
#token CMP "\<|\>|\<\=|\>\=|\=\=|\!\="
#token ASSIG "\="
#token LPAREN "\("
#token RPAREN "\)"
#token LSQUARE "\["
#token RSQUARE "\]"
#token COMMA "\,"
#token PUSH "PUSH|POP"
#token INT "[0-9]+"
#token ID "[a-zA-Z][a-zA-Z0-9]*"



def: DEF^ ID ops ENDEF!;

lego: griddef ops defs <<#0=createASTlist(_sibling);>>;
ops: (op)* <<#0=createASTlist(_sibling);>>;
defs: (def)* <<#0=createASTlist(_sibling);>>;

griddef: GRID^ INT INT;
op: move|while_loop|fits|height|assig;


assig: ID (ASSIG^ blockexpr|);


fits: FITS^ LPAREN! ID COMMA! INT COMMA! INT COMMA! INT RPAREN!;
height: HEIGHT^ LPAREN! block RPAREN!;

boolexpr: booland;
booland: boolatom (AND^ boolatom)*;
boolatom: BOOL|boolcmp|fits;
boolcmp: intexpr (CMP^ intexpr|);
intexpr: INT | height;

while_loop: WHILE^ LPAREN! boolexpr RPAREN! LSQUARE! ops RSQUARE!;
move: MOVE^ ID NESW INT;

coords: LPAREN! INT COMMA! INT RPAREN! <<#0=createASTlist(_sibling);>>;
blockexpr: place|push;
place: PLACE^ coords AT! coords;

push: block (PUSH^ ppr);
ppr: ID (PUSH^ ppr|);

block: ID|coords;
