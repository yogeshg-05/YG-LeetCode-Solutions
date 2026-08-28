class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        int odd = -1;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                if (odd != -1)
                    return "";
                odd = i;
            }
        }

        string mid = odd == -1 ? "" : string(1, char('a' + odd));

        vector<int> half(26);
        for (int i = 0; i < 26; i++)
            half[i] = cnt[i] / 2;

        int m = s.size() / 2;
        string t = target.substr(0, m);

        vector<int> rem = half;
        string best = "";

        for (int i = 0; i < m; i++) {
            int x = t[i] - 'a';

            for (int c = x + 1; c < 26; c++) {
                if (rem[c] > 0) {
                    vector<int> temp = rem;
                    temp[c]--;

                    string left = t.substr(0, i);
                    left += char('a' + c);

                    for (int k = 0; k < 26; k++)
                        left += string(temp[k], char('a' + k));

                    best = left;
                    break;
                }
            }

            if (rem[x] == 0)
                break;

            rem[x]--;
        }

        bool possible = true;

        for (int x : rem) {
            if (x != 0) {
                possible = false;
                break;
            }
        }

        if (possible) {
            string candidate = t + mid + string(t.rbegin(), t.rend());

            if (candidate > target)
                return candidate;
        }

        if (best != "")
            return best + mid + string(best.rbegin(), best.rend());

        return "";
    }
};