#include<iostream>
#include<vector>
#include <algorithm>
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include <stdlib.h>

using namespace std;

int main(){

	stringstream stream;
	char line [50];
	string str {"10,3,D1,H11,S2,C9\n gegege \n hehe\t123"};
	stream.str(str);
	ifstream ifile;
	ifile.open("../q");

	while(ifile.getline(line,49)){
		// stringstream ln;
		// ln.str(string(line));
		// cout<<"line:"<<line<<endl;
		// char buf[10];
		// int size, shownCards;
		// ln.getline(buf,9,',');
		// size = atoi(buf);
		// ln.getline(buf,9,',');
		// shownCards = atoi(buf);
		// cout<<"size: "<<size<<" shown: "<<shownCards<<endl<<"cards: ";
		// while(ln.getline(buf,9,',')){
		// 	cout<<buf<<' ';
		// }
		// cout<<endl;
		cout<<line<<'|'<<endl;
	}
	return 0;
}
