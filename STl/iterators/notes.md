# C++ Iterators - Complete Notes

## 1. What are Iterators?

An **iterator** is an object that acts like a pointer to access elements in a container (vector, list, map, etc.).

Think of it as a **bookmark** in a book - it points to a specific position and you can move it forward/backward.

```cpp
vector<int> v = {10, 20, 30, 40};
vector<int>::iterator it = v.begin();  // Iterator pointing to first element

cout << *it;     // 10 (access value using *)
it++;            // Move to next element
cout << *it;     // 20
```

**Key Point**: Iterators provide a **uniform way** to traverse different containers without knowing their internal structure.

---

## 2. Iterators vs Pointers

| Feature | Pointer | Iterator |
|---------|---------|----------|
| What it points to | Memory address | Container element |
| Works with | Arrays, raw memory | STL containers (vector, list, map, etc.) |
| Arithmetic | `ptr++`, `ptr + 5` | Depends on container type |
| Type | `int*`, `char*` | `vector<int>::iterator`, `list<int>::iterator` |
| Abstraction | Low-level | High-level |
| Safety | Can be dangerous | Safer with bounds |

### Detailed Comparison

```cpp
// POINTER (works with arrays)
int arr[] = {1, 2, 3, 4};
int* ptr = arr;
cout << *ptr;      // 1
ptr++;             // Move to next element
cout << *ptr;      // 2
ptr + 2;           // Jump 2 positions (direct memory arithmetic)

// ITERATOR (works with containers)
vector<int> v = {1, 2, 3, 4};
vector<int>::iterator it = v.begin();
cout << *it;       // 1
it++;              // Move to next element
cout << *it;       // 2
advance(it, 2);    // Jump 2 positions (using STL function)
```

### Why Iterators ≠ Pointers?

1. **Pointers are raw memory addresses**
   - Work only with contiguous memory (arrays, vectors)
   - Direct arithmetic: `ptr + 5` works

2. **Iterators are smart objects**
   - Work with non-contiguous memory too (lists, maps)
   - Can override operators to work differently for each container

```cpp
// Vector: contiguous memory, iterator behaves like pointer
vector<int> v = {1, 2, 3};
auto it = v.begin();
it + 2;  // ✓ Works! (Random access)

// List: non-contiguous memory, iterator is NOT a pointer
list<int> l = {1, 2, 3};
auto it2 = l.begin();
it2 + 2;  // ✗ ERROR! (Can only do it2++ or advance())
```

---

## 3. Why Use Iterators?

### Reason 1: **Generic Code**
Write code that works with ANY container.

```cpp
// Function works with vector, list, deque, etc.!
template<typename Iterator>
void printAll(Iterator start, Iterator end) {
    for (auto it = start; it != end; ++it) {
        cout << *it << " ";
    }
}

vector<int> v = {1, 2, 3};
list<int> l = {4, 5, 6};
printAll(v.begin(), v.end());  // Works!
printAll(l.begin(), l.end());  // Also works!
```

### Reason 2: **STL Algorithm Compatibility**
All STL algorithms use iterators.

```cpp
vector<int> v = {5, 2, 8, 1, 9};

// Sort
sort(v.begin(), v.end());

// Find
auto it = find(v.begin(), v.end(), 8);
if (it != v.end()) {
    cout << "Found at position: " << (it - v.begin());
}

// Reverse
reverse(v.begin(), v.end());

// All use iterators!
```

### Reason 3: **Flexibility with Different Containers**
Each container has memory layout differences, but iterators hide that complexity.

```cpp
// Vector: [1][2][3][4] (contiguous)
vector<int> v = {1, 2, 3, 4};
auto it1 = v.begin();  // Iterator handles contiguous memory

// List: [1]→[2]→[3]→[4] (linked nodes)
list<int> l = {1, 2, 3, 4};
auto it2 = l.begin();  // Iterator handles pointer jumping

// Same syntax, different internal logic!
```

### Reason 4: **Range Operations**
Easily work with subranges.

```cpp
vector<int> v = {1, 2, 3, 4, 5, 6};

// Sort only middle part
sort(v.begin() + 2, v.begin() + 5);  // Sort {3, 4, 5}

// Erase range
v.erase(v.begin() + 1, v.begin() + 3);  // Remove {2, 3}
```

---

## 4. Role of `auto` Keyword with Iterators

The `auto` keyword makes iterator declarations **much shorter and cleaner**.

### Without auto (verbose!)
```cpp
vector<int> v = {1, 2, 3};
vector<int>::iterator it = v.begin();  // Long type name!

vector<pair<string, int>> vp;
vector<pair<string, int>>::iterator it2 = vp.begin();  // Very long!
```

### With auto (clean!)
```cpp
vector<int> v = {1, 2, 3};
auto it = v.begin();  // Compiler figures out the type!

vector<pair<string, int>> vp;
auto it2 = vp.begin();  // Much cleaner!
```

### How `auto` Works
Compiler **automatically deduces** the type from the right-hand side.

```cpp
auto it = v.begin();
// Compiler sees: v is vector<int>
// So: it must be vector<int>::iterator

auto it2 = v.rbegin();
// Compiler deduces: vector<int>::reverse_iterator
```

### Real-World Example
```cpp
map<string, vector<int>> myMap;

// Without auto 😰
map<string, vector<int>>::iterator it = myMap.begin();

// With auto 😊
auto it = myMap.begin();

// Both are identical, but auto is WAY easier to read!
```

### When NOT to use auto
If you want to be **explicit** about the type for clarity.

```cpp
// Explicit (good for beginners learning)
vector<int>::iterator it = v.begin();

// Auto (good for experienced coders)
auto it = v.begin();
```

---

## 5. Types of Iterators

C++ has **5 types** of iterators based on capabilities:

### 1. Input Iterator (Read Only, Forward)
- Read elements once
- Move forward only
- Example: `istream_iterator`

```cpp
istream_iterator<int> it(cin);  // Read from input
cout << *it;  // Read value
++it;         // Move forward
```

### 2. Output Iterator (Write Only, Forward)
- Write elements once
- Move forward only
- Example: `ostream_iterator`

```cpp
ostream_iterator<int> it(cout, " ");
*it = 10;  // Write value to cout
++it;
```

### 3. Forward Iterator (Read/Write, Forward)
- Read and write multiple times
- Move forward only
- Example: `forward_list<int>::iterator`

```cpp
forward_list<int> fl = {1, 2, 3};
auto it = fl.begin();
*it = 10;  // Modify
++it;      // Move forward only
```

### 4. Bidirectional Iterator (Read/Write, Both Directions)
- Read and write multiple times
- Move forward AND backward
- Example: `list<int>::iterator`, `map<int>::iterator`

```cpp
list<int> l = {1, 2, 3};
auto it = l.begin();
++it;  // Forward
--it;  // Backward (works!)
```

### 5. Random Access Iterator (Full Access)
- All operations of bidirectional
- Jump to any position (`it + n`)
- Fastest type
- Example: `vector<int>::iterator`, `deque<int>::iterator`

```cpp
vector<int> v = {1, 2, 3, 4, 5};
auto it = v.begin();
it + 3;      // Jump 3 positions ✓
it += 2;     // Jump 2 ✓
it < v.end(); // Comparison ✓
```

**Visual Summary:**
```
Input →  [Read once]
Output → [Write once]
Forward → [Read/Write, →]
Bidirectional → [Read/Write, ← →]
Random Access → [Read/Write, ← →, Jump anywhere]
```

---

## 6. Iterator Operations

### Common Operations (All Iterators)
```cpp
*it        // Access element
it++       // Move to next (postfix)
++it       // Move to next (prefix, faster!)
it1 == it2 // Compare equality
it1 != it2 // Compare inequality
```

### Bidirectional Iterator Additional Operations
```cpp
it--       // Move to previous
--it       // Move to previous (prefix, faster!)
```

### Random Access Iterator Additional Operations
```cpp
it + n     // Jump forward by n
it - n     // Jump backward by n
it += n    // Move forward by n
it -= n    // Move backward by n
it1 - it2  // Distance between iterators
it[n]      // Access nth element (same as *(it + n))
it1 < it2  // Comparison operators
it1 > it2
it1 <= it2
it1 >= it2
```

### Example: All Operations
```cpp
vector<int> v = {10, 20, 30, 40, 50};
auto it = v.begin();

*it;           // 10
++it;          // Points to 20
*it;           // 20
it += 2;       // Points to 40
*it;           // 40
--it;          // Points to 30
it[1];         // Access v[current+1] = 40
v.end() - it;  // Distance from current to end
```

---

## 7. const_iterator

A **const_iterator** is an iterator that points to **const elements** (read-only).

```cpp
vector<int> v = {1, 2, 3};

// Regular iterator (can modify)
vector<int>::iterator it = v.begin();
*it = 10;  // ✓ Allowed

// Const iterator (cannot modify)
vector<int>::const_iterator cit = v.cbegin();
*cit;      // ✓ Read allowed
*cit = 10; // ✗ ERROR! Cannot modify
```

### When to use?
When you want to **prevent accidental modifications**.

```cpp
void printVector(const vector<int>& v) {
    // Must use const_iterator for const vector
    for (auto it = v.cbegin(); it != v.cend(); ++it) {
        cout << *it << " ";
    }
}
```

### cbegin() and cend()
Return const iterators explicitly.

```cpp
auto it1 = v.begin();   // iterator
auto it2 = v.cbegin();  // const_iterator

// Best practice: use cbegin/cend when not modifying
for (auto it = v.cbegin(); it != v.cend(); ++it) {
    cout << *it << " ";  // Just reading
}
```

---

## 8. Reverse Iterators

Already covered in vector notes, but here's a quick recap:

```cpp
vector<int> v = {1, 2, 3, 4};

// Forward iteration
for (auto it = v.begin(); it != v.end(); ++it)
    cout << *it << " ";  // 1 2 3 4

// Reverse iteration
for (auto it = v.rbegin(); it != v.rend(); ++it)
    cout << *it << " ";  // 4 3 2 1
```

**Note**: `++` on reverse iterator moves **backward** in the container!

---

## 9. Iterator Invalidation ⚠️

**Critical Concept**: Some operations invalidate iterators!

### Vector Invalidation Rules
```cpp
vector<int> v = {1, 2, 3, 4, 5};
auto it = v.begin() + 2;  // Points to 3

// DANGER: push_back might reallocate!
v.push_back(6);
cout << *it;  // ⚠️ UNDEFINED! Iterator might be invalid

// DANGER: insert/erase shifts elements
v.erase(v.begin());
cout << *it;  // ⚠️ Invalid! Points to wrong element or garbage
```

### Safe Pattern
```cpp
// After modifying, re-get iterator
it = v.begin() + 2;  // ✓ Safe again
```

### Container-Specific Rules
- **Vector**: Invalidated by push_back (if reallocation), insert, erase
- **List**: Only erased elements' iterators invalidated
- **Map/Set**: Only erased elements' iterators invalidated

---

## 10. Useful STL Functions with Iterators

### advance()
Move iterator by n positions.

```cpp
list<int> l = {1, 2, 3, 4, 5};
auto it = l.begin();
advance(it, 3);  // Move 3 positions
cout << *it;     // 4
```

### distance()
Get distance between two iterators.

```cpp
vector<int> v = {1, 2, 3, 4, 5};
auto it1 = v.begin();
auto it2 = v.end();
cout << distance(it1, it2);  // 5
```

### next() and prev()
Get iterator n positions away (doesn't modify original).

```cpp
vector<int> v = {1, 2, 3, 4, 5};
auto it = v.begin();
auto it2 = next(it, 2);   // 2 positions forward
auto it3 = prev(it2, 1);  // 1 position backward

cout << *it;   // 1 (unchanged)
cout << *it2;  // 3
cout << *it3;  // 2
```

---

## Quick Reference Card

```cpp
// Declaration
vector<int>::iterator it;           // Regular iterator
vector<int>::const_iterator cit;    // Read-only iterator
vector<int>::reverse_iterator rit;  // Reverse iterator
auto it = v.begin();                // Let compiler deduce type

// Common Operations
*it              // Access value
++it, it++       // Move forward
--it, it--       // Move backward (bidirectional/random)
it + n, it - n   // Jump positions (random access only)

// Range Iteration
for (auto it = v.begin(); it != v.end(); ++it)

// STL Functions
advance(it, n)      // Move iterator
distance(it1, it2)  // Get distance
next(it, n)         // Get iterator n ahead
prev(it, n)         // Get iterator n behind

// Container Methods
v.begin()    // First element
v.end()      // Past-the-end
v.rbegin()   // Last element (reverse)
v.rend()     // Before-first (reverse)
v.cbegin()   // Const begin
v.cend()     // Const end
```

---

## Pro Tips & Best Practices

1. **Use `auto`** - Makes code cleaner and less error-prone
   ```cpp
   auto it = v.begin();  // ✓ Better than vector<int>::iterator it
   ```

2. **Prefer prefix `++it`** over postfix `it++`
   ```cpp
   ++it;  // ✓ Slightly faster (no temporary copy)
   it++;  // Works, but creates temporary
   ```

3. **Use `cbegin()`/`cend()`** when not modifying
   ```cpp
   for (auto it = v.cbegin(); it != v.cend(); ++it)  // ✓ Read-only
   ```

4. **Watch for iterator invalidation** after insert/erase/push_back
   ```cpp
   auto it = v.begin();
   v.push_back(10);   // ⚠️ it might be invalid now!
   ```

5. **Use range-based for** when you don't need the iterator itself
   ```cpp
   for (int x : v)    // ✓ Simpler than iterators for just values
   ```

6. **Use algorithms** instead of manual iteration
   ```cpp
   auto it = find(v.begin(), v.end(), 5);           // ✓ Better
   // Than manual loop:
   for (auto it = v.begin(); it != v.end(); ++it)
       if (*it == 5) break;
   ```

---

## Common Mistakes to Avoid ❌

### 1. Dereferencing end()
```cpp
auto it = v.end();
cout << *it;  // ❌ UNDEFINED BEHAVIOR! end() is past-the-end
```

### 2. Using invalidated iterators
```cpp
auto it = v.begin();
v.clear();
cout << *it;  // ❌ Iterator is invalid after clear()
```

### 3. Wrong iterator type for container
```cpp
list<int> l = {1, 2, 3};
auto it = l.begin();
it + 2;  // ❌ ERROR! list iterator is not random access
advance(it, 2);  // ✓ Correct way
```

### 4. Comparing iterators from different containers
```cpp
vector<int> v1 = {1, 2};
vector<int> v2 = {3, 4};
if (v1.begin() == v2.begin())  // ❌ UNDEFINED BEHAVIOR!
```

---

## Interview Quick Points 🎯

**Q: What is an iterator?**
A: An object that acts like a pointer to traverse containers. Provides uniform interface for different container types.

**Q: Iterator vs Pointer?**
A: Pointers work with raw memory, iterators work with containers. Iterators are abstract and safer.

**Q: Why use iterators?**
A: Generic code, STL algorithm compatibility, flexibility across containers.

**Q: What does auto do?**
A: Automatically deduces the iterator type, making code cleaner and less error-prone.

**Q: Types of iterators?**
A: Input, Output, Forward, Bidirectional, Random Access (in increasing capability order).

**Q: What is iterator invalidation?**
A: When container modifications make existing iterators invalid/dangerous to use.

---

**Remember**: Iterators are the **backbone of STL** - mastering them unlocks the full power of C++ containers and algorithms! 