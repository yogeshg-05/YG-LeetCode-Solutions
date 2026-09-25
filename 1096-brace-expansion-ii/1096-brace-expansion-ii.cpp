class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        set<string> result;

        function<set<string>(int&, int)> parseExpr;
        function<set<string>(int&, int)> parseTerm;
        function<set<string>(int&, int)> parseFactor;

        parseFactor = [&](int& i, int end) -> set<string> {
            set<string> res;

            if (expression[i] == '{') {
                i++;
                res = parseExpr(i, end);
                i++;
            } else {
                res.insert(string(1, expression[i]));
                i++;
            }

            return res;
        };

        parseTerm = [&](int& i, int end) -> set<string> {
            set<string> res = {""};

            while (i < expression.size() &&
                   expression[i] != '}' &&
                   expression[i] != ',') {

                set<string> next = parseFactor(i, end);
                set<string> temp;

                for (const string& a : res)
                    for (const string& b : next)
                        temp.insert(a + b);

                res = temp;
            }

            return res;
        };

        parseExpr = [&](int& i, int end) -> set<string> {
            set<string> res;

            while (i < expression.size() && expression[i] != '}') {
                set<string> term = parseTerm(i, end);
                res.insert(term.begin(), term.end());

                if (i < expression.size() && expression[i] == ',')
                    i++;
            }

            return res;
        };

        int i = 0;
        result = parseExpr(i, expression.size());

        return vector<string>(result.begin(), result.end());
    }
};