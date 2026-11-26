class Solution {
public:
    bool canAliceWin(int n) {
        int stonesToRemove = 10;
        bool isAliceTurn = true;
        
        while (n >= stonesToRemove) {
            n -= stonesToRemove;
            stonesToRemove--;
            isAliceTurn = !isAliceTurn;
        }
        
        // If it is Bob's turn when a move can no longer be made, Bob loses and Alice wins.
        return !isAliceTurn;
    }
};