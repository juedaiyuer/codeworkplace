#include<string>
#include<cstring>
#include<iostream>

using namespace std;
/*
    1.wsh
    2.leetcode id=3
*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int num[256];
        memset(num, 0, sizeof(num));
        int start = 0, end = 0;
        int len = s.length();
        int ans = 0;
        while (true) {
            while (end < len && !num[s[end]]) { 
                /*
                    1.s[end]='a' or 'b'  or 'c' ...
                    2.num[s[end]],eg->num[a]=num[97],'a'->data
                    3.check character is repeated
                */
                num[s[end++]]++;
            }
            if (end - start > ans) {
                /*
                    1.判断最大子字符串
                */
                ans = end - start;
            }
            if (end >= len) {
                break;
            }
            while (num[s[end]]) {
                /*
                    1.当有重复字符出现的时候，start+1,下一个字符为起始位置重新遍历

                */
                num[s[start++]]--;
            }
        }
        return ans;
    }
};

int main(){
    Solution s1;
    string s("abcdabc");

    cout<<s1.lengthOfLongestSubstring(s);
    return 0;
}