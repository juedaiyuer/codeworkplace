#include<string>
#include<cstring>
#include<iostream>

using namespace std;
/*

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
                num[s[end++]]++;
            }
            if (end - start > ans) {
                ans = end - start;
            }
            if (end >= len) {
                break;
            }
            while (num[s[end]]) {
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