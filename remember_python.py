"""File to help remember common Python synthax and useful code snippets."""

# More on: https://neetcode.io/courses/lessons/python-for-coding-interviews
# Or in: https://docs.python.org/3
# Style Guide for Python Code (PEP 8): https://peps.python.org/pep-0008

# Some useful LeetCode patterns and code snippets to review also below under "LeetCode Python Boilerplate Patterns".

import bisect
import heapq
import itertools
import math
from array import array
from collections import Counter, defaultdict, deque
from functools import cmp_to_key, lru_cache
from typing import Optional

## Useful code snippets and syntax:

# Multiple assignments
n, m = 0, "abc"

# Increment
n = n + 1   # good
n += 1      # good
# n++       # bad

# None is null (absence of value)
n = None

# Vector and Swap in Python
v = [0] * 5
i = 2
j = 3
v[i], v[j] = v[j], v[i]

v = list(range(5))  # [0, 1, 2, 3, 4]
m = min(v)  # bult-in min, output: "0"
m = min(x for x in v if x > 0)  # example of filtered min, output: "1"

# Slicing: Similar to for-loop ranges - last index is non-inclusive. Note the syntax: v[start:end:step]. And v[::-1] returns a reversed list.
# print(v[1:4])  # Output: "[1, 2, 3]"

# But no out of bounds error
# print(v[0:10])  # Output: "[0, 1, 2, 3, 4]"

# Matrices
R, C = 3, 4
matrix = [[0] * C for _ in range(R)]  # Note that "[[0] * C] * R" is a classic bug - repeats a reference to same row R times -> thus changing one row will change all rows (then use list comprehension like that instead)

# .extend() vs .append() for lists
# Critical difference: .extend() unpacks items, whereas .append() adds the entire iterable object as a single nested element.
# Using .extend()
list_a = [1, 2]
list_a.extend([3, 4])
# print(list_a)   # Output: "[1, 2, 3, 4]"
# Using .append()
list_b = [1, 2]
list_b.append([3, 4])
# print(list_b)  # Output: "[1, 2, [3, 4]]"
# Using +=
list_c = [1, 2]
list_c += [3, 4]  # equivalent to .extend(), note that `+= 3` would give error here (because int is not iterable, but if `+= "a"` would work because string is iterable), note .append(3) also works fine.
# print(list_c)  # Output: "[1, 2, 3, 4]]"

# Unpacking lists
a, b, c = [1, 2, 3]

# Looping from i = 2 to i = 5
for i in range(2, 6):
    pass  # print(i)

# Looping from i = 5 to i = 2
for i in range(5, 1, -1):
    pass  # print(i)

# With index and value
nums = [1, 2, 3]
for i, n in enumerate(nums):
    # print(i, n)
    pass

# Zip - Loop through multiple arrays simultaneously with unpacking
nums1 = [1, 3, 5]
nums2 = [2, 4, 6]
for n1, n2 in zip(nums1, nums2):
    # print(n1, n2)
    pass
names = ["Alice", "Bob", "Charlie"]
scores = [85, 92, 78]
zipped = zip(names, scores)  # type is `<class 'zip'>`
# print(list(zipped))  # Output: "[('Alice', 85), ('Bob', 92), ('Charlie', 78)]"
# Can create dictionaries too:
score_dict = dict(zip(names, scores))
# print(score_dict)  # Output: "{'Alice': 85, 'Bob': 92, 'Charlie': 78}"
# Unzipping data: You can reverse the process and split a list of tuples back into separate sequences using the unpack operator *:
pairs = [('Alice', 85), ('Bob', 92)]
names, scores = zip(*pairs)
# print(names)  # Output: "('Alice', 'Bob')" - a tuple.
# By default, if you pass lists of different sizes, zip() stops as soon as the shortest list runs out of items, ignoring the extra data.
# To handle mismatch in size can:
# 1) strict=True: Added in Python 3.10, this flag will force the code to raise a ValueError if the sequences are not exactly the same length.
# 2) itertools.zip_longest(): This alternative utility from the standard library lets you fill in missing values with a placeholder like None instead of dropping them.

# Reverse
nums = [1, 2, 3]
nums.reverse()  # in-place.
# print(nums)  # Output: "[3, 2, 1]".

# Iterate in reverse order:
my_list = [1, 2, 3, 4, 5]
for item in reversed(my_list):  # iterator in reversed order, do not create additional copy like in slicing my_list[::-1].
    pass  # print(item)
# Index-based, if you need the index too
for i in range(len(my_list) - 1, -1, -1):
    pass  # print(i, my_list[i])
# With enumerate, if you want reversed values but original indices
for i, item in reversed(list(enumerate(my_list))):
    pass  # print(i, item)

# Strings
# (can use both double "text" or single quotes 'text' since we have no chars in Python - thus follow the current pattern in the codebase and stick to it)
s = "Hi, my name is Roger, nice to meet you!  "
i = s.find("Roger")  # Lowest index where substring was found, or -1 if not found.
# print(i)  # Output: "15"
# print(s[i:i+5])  # Output: "Roger", substr in Python is through slicing.
# s.isalnum()  # At least one character in the string and all alphanumeric (including non-English letters like "ñ" too).
# s.isalpha()
# s.isnumeric()
# s.isascii()  # Note: empty string is ASCII too.
s = s.replace("Roger", "Neuma")
# print(s)  # Output: "Hi, my name is Neuma, nice to meet you!  "
tokens = s.split(sep=" ")  # Returns a `list` separating by `sep` (default sep is the whitespace with empty strings discarded from the result)
s = s.strip()  # Returns a copy of the string (since immutable) with any leading and trailing whitespaces removed.
s = s.lower()


# Math
# Division is decimal by default
# print(5 / 2)  # Output: "2.5"

# Double slash rounds down
# print(5 // 2)  # Output: "2"

# CAREFUL: most languages round towards 0 by default
# So negative numbers will round down
# print(-3 // 2)  # Output: "-2"

# A workaround for rounding towards zero
# is to use decimal division and then convert to int.
# print(int(-3 / 2))  # Output: "-1"

# Modding is similar to most languages
# print(10 % 3)

# Except for negative values
# print(-10 % 3)  # Output: "2"

# To be consistent with other languages modulo
# print(math.fmod(-10, 3))  # Output: "-1.0"

# More math helpers
# print(math.floor(3 / 2))  # 1
# Note: math.floor() rounds a negative number down towards negative infinity, meaning it returns the largest integer less than or equal to the input.
# print(math.floor(-3.2))  # Output: "-4"

# print(math.ceil(3 / 2))  # 2
# print(math.sqrt(2))  # 1.4142...
# print(math.pow(2, 3))  # 8.0

# Note: math.pow(x, y) vs x**y
# print(math.pow(2, 3))  # 8.0  (always returns a float)
# print(2 ** 3)          # 8    (returns an int, since both operands are ints)
# For large integers - since math.pow works in floats, it's limited to the range of a C double (~1.8×10³⁰⁸ - calls C's pow underneath). ** with ints can grow as large as memory allows, exactly.
# print(2 ** 10000)         # exact, dynamic-precision integer
# print(math.pow(2, 10000))  # OverflowError: math range error
# Precision: because math.pow goes through floats, you can lose precision for large integer-like results (like `math.pow(10, 20)`, but `10 ** 20` is exact and precise).
# Speed: For simple scalar cases, ** is generally as fast or faster since it can special-case small integer powers. math.pow calls into the C library's float pow, which
# has fixed overhead but is predictable for float-only work — this matters more when working with NumPy/vectorized code, where you'd use ** on arrays anyway rather than math.pow (which doesn't vectorize).
# Bottom line:
# For pure integer math, use **. Use math.pow when you specifically want float semantics or are matching C-style numeric behavior (e.g., in a context expecting float everywhere).

# Max / Min Int
# float("inf")
# float("-inf")

# Python int numbers are infinite so they never overflow (int memory will increase on demand as far as possible with the memory available, but floats have a limit like above shown with math.pow and float("inf"))
# print(2 ** 200)

# But still less than infinity
# print(math.pow(2, 200) < float("inf"))  # Output: "True"

# Valid numeric strings can be converted
# print(int("123") + int("123"))  # Output: "246"
# Note: int(123.1) gives error, but float("123.1") works ok.

# And numbers can be converted to strings
# print(str(123) + str(123))  # Output: "123123"

# Remember, strings are immutable (if want mutable then convert to list with `list()`):
# s[0] = "A"  # Cannot do this.
# s += "def"  # This creates a new string.

# Min-Heap & Max-Heap (default is min_heap)
min_heap = []
heapq.heappush(min_heap, 5)
heapq.heappush(min_heap, 1)
min_val = heapq.heappop(min_heap)  # Returns 1, if only wants to see (and not pop) do min_heap[0] (note that min_heap[-1] is not the max)

# Convert an existing list to a heap in O(n) time
data = [3, 1, 4, 1, 5]
heapq.heapify(data)

# Max-Heap workaround (negate values)
max_heap = []
heapq.heappush(max_heap, -5)
heapq.heappush(max_heap, -1)
max_val = -heapq.heappop(max_heap)  # Returns 5.

# Nice trick/workaround for using a priority
pq = []  # heapq.heappush(pq, (priority, item))
heapq.heappush(pq, (5, "task_a"))
heapq.heappush(pq, (1, "task_b"))
top_priority, top_item = heapq.heappop(pq)  # pops (1, "task_b")
# print(f"p: {top_priority}, item: {top_item}")
# print("p:", top_priority, "item:", top_item)  # also works but no comma after {top_priority} here (automatically adds space when concat)
# This is a min-heap, so lowest priority pops first. For a max-heap, negate the key: `heapq.heappush(pq, (-priority, item))`

# Watch out: if two items have the same key and item isn't directly comparable (e.g. dicts, custom objects without __lt__), Python will throw a TypeError when it tries to break the tie by comparing item. Fix with a tie-breaker, usually an insertion counter:
counter = itertools.count()
pq = []  # heapq.heappush(pq, (priority, next(counter), item))
heapq.heappush(pq, (5, next(counter), "item"))
heapq.heappush(pq, (4, next(counter), "item"))
heapq.heappush(pq, (7, next(counter), "item"))
# print(pq)  # [(4, 1, 'item'), (5, 0, 'item'), (7, 2, 'item')]  # Note: only [0] is guaranteed to be the smaller (the other two are sorted because of insertion order here).

# Another option is having a wrapper class with __lt__
# Useful when the comparator logic is more complex than a single key (e.g. comparing multiple fields with different directions, or comparing based on a computed value).
# "I am encapsulating the comparator in the object" — it reads cleanly and avoids tuple-comparison edge cases entirely
class Task:
    def __init__(self, priority, item):
        self.priority = priority
        self.item = item
    def __lt__(self, other):
        return self.priority < other.priority   # define "personalized" order here
    def __str__(self):
        return f"Task: priority {self.priority}, item: {self.item}"

pq = []
heapq.heappush(pq, Task(5, "task_a"))
heapq.heappush(pq, Task(2, "task_b"))
top = heapq.heappop(pq)
# print(top)  # Output: "Task: priority 2, item: task_b"

# Queue & Double-Ended Queue
queue = deque([1, 2, 3])
queue.append(4)  # Push to right
front = queue.popleft()  # Pop from left -> 1 (O(1) time)
def delete_nth(d, n):
    d.rotate(-n)  # Rotate left
    d.popleft()
    d.rotate(n)  # Rotate right

# Custom key sorting (e.g., sort intervals by start time, then end time descending)
intervals = [[1, 4], [1, 2], [3, 5]]
intervals.sort(key=lambda x: (x[0], -x[1]))  # Result: [[1, 4], [1, 2], [3, 5]], in-place, has tag "reverse=True" to descending order too

people = [("Alice", 30), ("Bob", 25), ("Alice", 20)]
people.sort(key=lambda p: (p[0], -p[1]))  # sort by name ascending, then age descending
# print(people)  # Output: [('Alice', 30), ('Alice', 20), ('Bob', 25)]

# If does not want in-place
numbers = [2, 3, 7, 1]
sorted_numbers = sorted(numbers, reverse=True)  # returns [7, 3, 2, 1]

# Sorting hash maps (dicts)
employees = [
    {'name': 'Alice', 'age': 30},
    {'name': 'Bob', 'age': 25},
    {'name': 'Charlie', 'age': 35}
]
# Sort dictionaries by the value of the 'age' key (use that as the number to compare the list elements)
employees.sort(key=lambda person: person['age'])  # in-place
# print(employees)  # Output: [{'name': 'Bob', 'age': 25}, {'name': 'Alice', 'age': 30}, {'name': 'Charlie', 'age': 35}]

# If the ordering genuinely can't be expressed as "map to a key" (rare, but it happens — e.g. LeetCode's "largest number" problem where you compare a+b vs b+a - added below), use functools.cmp_to_key:
def compare(a, b):
    # return negative if a should come before b, positive if after, 0 if equal
    return -1 if a + b > b + a else (1 if a + b < b + a else 0)
nums = ["3", "30", "34", "5", "9"]  
nums.sort(key=cmp_to_key(compare))  # Output: ['9', '5', '34', '3', '30'] as expected to make that number the largest possible.

# Binary Search:
arr = [1, 3, 3, 5, 8]
# Find insertion index to keep array sorted.
idx_left = bisect.bisect_left(arr, 3)  # Returns 1 (index of first occurrence >= target - equiv to lower_bound in C++).
idx_right = bisect.bisect_right(arr, 3)  # Returns 3 (index of first occurrence > target - equiv to upper_bound in C++).
bisect.insort(arr, 7)  # Insert keeping sorted order.

# Set:
# print(set([1, 2, 3]))  # list to set, or `s = set()`.
# Note: empty `{}` is reserved for initializing hash map (type `dict`), to initialize hash set must use constructor `set()` or
# already initialize with one element like on BFS below `enqueued = {start}` (type: hash set).
mySet = {i for i in range(5)}  # Set comprehension, output: "{0, 1, 2, 3, 4}".

# Dict:
myMap = {i: 2*i for i in range(3)}  # Dict comprehension, output: "{0: 0, 1: 2, 2: 4}".

# Looping through hash maps (dicts)
myMap = {"alice": 90, "bob": 70}
for key in myMap:
    # print(key, myMap[key])
    pass

for val in myMap.values():
    # print(val)
    pass

for key, val in myMap.items():
    # print(key, val)
    pass

# Tuples - like lists but immutable, `[-1]` also works for last index, can also accept different types like lists (but the convention for lists is keeping them homogeneous, while tuples possibly being heterogeneous).
# Can also be used as key for hash map/set (lists cannot): 
myMap = {(1,2): 3}
# print(myMap[(1,2)])  # Output: "3"

mySet = set()
mySet.add((1, 2))
# print((1, 2) in mySet)  # Output: "True"

# Note: The Semantic Difference (Lists vs. Tuples)
# While both can hold mixed types, Python developers use them differently based on intent:
# - Tuples are Heterogeneous: Conventionally, tuples represent a single "record" with a fixed structure where the
# position of the item determines its meaning (e.g., (latitude, longitude) or (user_id, name, email)).
# - Lists are Homogeneous: Lists are conventionally used for collections of many items of the same type that can grow
# or shrink over time (e.g., a list of blog posts or a list of prices)

# Nested functions have access to outer variables
def outer(a, b):
    c = "c"
    def inner():
        return a + b + c
    return inner()
# print(outer("a", "b"))  # Output: "abc"

# Functions can modify objects but not reassign
# unless using `nonlocal` keyword:
def double(arr, val):
    def helper():
        # Modifying array works.
        for i, n in enumerate(arr):
            arr[i] *= 2
        
        # Will only modify val in the helper scope.
        # val *= 3  # Also, received `UnboundLocalError: cannot access local variable 'val' where it is not associated with a value`.

        # This will modify val outside helper scope.
        nonlocal val
        val *= 2
    helper()
    # print(arr, val)  # Output: "[2, 4] 6"

nums = [1, 2]
val = 3
double(nums, val)
# print(nums, val)  # Output: "[2, 4] 3"  # 3 here because `val` was immutable and "passed by object reference".

# Classes:
# You do not need to write destructors in Python because Python features an automatic garbage collector that completely manages memory deallocation.
# Python uses a primary mechanism of reference counting alongside a secondary cyclical garbage collector (the latter is to
# identify isolated groups referencing each other - in a cycle - which can be deallocated too) to automatically reclaim memory as soon as an object is no longer needed.
class MyClass:
    # Constructor.
    def __init__(self, nums):
        # Create member variables.
        self.nums = nums
        self.size = len(nums)
    
    # The `self` keyword is required as param.
    def getLength(self):
        return self.size

    def getDoubleLength(self):
        return 2 * self.getLength()
myObj = MyClass([1, 2, 3])

# Optional in Python (Python 3.9 and older - `from typing import Optional`):
def greet(name: Optional[str]):
    if name is None:
        print("Hello, Guest!")
    else:
        print(f"Hello, {name}!")

# Modern Syntax (Python 3.10+): You should use the | operator instead. Optional[str] is exactly equivalent to str | None.
def greet(name: str | None):
    pass  # Or "...".



## Examples:

# Counter - Frequency maps (`Counter` below is the `multiset` for Python - bult over a dict it seems)
counts = Counter("leetcode")
# print(counts)  # Output: "Counter({'e': 3, 'l': 1, 't': 1, 'c': 1, 'o': 1, 'd': 1})"
counts.subtract(['e'])  # Decrements count of 'e', `counts[x] -= 1` also works (maybe del counts[x] if you want it gone if reaching 0, though 0 is probably fine for most checks).
for letter, count in counts.items():
    # print(f"Letter: {letter}, count: {count}")
    pass
# print(counts.keys())  # Output: "dict_keys(['l', 'e', 't', 'c', 'o', 'd'])"
# print(counts.values())  # Output: "dict_values([1, 2, 1, 1, 1, 1])"
# print(counts.get("e"))  # Output: "2" (as expected after the decrement)

# More on Counters:
c = Counter([1, 1, 2, 3, 3, 3])   # from iterable
c = Counter("aabbbc")              # from string
# c = Counter(word for word in list_of_words)  # from generator
# Access — never raises KeyError
# print(c['x'])   # 0, not KeyError, even if 'x' was never seen (advantage of using Counter instead of standard dict for counting - `c[key] += 1` works fine here).
# Arithmetic between Counters (the multiset ops)
c1 = Counter([1,1,2,3])
c2 = Counter([1,2,2])
# print(c1 + c2)   # sums counts:      Counter({1:3, 2:3, 3:1})
# print(c1 - c2)   # subtracts, keeps only positive > 0: Counter({1:1, 3:1})
# print(c1 & c2)   # min of counts (intersection):   Counter({1:1, 2:1})
# print(c1 | c2)   # max of counts (union):          Counter({1:2, 2:2, 3:1})
# c1 - c2 and c1 & c2 are the workhorses for "is this a subset/anagram/permutation of that" problems (e.g., Valid Anagram, Ransom Note, Find All Anagrams in a String).
# most_common(n)
# print(c.most_common())      # Output: "[('b', 3), ('a', 2), ('c', 1)]" - all elements, sorted by count descending.
# print(c.most_common(2))     # Output: "[('b', 3), ('a', 2)]" - top 2: [(elem, count), ...]
# Used in Top K Frequent Elements type problems — often faster to write than manually building a heap,
# though for true O(n log k) you'd still want a heap-based approach if the interviewer cares about complexity.
# Note: .most_common(k) probably is O(N + k log N) in time (depending on CPython open-source implementation - "delegates
# to _heapq.nlargest(k, ...) when k is specified, and to sorted() when k is None" - O(N) to heapify and then O(k log N) to perform k pops) - Obs: syntax for nlargest is `heapq.nlargest(n, iterable, key=None)` which here could be called as `heapq.nlargest(k, c.items(), key=lambda x: x[1])`.
# elements() - Reconstructs a multiset-like iterable (type returned is `itertools.chain` - but can convert to `list` or `tuple`).
# Elements are returned in the order first encountered. If an element’s count is less than one, elements() will ignore it. Less commonly needed but occasionally used to regenerate a sequence.
# print(list(Counter({1:2, 3:1}).elements()))  # Output: "[1, 1, 3]".
# Boolean / equality checks
c1 == c2          # True if same counts for same keys
c3 = Counter(c1)  # Constructor accepts other Counter to copy from.
# print(c3)  # Output: "Counter({1: 2, 2: 1, 3: 1})"
c3[1] -= 2
c3[2] -= 2
# print(c3)  # Output: "Counter({3: 1, 1: 0, 2: -1})"
# print(+c3)  # Output: "Counter({3: 1})", not in-place - unary plus: drops zero and negative counts (handy after a subtraction).
list(c1.values()) # e.g. checking all counts equal for "balanced" problems

# Note: Practical LeetCode tip - for problems like "two strings are anagrams," Counter(s) == Counter(t) is a one-liner
# that's both correct and fast — no need to sort characters (O(n) vs O(n log n)), and it reads clean in an interview.
# (It already checks correspondent keys and values for equality)

# Grouping elements without KeyError checks
adj_list = defaultdict(list)  # If only `= {}` would throw "Ivalid Key" error.
adj_list[0].append(1)  # Automatically initializes empty list for key 0.
# print(adj_list.get(1))  # Output: "None"
# print(adj_list[1])  # Output: "[]"
# print(adj_list)  # Output: "defaultdict(<class 'list'>, {0: [1], 1: []})"  # an empty list `[]` was added to the key `1` as expected for `defaultdict(list)`.
# This technique is simpler and faster than an equivalent technique using dict.setdefault():
d = {}
for k, v in [('yellow', 1), ('blue', 2), ('yellow', 3), ('blue', 4), ('red', 1)]:
    d.setdefault(k, []).append(v)  # Documentation: If key is in the dictionary, return its value. If not, insert key with a value of default and return default. default defaults to None.
    # Also, there is in the Documentation `d.get(key, default=None)` = Return the value for key if key is in the dictionary, else default. If default is not given, it defaults to None, so that this method never raises a KeyError.
# Documentation: = `defaultdict(default_factory=function)`
# Note that the `default_factory` must be a function:
# `list` above - constructor for empty list.
# `int`, `float` - constructors for counting from zero/initializing with zero.
# Or `distances = defaultdict(lambda: float("inf"))` with a lambda function to customize the initialization value (like with Dijkstra below).

# A list can contain different types, but that is not the conventional/usual
mixed_list = [42, "Hello World", 3.14, True, [1, 2, 3]]  # A list with an integer, string, float, boolean, and a nested list
# The "Pythonic" Convention: In community standards, lists are typically reserved for *homogeneous* data (elements of the same type, like a list of user IDs). When to use Tuples instead: If you have a fixed collection of heterogeneous data where the index position implies meaning (e.g., a database row structured like (user_id, user_name, active_status)), a tuple is generally preferred over a list. Example when type hinting: `user_data: tuple[int, str, float] = (1, "Bob", 95.5)`
# print(type(mixed_list[0]))  # Output: <class 'int'>
# print(type(mixed_list[1]))  # Output: <class 'str'>
# print(type(mixed_list[4]))  # Output: <class 'list'>

# Python lists are untyped/heterogeneous by default - there's no compile-time guarantee it only holds ints. If an interviewer
# cares about that distinction, you can mention array module (array('i', [...])) or numpy arrays as the actual typed, contiguous-memory equivalents, but for algorithm interviews list is the expected answer and nobody will ding you for not using array.
a = array('i', [1, 2, 3])  # 'i' = signed int
a.append(4)                # array('i', [1, 2, 3, 4])
# print(a[0])              # 1

# To get the ASCII number of a char use built-in `ord()` - but no need to do that if directly comparing chars like `if "a" <= char <= "z":`
c1, c2, c3 = "a", "z", "A"
ascii_val_c1 = ord(c1)
# print(f"{c1}: {ascii_val_c1}, {c2}: {ord(c2)}, {c3}: {ord(c3)}")  # Output: "a: 97, z: 122, A: 65"
# Note that the built-in isalnum() method on the string character c1.isalnum() would also return true for non-English letters
# like "ñ" or "é" (general Unicode letters - non-ASCII characters can be considered alphabetical/letters too - `str.isalpha()` called by `str.isalnum()` in the docs).
# Obs: ASCII = American Standard Code for Information Interchange - numbers from 0 to 127 - Covers English letters (A-Z, a-z), numbers (0-9), basic symbols like punctuation, and includes hidden commands like new lines and tabs too. 
# Note: there is no type `char` in Python, both 'a' and "a" are of type `str` - `print(type('a'))`.

# On removing spaces:
text = "  Hello   World  "
no_spaces = text.replace(" ", "")  # Output: "HelloWorld" (note: not in-place).
trimmed = text.strip()  # Output: "Hello   World" (removes only from beginning and end) - there is .lstrip() and .rstrip() too.
normalized = " ".join(text.split())  # Output: "Hello World" (.split() tokenizes and removes tabs and newlines too - returning a list not in-place because str immutable remember)

# Reversing strings in Python:
# Use `text[::-1]` (Pythonic), or if to implement:
def reverse_string_pointers(s):
    char_list = list(s)  # Note: Python strings are immutable, so need to conver to list first.
    left, right = 0, len(char_list) - 1
    
    while left < right:
        char_list[left], char_list[right] = char_list[right], char_list[left]
        left += 1
        right -= 1
        
    return "".join(char_list)
# print(reverse_string_pointers("Python"))  # Output: "nohtyP"
# Note: for lists, since they are mutable, there is an in-place .reverse() method:
lst = ["a", "c", "b"]
lst.reverse()
# print(lst)  # ['b', 'c', 'a']

# How to break a line too long inside an `if` condition in Python?
# Recommended PEP 8 formatting (Python Style Guide) - pay attention to the identation of the closing bracket `):` too:
if (
    True  # condition_one
    and True  # condition_two
    and True  # condition_three
):
    # Your code here
    pass



## Toy problem:
def two_sum(nums: list[int], target: int) -> list[int]:
    """Finds indices of two numbers that add up to target."""
    seen = {}
    for i, num in enumerate(nums):
        diff = target - num
        if diff in seen:
            return [seen[diff], i]
        seen[num] = i
    return []

def main():
    result = two_sum([2, 7, 11, 15], 9)
    # print(f"Indices: {result}")

if __name__ == "__main__":  # Guard block prevents execution when imported as a module.
    main()  # The pattern is to keep code here minimal and encapsulate in auxiliary wrapper `main()` (to avoid error-prone/confusing global variables).

# Note: In Python, the `if __name__ == "__main__":` statement is a security check that determines whether a Python file is being run
# directly as a standalone script or being imported as a module into another file. It acts as the "entry point" of an application,
# allowing you to control exactly what code executes depending on how the file was invoked
# 1) When you run a file directly (e.g., typing `python3 script.py` in your terminal), Python internally assigns the string "__main__"
# to the special `__name__` variable.
# 2) When you import a file into another script (e.g., writing import script inside another file), Python assigns the actual name
# of the file (like "script") to the `__name__` variable.


# Another toy problem:
# https://neetcode.io/problems/is-palindrome
# https://leetcode.com/problems/valid-palindrome
class Solution:
    def isPalindrome(self, s: str) -> bool:
        l = 0
        r = len(s) - 1
        while l < r:
            while l < r and not self.isEnglishAlphaNumeric(s[l]):
                l += 1
            while r > l and not self.isEnglishAlphaNumeric(s[r]):
                r -= 1
            if s[l].lower() != s[r].lower():  # Do not forget `.lower()` here!
                return False
            l += 1
            r -= 1
        return True

    def isEnglishAlphaNumeric(self, c: str) -> bool:  # First argument has to be `self` too.
        return ("a" <= c <= "z") or ("A" <= c <= "Z") or ("0" <= c <= "9")


# Another toy problem:
# Group anagrams - how to get the signature of the words?
c = Counter("word")  # Counter({'o': 1, 'w': 1, 'r': 1, 'd': 1})
# Great for equality checks (Counter(s1) == Counter(s2)), but Counter is not hashable, so you can't use it directly as a dict key or put it in a set.
# For hashable signature:
# 1) Sort the word - O(L log L) - simpler to write first.
sig = "".join(sorted("word"))   # 'dorw', note that the output of `sorted` is a `list`, and note that this is O(L log L) per word.
# 2) Tuple of 26 counts (O(L) instead of O(L log L) - faster and hashable - nice if asked to optimize performance for getting the signature).
def signature(word):
    counts = [0] * 26  # mutable `list`.
    for ch in word:
        counts[ord(ch) - ord('a')] += 1
    return tuple(counts)
sig = signature("word")  # (0,0,0,1,0,...,1,...,1,...,1,...) — 26-length tuple.
# 3) Interesting how Xandão did too in the mock that I did for him in 2023:
# sig = "".join(["{}{}".format(k, c[k]) for k in sorted(c.keys())])  # Output: "d1o1r1w1" (how Xandão originally did).
sig_best = "".join([f"{k}{c[k]}" for k in sorted(c.keys())])  # Output: "d1o1r1w1" (my way).
# Note: if had not used `sorted` in the line above the misleading output would be "w1o1r1d1" (order of insertion) - which would be incorrect to compare two different words with same letters.
# Additional note: the complexity of the above is dominated by the sorting, so O(K log K) in time - but since these words have lowercase English
# letters then K ≤ 26 always, thus the complexity becomes O(26 log 26) = O(1) - that is why this is preferred over the sorting version in 1) above (which is O(L log L)).


# Another toy problem:
# (Covers local functions and how to call another class method from a first class method)
# https://neetcode.io/problems/valid-palindrome-ii
# https://leetcode.com/problems/valid-palindrome-ii
# You are given a string s, return true if the s can be a palindrome after deleting at most one character from it.
class Solution:
    def validPalindrome(self, s: str) -> bool:
        # If function only used here and not by other methods or by external API, it is good/Pythonic to keep the function local to signal
        # "Scope Awareness" to the interviewer and allow less typing under time pressure (no writing `self` or passing `s` etc).
        # Also, it's idiomatic Python - Python has first-class support for closures and nested functions. This is arguably even more
        # Pythonic than reaching for @staticmethod decorator for another method (which would be more of a Java/C++ habit ported into Python here).
        def isPalindrome(l: int, r: int) -> bool:  
            while l < r:
                if s[l] != s[r]:
                    return False
                l, r = l + 1, r - 1
            return True
        
        l, r = 0, len(s) - 1
        while l < r:
            if s[l] != s[r]:
                return isPalindrome(l + 1, r) or isPalindrome(l, r - 1)
            l, r = l + 1, r - 1
        
        # Note: if calling another method of the class from here it should be like `self.isPalindromeExtra(s, l + 1, r)` - start with `self.` and do not pass
        # `self` as argument (it is already automatically bound) otherwise error: `TypeError: Solution.isPalindromeExtra() takes 4 positional arguments but 5 were given` (bound `self` twice).
        return True

    def isPalindromeExtra(self, s: str, l: int, r: int) -> bool:
        pass  # or `...` here to better signal this is not implemented yet (no need of a dumb `return False` here - because Python does not compile-checks the
              # type; and if this is called it returns `None`, not an Error - which is delicate because `None` is understood as `False` if treated as boolean down the road).


# Another toy problem:
# Finding the k most frequent elements in a list. This is the textbook case — dict for O(1) counting, heapq for efficiently
# pulling out the top k without a full sort (O(n log k)).
def top_k_frequent(nums, k):
    # Step 1: dict does the O(n) counting — O(1) amortized per insert
    counts = Counter(nums)  # {value: frequency}

    # Step 2: heap keeps only the k largest we've seen so far
    # We push (frequency, value) tuples; heapq is a MIN-heap,
    # so pushing a full min-heap and popping when size > k
    # keeps the k LARGEST elements, O(log k) per operation.
    heap = []
    for val, freq in counts.items():
        heapq.heappush(heap, (freq, val))
        if len(heap) > k:
            heapq.heappop(heap)  # discard the current smallest

    # heap now holds exactly the k most frequent (freq, val) pairs
    return [val for freq, val in heap]

nums = [1, 1, 1, 2, 2, 3, 4, 4, 4, 4]
# print(top_k_frequent(nums, 2))  # -> [1, 4]  (order not guaranteed)

# Common variants of this exact pattern you'll see on LeetCode:
# - K closest points to origin — dict/list of points, heap keyed by negative distance (max-heap trick)
# - Task Scheduler — Counter for task frequencies, max-heap to always schedule the most frequent remaining task
# - Merge k sorted lists — heap holds one head pointer per list, popping gives global order

# If you think you need a C++ map (sorted) and just a priority queue is not enough think about:
# - bisect module + a plain sorted list — gives O(log n) search via bisect_left/bisect_right, but O(n) insertion because the
# list has to shift elements. Fine when you mostly search and rarely mutate, or when insertions are batched.
# - Combine dict (for O(1) key lookup) with heapq or a sorted structure (for order) when a problem needs both — this dict+heap
# combo is a very common LeetCode pattern (like above) for problems that "feel like" they want std::map.



## Documentation summary and complexities:
# list -> append(), pop() - O(1) amortized; pop(0), insert(0, val), insert(position, val) - O(n); lst.remove(val), val in lst - O(n)
# dict (hash map) -> d[k] = v, k in d, del d[k] - O(1) average ("average" because *hash collisions* or for when *it is full* - when Python allocates a larger memory array and re-hashes every existing key into the new table)
# set (hash set) -> s.add(x), x in s, s.remove(x) - O(1) average
# collections.deque (double-ended queue) -> append(), pop(), appendleft(), popleft() - O(1) - `d[0]` and `d[-1]` also works, `d.extend(other_list_or_string)` (add multiple elements at once, note that extend_left calls append_left thus reversing the other of the input extra elements added), `d.rotate(k)` (right rotation) and `d.rotate(-k)` (left rotation) - `list` does not have `.rotate()`
# min-heap -> heappush(h, val), heappop(h) - O(log n), `min_heap[0]` to see the min in O(1)

# Also, for `dict`, check `defaultdict` above, and there is `d.get(key, default=None)` (if key not present returns default/None, so this .get never raises a KeyError like `[]` for the standard dict).



## Notes:

# Note 1)
# Python does not use pass-by-value or pass-by-reference; instead, it uses a mechanism called pass-by-object-reference (also known as pass-by-assignment).
# In Python, every variable is a name (label) that points to an object in memory. When you pass an argument to a function, Python passes a copy of that
# reference. How the data behaves depends entirely on whether the object is mutable (changeable) or immutable (unchangeable).

# Immutable Objects (Behaves like Pass-by-Value): int, float, string, tuple, bool, frozenset.
# Mutable Objects (Behaves like Pass-by-Reference): list, dict, set, custom class objects.

# Obs: Even with a mutable object, reassigning the variable inside the function breaks the link to the original object.
# Reassignment binds the local variable to a completely new memory location.
# Attention: but note that `+=` operator for mutable objects (like list and set - `|=` (in-place union) for set) is not reassigning but actually calling the internal `__iadd__` method (equivalent to list.extend(other_list)) that modifies the object in-place and return it (and thus changes it outside as well).
    # But note that `lst = lst + [3, 4]` (does not change outside function since reassigning/rebinding local name) is different than `lst += [3, 4]` (internal `__iadd__` extending original memory referenced).
def reassign_list(lst):
    lst.append(4)  # Changes it outside too (note that `+= [4]` also changes outside - tested).
    lst = [100, 200]  # The '=' operator reassigns 'lst' to a new object.
    # print(f"Inside function: {lst}")  # Output: [100, 200]

my_list = [1, 2, 3]
reassign_list(my_list)
# print(f"Outside function: {my_list}")  # Output: [1, 2, 3, 4]

# Obs: If you need to pass a mutable object to a function but want to guarantee that the function won't change the original data, you should
# pass a explicit copy using my_list.copy() or the copy.deepcopy() module.


# Note 2)
# There is no `long` type for larger ints in Python 3 - int's memory is dynamically set on demand (arbitrary precision - grows on demand if memory available);
# and float has already a double precision behind the curtains (64-bit IEEE 754 double-precision float).


# Note 3)
# We also have `continue` and `break` for loops in Python, just like C++.


# Note 4)
# Compiled (C++) vs Interpreted (Python)

# - C++ is compiled: before your program ever runs, a compiler translates the entire source file into machine code (an executable). The compiler
# needs to resolve every function call to a concrete address/signature at compile time, checking types and existence as it goes, top to bottom
# through the file.

# - Python is interpreted: there's no separate compile-to-machine-code step you control. The interpreter reads and executes your code more or
# less line by line (technically it compiles to bytecode on the fly, but that's an internal detail, not an upfront whole-program pass).
# Function bodies aren't even looked at until they're called, not when they're defined.

# Why C++ needs the auxiliary function declared/defined before use?

# - When the C++ compiler hits a call like isPalindrome() (think of it as an auxiliary extra function here) inside validPalindrome(), it needs
# to already know isPalindrome's signature (return type, parameter types) to generate correct machine code and check types — that's why you
# need it declared above (a full definition, or at least a forward declaration/prototype like `bool isPalindrome(string s, int l, int r);`) before the point of use.
# - Python, on the other hand, doesn't check that isPalindrome exists when it reads the def validPalindrome block — it just stores that block as-is. It only looks
# up isPalindrome by name at the moment validPalindrome is actually called and execution reaches that line. As long as isPalindrome exists
# somewhere in scope by the time it's called (not by the time it's defined), you're fine — even if it's defined later in the file, as in your class.

# -> "The real mechanism is when name resolution happens - at Compile time for C++, and at runtime for Python (self.isPalindrome is just a lookup performed when that line runs, not when the function is defined)".
# - "Compilation requires that upfront whole-program resolution because the output is a finished binary — there's no "runtime" left to look things up in,
# everything must already be nailed down. Interpretation, by contrast, has no such finished-artifact step; the interpreter is still "there" at every line, so it can defer resolution until that line runs."
# - "So yes: interpreted execution is what makes late resolution possible, and compilation is what forces early resolution to be necessary. It's
# not a coincidence — it's a direct structural consequence of how each one gets from source code to running behavior."
# - "One caveat, for full precision: Not all compiled languages behave like C++, and not all interpreted languages resolve as late as Python — this
# is really about static binding vs dynamic binding, and "compiled vs interpreted" is the common cause, not a strict logical equivalence."



# One more extra problem:
# (Exemplifying the use of cmp_to_key for sorting)
# https://neetcode.io/problems/largest-number
# https://leetcode.com/problems/largest-number

# You are given a list of non-negative integers nums, arrange them such that they form the largest number and return it.
# Since the result may be very large, so you need to return a string instead of an integer.

# Example 1:
# Input: nums = [10,2]
# Output: "210"

# Example 2:
# Input: nums = [3,30,34,5,9]
# Output: "9534330"

# Constraints:
# 1 <= nums.length <= 100
# 0 <= nums[i] <= 1,000,000,000

class Solution:
    def largestNumber(self, nums: list[int]) -> str:
        nums_str = []
        for num in nums:
            nums_str.append(str(num))

        def compare(n1, n2):
            if n1 + n2 > n2 + n1:
                return -1  # Means that n1 should be placed before n2 indeed.
            else:
                return 1
        nums_str.sort(key=cmp_to_key(compare))
        return str(int("".join(nums_str)))  # Edge case with all nums being 0 also handled by int() here. In C++ that was handled as `return res[0] == '0' ? "0" : res;`. Could also have done `return res if res[0] != "0" else "0"` in Python here.



## LeetCode Python Boilerplate Patterns:

# DFS on a graph (adjacency list, avoid cycles)
def dfs_graph(start, graph):
    visited = set()

    def dfs(node):
        # doSomething(node)
        visited.add(node)
        for neighbor in graph[node]:
            if neighbor not in visited:  # `not in` is the idiomatic operator designed specifically for this use case, and is preferred/more Pythonic over `if not neighbor in visited:`.
                dfs(neighbor)

    dfs(start)
    return visited

# BFS on a graph (shortest path, unweighted)
def bfs_graph(start, target, graph):
    queue = deque([(start, 0)])  # (node, distance).
    enqueued = {start}  # Can start a set this way too.
    while queue:
        node, dist = queue.popleft()
        if node == target:  # Equivalent to `doSomething(node)` here.
            return dist
        for neighbor in graph[node]:
            if neighbor not in enqueued:
                queue.append((neighbor, dist + 1))
                enqueued.add(neighbor)
    return -1  # Unreachable (if target present in the graph).

# BFS on a grid (shortest path)
def bfs_grid(start, target, grid):
    rows, cols = len(grid), len(grid[0])
    queue = deque([(start[0], start[1], 0)])
    enqueued = {start}
    while queue:
        r, c, dist = queue.popleft()
        if (r, c) == target:
            return dist
        for dr, dc in [(0,1), (0,-1), (1,0), (-1,0)]:  # Nice iteration through directions.
            nr, nc = r + dr, c + dc
            if (0 <= nr < rows and 0 <= nc < cols and (nr, nc) not in enqueued and grid[nr][nc] != 0):
                queue.append((nr, nc, dist + 1))
                enqueued.add((nr, nc))
    return -1  # Unreachable (if target reachable from start in the grid).

# Backtracking (DFS with undo)
def backtrack(path, choices, result):
    if is_solution(path):
        result.append(path[:])  # Snapshot (copy), otherwise would have added there an object reference (mutable).
        return
    for choice in choices:
        if not is_valid(choice, path):
            continue
        path.append(choice)
        backtrack(path, choices, result)
        path.pop()  # Undo.

#  Boilerplate for `backtrack` above.
def is_solution(path):
    pass
def is_valid(choice, path):
    pass

# DFS on a tree (recursive)
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def dfs_tree(node):
    if node is None:
        return
    # pre-order: process node here
    dfs_tree(node.left)
    # in-order: process node here
    dfs_tree(node.right)
    # post-order: process node here

# Topological sort (Kahn's algorithm, BFS-based)
def topo_sort(num_nodes, edges):
    graph = defaultdict(list)  # This way when doing `graph[u]` for the first time it initializes its value to an empty list `[]` instead of raising an error.
    indegree = [0] * num_nodes
    for u, v in edges:  # u -> v.
        graph[u].append(v)
        indegree[v] += 1

    queue = deque([n for n in range(num_nodes) if indegree[n] == 0])  # `deque` initialized from `list`.
    order = []
    while queue:
        node = queue.popleft()
        order.append(node)
        for neighbor in graph[node]:
            indegree[neighbor] -= 1
            if indegree[neighbor] == 0:
                queue.append(neighbor)

    return order if len(order) == num_nodes else []  # Where `[]` means that a cycle was detected.

# Linked List
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

# Dummy head pattern (simplifies edge cases)
def solve(head):
    dummy = ListNode(0, head)
    prev, curr = dummy, head
    while curr:
        # ... manipulate prev/curr/curr.next
        prev, curr = curr, curr.next
    return dummy.next

# Reverse a linked list in-place
def reverse_list(head):
    prev, curr, next = None, head, None
    while curr:
        next = curr.next
        curr.next = prev
        prev = curr
        curr = next

    head = prev
    return head

# Remove Nth node from end (one pass - pretty neat)
def remove_nth_from_end(head, n):
    dummy = ListNode(0, head)
    fast = slow = dummy
    for _ in range(n):
        fast = fast.next
    while fast.next:
        fast = fast.next
        slow = slow.next
    slow.next = slow.next.next
    return dummy.next

# Fast/slow pointers (find middle, detect cycle) below:

# `findMiddle()` - if odd number of elements, the middle one stays in the first half.
def end_of_first_half(head):
    if head is None:
        return head
    slow = fast = head
    while fast.next and fast.next.next:  # Remember: the logical `and` allows short circuit if `fast.next` is `None` already.
        slow = slow.next
        fast = fast.next.next
    return slow

def has_cycle(head):
    if head is None:
        return False
    
    slow = fast = head
    while fast.next and fast.next.next:
        slow = slow.next
        fast = fast.next.next
        if slow == fast:
            return True

    return False

# Merge two sorted lists
def merge_two_sorted_lists(l1, l2):
    dummy = ListNode()
    tail = dummy
    while l1 and l2:
        if l1.val <= l2.val:
            tail.next, l1 = l1, l1.next
        else:
            tail.next, l2 = l2, l2.next
        tail = tail.next
    tail.next = l1 or l2  # equivalent to `= l1 if l1 is not None else l2`, or even `l1 if l1 else l2` since a non-None object is truthy in Python (while None is falsy). Also, note that `is not` is a single operator designed for this use case and preferred over `not ... is` on the first alternative in this phrase here.
    return dummy.next

# Two Pointer:

def two_sum_sorted(nums, target):  # Classic example.
    left, right = 0, len(nums) - 1
    while left < right:
        curr = nums[left] + nums[right]
        if curr == target:
            return (left, right)
        elif curr < target:
            left += 1
        else:
            right -= 1
    return (-1, -1)

# Same direction, fast/slow (in-place array modification - pretty neat)
def remove_duplicates(nums):
    slow = 0
    for fast in range(1, len(nums)):
        if nums[fast] != nums[slow]:
            slow += 1
            nums[slow] = nums[fast]
    return slow + 1  # New length.

# Sliding window (variable size - pretty neat)
def longest_substring_no_repeat(s):
    seen = set()
    left = 0
    max_len = 0
    for right in range(len(s)):
        while s[right] in seen:
            seen.remove(s[left])
            left += 1
        seen.add(s[right])
        max_len = max(max_len, right - left + 1)
    return max_len

# Sliding window (fixed size)
def max_sum_fixed_window(nums, k):
    window_sum = sum(nums[:k])  # Can call `sum` this way.
    max_sum = window_sum
    for right in range(k, len(nums)):
        window_sum += nums[right] - nums[right - k]
        max_sum = max(max_sum, window_sum)
    return max_sum

# Three pointer (3Sum pattern)
def three_sum(nums):
    nums.sort()
    result = []
    for i in range(len(nums) - 2):
        if i > 0 and nums[i] == nums[i - 1]:
            continue  # Skip duplicates.
        left, right = i + 1, len(nums) - 1
        while left < right:
            total = nums[i] + nums[left] + nums[right]
            if total == 0:
                result.append([nums[i], nums[left], nums[right]])
                left += 1
                right -= 1
                while left < right and nums[left] == nums[left - 1]:
                    left += 1
                while left < right and nums[right] == nums[right + 1]:
                    right -= 1
            elif total < 0:
                left += 1
            else:
                right -= 1
    return result

# K closest points / custom comparator (tuple trick)
def k_closest(points, k):
    heap = []
    for x, y in points:
        dist = x * x + y * y
        heapq.heappush(heap, (-dist, x, y))  # Max-heap of size k.
        if len(heap) > k:
            heapq.heappop(heap)
    return [(x, y) for _, x, y in heap]

# Merge K sorted lists
def merge_k_lists(lists):
    heap = []
    for i, node in enumerate(lists):
        if node:
            heapq.heappush(heap, (node.val, i, node))  # Here `i` breaks val ties.

    dummy = ListNode()
    tail = dummy
    while heap:
        val, i, node = heapq.heappop(heap)  # Min-heap returns the smallest, or if tie returns the one with smallest index `i` for the input list.
        tail.next = node
        tail = tail.next
        if node.next:
            heapq.heappush(heap, (node.next.val, i, node.next))
    return dummy.next

# Dijkstra's shortest path (heap-based)
def dijkstra(graph, start):
    # graph: dict[node] -> list of (neighbor, weight)
    dist = defaultdict(lambda: float("inf"))
    dist[start] = 0
    heap = [(0, start)]
    while heap:
        d, node = heapq.heappop(heap)
        if d > dist[node]:
            continue  # stale entry
        for neighbor, weight in graph[node]:
            new_dist = d + weight
            if new_dist < dist[neighbor]:
                dist[neighbor] = new_dist
                heapq.heappush(heap, (new_dist, neighbor))
    return dist

# Binary Search
def binary_search(nums, target):
    left, right = 0, len(nums) - 1
    while left <= right:
        mid = (left + right) // 2  # Round down.
        if nums[mid] == target:
            return mid
        elif nums[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1

# Search on answer space ("binary search the answer") - interesting to remember given the constraints (hint), or input.
# Use when the problem asks to minimize/maximize a value and you can write a feasible(x) check that's
# monotonic (False...False True...True or vice versa - like "First machine factory version with problem etc").
def binary_search_answer(lo, hi, feasible):
    while lo < hi:  # Check edge case of equality to return `lo`.
        mid = (lo + hi) // 2
        if feasible(mid):
            hi = mid       # Mid works, try smaller.
        else:
            lo = mid + 1   # Mid doesn't work, need bigger.
    return lo

# Example: minimum capacity to ship packages within `days`:
def ship_within_days(weights, days):
    def feasible(capacity):
        needed_days, curr = 1, 0
        for w in weights:
            if curr + w > capacity:
                needed_days += 1
                curr = 0
            curr += w
        return needed_days <= days

    lo, hi = max(weights), sum(weights)  # Since all objects have to fit, the minimum capacity is = size of largest weight, and the max capacity is the sum of all weights (shipping all together in 1 day).
    return binary_search_answer(lo, hi, feasible)

# Search in rotated sorted array
def search_rotated(nums, target):
    left, right = 0, len(nums) - 1
    while left <= right:
        mid = (left + right) // 2
        if nums[mid] == target:
            return mid
        if nums[left] <= nums[mid]:  # Left half is sorted.
            if nums[left] <= target < nums[mid]:
                right = mid - 1
            else:
                left = mid + 1
        else:  # Right half is sorted.
            if nums[mid] < target <= nums[right]:
                left = mid + 1
            else:
                right = mid - 1
    return -1

# Dynamic Programming
# 1D DP (bottom-up, e.g., climbing stairs / house robber)
def climb_stairs(n):
    if n <= 2:
        return n
    dp = [0] * (n + 1)
    dp[1], dp[2] = 1, 2
    for i in range(3, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]
    return dp[n]

# Space-optimized (rolling variables)
def climb_stairs_optimized(n):
    if n <= 2:
        return n
    prev2, prev1 = 1, 2
    for _ in range(3, n + 1):
        prev2, prev1 = prev1, prev1 + prev2
    return prev1

# Top-down memoization
def solve(n):
    @lru_cache(maxsize=None)  # The arguments of the cached function must be hashable (tuple, int ...). Show you know under the hood and maybe prioritize implementing with `memo` indeed.
    def dp(i):
        if i <= 2:
            return i
        return dp(i - 1) + dp(i - 2)
    return dp(n)

# 2D DP (grid path / edit distance style)
def unique_paths(m, n):
    dp = [[1] * n for _ in range(m)]
    for r in range(1, m):
        for c in range(1, n):
            dp[r][c] = dp[r - 1][c] + dp[r][c - 1]
    return dp[m - 1][n - 1]

def edit_distance(word1, word2):
    m, n = len(word1), len(word2)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    for i in range(m + 1):
        dp[i][0] = i
    for j in range(n + 1):
        dp[0][j] = j
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if word1[i - 1] == word2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                dp[i][j] = 1 + min(dp[i - 1][j],    # delete
                                    dp[i][j - 1],    # insert
                                    dp[i - 1][j - 1]) # replace
    return dp[m][n]

# 0/1 Knapsack
def knapsack(weights, values, capacity):
    n = len(weights)
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        for w in range(capacity + 1):
            dp[i][w] = dp[i - 1][w]  # skip item i-1
            if weights[i - 1] <= w:
                dp[i][w] = max(dp[i][w],
                                dp[i - 1][w - weights[i - 1]] + values[i - 1])
    return dp[n][capacity]

# Longest Increasing Subsequence (O(n log n))
def length_of_lis(nums):
    tails = []
    for num in nums:
        idx = bisect.bisect_left(tails, num)
        if idx == len(tails):
            tails.append(num)
        else:
            tails[idx] = num
    return len(tails)

# Intervals
# Sort + merge overlapping intervals
def merge_intervals(intervals):
    intervals.sort(key=lambda x: x[0])
    merged = [intervals[0]]
    for start, end in intervals[1:]:
        if start <= merged[-1][1]:  # overlap
            merged[-1][1] = max(merged[-1][1], end)
        else:
            merged.append([start, end])
    return merged

# Insert interval
def insert_interval(intervals, new_interval):
    result = []
    i = 0
    n = len(intervals)
    while i < n and intervals[i][1] < new_interval[0]:
        result.append(intervals[i])
        i += 1
    while i < n and intervals[i][0] <= new_interval[1]:
        new_interval[0] = min(new_interval[0], intervals[i][0])
        new_interval[1] = max(new_interval[1], intervals[i][1])
        i += 1
    result.append(new_interval)
    while i < n:
        result.append(intervals[i])
        i += 1
    return result

# Meeting rooms II (min rooms needed, heap-based)
def min_meeting_rooms(intervals):
    intervals.sort(key=lambda x: x[0])
    heap = []  # end times of ongoing meetings
    for start, end in intervals:
        if heap and heap[0] <= start:
            heapq.heapreplace(heap, end)
        else:
            heapq.heappush(heap, end)
    return len(heap)

# Union-Find (Disjoint Set Union)
# (Common uses: number of connected components, redundant connection, accounts merge, Kruskal's MST)
class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
        self.count = n  # number of connected components

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # path compression
        return self.parent[x]

    def union(self, x, y):
        root_x, root_y = self.find(x), self.find(y)
        if root_x == root_y:
            return False  # already connected
        if self.rank[root_x] < self.rank[root_y]:
            root_x, root_y = root_y, root_x
        self.parent[root_y] = root_x
        if self.rank[root_x] == self.rank[root_y]:
            self.rank[root_x] += 1
        self.count -= 1
        return True

# Trie (Prefix Tree)
class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word):
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_end = True

    def search(self, word):
        node = self._find(word)
        return node is not None and node.is_end

    def starts_with(self, prefix):
        return self._find(prefix) is not None

    def _find(self, word):
        node = self.root
        for ch in word:
            if ch not in node.children:
                return None
            node = node.children[ch]
        return node

# Monotonic Stack
# (Useful for "next greater/smaller element" style problems)
def next_greater_element(nums):
    n = len(nums)
    result = [-1] * n
    stack = []  # indices, values in decreasing order
    for i in range(n):
        while stack and nums[stack[-1]] < nums[i]:
            result[stack.pop()] = nums[i]
        stack.append(i)
    return result

# Daily temperatures (distance to next warmer day)
def daily_temperatures(temps):
    n = len(temps)
    result = [0] * n
    stack = []
    for i, t in enumerate(temps):
        while stack and temps[stack[-1]] < t:
            prev_i = stack.pop()
            result[prev_i] = i - prev_i
        stack.append(i)
    return result

# Prefix Sum
def build_prefix_sum(nums):
    prefix = [0] * (len(nums) + 1)
    for i, num in enumerate(nums):
        prefix[i + 1] = prefix[i] + num
    return prefix  # sum(nums[i:j]) == prefix[j] - prefix[i]

# Subarray sum equals K (hashmap + prefix sum)
def subarray_sum_equals_k(nums, k):
    count = 0
    curr_sum = 0
    seen = {0: 1}  # prefix sum -> frequency
    for num in nums:
        curr_sum += num
        count += seen.get(curr_sum - k, 0)
        seen[curr_sum] = seen.get(curr_sum, 0) + 1
    return count

# Quick decision guide
# Signal in problem                                                     ->    Likely pattern
# "shortest path", "minimum steps", "level by level"                    ->    BFS
# "all paths", "all combinations", tree traversal, connected components ->    DFS / backtracking
# Reversing, cycle detection, merging, "kth from end"                   ->    Linked list two-pointer (fast/slow)
# Sorted array, pair/triplet sum, palindrome                            ->    Two pointer (converging)
# Substring/subarray with a condition                                   ->    Sliding window
# "Kth largest/smallest", "top K", running median                       ->    Heap
# Sorted array/matrix, "minimize the maximum", "find in O(log n)"       ->    Binary search
# "number of ways", "min/max cost", overlapping subproblems             ->    Dynamic programming
# Scheduling, overlapping ranges, "meeting rooms"                       ->    Intervals
# "connected components", "is there a cycle", grouping                  ->    Union-Find
# Prefix matching, autocomplete, word search dictionary                 ->    Trie
# "next greater/smaller", stock span, histogram area                    ->    Monotonic stack
# Subarray sum, range sum queries                                       ->    Prefix sum (+ hashmap for "equals K")


# Python interview idioms worth having muscle memory for (coming from C++):
# from collections import defaultdict, Counter, deque
# import heapq, bisect
# import math
# from functools import lru_cache, cache

# defaultdict avoids KeyError boilerplate when trying to access a key not present but wanting default behavior on that case.
graph = defaultdict(list)

# Counter for frequency maps.
k = 2
freq = Counter(nums)
most_common = freq.most_common(k)  # k most frequent elements.

# enumerate instead of manual indexing.
for i, val in enumerate(nums):
    ...

# zip for parallel iteration.
list1, list2 = ["a", "b"], [1, 2]
for a, b in zip(list1, list2):
    ...

# Sorting with custom key (no comparator functions like C++).
pairs = []
pairs.sort(key=lambda x: (x[0], -x[1]))  # multi-key sort.

# Unpacking/swapping.
a, b = b, a

# List comprehension vs. explicit loop (use for simple transforms).
squares = [x * x for x in nums if x % 2 == 0]

# Note: `math.inf` requires `import math`. It is functionally identical to `float("inf")` - so prefer `float("inf")` instead for LeetCode problems (normally enough).
# Claude commented too: math.inf (or `float("inf")`) instead of INT_MAX/MIN
best = math.inf  # type float -> limits for float since for int the limit is basically the system memory.
worst = -math.inf
