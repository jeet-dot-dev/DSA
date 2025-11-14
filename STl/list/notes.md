# C++ STL List - Detailed Notes

## What is List?

`std::list` is a container in C++ Standard Template Library (STL) that implements a **doubly linked list** data structure. It stores elements in non-contiguous memory locations, where each element contains:
- The data value
- A pointer to the next element
- A pointer to the previous element

### Key Characteristics:
- **Non-contiguous memory**: Elements are scattered in memory
- **Bidirectional traversal**: Can move forward and backward
- **Dynamic size**: Grows and shrinks automatically
- **No random access**: Cannot access elements directly by index (no `[]` operator)
- **Efficient insertion/deletion**: O(1) time complexity at any position (if iterator is known)

---

## Difference Between Array, Vector, and List

| Feature | Array | Vector | List |
|---------|-------|--------|------|
| **Memory** | Contiguous | Contiguous | Non-contiguous |
| **Size** | Fixed | Dynamic | Dynamic |
| **Random Access** | Yes O(1) | Yes O(1) | No O(n) |
| **Insertion at End** | N/A | O(1) amortized | O(1) |
| **Insertion at Middle** | N/A | O(n) | O(1)* |
| **Deletion at Middle** | N/A | O(n) | O(1)* |
| **Memory Overhead** | None | Minimal | High (2 pointers per element) |
| **Cache Friendly** | Yes | Yes | No |
| **Iterator Invalidation** | N/A | Yes (on reallocation) | No (except deleted elements) |

*O(1) if you already have an iterator to that position

### When to Use What?

**Use Array when:**
- Size is fixed and known at compile time
- Need fast random access
- Memory is limited

**Use Vector when:**
- Need dynamic size
- Frequent access by index
- Insertions/deletions mainly at the end
- Cache performance matters

**Use List when:**
- Frequent insertions/deletions in the middle
- Don't need random access
- Iterator stability is important
- Order of elements needs to be maintained with frequent modifications

---

## Is List a Doubly Linked List?

**Yes!** `std::list` is implemented as a **doubly linked list**.

### Structure:
```
[nullptr] ← [Data|Prev|Next] ↔ [Data|Prev|Next] ↔ [Data|Prev|Next] → [nullptr]
              ^                                                           ^
            head                                                        tail
```

### Why Doubly Linked?
- Allows bidirectional iteration (`begin()` to `end()` and `rbegin()` to `rend()`)
- Efficient deletion: O(1) if you have iterator
- Can traverse backward efficiently
- Supports reverse iterators

---

## Operations Performed on List

### 1. **Element Access**
```cpp
front()           // Access first element
back()            // Access last element
// Note: No operator[] or at() - no random access!
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
empty()           // Check if list is empty
size()            // Return number of elements
max_size()        // Return maximum possible size
```

### 4. **Modifiers**
```cpp
// Adding elements
push_front(val)       // Add element at beginning
push_back(val)        // Add element at end
emplace_front(args)   // Construct element at beginning
emplace_back(args)    // Construct element at end
insert(pos, val)      // Insert element at position
emplace(pos, args)    // Construct element at position

// Removing elements
pop_front()           // Remove first element
pop_back()            // Remove last element
erase(pos)            // Remove element at position
erase(first, last)    // Remove range of elements
remove(val)           // Remove all elements with value
remove_if(pred)       // Remove elements satisfying condition
clear()               // Remove all elements

// Other modifiers
assign(n, val)        // Assign n elements with value
assign(first, last)   // Assign from range
resize(n)             // Resize container
swap(other_list)      // Swap contents with another list
```

### 5. **Operations (Unique to List)**
```cpp
// Splicing - move elements from one list to another
splice(pos, other_list)              // Transfer all elements
splice(pos, other_list, it)          // Transfer single element
splice(pos, other_list, first, last) // Transfer range

// Sorting and merging
sort()                    // Sort in ascending order
sort(comp)                // Sort with custom comparator
merge(other_list)         // Merge two sorted lists
merge(other_list, comp)   // Merge with custom comparator

// Removing duplicates
unique()                  // Remove consecutive duplicates
unique(pred)              // Remove consecutive duplicates with predicate

// Reversing
reverse()                 // Reverse the order of elements
```

---

## Types of List Initialization

### 1. **Default Constructor (Empty List)**
```cpp
std::list<int> myList;
// Creates an empty list
```

### 2. **Fill Constructor**
```cpp
std::list<int> myList(5);          // 5 elements with default value (0)
std::list<int> myList(5, 100);     // 5 elements with value 100
// Output: 100 100 100 100 100
```

### 3. **Range Constructor**
```cpp
std::list<int> list1 = {1, 2, 3, 4, 5};
std::list<int> list2(list1.begin(), list1.end());
// list2 is a copy of list1

int arr[] = {10, 20, 30, 40};
std::list<int> list3(arr, arr + 4);
// list3: 10 20 30 40
```

### 4. **Copy Constructor**
```cpp
std::list<int> list1 = {1, 2, 3, 4, 5};
std::list<int> list2(list1);
// list2 is a copy of list1
```

### 5. **Move Constructor (C++11)**
```cpp
std::list<int> list1 = {1, 2, 3, 4, 5};
std::list<int> list2(std::move(list1));
// list2 now owns the data, list1 is empty
```

### 6. **Initializer List (C++11)**
```cpp
std::list<int> myList = {1, 2, 3, 4, 5};
// or
std::list<int> myList{1, 2, 3, 4, 5};
```

### 7. **Assignment Operator**
```cpp
std::list<int> list1 = {1, 2, 3};
std::list<int> list2;
list2 = list1;  // Copy assignment
```

### 8. **Using assign() Method**
```cpp
std::list<int> myList;
myList.assign(5, 10);           // 10 10 10 10 10
myList.assign({1, 2, 3, 4, 5}); // 1 2 3 4 5
```

---

## Time Complexity Summary

| Operation | Time Complexity |
|-----------|----------------|
| Access (by index) | O(n) |
| Insert at beginning | O(1) |
| Insert at end | O(1) |
| Insert at position | O(1)* |
| Delete at beginning | O(1) |
| Delete at end | O(1) |
| Delete at position | O(1)* |
| Search | O(n) |
| Sort | O(n log n) |
| Reverse | O(n) |

*O(1) if iterator to position is already available, otherwise O(n) to reach the position

---

## Advantages of List

1. **Efficient Insertion/Deletion**: O(1) at any position with iterator
2. **No Reallocation**: Elements don't move in memory
3. **Iterator Stability**: Iterators remain valid after insert/delete (except for deleted elements)
4. **No Capacity Issues**: No need to reserve memory
5. **Bidirectional Traversal**: Can move forward and backward

---

## Disadvantages of List

1. **No Random Access**: Cannot use `list[i]` to access elements
2. **Extra Memory**: Each element stores two pointers (8-16 bytes overhead)
3. **Poor Cache Performance**: Non-contiguous memory affects CPU cache
4. **Slower Traversal**: Compared to vector due to pointer chasing
5. **No Binary Search**: Cannot use standard binary search (requires random access)

---

## Important Notes

### Iterator Invalidation
- **Insertion**: No iterators invalidated
- **Deletion**: Only iterators to deleted elements are invalidated
- This is different from vector where insertion can invalidate all iterators!

### Sorting
- List provides its own `sort()` member function
- Don't use `std::sort()` - it requires random access iterators
- Use `list.sort()` which uses merge sort internally

### Comparison with forward_list
- `std::forward_list` is a singly linked list (only next pointer)
- Smaller memory overhead than list
- Cannot traverse backward
- No `size()` function (O(1) would require extra memory)

---

## Common Use Cases

1. **Implementing LRU Cache**: Frequent deletions and insertions
2. **Undo/Redo Functionality**: Maintaining history with bidirectional access
3. **Task Scheduling**: Where tasks are added and removed frequently
4. **Music/Video Playlists**: Where songs are added, removed, and reordered
5. **Browser History**: Back and forward navigation

---

## Best Practices

1. **Use list when** you need frequent insertions/deletions in the middle
2. **Prefer vector** for most use cases due to better cache performance
3. **Keep iterators** when you need to modify elements frequently
4. **Use emplace** instead of push for better performance
5. **Avoid size()** in loops if possible (some implementations may not cache size)

---

## Example: Complete Usage

```cpp
#include <iostream>
#include <list>
#include <algorithm>

int main() {
    // Creation
    std::list<int> myList = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // Display
    for(int x : myList) 
        std::cout << x << " ";
    std::cout << "\n";
    
    // Insertion
    myList.push_front(0);
    myList.push_back(7);
    
    // Sorting
    myList.sort();
    
    // Remove duplicates
    myList.unique();
    
    // Reverse
    myList.reverse();
    
    // Find and erase
    auto it = std::find(myList.begin(), myList.end(), 5);
    if(it != myList.end())
        myList.erase(it);
    
    return 0;
}
``` 