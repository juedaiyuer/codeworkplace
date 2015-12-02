
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>         //C++ 11 standard
 
using namespace std;
 
class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        unordered_map<int, int> umap;
        // initialize the variable with 0 to prevent none result

        vector<int> output(2);    // vector 2 data ,default data
        
        for (int i = 0; i < numbers.size(); i++)
        {
        	// Avoid the situations like 4 = 8 - 4
			if (umap.find(numbers[i]) != umap.end())
			{
				output[0] = umap[numbers[i]] + 1;   //
				output[1] = i + 1;
			}
			else
			{
				umap.insert(make_pair(target - numbers[i], i));  
			}
		}
		return output;
    }
};
 
int main()
{
	Solution s1;
	vector<int> numbers = {1,2,4,4,5};
	int target = 9;
	
	vector<int> output = s1.twoSum(numbers, target);
	cout << output[0] << " " << output[1] << endl;

	return 0;
}