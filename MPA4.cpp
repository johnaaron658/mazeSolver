#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

enum block { wall, origin, space, goal, path };

class square{
public:
	block type;
	bool visited;
	int x,y;
	string c;
	square();
	square(char c,int,int);
};

//problems: change c when type changes.

square::square(){
	this->c = "";
	type = wall;
}

square::square(char c,int x,int y){
	char c_arr[2];
	c_arr[0] = c; c_arr[1] = '\0';
	this->c = string(c_arr);
	this->x = x;
	this->y = y;
	if(c == '#') type = wall;
	else if(c == 'o') type = origin;
	else if(c == '.') type = space;
	else if(c == '*') type = goal;
	else if(c == 'x') type = path;
	visited = false;
}

class maze{
public:
	int m,n;
	int or_x,or_y;
	square **map;
	maze(list);
	~maze();
	string toString();
};

maze::maze(vector<string> s){
	m = s.size();
	n = s[0].size();
	map = new square*[m];
	for(int i = 0; i < m; i++){
		map[i] = new square[n];
		for(int j = 0; j < n; j++){
			map[i][j] = square(s[i][j],i,j);
			if(map[i][j].type == origin){
				or_x = i; or_y = j;
			}
		}
	}
}

maze::~maze(){
	for(int i = 0; i < m ; i++)
		delete[] map[i];
	delete[] map;
}

string maze::toString(){
	string s = "";
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++)
			s = s+map[i][j].c;
		s = s+"\n";
	}
	return s;
}

template <class T>
class agenda{
private:
	T *adt;
	int type;
public:
	agenda();
	~agenda(){delete adt;}
	void add(square a){adt->push(a);}
	bool del(){adt->pop();}
	bool isEmpty(){return adt->empty();}
	int getSize(){return adt->size();}
	square peek();
};

template <class T>
agenda<T>::agenda(){
	adt = new T();
	string t1 = typeid(*adt).name();
	string t2 = typeid(stack<square>).name();
	string t3 = typeid(queue<square>).name();
	if(t1.compare(t2)==0) type = 1;
	else if(t1.compare(t3)==0) type = 2;
}

template <class T>
agenda<T>::peek(){
	if(type == 1) adt->top();
	else adt->front();
}

template <class T>
class mazeSolver{
private:
	agenda *a;
	maze *m;
	stack<square> track;
public:
	mazeSolver();
	~mazeSolver();
	void solve();
	void writeSolution(string);
};

mazeSolver<T>::mazeSolver(vector<string> s){
	m = new maze(s);
	a = new agenda<T>();
}

mazeSolver<T>::~mazeSolver(){
	delete m;
	delete a;
}

void mazeSolver<T>::solve(){
	int x = m.or_x;
	int y = m.or_y;
	bool flag;
	while(m.map[x][y].type != goal){
		flag = true;
		if(m.map[x-1][y].type != wall || !m.map[x-1][y].visited) x--; // left check.
		else if(m.map[x][y-1].type != wall || !m.map[x][y-1].visited) y--; // top check.
		else if(m.map[x+1][y].type != wall || !m.map[x+1][y].visited) x++; // right check.
		else if(m.map[x][y+1].type != wall || !m.map[x][y+1].visited) y++; // bottom check.
		else{
			a.del();
			track.pop();
			flag = false;
			m.map[]
		}
		if(flag){
			a.add(m.map[x][y]);
			track.push(m.map[x][y]);
			m.map[x][y].visited = true;
			m.map[x][y].type = path;
		}
		if(m.map[x][y].type == origin) break;
	}
}

void writeSolution(string s){

}

int main(){
	int x;
	ifstream input("maze.in");
	input >> x; // n is the number of test cases.
	for(int i = 0; i < x; i++){
		int m,n;
		input >> m;
		input >> n;
		vector<string> sList;
		for(int j = 0; j < m; j++){
			string s;
			input >> s;
			sList.push_back(s);
		}
		mazeSolver<queue<square> > m(s);
		mazeSolver<
		m.solve();
	}
	input.close();
	return 0;
}
