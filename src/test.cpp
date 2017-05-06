#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;

int main(){
	vector<int> vec {1,2,3,4,5};
	
	random_shuffle(vec.begin(), vec.end());
	for(int i : vec) cout<<i<<' ';
	cout<<endl;
	return 0;
}
