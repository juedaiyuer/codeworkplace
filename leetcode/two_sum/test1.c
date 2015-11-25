#include<vector>
#include<algorithm>
#include<iostream>

/*
  1.leetcode for two sum---no.1
  2.the method of two pointer
  3.input not sort  
  4. author by wsh
*/

using namespace std;

class Solution 
{
    public:
            vector<int> twoSum(vector<int> &numbers, int target) {
            int sz = numbers.size();
            int left = 0, right = sz - 1, sum = 0;

            vector<int> sorted (numbers);       //vector copy
            sort(sorted.begin(), sorted.end());

            vector<int> index;                          //empty vector of index 
            while (left < right) {
                sum = sorted[left] + sorted[right];
                   if (sum == target) {
                            // find the answer
                          for (int i = 0; i < sz; i++) {                         
                                if (numbers[i] == sorted[left])
                                    index.push_back(i + 1);
                                else if (numbers[i] == sorted[right])
                                    index.push_back(i + 1);
                                if (index.size() == 2)
                                    return index; 
                          }                                 
                    }
                   else if (sum > target) 
                    {
                        right--;
                    } 
                    else 
                    {
                        left++;
                    }
            }
};

void main()
{
  cout<<" test of two pointer"<<endl;
}
