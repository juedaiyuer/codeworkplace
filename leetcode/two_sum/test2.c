
#include<string.h>        //memset 

const int N = 200002;
const int OFFSET = 100000;

class Solution {
    private:
        int idOfNum[N];
    public:
        vector<int> twoSum(vector<int> &numbers, int target) {
            vector<int> index;
            memset(idOfNum, 0, sizeof(idOfNum));      //array of idOfNum  

            int sz = numbers.size();
            for (int i = 0; i < sz; i++) {
                int rest = target - numbers[i];
                if (idOfNum[rest + OFFSET]) {
                    index.push_back(idOfNum[rest + OFFSET]);
                    index.push_back(i + 1);
                    return index;
                }
                idOfNum[numbers[i] + OFFSET] = i + 1;
            }
          
        }
};