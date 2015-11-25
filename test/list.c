#include<list>
#include<iostream>

using namespace std;

int main()
{
  std:list<std::wstring> l;
  l.push_back("Some text pushed at back");
  l.push_front("Some text pushed at front");

  return 0;
 
}
