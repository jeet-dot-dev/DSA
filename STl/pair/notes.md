# C++ STL Pair - Detailed Notes

## What is Pair?

`std::pair` is a **simple container** in C++ STL (defined in `<utility>` header) that stores **exactly two heterogeneous objects** as a single unit. It's a template class that combines two values which may be of different types.

### Structure:
```cpp
template <class T1, class T2>
struct pair {
    T1 first;   // First element
    T2 second;  // Second element
};
```

### Key Characteristics:
- **Fixed size**: Always contains exactly 2 elements
- **Heterogeneous**: Can store different data types (int with string, double with char, etc.)
- **Direct access**: Members accessed via `.first` and `.second`
- **Lightweight**: Minimal overhead
- **Header**: `#include <utility>`
- **Namespace**: `std::`

### Basic Example:
```cpp
#include <utility>
#include <string>

std::pair<int, std::string> student;
student.first = 101;           // Roll number
student.second = "John";       // Name

// Or using make_pair
auto student2 = std::make_pair(102, "Alice");
```

---

## Why Pair?

### 1. **Return Multiple Values from Function**
Before C++17 (without structured bindings), pair was the easiest way to return two values:

```cpp
std::pair<int, int> divideWithRemainder(int dividend, int divisor) {
    int quotient = dividend / divisor;
    int remainder = dividend % divisor;
    return std::make_pair(quotient, remainder);
}

// Usage
auto result = divideWithRemainder(17, 5);
std::cout << "Quotient: " << result.first << "\n";    // 3
std::cout << "Remainder: " << result.second << "\n";  // 2
```

### 2. **Associative Containers**
Used internally by `map`, `multimap`, `unordered_map`:

```cpp
std::map<std::string, int> ages;
ages["John"] = 25;

// Map stores elements as pair<const Key, Value>
for(const auto& p : ages) {
    std::cout << p.first << ": " << p.second << "\n";
}
```

### 3. **Storing Related Data**
Keep two related values together:

```cpp
std::pair<double, double> coordinates(3.5, 7.2);  // (x, y)
std::pair<std::string, int> nameAge("Alice", 30);
std::pair<int, bool> resultStatus(42, true);
```

### 4. **Algorithm Results**
Many STL algorithms return pairs:

```cpp
auto result = std::minmax({5, 2, 8, 1, 9});
// result is pair<int, int> with min and max
std::cout << "Min: " << result.first << ", Max: " << result.second;
```

### 5. **Simpler than Creating Custom Struct**
When you need a quick temporary structure:

```cpp
// Instead of:
struct Point { int x, y; };

// You can use:
std::pair<int, int> point;
```

---

## What are Its Uses?

### 1. **Coordinate Systems (2D Points)**
```cpp
std::pair<int, int> point(10, 20);  // (x, y)
std::pair<double, double> gps(28.6139, 77.2090);  // Latitude, Longitude
```

### 2. **Key-Value Storage**
```cpp
std::pair<std::string, int> entry("apple", 5);
// Key: apple, Value: 5
```

### 3. **Graph Algorithms**
```cpp
// Edge: (destination, weight)
std::vector<std::pair<int, int>> adj[V];  // Adjacency list
adj[0].push_back({1, 10});  // Edge from 0 to 1 with weight 10
```

### 4. **Sorting with Multiple Criteria**
```cpp
std::vector<std::pair<int, std::string>> students;
students.push_back({95, "Alice"});
students.push_back({87, "Bob"});
students.push_back({95, "Charlie"});

std::sort(students.begin(), students.end());
// Sorts by first (marks), then by second (name) automatically
```

### 5. **Range Representation**
```cpp
std::pair<int, int> range(1, 100);  // [start, end]
```

### 6. **Database Query Results**
```cpp
std::vector<std::pair<int, std::string>> queryResult;
// ID, Name pairs from database
```

### 7. **Swapping Two Variables**
```cpp
std::pair<int, int> values(10, 20);
values = std::make_pair(values.second, values.first);  // Swap
```

### 8. **Iterator Pairs (Ranges)**
```cpp
auto range = std::equal_range(vec.begin(), vec.end(), value);
// Returns pair of iterators [lower_bound, upper_bound]
```

---

## Types of Pair Initialization

### 1. **Default Constructor**
```cpp
std::pair<int, double> p1;
// Default values: p1.first = 0, p1.second = 0.0
```

### 2. **Value Initialization**
```cpp
std::pair<int, std::string> p2(1, "Hello");
// p2.first = 1, p2.second = "Hello"
```

### 3. **Copy Constructor**
```cpp
std::pair<int, int> p3(10, 20);
std::pair<int, int> p4(p3);  // Copy
// p4.first = 10, p4.second = 20
```

### 4. **Using make_pair()**
```cpp
auto p5 = std::make_pair(3.14, 'A');
// Type automatically deduced: pair<double, char>

auto p6 = std::make_pair(100, "Text");
// Type: pair<int, const char*>
```

### 5. **Uniform Initialization (C++11)**
```cpp
std::pair<int, double> p7{5, 2.5};
std::pair<std::string, int> p8{"Age", 25};
```

### 6. **Copy Assignment**
```cpp
std::pair<int, int> p9, p10;
p9 = std::make_pair(1, 2);
p10 = p9;  // Copy assignment
```

### 7. **Move Constructor (C++11)**
```cpp
std::pair<std::string, int> p11("Hello", 42);
std::pair<std::string, int> p12(std::move(p11));
// p11's string is moved to p12
```

### 8. **Piecewise Construction (C++11)**
```cpp
std::pair<std::string, std::string> p13(
    std::piecewise_construct,
    std::forward_as_tuple("First"),
    std::forward_as_tuple(5, 'x')  // Creates "xxxxx"
);
// p13 = {"First", "xxxxx"}
```

### 9. **Direct List Initialization (C++11)**
```cpp
std::pair<int, std::string> p14 = {42, "Answer"};
```

### 10. **Structured Binding (C++17)**
```cpp
auto [id, name] = std::make_pair(101, "Alice");
// id = 101, name = "Alice"
```

---

## What is Pair of Pair?

A **pair of pair** is when you nest a pair inside another pair, creating a structure that can hold **3 or more values**.

### Syntax:
```cpp
std::pair<Type1, std::pair<Type2, Type3>> nestedPair;
```

### Example 1: 3D Coordinates
```cpp
// Storing (x, (y, z))
std::pair<int, std::pair<int, int>> point3D;
point3D.first = 10;                    // x
point3D.second.first = 20;             // y
point3D.second.second = 30;            // z

// Or using make_pair
auto point = std::make_pair(10, std::make_pair(20, 30));
std::cout << point.first << ", "                    // 10
          << point.second.first << ", "             // 20
          << point.second.second << "\n";           // 30
```

### Example 2: Student Record (ID, Name, Marks)
```cpp
std::pair<int, std::pair<std::string, double>> student;
student.first = 101;                        // Roll number
student.second.first = "Alice";             // Name
student.second.second = 95.5;               // Marks

// Better with make_pair
auto s = std::make_pair(101, std::make_pair("Alice", 95.5));
```

### Example 3: Range with Value
```cpp
// Storing (value, (start, end))
std::pair<int, std::pair<int, int>> rangeWithValue;
rangeWithValue = std::make_pair(42, std::make_pair(10, 20));
// Value: 42, Range: [10, 20]
```

### Vector of Pair of Pairs
```cpp
std::vector<std::pair<int, std::pair<int, int>>> data;
data.push_back({1, {10, 20}});
data.push_back({2, {30, 40}});

// Access
for(const auto& item : data) {
    std::cout << item.first << ": ("
              << item.second.first << ", "
              << item.second.second << ")\n";
}
```

### Limitations:
- **Readability**: Gets confusing with deep nesting
- **Hard to maintain**: `p.second.second.first` is not intuitive
- **Better alternatives**: Use `tuple` for 3+ elements or create a struct

### When to Use tuple Instead:
```cpp
// Instead of pair of pair:
std::pair<int, std::pair<int, int>> p;

// Use tuple:
std::tuple<int, int, int> t;
t = std::make_tuple(10, 20, 30);
int x = std::get<0>(t);
int y = std::get<1>(t);
int z = std::get<2>(t);
```

---

## Difference Between Pair, Array, and List

| Feature | Pair | Array | List |
|---------|------|-------|------|
| **Header** | `<utility>` | `<array>` | `<list>` |
| **Size** | Fixed (2 elements) | Fixed | Dynamic |
| **Element Types** | Can be different | Must be same | Must be same |
| **Access Members** | `.first`, `.second` | `[index]` or `.at()` | Iterators only |
| **Random Access** | Yes | Yes O(1) | No O(n) |
| **Memory** | Stack | Stack/Contiguous | Heap/Non-contiguous |
| **Iterator Type** | N/A (not iterable) | Random Access | Bidirectional |
| **Sorting** | Built-in comparison | `std::sort()` | `.sort()` member |
| **Use Case** | 2 related values | Fixed-size same-type data | Dynamic linked list |
| **Overhead** | Minimal | None | High (pointers) |
| **Modification** | Direct assignment | Direct assignment | Insert/delete ops |

### Comparison Table - Detailed:

#### **Pair**
```cpp
std::pair<int, std::string> p(1, "One");
p.first = 2;
p.second = "Two";
// Cannot iterate, fixed 2 elements, different types OK
```

**Pros:**
- Can mix types
- Very lightweight
- Simple access (`.first`, `.second`)
- Built-in comparison operators

**Cons:**
- Only 2 elements
- Not iterable
- Limited functionality

#### **Array (std::array)**
```cpp
std::array<int, 5> arr = {1, 2, 3, 4, 5};
arr[0] = 10;
for(int x : arr) cout << x << " ";
// Iterable, fixed size, same type only
```

**Pros:**
- Random access O(1)
- Can iterate
- No dynamic allocation
- Bounds checking with `.at()`

**Cons:**
- Fixed size at compile time
- All elements same type
- Cannot grow/shrink

#### **List (std::list)**
```cpp
std::list<int> lst = {1, 2, 3, 4, 5};
lst.push_back(6);
lst.push_front(0);
for(int x : lst) cout << x << " ";
// Iterable, dynamic size, same type only
```

**Pros:**
- Dynamic size
- O(1) insert/delete anywhere
- Iterator stability
- Can grow/shrink

**Cons:**
- No random access
- High memory overhead
- Poor cache performance
- All elements same type

### When to Use What?

| Scenario | Use |
|----------|-----|
| Need exactly 2 values, possibly different types | **Pair** |
| Need 3+ values, possibly different types | **Tuple** or **Struct** |
| Fixed-size collection, same type | **Array** |
| Dynamic collection, random access | **Vector** |
| Dynamic collection, frequent middle operations | **List** |
| Key-value storage | **Map** (uses pair internally) |

---

## What is Vector of Pair?

A **vector of pair** is a dynamic array where each element is a pair. It combines the benefits of vector (dynamic size, random access) with pair (storing two related values).

### Syntax:
```cpp
std::vector<std::pair<Type1, Type2>> vecOfPairs;
```

### Declaration and Initialization:

#### Method 1: Empty Vector
```cpp
std::vector<std::pair<int, std::string>> students;
```

#### Method 2: With Initial Size
```cpp
std::vector<std::pair<int, int>> coords(10);
// 10 pairs with default values (0, 0)
```

#### Method 3: Initializer List
```cpp
std::vector<std::pair<int, std::string>> students = {
    {101, "Alice"},
    {102, "Bob"},
    {103, "Charlie"}
};
```

#### Method 4: Using make_pair
```cpp
std::vector<std::pair<double, double>> points;
points.push_back(std::make_pair(3.5, 2.1));
points.push_back(std::make_pair(1.2, 4.8));
```

### Common Operations:

#### 1. Adding Elements
```cpp
std::vector<std::pair<int, std::string>> vec;

// Method 1: push_back with {}
vec.push_back({1, "One"});

// Method 2: push_back with make_pair
vec.push_back(std::make_pair(2, "Two"));

// Method 3: emplace_back (more efficient)
vec.emplace_back(3, "Three");
```

#### 2. Accessing Elements
```cpp
std::cout << vec[0].first << ": " << vec[0].second << "\n";
std::cout << vec.at(1).first << ": " << vec.at(1).second << "\n";
```

#### 3. Iterating
```cpp
// Range-based for loop
for(const auto& p : vec) {
    std::cout << p.first << " -> " << p.second << "\n";
}

// Iterator
for(auto it = vec.begin(); it != vec.end(); ++it) {
    std::cout << it->first << " -> " << it->second << "\n";
}

// C++17 structured binding
for(const auto& [key, value] : vec) {
    std::cout << key << " -> " << value << "\n";
}
```

#### 4. Sorting
```cpp
// Sorts by first element, then by second
std::sort(vec.begin(), vec.end());

// Custom comparator - sort by second element
std::sort(vec.begin(), vec.end(), 
    [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

// Sort descending by first
std::sort(vec.begin(), vec.end(), 
    [](const auto& a, const auto& b) {
        return a.first > b.first;
    });
```

#### 5. Searching
```cpp
// Find pair with first = 2
auto it = std::find_if(vec.begin(), vec.end(),
    [](const auto& p) { return p.first == 2; });

if(it != vec.end()) {
    std::cout << "Found: " << it->second << "\n";
}
```

### Real-World Examples:

#### Example 1: Graph Adjacency List
```cpp
// Graph with weighted edges
std::vector<std::pair<int, int>> adj[V];  // Array of vectors of pairs

// Add edge from u to v with weight w
adj[u].push_back({v, w});

// Traverse
for(auto [vertex, weight] : adj[u]) {
    std::cout << u << " -> " << vertex << " (weight: " << weight << ")\n";
}
```

#### Example 2: Coordinate System
```cpp
std::vector<std::pair<double, double>> points;
points.emplace_back(1.5, 2.5);
points.emplace_back(3.0, 4.0);

// Calculate distances, sort by distance, etc.
```

#### Example 3: Frequency Counter
```cpp
std::vector<std::pair<char, int>> frequency;
frequency.push_back({'a', 5});
frequency.push_back({'b', 3});
frequency.push_back({'c', 7});

// Sort by frequency
std::sort(frequency.begin(), frequency.end(),
    [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
```

#### Example 4: Student Database
```cpp
std::vector<std::pair<std::string, int>> students;
students.emplace_back("Alice", 95);
students.emplace_back("Bob", 87);
students.emplace_back("Charlie", 92);

// Find student with highest marks
auto topStudent = std::max_element(students.begin(), students.end(),
    [](const auto& a, const auto& b) {
        return a.second < b.second;
    });
```

### Advantages of Vector of Pair:
1. **Dynamic size**: Grow/shrink as needed
2. **Random access**: O(1) access to any element
3. **Flexible storage**: Two related values together
4. **STL algorithms**: Can use sort, find, etc.
5. **Cache friendly**: Better than vector of objects for small pairs

### Disadvantages:
1. **Limited to 2 elements**: Use vector of tuple for more
2. **Less readable**: Than custom structs for complex data
3. **Memory**: Slight overhead for pair structure

---

## Difference Between emplace_back and push_back

Both add elements to the end of a container, but they work differently internally.

### push_back
```cpp
void push_back(const T& value);  // Copy
void push_back(T&& value);       // Move (C++11)
```

**How it works:**
1. Creates the object **outside** the container
2. **Copies** or **moves** it into the container

### emplace_back (C++11)
```cpp
template<class... Args>
void emplace_back(Args&&... args);
```

**How it works:**
1. Constructs the object **directly inside** the container
2. **No copy or move** operation needed

### Key Differences Table:

| Feature | push_back | emplace_back |
|---------|-----------|--------------|
| **Object Creation** | Outside container | Inside container |
| **Copy/Move** | May copy/move | No copy/move |
| **Arguments** | Takes complete object | Takes constructor arguments |
| **Performance** | Slightly slower | Slightly faster |
| **C++ Version** | C++98 | C++11 |
| **Syntax** | `vec.push_back(Type(args))` | `vec.emplace_back(args)` |

### Example 1: Basic Types
```cpp
std::vector<int> vec;

vec.push_back(5);      // OK
vec.emplace_back(5);   // OK - same performance for primitives
```

### Example 2: Pairs
```cpp
std::vector<std::pair<int, std::string>> students;

// Using push_back - creates temporary pair
students.push_back(std::make_pair(101, "Alice"));
students.push_back({102, "Bob"});  // Implicit pair creation

// Using emplace_back - constructs pair in-place (more efficient)
students.emplace_back(103, "Charlie");  // Direct construction
```

**What happens internally:**

```cpp
// push_back:
// 1. Create temporary pair: pair<int, string>(101, "Alice")
// 2. Move/copy temporary into vector
// 3. Destroy temporary

// emplace_back:
// 1. Construct pair directly in vector's memory
// (No temporary, no move, no copy)
```

### Example 3: Custom Class
```cpp
class Student {
public:
    int id;
    std::string name;
    
    Student(int i, std::string n) : id(i), name(n) {
        std::cout << "Constructor called\n";
    }
    
    Student(const Student& s) : id(s.id), name(s.name) {
        std::cout << "Copy constructor called\n";
    }
    
    Student(Student&& s) : id(s.id), name(std::move(s.name)) {
        std::cout << "Move constructor called\n";
    }
};

std::vector<Student> students;

// push_back
students.push_back(Student(101, "Alice"));
// Output:
// Constructor called        (creates temporary)
// Move constructor called   (moves into vector)

// emplace_back
students.emplace_back(102, "Bob");
// Output:
// Constructor called        (constructs directly in vector)
```

### Example 4: Vector of Pairs - Comparison
```cpp
std::vector<std::pair<std::string, std::string>> data;

// push_back - multiple steps
data.push_back(std::make_pair("Key1", "Value1"));
// 1. make_pair creates temporary
// 2. Temporary moved into vector

data.push_back({"Key2", "Value2"});
// 1. Implicit pair construction
// 2. Moved into vector

// emplace_back - single step (BETTER)
data.emplace_back("Key3", "Value3");
// Constructs pair directly in vector
```

### Performance Comparison:

```cpp
#include <chrono>

std::vector<std::pair<std::string, std::string>> vec1, vec2;

// Benchmark push_back
auto start = std::chrono::high_resolution_clock::now();
for(int i = 0; i < 1000000; i++) {
    vec1.push_back({"key" + std::to_string(i), "value" + std::to_string(i)});
}
auto end = std::chrono::high_resolution_clock::now();
auto push_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

// Benchmark emplace_back
start = std::chrono::high_resolution_clock::now();
for(int i = 0; i < 1000000; i++) {
    vec2.emplace_back("key" + std::to_string(i), "value" + std::to_string(i));
}
end = std::chrono::high_resolution_clock::now();
auto emplace_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

// emplace_back is typically 5-15% faster
```

### When to Use What?

#### Use **emplace_back** when:
```cpp
// 1. Adding pairs to vector
vec.emplace_back(1, "One");

// 2. Adding custom objects
vec.emplace_back(constructor_args);

// 3. Performance matters
vec.emplace_back(x, y, z);

// 4. Want to avoid temporary objects
vec.emplace_back(std::string("Hello"));
```

#### Use **push_back** when:
```cpp
// 1. Already have constructed object
Student s(101, "Alice");
vec.push_back(s);  // Copy existing object

// 2. Moving existing object
vec.push_back(std::move(s));

// 3. Code readability matters more
vec.push_back({1, 2});  // More familiar syntax

// 4. Simple types where performance difference negligible
vec.push_back(42);
```

### Best Practice Recommendation:

```cpp
std::vector<std::pair<int, std::string>> vec;

// ✅ PREFER emplace_back for constructing new objects
vec.emplace_back(1, "One");

// ✅ Use push_back when you already have the object
std::pair<int, std::string> p(2, "Two");
vec.push_back(std::move(p));

// ❌ AVOID: Creating temporary just for push_back
vec.push_back(std::make_pair(3, "Three"));  // Unnecessary temporary

// ✅ BETTER: Use emplace_back instead
vec.emplace_back(3, "Three");
```

### Memory and Performance Impact:

For `std::vector<std::pair<std::string, std::string>>`:

```cpp
// push_back with make_pair:
// - Allocate memory for temporary pair
// - Construct strings in temporary
// - Move pair into vector
// - Destroy temporary
// Total: 1 pair construction + 1 move + strings moved

// emplace_back:
// - Construct pair directly in vector's memory
// - Construct strings directly in final location
// Total: 1 pair construction (no moves)
```

**Savings:** Eliminates temporary object creation and move operations.

---

## Additional Info

### 1. Pair Comparison

Pairs have built-in comparison operators that compare **lexicographically**:

```cpp
std::pair<int, int> p1(1, 2);
std::pair<int, int> p2(1, 3);
std::pair<int, int> p3(2, 1);

p1 < p2   // true  (same first, 2 < 3)
p1 < p3   // true  (1 < 2)
p1 == p1  // true
p1 != p2  // true
```

**Comparison Logic:**
1. Compare `first` elements
2. If equal, compare `second` elements

This makes pairs automatically sortable!

### 2. Pair with Complex Types

```cpp
// Pair of vectors
std::pair<std::vector<int>, std::vector<int>> vecPair;
vecPair.first = {1, 2, 3};
vecPair.second = {4, 5, 6};

// Pair of maps
std::pair<std::map<int, int>, std::string> mapPair;

// Pair of pairs (covered earlier)
std::pair<std::pair<int, int>, std::pair<int, int>> doublePair;
```

### 3. Swap Function

```cpp
std::pair<int, int> p1(1, 2);
std::pair<int, int> p2(3, 4);

p1.swap(p2);
// p1 = (3, 4), p2 = (1, 2)

// Or use std::swap
std::swap(p1, p2);
```

### 4. Tie Function (C++11)

Used to unpack pairs (or tuples):

```cpp
std::pair<int, std::string> student(101, "Alice");

int id;
std::string name;

std::tie(id, name) = student;
// id = 101, name = "Alice"

// Ignore elements with std::ignore
std::tie(id, std::ignore) = student;
// Only extracts first element
```

### 5. Structured Bindings (C++17)

Modern way to unpack pairs:

```cpp
auto [id, name] = std::make_pair(101, "Alice");
// id = 101, name = "Alice"

// In loops
std::vector<std::pair<int, std::string>> vec = {{1, "One"}, {2, "Two"}};
for(const auto& [num, word] : vec) {
    std::cout << num << ": " << word << "\n";
}
```

### 6. Pair in Algorithms

```cpp
// minmax - returns pair
auto result = std::minmax({5, 2, 8, 1, 9});
std::cout << "Min: " << result.first << ", Max: " << result.second;

// equal_range - returns pair of iterators
auto range = std::equal_range(vec.begin(), vec.end(), value);

// insert in map - returns pair<iterator, bool>
auto [it, success] = myMap.insert({key, value});
if(success) {
    std::cout << "Inserted successfully\n";
}
```

### 7. Performance Considerations

```cpp
// Pair is lightweight - typically just:
sizeof(std::pair<int, int>)  // 8 bytes (2 * 4)
sizeof(std::pair<int, double>)  // 16 bytes (4 + 4 padding + 8)

// Padding considerations
std::pair<char, int>  // May be 8 bytes (1 + 3 padding + 4)
std::pair<int, char>  // May be 8 bytes (4 + 1 + 3 padding)

// Tip: Put larger type first to minimize padding
```

### 8. Pair vs Tuple vs Struct

```cpp
// Pair - exactly 2 elements
std::pair<int, std::string> p(1, "One");
p.first, p.second

// Tuple - N elements
std::tuple<int, std::string, double> t(1, "One", 1.5);
std::get<0>(t), std::get<1>(t), std::get<2>(t)

// Struct - named members (most readable)
struct Data {
    int id;
    std::string name;
    double value;
};
Data d{1, "One", 1.5};
d.id, d.name, d.value
```

**Recommendation:**
- **Pair**: Quick 2-value storage, temporary data
- **Tuple**: 3+ values, still temporary
- **Struct**: Complex data types, long-term storage, better readability

### 9. Common Pitfalls

```cpp
// ❌ BAD: Confusing first/second
std::pair<std::string, int> student("Alice", 25);
// Which is name? Which is age? Not clear!

// ✅ BETTER: Use struct for clarity
struct Student {
    std::string name;
    int age;
};

// ❌ BAD: Deep nesting
std::pair<int, std::pair<int, std::pair<int, int>>>

// ✅ BETTER: Use tuple or struct
std::tuple<int, int, int, int>

// ❌ BAD: Modifying const pair
const std::pair<int, int> p(1, 2);
// p.first = 3;  // Error!

// ✅ GOOD: Non-const if you need to modify
std::pair<int, int> p(1, 2);
p.first = 3;  // OK
```

### 10. Real-World Usage Patterns

```cpp
// Pattern 1: Returning multiple values
std::pair<bool, int> divide(int a, int b) {
    if(b == 0) return {false, 0};
    return {true, a / b};
}

auto [success, result] = divide(10, 2);

// Pattern 2: Caching results
std::map<int, std::pair<int, int>> cache;
// Key -> (result, timestamp)

// Pattern 3: Priority queue with custom compare
auto compare = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.second > b.second;
};
std::priority_queue<std::pair<int, int>, 
                    std::vector<std::pair<int, int>>,
                    decltype(compare)> pq(compare);

// Pattern 4: Graph representation
std::vector<std::vector<std::pair<int, int>>> graph(n);
// graph[u] = list of (vertex, weight) pairs
```

### 11. C++20 Additions

```cpp
// Spaceship operator <=>
std::pair<int, int> p1(1, 2);
std::pair<int, int> p2(1, 3);

auto result = p1 <=> p2;  // Three-way comparison
// Returns: std::strong_ordering::less
```

### 12. Thread Safety

- Pair itself is **not thread-safe**
- Concurrent reads are safe
- Concurrent writes need synchronization
- Use mutex or atomic for concurrent access

```cpp
std::mutex mtx;
std::pair<int, int> shared_pair;

// Thread-safe write
{
    std::lock_guard<std::mutex> lock(mtx);
    shared_pair = {1, 2};
}
```

---

## Summary - Quick Reference

```cpp
// Creating pairs
std::pair<int, std::string> p1(1, "One");
auto p2 = std::make_pair(2, "Two");
std::pair<int, std::string> p3{3, "Three"};

// Accessing
p1.first, p1.second

// Vector of pairs
std::vector<std::pair<int, std::string>> vec;
vec.push_back({1, "One"});
vec.emplace_back(2, "Two");  // Preferred

// Sorting
std::sort(vec.begin(), vec.end());

// Unpacking
auto [a, b] = p1;  // C++17

// Comparison
p1 < p2  // Lexicographic comparison
```

**Remember:** Pair is perfect for **simple 2-value storage**. For complex data or more than 2 values, consider using **struct** or **tuple**! 