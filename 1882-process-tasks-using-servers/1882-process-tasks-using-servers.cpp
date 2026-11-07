
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        // {weight, server index}
        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> available;

        // {free time, weight, server index}
        priority_queue<tuple<long long, int, int>,
                       vector<tuple<long long, int, int>>,
                       greater<tuple<long long, int, int>>> busy;

        int n = servers.size();
        vector<int> ans;

        // Initially, all servers are available.
        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        long long time = 0;

        for (int i = 0; i < tasks.size(); i++) {
            time = max(time, (long long)i);

            // Release all servers that have finished.
            while (!busy.empty() &&
                   get<0>(busy.top()) <= time) {
                auto [freeTime, weight, idx] = busy.top();
                busy.pop();

                available.push({weight, idx});
            }

            // Wait until the earliest server becomes free.
            if (available.empty()) {
                time = get<0>(busy.top());

                while (!busy.empty() &&
                       get<0>(busy.top()) <= time) {
                    auto [freeTime, weight, idx] = busy.top();
                    busy.pop();

                    available.push({weight, idx});
                }
            }

            // Select the server with minimum weight, then index.
            auto [weight, idx] = available.top();
            available.pop();

            ans.push_back(idx);

            // Mark the server as busy.
            busy.push({time + tasks[i], weight, idx});
        }

        return ans;
    }
};
