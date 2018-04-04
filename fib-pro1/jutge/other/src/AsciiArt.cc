#include <iostream>
#include <string>
#include <sstream>


using namespace std;
const string a[] = {
	"#####",
	"#   #",
	"#####",
	"#   #",
	"#   #"
};
const string b[] = {
	"####.",
	"#   #",
	"####.",
	"#   #",
	"#####"
};
const string c[] = {
	" ####",
	"#    ",
	"#    ",
	"#    ",
	" ####"
};
const string d[] = {
	"#### ",
	"#   #",
	"#   #",
	"#   #",
	"#### "
};
const string e[] = {
	"#####",
	"#    ",
	"#####",
	"#    ",
	"#####"
};
const string f[] = {
	"#####",
	"#    ",
	"###  ",
	"#    ",
	"#    "
};
const string g[] = {
	"#####",
	"#   ",
	"#  ##",
	"#   #",
	"#### "
};
const string h[] = {
	"#   #",
	"#   #",
	"#####",
	"#   #",
	"#   #"
};
const string i[] = {
	"#####",
	"  #  ",
	"  #  ",
	"  #  ",
	"#####"
};
const string j[] = {
	"#####",
	"    #",
	"    #",
	"    #",
	"#### "
};
const string k[] = {
	"#  #",
	"# # ",
	"##  ",
	"# # ",
	"#  #"
};
const string l[] = {
	"#    ",
	"#    ",
	"#    ",
	"#    ",
	"#####"
};
const string m[] = {
	"#    #",
	"##  ##",
	"# ## #",
	"#    #",
	"#    #"
};
const string n[] = {
	"#   #",
	"##  #",
	"# # #",
	"#  ##",
	"#   #"
};
const string o[] = {
	"#####",
	"#   #",
	"#   #",
	"#   #",
	"#####"
};
const string p[] = {
	"#####",
	"#   #",
	"#####",
	"#    ",
	"#    "
};

const string q[] = {
	"#####",
	"#   #",
	"# # #",
	"#  ##",
	"#####"
};
const string r[] = {
	"#### ",
	"#   #",
	"#### ",
	"#  # ",
	"#   #"
};
const string s[] = {
	"#####",
	"#    ",
	"#####",
	"    #",
	"#####"
};
const string t[] = {
	"#####",
	"  #  ",
	"  #  ",
	"  #  ",
	"  #  "
};
const string u[] = {
	"#   #",
	"#   #",
	"#   #",
	"#   #",
	"#####"
};
const string v[] = {
	"#   #",
	"#   #",
	" #  #",
	"  # #",
	"    #"
};
const string w[] = {
	"#   #",
	"#   #",
	"# # #",
	"# # #",
	"#####"
};
const string x[] = {
	"#   #",
	" # # ",
	"  #  ",
	" # # ",
	"#   #"
};
const string y[] = {
	"#   #",
	" # # ",
	"  #  ",
	"  #  ",
	"  #  "
};
const string z[] = {
	"#####",
	"   # ",
	"  #  ",
	" #   ",
	"#####"
};

const string space[] = {
	"     ",
	"     ",
	"     ",
	"     ",
	"     "
};




const string strings[][5] = {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,space};

int getIndex(char character) {
	if (character >= 'a' && character <= 'z')
		return character - 'a';
	return getIndex('z')+1;
}

int main() {

	string text;
	getline(cin, text);

	int size = text.size();
	cout << endl;
	for (int line = 0; line < 5; line++) {
		for (int index = 0; index < size; index++) {
			char character = text[index];
			int idx = getIndex(character);
			cout << strings[idx][line] << " ";
		}
		cout << endl;
	}
	cout << endl;



	return 0;
}


