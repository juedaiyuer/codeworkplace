#include<memory>
//#include<assert>
#include<iostream>

using namespace std;

int main(){
	
	shared_ptr<int> spi(new int(1024));
	cout<<"spi:"<<*spi<<'\n';
	
	return 0;
}
