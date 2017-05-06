#include<iostream>
#include<vector>

using namespace std;

int main(){
	for(int i = 0; i<= 10;i++){
		cout<<" "<<i;
		if(i== 5){
			i = 9;
			continue;
		}
	}

	return 0;
}
