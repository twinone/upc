#header
<<
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

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

  bool attached;
} Block;

vector<Block*> allBlocks;
map<string, AST*> functions;
map<string, Block*> blocks;
Block grid;

int heightAt(int x, int y);
Block* top(int x, int y);
int level(Block *b);
inline bool contains(Block *b, int x, int y);
void printBlock(Block *b, bool fancy);

inline int toInt(AST *a) { return atoi(a->text.c_str()); }

Block *newBlock() {
  Block *b;
  b = new Block;
  b->x = -1;
  b->y = -1;
  allBlocks.push_back(b);
  return b;
}

Block *namedBlock(AST *a) {
  return blocks[a->text];
}

// Attach block "b" to block "to"
void attach(Block *b, Block *to) {
  to->blocks.push_back(b);
	b->parent = to;
  b->attached = true;
}

// Detaches this block from it's parent and sets it's coordinates to (0,0)
// Size is left unchanged
void detach(Block *b) {
  if (b->parent != NULL) {
    Block *p = b->parent;
    vector<Block*>::iterator it = find(p->blocks.begin(), p->blocks.end(), b);
    if(it != p->blocks.end())
      p->blocks.erase(it);
    b->parent = NULL;
  }
  b->x = -1;
  b->y = -1;
  b->attached = false;
}

inline bool isDetached(Block *b) { return b->x != -1 && b->y != -1; }

// Get the block that contains (x,y)
Block *at(Block *b, int x, int y) {
  for (int i = 0; i < b->blocks.size(); i++) {
    if (contains(b->blocks[i], x, y)) return b->blocks[i];
  }
  return NULL;
}

// Gets the block that's on the top of the stack at the position (x,y)
Block *top(int x, int y) {
  Block *r = &grid;
  while (true) {
    Block *t = at(r, x, y);
    if (t == NULL) return r;
    r = t;
  }
}


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

// Processess and stores function definitions as plain AST
// If the AST is semantically incorrect it will throw a runtime error
// when executed, but not a compile-time error, because we do not analyze
// it until it's executed
void processDefs(AST *a) {
	a = a->down;
	while (a != NULL) {
		D(cerr<<"READ DEF "<<a->down->text<<endl;)
//		D(ASTPrint(a->down->right);)
		functions.insert(std::pair<string,AST*>(a->down->text,a->down->right));
		a = a->right;
	}
}

// Returns true if (x,y) is inside the block
inline bool contains(Block *b, int x, int y) {
  return x >= b->x && y >= b->y && x < b->x+b->w && y < b->y+b->h;
}

// returns true if the block b is completely contained inside block a
// That means you can place b on top of a without hanging edges
// this function does not check coordinates, only sizes
inline bool containsBlock(Block *a, Block *b) {
  return a->w >= b->w && a->h >= b->h;
}

// Returns n>=0 if you can physically place the block
// ontop of dst at the given coordinates (ignoring src's coords)
// If it cannot be placed, it returns -1
int canPlace(Block *src,  int x, int y) {
  Block *dst = top(x, y);
  int h = heightAt(x,y);
  for (int i = 0; i < src->h; i++) {
    for (int j = 0; j < src->w; j++) {
      if (heightAt(x+j, y+i) != h) {
        //D(cerr << "cannot place block: conflicts at ("<<x+j<<","<<y+i<<") expected"<<h<<", but got "<<(heightAt(x+j, y+i))<<endl;)
        return -1;
      }
    }
  }
  return h;
}

// returns true if one or more coordinates of a and b are common
bool intersects(Block *a, Block *b) {
  if (b->w < a->w || b->h < a->h) return false;

  // we check if one of the four corners of a is inside b or the other way around
  return contains(a, b->x, b->y) || contains(a, b->x+b->w, b->y)
    || contains(a, b->x, b->y+b->h) || contains(a, b->x+b->w, b->y+b->h)
    || contains(b, a->x, a->y) || contains(b, a->x+a->w, a->y)
    || contains(b, a->x, a->y+a->h) || contains(b, a->x+a->w, a->y+a->h);
}

Block *processPop(AST *a) {
  return NULL;
}
Block *processPush(AST *a) {
  AST *x = a->down;
  AST *y = x->right;
  Block *b1;
  if (x->kind == "list") { // block literal
    b1 = newBlock();
    b1->w = toInt(x->down);
    b1->h = toInt(x->down->right);
    D(cerr << "Created anonymous block of " << b1->w << "x" << b1->h << " for push" << endl;)
  }
  // else it's a named block
  else {
    b1 = namedBlock(x);
    D(cerr << "Named block " << x->text << " "<<"["<<b1->w<<"x"<<b1->h<<"]" << " for push" << endl;)
  }
  Block *b2 = namedBlock(y);
  int foundh = -1;
  int fx = 0;
  int fy = 0;
  for (int i = 0; i <= b2->h-b1->h; i++) {
    for (int j = 0; j <= b2->w-b1->w; j++) {
      int nh = canPlace(b1, b2->x+j, b2->y+i);
      if (foundh == -1 || (nh >= level(b2) && nh < foundh)) {
        //D(cerr << "got better pos for block ("<<j+b2->x<<","<<i+b2->y<<"): "<<nh<<" old was:"<<foundh<<endl;)
        fx = j+b2->x; fy = i+b2->y;
        foundh = nh;
      }
    }
  }
  if (foundh != -1) {
    D(cerr << "placed at ("<<fx<<","<<fy<<"): "<<endl;)

    detach(b1);
    b1->x = fx;
    b1->y = fy;
    attach(b1, top(fx, fy));
  } else {
    D(cerr << "no spot found for the block" << endl;)
  }
  return NULL;
}



Block *processPlace(AST *a) {
  Block *b = newBlock();

	AST *size = a->down;
	AST *coords = size->right;

	b->x = toInt(coords->down) -1;
	b->y = toInt(coords->down->right) -1;

	b->w = toInt(size->down);
	b->h = toInt(size->down->right);

  attach(b, &grid);
	return b;
}


void processAssig(AST *a) {
	string name = a->down->text;
	Block *b = new Block;
  a = a->down->right;
	switch (a->type) {
		case PLACE: b = processPlace(a); break;
    case PUSH: b = a->text == "PUSH" ? processPush(a) : processPop(a); break;
	}
	blocks.insert(std::pair<string, Block*>(name, b));
}



// Move moves the block and everything above it
void processMove(AST *a) {
  Block *b = namedBlock(a->down);
	if (b == NULL) {
		W(cout << "warning: ignoring instruction: block " << a->down->text << " undefined" << endl;)
		return;
	}
	string nesw = a->down->right->text;
  int num = toInt(a->down->right->right);
	int newX = b->x + getdx(a);
	int newY = b->y + getdy(a);
  // TODO checks
  b->x = newX; b->y = newY;
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

// Returns how many blocks are under this block
int level(Block *b) {
  if (b->parent == NULL) return 0;
  return level(b->parent) + 1;
}

// Returns the height at the specified position
// The height is defined as the number of blocks on top of it
// Counting from block b
int heightAt(int x, int y) {
  /*int n = 0;
  for (int i = 0; i < b->blocks.size(); i++) {
    Block bb = *b->blocks[i];
    if (contains(&bb, x,y)) {
      n += heightAt(&bb, x, y) + 1;
      break;
    }
  }


  return n;*/
  // Doesnt work with overlapping blocks
  /*return level(top(x,y));*/
  int n = 0;
  for (int i = 0; i < allBlocks.size(); i++) {
    if (allBlocks[i]->attached && contains(allBlocks[i], x, y)) n++;
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
      cout << heightAt(j, i);
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
//  ASTPrint(root);
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
