class Solution:
    def lexPalindromicPermutation(self, s: str, target: str) -> str:
        cnt = [0] * 26

        for ch in s:
            cnt[ord(ch) - ord('a')] += 1

        odd = [i for i in range(26) if cnt[i] % 2]

        if len(odd) > 1:
            return ""

        mid = chr(ord('a') + odd[0]) if odd else ""
        half = [x // 2 for x in cnt]
        m = len(s) // 2
        t = target[:m]

        rem = half[:]
        best = None

        for i in range(m):
            x = ord(t[i]) - ord('a')

            for c in range(x + 1, 26):
                if rem[c] > 0:
                    rem2 = rem[:]
                    rem2[c] -= 1
                    left = t[:i] + chr(ord('a') + c)

                    for k in range(26):
                        left += chr(ord('a') + k) * rem2[k]

                    best = left
                    break

            if rem[x] == 0:
                break

            rem[x] -= 1

        if all(x == 0 for x in rem):
            candidate = t + mid + t[::-1]
            if candidate > target:
                return candidate

        if best is not None:
            return best + mid + best[::-1]

        return ""