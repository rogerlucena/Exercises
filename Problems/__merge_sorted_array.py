"""Exercises in Python."""

# https://neetcode.io/problems/merge-sorted-array
# https://leetcode.com/problems/merge-sorted-array
# Remember: nice solution in-place comparing largest (for last) instead of smallest (much simpler to avoid
# extra memory here when adding to nums1 itself).

"""
You are given two integer arrays nums1 and nums2, both sorted in non-decreasing order, along with two integers m and n, where:

- m is the number of valid elements in nums1,
- n is the number of elements in nums2.

The array nums1 has a total length of (m+n), with the first m elements containing the values to be merged, and the last n elements set to 0 as placeholders.

Your task is to merge the two arrays such that the final merged array is also sorted in non-decreasing order and stored entirely within nums1.
You must modify nums1 in-place and do not return anything from the function.

Example 1:
Input: nums1 = [10,20,20,40,0,0], m = 4, nums2 = [1,2], n = 2
Output: [1,2,10,20,20,40]

Example 2:
Input: nums1 = [0,0], m = 0, nums2 = [1,2], n = 2
Output: [1,2]
"""

# Elegant in-place solution without extra memory comparing the largest and having `while i2 >= 0` first (to avoid extra code).
# O(m + n) in time and O(1) in space.
# Note: brute force of adding all nums2 to nums1 first and then calling `.sort()` over nums1 would be O((m + n) log(m + n)) in
# time (comment the brute-force first to show that you already know it, especially if stuck).
class Solution:
    def merge(self, nums1: list[int], m: int, nums2: list[int], n: int) -> None:
        """
        Do not return anything, modify nums1 in-place instead.
        """
        i1, i2, last = m - 1, n - 1, m + n - 1
        while i2 >= 0:
            if i1 >= 0 and nums1[i1] > nums2[i2]:
                nums1[last] = nums1[i1]
                i1 -= 1
            else:
                nums1[last] = nums2[i2]
                i2 -= 1
            last -= 1

    def mergeExtraMemory(self, nums1: list[int], m: int, nums2: list[int], n: int) -> None:  # O(m + n) in time and O(m) in space.
        nums1_copy = []
        for i in range(m):
            nums1_copy.append(nums1[i])
        i1, i2, i3 = 0, 0, 0
        while i1 < m and i2 < n:
            if nums1_copy[i1] <= nums2[i2]:
                nums1[i3] = nums1_copy[i1]
                i1 += 1
            else:
                nums1[i3] = nums2[i2]
                i2 += 1
            i3 += 1
        while i1 < m:
            nums1[i3] = nums1_copy[i1]
            i1, i3 = i1 + 1, i3 + 1
        while i2 < n:
            nums1[i3] = nums2[i2]
            i2, i3 = i2 + 1, i3 + 1


def main() -> None:
    return 

if __name__ == "__main__":
    main()