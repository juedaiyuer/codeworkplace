/*
    1.have some problems
    2.not run test 
*/

class Solution {
public:
    string convert(string s, int nRows) {
        string result;
        if (nRows < 2) return s;
        for (int i = 0;i < nRows;i++) {
            for (int j = i;j < s.length();j += 2 * (nRows - 1)) {       //s[j]位于首行的位置，首行相距为2*（nRows-1）
                result.push_back(s[j]);                                         
                if (i > 0 && i < nRows - 1) {                                 // i代表着行数,
                    if (j + 2 * (nRows - i - 1) < s.length())
                        result.push_back(s[j + 2 * (nRows - i - 1)]);
                }
            }
        }
        return result;
    }
};