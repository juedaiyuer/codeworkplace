#include<string>
#include<iostream>
#include<cstring>

using namespace std;

int main(){
	int num[256];
	memset[num,0,sizeof(num)];  // num chu shi hua 
	string s ("abceabef");

	int start =0,end = 0;
	int len = s.length();
	int ans =0;

	while(end<len && !num[s[end]]){
		num[s[end++]]++;
		cout<<num[s[end++]]++<<endl;
	}

	return 0;
}