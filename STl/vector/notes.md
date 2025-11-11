# C++ Vector - Complete Notes

## 1. Size vs Capacity

**Size** = Number of elements currently in the vector
**Capacity** = Total space allocated (can hold this many elements without reallocation)

```cpp
vector<int> v;
v.push_back(1);
v.push_back(2);
cout << v.size();     // 2 (actual elements)
cout << v.capacity(); // 2 or more (allocated space)
```

**Key Point**: Capacity is always >= Size. Vector pre-allocates extra space to avoid frequent reallocations.

---

## 2. How Vector Internally Works

- Vector uses **dynamic arrays** stored in contiguous memory
- When created, allocates initial capacity (implementation-dependent)
- When size exceeds capacity:
  1. Allocates new larger memory (typically 2x current capacity)
  2. Copies/moves all elements to new location
  3. Deallocates old memory

```cpp
vector<int> v;           // capacity: 0
v.push_back(1);          // capacity might become 1
v.push_back(2);          // capacity might become 2
v.push_back(3);          // capacity might become 4 (doubled!)
```

**Memory Layout**: `[elem0][elem1][elem2][empty][empty]...`

---

## 3. push_back() vs emplace_back()

### push_back()
- Creates object first, then copies/moves it into vector
- Takes an object as parameter

### emplace_back()
- Constructs object **directly** in vector's memory
- Takes constructor arguments
- More efficient (no copy/move)

```cpp
vector<pair<int, int>> v;

// push_back: create pair, then copy into vector
v.push_back(make_pair(1, 2));  // or v.push_back({1, 2});

// emplace_back: construct pair directly in vector
v.emplace_back(1, 2);          // More efficient!
```

**When to use**: Use `emplace_back()` for complex objects to avoid extra copy.

---

## 4. Array vs Vector

| Feature | Array | Vector |
|---------|-------|--------|
| Size | Fixed at compile-time | Dynamic (can grow/shrink) |
| Memory | Stack (usually) | Heap |
| Declaration | `int arr[5]` | `vector<int> v(5)` |
| Bounds checking | No | Yes (with `.at()`) |
| Functions | Minimal | Rich (push_back, insert, etc.) |
| Overhead | None | Small (size, capacity tracking) |

```cpp
// Array
int arr[5] = {1, 2, 3, 4, 5};  // Fixed size

// Vector
vector<int> v = {1, 2, 3, 4, 5};  
v.push_back(6);                // Can grow!
```

---

## 5. "Vector only grows when size would exceed capacity"

This means vector doesn't reallocate memory on every `push_back()`.

```cpp
vector<int> v;
v.reserve(10);              // Pre-allocate capacity = 10

v.push_back(1);             // size=1, cap=10 (no reallocation)
v.push_back(2);             // size=2, cap=10 (no reallocation)
// ... up to 10 elements ...
v.push_back(11);            // size=11, cap=20 (NOW it grows!)
```

**Growth happens only when**: `size + 1 > capacity`

**Why?** To minimize expensive memory reallocations. Amortized O(1) insertion time.

---

## 6. Vector Functions Reference

### Access
```cpp
v[i]           // Access element (no bounds check)
v.at(i)        // Access element (throws exception if out of bounds)
v.front()      // First element
v.back()       // Last element
v.data()       // Pointer to underlying array
```

### Capacity
```cpp
v.size()       // Number of elements
v.capacity()   // Allocated space
v.empty()      // Returns true if size == 0
v.reserve(n)   // Pre-allocate space for n elements
v.shrink_to_fit() // Reduce capacity to match size
```

### Modifiers
```cpp
v.push_back(x)    // Add element at end
v.emplace_back(x) // Construct element at end
v.pop_back()      // Remove last element
v.insert(pos, x)  // Insert x before pos
v.erase(pos)      // Remove element at pos
v.erase(first, last) // Remove range [first, last)
v.clear()         // Remove all elements (size=0)
v.resize(n)       // Change size to n
v.assign(n, x)    // Assign n copies of x
v.swap(v2)        // Swap contents with v2
```

### Example
```cpp
vector<int> v = {1, 2, 3};
v.push_back(4);              // {1,2,3,4}
v.pop_back();                // {1,2,3}
v.insert(v.begin() + 1, 9);  // {1,9,2,3}
v.erase(v.begin());          // {9,2,3}
v.clear();                   // {}
```

---

## 7. Why erase() and insert() are Costly?

**Reason**: Both require **shifting elements** in contiguous memory.

### insert() at position i:
1. Shift all elements from i to end **one position right**
2. Insert new element at position i
3. Time: **O(n)**

```cpp
// Insert 99 at index 1
// Before: [10, 20, 30, 40]
//          0   1   2   3
// After:  [10, 99, 20, 30, 40]
//          0   1   2   3   4
// Must shift 20, 30, 40 → O(n)
```

### erase() at position i:
1. Shift all elements after i **one position left**
2. Decrease size
3. Time: **O(n)**

```cpp
// Erase index 1
// Before: [10, 20, 30, 40]
//          0   1   2   3
// After:  [10, 30, 40]
//          0   1   2
// Must shift 30, 40 ← O(n)
```

**Costly at**: Beginning/middle. Fast at end (push_back/pop_back are O(1)).

---

## 8. Vector Iterator

An **iterator** is an object that points to an element in the vector (like a smart pointer).

```cpp
vector<int> v = {10, 20, 30};
vector<int>::iterator it = v.begin();

cout << *it;        // 10 (dereference)
it++;               // Move to next element
cout << *it;        // 20
```

**Why use?** Generic way to traverse containers. Works with algorithms.

```cpp
// Find element using iterator
auto it = find(v.begin(), v.end(), 20);
if (it != v.end()) {
    cout << "Found at index: " << (it - v.begin());
}
```

---

## 9. begin() and end()

### begin()
- Returns iterator to the **first element**
- `*v.begin()` gives first element value

### end()
- Returns iterator to **one past the last element** (not the last element!)
- Used as sentinel/boundary
- **Never dereference** `v.end()`

```cpp
vector<int> v = {1, 2, 3};

//        begin()         end()
//          ↓              ↓
//        [1] [2] [3]  [past-end]

auto it = v.begin();    // Points to 1
cout << *it;            // 1 ✓

it = v.end();
cout << *it;            // UNDEFINED BEHAVIOR! ✗
```

### Traversal Pattern
```cpp
for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
}
// Output: 1 2 3
```

---

## 10. rbegin() and rend()

**Reverse iterators** - traverse vector in reverse order.

### rbegin()
- Returns iterator to the **last element**
- Moves **backward** with `++`

### rend()
- Returns iterator to **one before first element**
- Boundary marker

```cpp
vector<int> v = {1, 2, 3, 4};

//    rend()                    rbegin()
//      ↓                         ↓
//  [before] [1] [2] [3] [4]

for (auto it = v.rbegin(); it != v.rend(); ++it) {
    cout << *it << " ";
}
// Output: 4 3 2 1
```

### Comparison
```cpp
vector<int> v = {1, 2, 3};

// Forward
cout << *v.begin();   // 1
cout << *(v.end()-1); // 3

// Reverse
cout << *v.rbegin();  // 3
cout << *(v.rend()-1);// 1
```

---

## Quick Reference Card

```cpp
// Creation
vector<int> v;              // Empty
vector<int> v(5);           // 5 elements (value 0)
vector<int> v(5, 10);       // 5 elements (value 10)
vector<int> v = {1,2,3};    // Initializer list

// Most Used Operations
v.push_back(x);             // Add at end - O(1)*
v.pop_back();               // Remove from end - O(1)
v.size();                   // Current size
v[i];                       // Access element
v.clear();                  // Empty the vector

// Iteration
for(int x : v)              // Range-based
for(auto it = v.begin(); it != v.end(); ++it)  // Iterator
for(int i = 0; i < v.size(); i++)              // Index

// When to use what?
// - Use push_back/pop_back: Very fast O(1)
// - Avoid insert/erase in middle: Slow O(n)
// - Need sorted insertions? Consider set/multiset
// - Need frequent middle operations? Consider list/deque
```

---

**Pro Tips:**
- Use `reserve()` if you know final size → avoids reallocations
- Use `emplace_back()` for complex objects → avoids copies
- Use `shrink_to_fit()` after many deletions → reclaim memory
- Check `empty()` instead of `size() == 0` → clearer intent
