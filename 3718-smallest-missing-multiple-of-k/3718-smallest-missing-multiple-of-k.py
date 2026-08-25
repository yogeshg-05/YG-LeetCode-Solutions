class Solution(object):
    def missingMultiple(self, nums, k):
        nums = set(nums)
        multiple = k

        while multiple in nums:
            multiple += k

        return multiple