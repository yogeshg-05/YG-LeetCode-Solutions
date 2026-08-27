class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        vector<int> sc(26), pc(26);
        
        for (char c : s)
            sc[c - 'a']++;
        
        int n = target.size();
        
        for (int i = 0; i < n; i++)
            pc[target[i] - 'a']++;
        
        for (int i = n - 1; i >= 0; i--) {
            pc[target[i] - 'a']--;
            
            bool possible = true;
            for (int j = 0; j < 26; j++) {
                if (pc[j] > sc[j]) {
                    possible = false;
                    break;
                }
            }
            
            if (!possible)
                continue;
            
            int x = target[i] - 'a';
            
            for (int c = x + 1; c < 26; c++) {
                if (sc[c] > pc[c]) {
                    string ans = target.substr(0, i);
                    ans += char('a' + c);
                    
                    vector<int> rem = sc;
                    
                    for (int j = 0; j < i; j++)
                        rem[target[j] - 'a']--;
                    
                    rem[c]--;
                    
                    for (int j = 0; j < 26; j++)
                        ans += string(rem[j], char('a' + j));
                    
                    return ans;
                }
            }
        }
        
        return "";
    }
};