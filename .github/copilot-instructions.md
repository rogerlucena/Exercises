# AI Coding Agent Instructions

This is an interview exercise repository focused on competitive programming and algorithm problem-solving in C++.

## Repository Structure

- **`Problems/`** – Main directory containing ~70+ algorithm problems (e.g., `__3_sum_zero.cpp`, `__longest_increasing_subsequence.cpp`). File naming convention:
  - `__` prefix: Key/interesting problems with essential algorithmic ideas to retain
  - `_` prefix: Challenging problems (higher difficulty but may lack core insights)
  - No prefix: Standard problems
  
- **`remember_*.cpp`** – Reference implementations and pattern reminders:
  - `remember_vector.cpp`, `remember_strings.cpp`, `remember_hash_map.cpp`: STL basics
  - `remember_sort_binary_search_and_lower_bound.cpp`, `remember_stack_and_queue.cpp`: Core algorithms
  - `remember_by_heart.cpp`: DFS/BFS template code, recursion patterns
  - Contain pseudo-code and working examples—reference these when writing graph/tree solutions

- **`tools.cpp`** – Shared utilities (always included in Problems):
  - `printVector()`, `printMatrix()`: Templated output functions
  - `ListNode` struct with `generateList()`: Linked list helpers
  - Include via `#include "tools.cpp"` from Problem files

- **`main.cpp`** – Minimal entry point for testing (compiles and runs individual problems)

- **`My Notes.txt`** – 500+ lines of algorithm theory: complexity analysis, sorting stability, DFS/BFS applications, topological sort, two-pointer techniques, tree traversals

## Key Architectural Patterns

### File & Include Structure
- Problems include: `#include <vector> <iostream> <algorithm>` + `#include "tools.cpp"`
- No header guards—files directly included (legacy C++ style)
- Standard library: `<vector>`, `<unordered_map>`, `<unordered_set>`, `<queue>`, `<stack>`, `<algorithm>`, `<string>`, `<functional>`, `<limits>`

### Compilation & Execution
- **Build**: CMake via `CMakeLists.txt` (minimal, targets `main.cpp` only)
- **Manual compile**: `g++ -std=c++17 <file>.cpp -o <file>; ./<file>`
- **No automated tests**—verify solutions by running compiled executable and checking output manually

### Critical Coding Conventions
1. **Vector edge case handling**: Empty vectors (`v.size() - 1`) risk underflow → always check `v.size() == 0` separately before backward iteration
2. **Two-pointer technique**: Core pattern (e.g., `__3_sum_zero.cpp`). Start with brute force, analyze which iterations can be skipped
3. **DFS template** (in `remember_by_heart.cpp`): Use recursive form preferentially; keep `visited` boolean map; mark visited *before* recursing on neighbors
4. **BFS template**: Keep `enqueued` set (not `visited`) to track added-to-queue nodes; mark enqueued *before* adding to queue
5. **Topological sort patterns**: 
   - In-degree based (queue): for cycle detection, track `visitedCount` vs `V`
   - DFS+stack: only for known DAGs
   - Observation: First vertex always has in-degree 0; max edges in DAG = n(n-1)/2
6. **Stable sorting**: Merge/Insertion sorts preserve element order; Quick/Heap do not
7. **Linked lists**: Always use provided `ListNode` struct from `tools.cpp`; for merge sort, no extra space needed (insertion is O(1))

## Common Algorithmic Patterns in Codebase

- **Binary search & lower_bound**: See `remember_sort_binary_search_and_lower_bound.cpp`
- **DP & subsequences**: `__longest_increasing_subsequence.cpp`, `__longest_common_subsequence.cpp`
- **Graphs (DFS/BFS)**: `__course_schedule_dependecies.cpp`, `__evaluate_division.cpp`
- **Priority queues & heaps**: `remember_priority_queue.cpp`
- **Interval/merge problems**: `__merge_k_sorted_linked_lists.cpp`, `__meeting_rooms.cpp`
- **Matrix search**: `__search_2d_matrix.cpp`
- **Tree traversals**: See `My Notes.txt`—Inorder (BST ascending), Preorder (copy), Postorder (delete)

## Dependencies & Environment

- **Language**: C++11/C++17 (stdlib with containers, templates, structured bindings)
- **External libs**: None (pure STL)
- **IDE setup**: CMake project with `.vscode/settings.json` configuration
- **Compilation standard**: `-std=c++11` in CMake; local testing uses `-std=c++17`

## Conventions for New Solutions

1. Include `#include "tools.cpp"` for vector/matrix printing and `ListNode`
2. Name functions clearly; avoid main() if only solving one problem (test in isolation)
3. Document problem source (e.g., comment with LeetCode/InterviewBit URL)
4. For graph problems: template DFS/BFS from `remember_by_heart.cpp`
5. Add comments on algorithmic trick or complexity (e.g., "two-pointer O(n²)", "DP O(n²) space")
6. Manually test with edge cases (empty input, single element, duplicates)

## Debugging & Testing Workflow

1. Compile: `g++ -std=c++17 Problems/__<name>.cpp -o <name>`
2. Run: `./<name>`
3. Use `printVector()` / `printMatrix()` helpers for output verification
4. Common pitfalls (from codebase comments):
   - Forgotten edge cases in vector loops
   - Off-by-one in two-pointer techniques
   - Duplicate handling in sorted-array problems (use deduplication checks)
   - DFS stack vs queue confusion (recursive DFS vs iterative BFS)
