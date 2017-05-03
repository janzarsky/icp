#include<iostream>
#include<vector>

using namespace std;


class A{
	int a;
	protected:
		int b=9;
	public:
		int c;
		static int st;
		A(){};
		A(int cisla){c = cisla;}

};

class B:public A{
	vector<int> vec  {1,2,3};
	public:
		int cislo = 10;
	B makeb(){
		B temp;
		temp.cislo =11;
		return temp;
	}
	vector<int> & GetVec(){
		return this->vec;
	}
	B(){cout<<"B construcror"<<endl;}
	B(int k){c = k;}
	B(B const & ){cout<<"B copy constructor"<<endl;}
	B& operator=(B const &){cout<<"B operator ="<<endl;}
};


int A::st = 100;
int main(){
	int b = 10;
	int * a = &b;

	vector<int> vec;
	cout<<vec.size()<<endl;

	return 0;
}
