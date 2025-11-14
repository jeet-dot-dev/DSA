# C++ STL Deque - Detailed Notes

## What is Deque?

`std::deque` (pronounced "deck") stands for **Double-Ended Queue**. It's a sequence container in C++ STL that allows:
- Fast insertion and deletion at **both ends** (front and back)
- Random access to elements (like vector)
- Dynamic size (grows and shrinks automatically)

### Key Characteristics:
- **Indexed access**: Can access elements using `[]` operator in O(1) time
- **Non-contiguous memory**: Elements stored in chunks (not one continuous block)
- **No reallocation**: Adding elements doesn't invalidate existing elements
- **Bi-directional insertion/deletion**: Efficient at both ends
- **Random access iterators**: Supports `+`, `-`, `<`, `>` operations on iterators

### Internal Structure:
```
Deque is implemented as a collection of fixed-size arrays:

    Map (Array of pointers)
    ┌───┬───┬───┬───┬───┐
    │ * │ * │ * │ * │ * │  → Pointers to chunks
    └─┼─┴─┼─┴─┼─┴─┼─┴─┼─┘
      │   │   │   │   │
      ↓   ↓   ↓   ↓   ↓
    [x][x][x][x][x]  Chunk 1
    [x][x][x][x][x]  Chunk 2  
    [x][x][x][x][x]  Chunk 3  ← Elements stored here
    [x][x][x][x][x]  Chunk 4
    [x][x][x][x][x]  Chunk 5
```

---

## What are Sequence Containers?

**Sequence Containers** are container classes in STL that store elements in a **linear sequence** where you have control over the order of elements.

### Types of Sequence Containers:

1. **array** - Fixed-size array
2. **vector** - Dynamic array
3. **deque** - Double-ended queue
4. **list** - Doubly linked list
5. **forward_list** - Singly linked list

### Characteristics of Sequence Containers:
- Elements are ordered in a specific sequence
- You can access elements by their position
- Order is maintained based on insertion
- Different containers optimize for different operations

### Comparison:

| Container | Random Access | Insert/Delete Front | Insert/Delete Back | Insert/Delete Middle |
|-----------|---------------|---------------------|--------------------|--------------------|
| **array** | O(1) | N/A | N/A | N/A |
| **vector** | O(1) | O(n) | O(1) | O(n) |
| **deque** | O(1) | O(1) | O(1) | O(n) |
| **list** | O(n) | O(1) | O(1) | O(1)* |
| **forward_list** | O(n) | O(1) | O(n) | O(1)* |

*If iterator to position is available

---

## Difference Between Deque and Dequeue

### Deque (Data Structure)
- **Full name**: Double-Ended Queue
- **Pronunciation**: "deck"
- **Definition**: A data structure/container class `std::deque<T>`
- **In C++**: `#include <deque>`
- **Usage**: `std::deque<int> dq;`

### Dequeue (Operation)
- **Pronunciation**: "dee-queue"
- **Definition**: An **operation** that removes an element from a queue
- **Opposite of**: Enqueue (adding to queue)
- **Usage**: The act of removing from any queue data structure

### Simple Analogy:
```
Deque   = The container (like a water bottle)
Dequeue = The action of removing (like drinking from the bottle)
```

**Common Confusion**: People often misspell "deque" as "dequeue" or confuse the data structure with the operation!

---

## Difference Between List and Deque

| Feature | List | Deque |
|---------|------|-------|
| **Memory Layout** | Non-contiguous (linked nodes) | Semi-contiguous (chunks) |
| **Random Access** | ❌ No - O(n) | ✅ Yes - O(1) |
| **`[]` operator** | ❌ Not available | ✅ Available |
| **`.at()` method** | ❌ Not available | ✅ Available |
| **Iterator Type** | Bidirectional | Random Access |
| **Insert at Front** | O(1) | O(1) |
| **Insert at Back** | O(1) | O(1) |
| **Insert at Middle** | O(1)* | O(n) |
| **Memory per Element** | High (2 pointers) | Low (just the data) |
| **Cache Friendly** | ❌ Poor | ✅ Better than list |
| **Iterator Invalidation** | Only deleted elements | On insert at ends |
| **Splice Operation** | ✅ Yes | ❌ No |

*If you have iterator to the position

### When to Use What?

**Use List when:**
- Frequent insertions/deletions in the middle
- Need iterator stability
- Don't need random access
- Order changes frequently

**Use Deque when:**
- Need fast insertion/deletion at both ends
- Need random access to elements
- Want vector-like performance with efficient front operations
- Implementing queue or double-ended queue

---

## Why `d[2]` is Possible but `l[2]` is Not?

### The Answer: Iterator Types

#### Deque - Random Access Iterator
```cpp
std::deque<int> d = {10, 20, 30, 40, 50};
std::cout << d[2];  // ✅ Works! Output: 30

// Why? Deque provides random access iterator
// Can jump directly to any position in O(1)
```

**How Deque Achieves This:**
1. Maintains a map (array) of pointers to chunks
2. Each chunk has fixed size (e.g., 512 bytes)
3. To access `d[i]`:
   - Calculate: `chunk_index = i / chunk_size`
   - Calculate: `offset = i % chunk_size`
   - Access: `map[chunk_index][offset]`
4. All arithmetic operations are O(1)

#### List - Bidirectional Iterator
```cpp
std::list<int> l = {10, 20, 30, 40, 50};
// std::cout << l[2];  // ❌ Compilation Error!

// Why? List only has bidirectional iterator
// Must traverse node by node
```

**Why List Cannot Do This:**
1. Elements stored in separate nodes
2. Each node has pointer to next and previous
3. No way to calculate memory address of nth element
4. Must traverse: node1 → node2 → node3
5. This is O(n), not O(1)

### Iterator Capabilities Comparison

```cpp
// Random Access (Deque, Vector, Array)
iterator + n        // ✅ Jump n positions
iterator - n        // ✅ Jump back n positions
iterator1 - iterator2  // ✅ Distance between
iterator[n]         // ✅ Access nth element
iterator < iterator2   // ✅ Comparison

// Bidirectional (List)
iterator++          // ✅ Next element only
iterator--          // ✅ Previous element only
// Cannot do arithmetic operations
```

### Visual Example:

**Deque (Random Access):**
```
Index:  0   1   2   3   4
       ┌───┬───┬───┬───┬───┐
Data:  │10 │20 │30 │40 │50 │
       └───┴───┴───┴───┴───┘
         ↑       ↑
         d[0]    d[2] → Direct access!
```

**List (Bidirectional):**
```
[10|prev|next] → [20|prev|next] → [30|prev|next] → [40|prev|next] → [50|prev|next]
  ↑                                  ↑
  l.front()                    Must traverse: l.begin() → ++ → ++ → here
```

---

## All Operations of Deque

### 1. **Element Access**
```cpp
operator[]        // Access element (no bounds checking)
at()              // Access element (with bounds checking)
front()           // Access first element
back()            // Access last element
```

**Example:**
```cpp
std::deque<int> dq = {10, 20, 30, 40, 50};
dq[2];      // 30 (no bounds check)
dq.at(2);   // 30 (throws exception if out of range)
dq.front(); // 10
dq.back();  // 50
```

### 2. **Iterators**
```cpp
begin(), end()           // Forward iterators
rbegin(), rend()         // Reverse iterators
cbegin(), cend()         // Const iterators
crbegin(), crend()       // Const reverse iterators
```

### 3. **Capacity**
```cpp
empty()           // Check if deque is empty
size()            // Return number of elements
max_size()        // Return maximum possible size
shrink_to_fit()   // Reduce memory to fit size (C++11)
```

**Example:**
```cpp
std::deque<int> dq;
if(dq.empty())                    // true
    std::cout << "Deque is empty";
std::cout << dq.size();           // 0
dq.shrink_to_fit();               // Release unused memory
```

### 4. **Modifiers - Adding Elements**

#### At Front:
```cpp
push_front(val)        // Add element at front
emplace_front(args)    // Construct element at front (C++11)
```

#### At Back:
```cpp
push_back(val)         // Add element at back
emplace_back(args)     // Construct element at back (C++11)
```

#### At Position:
```cpp
insert(pos, val)              // Insert single element
insert(pos, n, val)           // Insert n copies
insert(pos, first, last)      // Insert range
insert(pos, {list})           // Insert initializer list (C++11)
emplace(pos, args)            // Construct at position (C++11)
```

**Example:**
```cpp
std::deque<int> dq;

dq.push_back(10);              // [10]
dq.push_front(5);              // [5, 10]
dq.emplace_back(15);           // [5, 10, 15]
dq.emplace_front(1);           // [1, 5, 10, 15]

auto it = dq.begin() + 2;
dq.insert(it, 7);              // [1, 5, 7, 10, 15]
```

### 5. **Modifiers - Removing Elements**

#### At Front:
```cpp
pop_front()           // Remove first element
```

#### At Back:
```cpp
pop_back()            // Remove last element
```

#### At Position:
```cpp
erase(pos)            // Remove element at position
erase(first, last)    // Remove range of elements
```

#### All Elements:
```cpp
clear()               // Remove all elements
```

**Example:**
```cpp
std::deque<int> dq = {1, 2, 3, 4, 5};

dq.pop_front();       // [2, 3, 4, 5]
dq.pop_back();        // [2, 3, 4]

auto it = dq.begin() + 1;
dq.erase(it);         // [2, 4]

dq.clear();           // []
```

### 6. **Other Modifiers**
```cpp
assign(n, val)        // Assign n elements with value
assign(first, last)   // Assign from range
assign({list})        // Assign from initializer list
resize(n)             // Resize container
resize(n, val)        // Resize with default value
swap(other)           // Swap contents with another deque
```

**Example:**
```cpp
std::deque<int> dq1, dq2;

dq1.assign(5, 100);           // [100, 100, 100, 100, 100]
dq1.resize(3);                // [100, 100, 100]
dq1.resize(5, 50);            // [100, 100, 100, 50, 50]

dq2 = {1, 2, 3};
dq1.swap(dq2);                // dq1: [1,2,3], dq2: [100,100,100,50,50]
```

---

## Types of Deque Initialization

### 1. **Default Constructor (Empty Deque)**
```cpp
std::deque<int> dq;
// Creates an empty deque
```

### 2. **Fill Constructor**
```cpp
std::deque<int> dq(5);          // 5 elements with default value (0)
std::deque<int> dq(5, 100);     // 5 elements with value 100
// Output: 100 100 100 100 100
```

### 3. **Range Constructor**
```cpp
std::deque<int> dq1 = {1, 2, 3, 4, 5};
std::deque<int> dq2(dq1.begin(), dq1.end());
// dq2 is a copy of dq1

int arr[] = {10, 20, 30, 40};
std::deque<int> dq3(arr, arr + 4);
// dq3: 10 20 30 40
```

### 4. **Copy Constructor**
```cpp
std::deque<int> dq1 = {1, 2, 3, 4, 5};
std::deque<int> dq2(dq1);
// dq2 is a copy of dq1
```

### 5. **Move Constructor (C++11)**
```cpp
std::deque<int> dq1 = {1, 2, 3, 4, 5};
std::deque<int> dq2(std::move(dq1));
// dq2 now owns the data, dq1 is empty
```

### 6. **Initializer List (C++11)**
```cpp
std::deque<int> dq = {1, 2, 3, 4, 5};
// or
std::deque<int> dq{1, 2, 3, 4, 5};
```

### 7. **Assignment Operator**
```cpp
std::deque<int> dq1 = {1, 2, 3};
std::deque<int> dq2;
dq2 = dq1;  // Copy assignment
```

---

## Time Complexity Summary

| Operation | Time Complexity | Notes |
|-----------|----------------|-------|
| Random Access `[]` or `.at()` | O(1) | Direct calculation |
| Insert/Delete at Front | O(1) | Main advantage |
| Insert/Delete at Back | O(1) | Like vector |
| Insert/Delete at Middle | O(n) | Must shift elements |
| Search | O(n) | Linear search |
| Push/Pop Front | O(1) | Efficient |
| Push/Pop Back | O(1) | Efficient |

---

## Advantages of Deque

1. **Fast Operations at Both Ends**: O(1) push/pop at front and back
2. **Random Access**: Can use `[]` operator like vector
3. **No Reallocation**: Unlike vector, no need to move all elements
4. **Better Memory Management**: Chunks prevent wasting memory
5. **Iterator Arithmetic**: Supports random access iterators
6. **No Capacity Reservation**: Grows on demand without reserve

---

## Disadvantages of Deque

1. **Slower Random Access than Vector**: More pointer indirection
2. **More Complex Implementation**: Overhead of managing chunks
3. **Iterator Invalidation**: Insert at ends can invalidate iterators
4. **Cache Performance**: Not as good as vector's contiguous memory
5. **Memory Overhead**: Needs to maintain map of pointers
6. **No .data() Method**: Cannot get pointer to underlying array

---

## Iterator Invalidation Rules

### Insert Operations:
- **At front/back**: All iterators invalidated, references remain valid
- **In middle**: All iterators and references invalidated

### Erase Operations:
- **At front/back**: Only erased element's iterator invalidated
- **In middle**: All iterators and references invalidated

### Example:
```cpp
std::deque<int> dq = {1, 2, 3, 4, 5};
auto it = dq.begin() + 2;  // Points to 3

dq.push_front(0);   // it is now INVALID!
dq.push_back(6);    // it is now INVALID!

// Safe: Get new iterator
it = dq.begin() + 3;
```

---

## Deque vs Vector vs List - Quick Decision Guide

### Choose **Vector** when:
- ✅ Mostly access by index
- ✅ Add/remove only at back
- ✅ Need cache-friendly memory
- ✅ Rarely insert in middle

### Choose **Deque** when:
- ✅ Add/remove at both ends
- ✅ Need random access
- ✅ Don't know final size
- ✅ Want queue/double-ended queue behavior

### Choose **List** when:
- ✅ Frequent insert/delete in middle
- ✅ Need iterator stability
- ✅ Don't need random access
- ✅ Splice operations needed

---

## Common Use Cases

1. **Implementing Queue**: FIFO (First In First Out)
   ```cpp
   dq.push_back(x);    // Enqueue
   dq.pop_front();     // Dequeue
   ```

2. **Implementing Deque**: Double-ended operations
   ```cpp
   dq.push_front(x);   // Add to front
   dq.push_back(x);    // Add to back
   dq.pop_front();     // Remove from front
   dq.pop_back();      // Remove from back
   ```

3. **Sliding Window Problems**: Keep window of elements
4. **Browser History**: Navigate forward and backward
5. **Task Scheduler**: Priority tasks at front, regular at back
6. **Palindrome Checker**: Compare from both ends
7. **Undo/Redo**: Operations from both ends

---

## Important Notes

### 1. **No .reserve() or .capacity()**
Unlike vector, deque doesn't have these methods because it doesn't use contiguous memory.

### 2. **Memory Management**
```cpp
// Vector: Doubles capacity when full (wastes memory)
// Deque: Adds new chunk (efficient memory use)
```

### 3. **When NOT to Use Deque**
- When you need maximum random access speed → use **vector**
- When you need frequent middle insertions → use **list**
- When memory is extremely limited → use **vector** (less overhead)

### 4. **Thread Safety**
- Same as other STL containers: NOT thread-safe
- Need external synchronization for concurrent access

---

## Complete Example: Using Deque

```cpp
#include <iostream>
#include <deque>
#include <algorithm>

int main() {
    // 1. Creation and initialization
    std::deque<int> dq = {3, 1, 4, 1, 5};
    
    // 2. Add elements at both ends
    dq.push_front(0);        // [0, 3, 1, 4, 1, 5]
    dq.push_back(9);         // [0, 3, 1, 4, 1, 5, 9]
    
    // 3. Random access
    std::cout << "Element at index 2: " << dq[2] << "\n";  // 1
    std::cout << "Element at index 4: " << dq.at(4) << "\n"; // 1
    
    // 4. Modify elements
    dq[2] = 2;               // [0, 3, 2, 4, 1, 5, 9]
    
    // 5. Remove from both ends
    dq.pop_front();          // [3, 2, 4, 1, 5, 9]
    dq.pop_back();           // [3, 2, 4, 1, 5]
    
    // 6. Insert in middle
    auto it = dq.begin() + 2;
    dq.insert(it, 7);        // [3, 2, 7, 4, 1, 5]
    
    // 7. Iterate and display
    std::cout << "Deque elements: ";
    for(int x : dq) 
        std::cout << x << " ";
    std::cout << "\n";
    
    // 8. Sorting
    std::sort(dq.begin(), dq.end());
    
    // 9. Size and capacity info
    std::cout << "Size: " << dq.size() << "\n";
    std::cout << "Empty: " << (dq.empty() ? "Yes" : "No") << "\n";
    
    return 0;
}
```

---

## Best Practices

1. **Use emplace over push**: More efficient (constructs in place)
   ```cpp
   dq.emplace_back(args);  // Better
   dq.push_back(T(args));  // Creates temporary
   ```

2. **Prefer at() in debug mode**: Catches out-of-bounds errors
   ```cpp
   dq.at(i);  // Throws exception if i >= size
   dq[i];     // Undefined behavior if i >= size
   ```

3. **Reserve iterators carefully**: They can be invalidated easily

4. **Use shrink_to_fit()**: After many deletions to free memory
   ```cpp
   dq.shrink_to_fit();
   ```

5. **Choose right container**: Don't use deque if vector suffices

---

## Extra Info

### Memory Layout Detail
```
Typical chunk size: 512 bytes
For int (4 bytes): 128 integers per chunk

If deque has 300 elements:
- Chunk 1: 128 elements
- Chunk 2: 128 elements  
- Chunk 3: 44 elements
- Total: 3 chunks
```

### Performance Tips
1. Deque is typically 2-3x slower than vector for random access
2. But much faster than vector for front insertions
3. Better memory efficiency than vector when size varies

### Interesting Fact
The C++ standard doesn't specify exactly how deque should be implemented, but most implementations use the "map of chunks" approach described here.

### Default Underlying Container
Deque is the default underlying container for:
- `std::stack` (can use deque or vector)
- `std::queue` (can use deque or list)

```cpp
std::queue<int> q;  // Uses deque by default
std::stack<int> s;  // Uses deque by default
``` 