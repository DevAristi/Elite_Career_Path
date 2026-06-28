from typing import List
#Problem: Contains Duplicate (NeetCode 150)
#Difficulty: Easy
#Strategy: Time Complexity Optimization


#---My Thought Process---
# 1. Initial Approach (Sorting)-(In LeetCode-Contains Duplicate):
#   Idea: Sort the list first. If duplicates exist, they will be next to each other.
#   The Problem: Sorting takes O(n log n). It's better than brute force, but not the fastest.

# 2. Optimization-HashSet (In NeetCode-Contains Duplicate):
#   Idea: Use a HashSet to track numbers I've already seen while iterating.
#   Result: I only needed to pass through the list once.
#   Complexity: Improved to O(n) (Linear Time) with O(n) space.


#---BEFORE(LEETCODE)
#class Solution:
# class Solution:
#     def hasDuplicate(self, nums: List[int]) -> bool:
#         nums.sort()
#         for i in range(len(nums) - 1):
#             if nums[i] == nums[i+1]:
#                 return True
#         return False

#---AFTER(NEETCODE)
class Solution:
    def hasDuplicate(self, nums: List[int]) -> bool:
        seen = set()

        for num in nums:
            if num in seen:
                return True
            seen.add(num)
        
        return False 