class Solution:
    def lexGreaterPermutation(self, s: str, target: str) -> str:
        cnt = [0] * 26

        for c in s:
            cnt[ord(c) - ord('a')] += 1

        n = len(target)

        for i in range(n):
            x = ord(target[i]) - ord('a')

            if cnt[x] == 0:
                break

            cnt[x] -= 1
        else:
            i = n

        for j in range(i, -1, -1):
            if j < i:
                cnt[ord(target[j]) - ord('a')] += 1

            x = ord(target[j]) - ord('a') if j < n else -1

            for k in range(x + 1, 26):
                if cnt[k] > 0:
                    ans = target[:j] + chr(k + ord('a'))
                    cnt[k] -= 1

                    for c in range(26):
                        ans += chr(c + ord('a')) * cnt[c]

                    return ans

        return ""