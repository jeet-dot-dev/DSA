# C++ STL Stack - Detailed Notes

## Why Stack is NOT a Sequence Container?

Stack is **NOT a sequence container** - it's a **Container Adapter**.

### What is a Container Adapter?

A **Container Adapter** is a wrapper that provides a **restricted interface** to an underlying container. It **adapts** (modifies) the interface of a sequential container to provide specific functionality.

### Key Points:

**Container Adapters in STL:**
1. `std::stack` - LIFO (Last In First Out)
2. `std::queue` - FIFO (First In First Out)
3. `std::priority_queue` - Priority-based access

**Sequence Containers in STL:**
1. `std::array` - Fixed-size array
2. `std::vector` - Dynamic array
3. `std::deque` - Double-ended queue
4. `std::list` - Doubly linked list
5. `std::forward_list` - Singly linked list

### Why Stack is a Container Adapter:

```cpp
// Stack doesn't store elements directly
// It USES another container internally!

template<
    class T,
    class Container = std::deque<T>  // Default underlying container
> class stack;
```

**Visual Representation:**
```
┌─────────────────────────────┐
│    Stack (Adapter)          │  ← Restricted Interface
│  - push()                   │     (only top access)
│  - pop()                    │
│  - top()                    │
├─────────────────────────────┤
│  Underlying Container       │  ← Actual storage
│  (deque/vector/list)        │     (can be any sequence container)
│  - Stores actual elements   │
└─────────────────────────────┘
```

### Stack Using Different Underlying Containers:

```cpp
// 1. Default - uses deque
std::stack<int> s1;

// 2. Using vector
std::stack<int, std::vector<int>> s2;

// 3. Using list
std::stack<int, std::list<int>> s3;

// 4. Cannot use - forward_list (no push_back)
// std::stack<int, std::forward_list<int>> s4;  // ❌ Won't compile
```

### Differences: Sequence Container vs Container Adapter

| Feature | Sequence Container | Container Adapter (Stack) |
|---------|-------------------|---------------------------|
| **Direct Storage** | Yes | No (uses another container) |
| **Full Interface** | Yes (many operations) | No (restricted) |
| **Random Access** | Some have it | No |
| **Iterators** | Yes | No (cannot iterate) |
| **Custom Interface** | Standard | Specialized (LIFO) |
| **Examples** | vector, deque, list | stack, queue, priority_queue |

### Why This Design?

**Benefits of Container Adapter Pattern:**

1. **Reusability**: Don't reinvent the wheel
   ```cpp
   // Stack reuses existing containers
   // No need to write storage logic again
   ```

2. **Flexibility**: Choose best underlying container
   ```cpp
   std::stack<int, std::vector<int>> fastStack;    // Cache-friendly
   std::stack<int, std::list<int>> flexibleStack;  // Memory-efficient
   ```

3. **Simplicity**: Clean, focused interface
   ```cpp
   // Only what you need for LIFO
   s.push(x);
   s.pop();
   s.top();
   // No random access, no iterators - prevents misuse
   ```

4. **Type Safety**: Enforces LIFO behavior
   ```cpp
   // Cannot accidentally access middle elements
   // Cannot iterate (which would break LIFO concept)
   ```

### Simple Analogy:

Think of a **stack of plates**:
- **Container Adapter (Stack)**: The rule "only take from top"
- **Underlying Container**: The actual shelf holding the plates (could be wooden, metal, plastic)

The **rule** (adapter) stays the same, but the **shelf** (container) can change!

---

## What is Stack?

`std::stack` is a **container adapter** that provides LIFO (Last In First Out) data structure functionality.

### Definition:
```cpp
template<
    class T,                        // Element type
    class Container = std::deque<T> // Underlying container (default: deque)
> class stack;
```

### LIFO Principle:
**Last In, First Out** - The last element added is the first to be removed.

```
Push Operations:          Pop Operations:
    ↓                         ↑
  ┌───┐                     ┌───┐
  │ 5 │ ← Top (newest)      │ 5 │ ← Removed first
  ├───┤                     ├───┤
  │ 4 │                     │ 4 │ ← Removed second
  ├───┤                     ├───┤
  │ 3 │                     │ 3 │ ← Removed third
  ├───┤                     ├───┤
  │ 2 │                     │ 2 │ ← Removed fourth
  ├───┤                     ├───┤
  │ 1 │ ← Bottom (oldest)   │ 1 │ ← Removed last
  └───┘                     └───┘
```

### Key Characteristics:

1. **No Random Access**: Cannot access middle elements
2. **No Iterators**: Cannot traverse the stack
3. **Top-Only Access**: Only top element is accessible
4. **Dynamic Size**: Grows and shrinks automatically
5. **Type-Safe**: Template ensures type consistency

### Header and Namespace:
```cpp
#include <stack>
using namespace std;

// Or
std::stack<int> s;
```

### Basic Operations Example:
```cpp
std::stack<int> s;

s.push(10);     // [10]
s.push(20);     // [10, 20]
s.push(30);     // [10, 20, 30]

cout << s.top();  // 30 (peek at top)

s.pop();        // [10, 20] (removes 30)
s.pop();        // [10] (removes 20)

cout << s.top();  // 10
```

---

## How to Print a Stack?

**Problem**: Stack doesn't provide iterators, so you cannot directly loop through it!

**Challenge**: Accessing elements requires popping them, which destroys the stack.

### Method 1: Destructive Print (Empties the Stack)

```cpp
void printStack(std::stack<int> s) {  // Pass by value (creates copy)
    if(s.empty()) {
        std::cout << "Stack is empty!\n";
        return;
    }
    
    std::cout << "Stack (top to bottom): ";
    while(!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << "\n";
}

// Usage
std::stack<int> myStack;
myStack.push(10);
myStack.push(20);
myStack.push(30);

printStack(myStack);  // Pass by value - original stack unchanged
// Output: Stack (top to bottom): 30 20 10
```

**Note**: Passing by value creates a copy, so original stack remains intact.

### Method 2: Using Temporary Stack (Preserves Original)

```cpp
void printStackPreserve(std::stack<int> s) {
    std::stack<int> temp;
    
    // Transfer to temp (reverses order)
    while(!s.empty()) {
        temp.push(s.top());
        s.pop();
    }
    
    // Print from temp (bottom to top of original)
    std::cout << "Stack (bottom to top): ";
    while(!temp.empty()) {
        std::cout << temp.top() << " ";
        temp.pop();
    }
    std::cout << "\n";
}

// Output: Stack (bottom to top): 10 20 30
```

### Method 3: Using Vector/Deque (If You Need to Preserve and Print)

```cpp
void printStackNonDestructive(std::stack<int>& s) {
    if(s.empty()) {
        std::cout << "Stack is empty!\n";
        return;
    }
    
    // Copy to vector
    std::vector<int> temp;
    std::stack<int> copy = s;  // Copy the stack
    
    while(!copy.empty()) {
        temp.push_back(copy.top());
        copy.pop();
    }
    
    // Print
    std::cout << "Stack (top to bottom): ";
    for(int x : temp) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    
    // Original stack 's' is unchanged
}
```

### Method 4: Recursive Print (Elegant but Uses Call Stack)

```cpp
void printStackRecursive(std::stack<int>& s) {
    if(s.empty()) return;
    
    int top = s.top();
    s.pop();
    
    // Recursive call
    printStackRecursive(s);
    
    // Print in reverse order (bottom to top)
    std::cout << top << " ";
    
    // Restore the element
    s.push(top);
}

// Wrapper function
void printStack(std::stack<int>& s) {
    std::cout << "Stack (bottom to top): ";
    printStackRecursive(s);
    std::cout << "\n";
}
```

### Method 5: Debug Print with Copy (Most Practical)

```cpp
template<typename T>
void debugPrintStack(std::stack<T> s, const std::string& name = "Stack") {
    std::cout << name << " (size=" << s.size() << "): ";
    
    if(s.empty()) {
        std::cout << "[empty]\n";
        return;
    }
    
    std::cout << "[top] ";
    while(!s.empty()) {
        std::cout << s.top();
        s.pop();
        if(!s.empty()) std::cout << " -> ";
    }
    std::cout << " [bottom]\n";
}

// Usage
std::stack<int> myStack;
myStack.push(5);
myStack.push(10);
myStack.push(15);

debugPrintStack(myStack, "MyStack");
// Output: MyStack (size=3): [top] 15 -> 10 -> 5 [bottom]
```

### Why Can't We Use Iterator?

```cpp
// ❌ This doesn't exist for stack:
for(auto it = s.begin(); it != s.end(); ++it)  // Compilation error!

// ❌ This doesn't exist for stack:
for(int x : s)  // Compilation error!
```

**Reason**: Stack deliberately hides iteration to enforce LIFO behavior. Allowing iteration would violate the stack's conceptual model.

### Workaround: Access Underlying Container (Hacky)

```cpp
// This is non-standard and should be avoided!
// Some implementations allow accessing protected member
// DO NOT USE IN PRODUCTION CODE

template<class T, class Container>
Container& getContainer(std::stack<T, Container>& s) {
    struct HackedStack : std::stack<T, Container> {
        static Container& getContainer(std::stack<T, Container>& s) {
            return s.*&HackedStack::c;  // Access protected member 'c'
        }
    };
    return HackedStack::getContainer(s);
}
```

**Better Approach**: If you need iteration, don't use `std::stack`. Use `std::vector` or `std::deque` directly!

---

## What Functions Does Stack Have?

Stack provides a **minimal interface** focused on LIFO operations.

### Complete Function List:

#### 1. **Constructor**
```cpp
// Default constructor
std::stack<int> s1;

// Copy constructor
std::stack<int> s2(s1);

// Move constructor (C++11)
std::stack<int> s3(std::move(s1));

// With underlying container
std::deque<int> deq = {1, 2, 3};
std::stack<int> s4(deq);
```

#### 2. **Element Access**

```cpp
top()  // Access the top element (reference)
```

**Example:**
```cpp
std::stack<int> s;
s.push(10);
s.push(20);

std::cout << s.top();  // 20
s.top() = 99;          // Modify top element
std::cout << s.top();  // 99
```

**Important**: `top()` on empty stack is **undefined behavior**! Always check `empty()` first.

```cpp
if(!s.empty()) {
    std::cout << s.top();
} else {
    std::cout << "Stack is empty!";
}
```

#### 3. **Capacity**

```cpp
empty()    // Check if stack is empty (returns bool)
size()     // Return number of elements (returns size_t)
```

**Example:**
```cpp
std::stack<int> s;

std::cout << s.empty();  // true (1)
std::cout << s.size();   // 0

s.push(10);
s.push(20);

std::cout << s.empty();  // false (0)
std::cout << s.size();   // 2
```

#### 4. **Modifiers**

```cpp
push(value)        // Add element to top
emplace(args...)   // Construct element in-place at top (C++11)
pop()              // Remove top element (returns void!)
swap(other_stack)  // Swap contents with another stack
```

**push() Example:**
```cpp
std::stack<int> s;
s.push(10);
s.push(20);
s.push(30);
// Stack: [10, 20, 30] (30 at top)
```

**emplace() Example (C++11):**
```cpp
std::stack<std::pair<int, std::string>> s;

s.push({1, "One"});              // Creates temporary pair
s.emplace(2, "Two");             // Constructs pair in-place (more efficient)

std::stack<std::vector<int>> s2;
s2.emplace(5, 100);              // Creates vector with 5 elements of value 100
```

**pop() Example:**
```cpp
std::stack<int> s;
s.push(10);
s.push(20);
s.push(30);

s.pop();  // Removes 30 (returns nothing!)
s.pop();  // Removes 20

std::cout << s.top();  // 10
```

**⚠️ Important**: `pop()` doesn't return the value! You must use `top()` first.

```cpp
// ❌ WRONG: pop() returns void
int x = s.pop();  // Compilation error!

// ✅ CORRECT: Use top() then pop()
int x = s.top();
s.pop();
```

**Why doesn't pop() return value?**
- **Exception safety**: If copying the return value throws exception, element is lost
- **Efficiency**: Separating concerns (query vs modify)
- **Design principle**: Do one thing well

**swap() Example:**
```cpp
std::stack<int> s1, s2;
s1.push(1);
s1.push(2);
s2.push(10);
s2.push(20);

s1.swap(s2);
// s1: [10, 20]
// s2: [1, 2]

// Or use std::swap
std::swap(s1, s2);
```

#### 5. **Comparison Operators (C++20 onwards)**

```cpp
==, !=, <, <=, >, >=, <=>  // Compare two stacks
```

**Example:**
```cpp
std::stack<int> s1, s2;
s1.push(1); s1.push(2);
s2.push(1); s2.push(2);

s1 == s2  // true
s1 != s2  // false

s2.push(3);
s1 < s2   // true (lexicographic comparison)
```

### Function Summary Table:

| Function | Description | Returns | Time Complexity |
|----------|-------------|---------|-----------------|
| `push(val)` | Add element to top | void | O(1) |
| `emplace(args)` | Construct element at top | void | O(1) |
| `pop()` | Remove top element | void | O(1) |
| `top()` | Access top element | reference | O(1) |
| `empty()` | Check if empty | bool | O(1) |
| `size()` | Get number of elements | size_t | O(1) |
| `swap(other)` | Swap contents | void | O(1) |

### What Stack DOESN'T Have:

❌ No `begin()`, `end()` - No iterators
❌ No `operator[]` - No random access
❌ No `at()` - No indexed access
❌ No `clear()` - Must pop until empty
❌ No `front()` - Only `top()` available
❌ No `insert()` - Only push at top
❌ No `erase()` - Only pop from top

### Complete Usage Example:

```cpp
#include <iostream>
#include <stack>
#include <string>

int main() {
    std::stack<std::string> books;
    
    // Check if empty
    if(books.empty()) {
        std::cout << "Stack is empty\n";
    }
    
    // Add elements
    books.push("Book 1");
    books.push("Book 2");
    books.push("Book 3");
    books.emplace("Book 4");  // Constructs string in-place
    
    // Size
    std::cout << "Stack size: " << books.size() << "\n";  // 4
    
    // Access top
    std::cout << "Top book: " << books.top() << "\n";  // Book 4
    
    // Modify top
    books.top() = "Modified Book 4";
    
    // Remove elements
    while(!books.empty()) {
        std::cout << "Removing: " << books.top() << "\n";
        books.pop();
    }
    
    // Now empty
    std::cout << "Stack size: " << books.size() << "\n";  // 0
    
    return 0;
}
```

---

## Difference Between Stack and Queue

Both are **container adapters**, but with different access patterns.

### Visual Comparison:

**Stack (LIFO):**
```
Push →  ┌───┐  ← Pop
        │ 3 │ (Last In, First Out)
        ├───┤
        │ 2 │
        ├───┤
        │ 1 │
        └───┘
```

**Queue (FIFO):**
```
Push →  ┌───┬───┬───┐  ← Pop
        │ 3 │ 2 │ 1 │ (First In, First Out)
        └───┴───┴───┘
```

### Detailed Comparison Table:

| Feature | Stack | Queue |
|---------|-------|-------|
| **Principle** | LIFO (Last In First Out) | FIFO (First In First Out) |
| **Insertion** | `push()` at top | `push()` at back |
| **Deletion** | `pop()` from top | `pop()` from front |
| **Access** | `top()` only | `front()` and `back()` |
| **Real-World Analogy** | Stack of plates | Line at ticket counter |
| **Default Container** | `std::deque` | `std::deque` |
| **Alternative Containers** | vector, list, deque | list, deque (not vector) |
| **Header** | `<stack>` | `<queue>` |

### Operations Comparison:

```cpp
// Stack
std::stack<int> s;
s.push(10);         // Add to top
s.push(20);
s.push(30);
s.top();            // Access: 30 (last added)
s.pop();            // Remove: 30 (last added)

// Queue
std::queue<int> q;
q.push(10);         // Add to back
q.push(20);
q.push(30);
q.front();          // Access: 10 (first added)
q.back();           // Access: 30 (last added)
q.pop();            // Remove: 10 (first added)
```

### Function Comparison:

| Operation | Stack | Queue |
|-----------|-------|-------|
| Add element | `push()` | `push()` |
| Remove element | `pop()` | `pop()` |
| Access next to remove | `top()` | `front()` |
| Access last added | `top()` | `back()` |
| Check empty | `empty()` | `empty()` |
| Get size | `size()` | `size()` |

### Detailed Example:

```cpp
#include <stack>
#include <queue>
#include <iostream>

int main() {
    std::stack<int> s;
    std::queue<int> q;
    
    // Add 1, 2, 3 to both
    for(int i = 1; i <= 3; i++) {
        s.push(i);
        q.push(i);
    }
    
    std::cout << "Stack removes (LIFO): ";
    while(!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    // Output: 3 2 1 (reverse order)
    
    std::cout << "\nQueue removes (FIFO): ";
    while(!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    // Output: 1 2 3 (same order)
    
    return 0;
}
```

### Use Case Comparison:

| Stack Use Cases | Queue Use Cases |
|-----------------|-----------------|
| Function call management | Task scheduling |
| Undo/Redo operations | Print job management |
| Expression evaluation | BFS traversal |
| Backtracking algorithms | Request handling |
| Browser back button | Message queuing |
| Syntax parsing | Customer service line |
| DFS traversal | Buffering streams |

### Memory Layout:

**Stack Operations:**
```
Initial: [1, 2, 3]
push(4): [1, 2, 3, 4]  ← Added at end
pop():   [1, 2, 3]     ← Removed from end
top():   3             ← Access end
```

**Queue Operations:**
```
Initial: [1, 2, 3]
push(4): [1, 2, 3, 4]  ← Added at end
pop():   [2, 3, 4]     ← Removed from front
front(): 2             ← Access front
back():  4             ← Access end
```

### Why Queue Can't Use Vector?

```cpp
// Queue needs efficient front deletion
// Vector: O(n) for front deletion (must shift all elements)
// Deque: O(1) for front deletion

// This is why queue's default is deque:
template<class T, class Container = std::deque<T>>
class queue;

// Stack can use vector because it only operates on back:
template<class T, class Container = std::deque<T>>
class stack;

std::stack<int, std::vector<int>> s;  // ✅ OK
std::queue<int, std::vector<int>> q;  // ❌ Bad performance
```

---

## Use Cases of Stack

### 1. **Function Call Management (Call Stack)**

How programs manage function calls:

```cpp
void functionC() {
    std::cout << "In C\n";
}

void functionB() {
    std::cout << "In B\n";
    functionC();  // C pushed on stack
    std::cout << "Back to B\n";
}

void functionA() {
    std::cout << "In A\n";
    functionB();  // B pushed on stack
    std::cout << "Back to A\n";
}

int main() {
    functionA();  // A pushed on stack
    return 0;
}

// Call Stack:
// main() → functionA() → functionB() → functionC()
// Returns in reverse: functionC() → functionB() → functionA() → main()
```

### 2. **Expression Evaluation**

#### Infix to Postfix Conversion:
```cpp
// Convert: (A + B) * C → AB+C*

std::stack<char> operators;
std::string infix = "(A+B)*C";
std::string postfix = "";

// Algorithm uses stack to manage operator precedence
```

#### Evaluate Postfix Expression:
```cpp
int evaluatePostfix(std::string exp) {
    std::stack<int> s;
    
    for(char c : exp) {
        if(isdigit(c)) {
            s.push(c - '0');
        } else {
            int val2 = s.top(); s.pop();
            int val1 = s.top(); s.pop();
            
            switch(c) {
                case '+': s.push(val1 + val2); break;
                case '-': s.push(val1 - val2); break;
                case '*': s.push(val1 * val2); break;
                case '/': s.push(val1 / val2); break;
            }
        }
    }
    return s.top();
}

// Example: "23*5+" = (2*3)+5 = 11
```

### 3. **Parentheses Matching**

```cpp
bool isValidParentheses(std::string s) {
    std::stack<char> st;
    
    for(char c : s) {
        if(c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if(st.empty()) return false;
            
            char top = st.top();
            if((c == ')' && top == '(') ||
               (c == '}' && top == '{') ||
               (c == ']' && top == '[')) {
                st.pop();
            } else {
                return false;
            }
        }
    }
    
    return st.empty();
}

// Examples:
// "()" → true
// "()[]{}" → true
// "(]" → false
// "([)]" → false
```

### 4. **Undo/Redo Functionality**

```cpp
class TextEditor {
    std::stack<std::string> undoStack;
    std::stack<std::string> redoStack;
    std::string currentText;
    
public:
    void write(std::string text) {
        undoStack.push(currentText);
        currentText = text;
        // Clear redo stack on new action
        while(!redoStack.empty()) redoStack.pop();
    }
    
    void undo() {
        if(!undoStack.empty()) {
            redoStack.push(currentText);
            currentText = undoStack.top();
            undoStack.pop();
        }
    }
    
    void redo() {
        if(!redoStack.empty()) {
            undoStack.push(currentText);
            currentText = redoStack.top();
            redoStack.pop();
        }
    }
};
```

### 5. **Browser History (Back Button)**

```cpp
class BrowserHistory {
    std::stack<std::string> backStack;
    std::stack<std::string> forwardStack;
    std::string currentPage;
    
public:
    BrowserHistory(std::string homepage) : currentPage(homepage) {}
    
    void visit(std::string url) {
        backStack.push(currentPage);
        currentPage = url;
        // Clear forward history
        while(!forwardStack.empty()) forwardStack.pop();
    }
    
    std::string back() {
        if(!backStack.empty()) {
            forwardStack.push(currentPage);
            currentPage = backStack.top();
            backStack.pop();
        }
        return currentPage;
    }
    
    std::string forward() {
        if(!forwardStack.empty()) {
            backStack.push(currentPage);
            currentPage = forwardStack.top();
            forwardStack.pop();
        }
        return currentPage;
    }
};
```

### 6. **Depth-First Search (DFS)**

```cpp
void DFS(int start, std::vector<int> adj[], int V) {
    std::vector<bool> visited(V, false);
    std::stack<int> s;
    
    s.push(start);
    
    while(!s.empty()) {
        int node = s.top();
        s.pop();
        
        if(!visited[node]) {
            std::cout << node << " ";
            visited[node] = true;
            
            // Push adjacent nodes
            for(int neighbor : adj[node]) {
                if(!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
}
```

### 7. **Backtracking Algorithms**

```cpp
// N-Queens, Sudoku Solver, Maze Solver
bool solveMaze(int maze[][], int x, int y) {
    std::stack<std::pair<int, int>> path;
    
    path.push({x, y});
    
    while(!path.empty()) {
        auto [cx, cy] = path.top();
        
        if(isDestination(cx, cy)) {
            return true;  // Found path
        }
        
        // Try all 4 directions
        // If valid, push to stack
        // If dead end, pop (backtrack)
    }
    
    return false;
}
```

### 8. **Stock Span Problem**

```cpp
// Calculate how many consecutive days before current day
// had price less than or equal to current day's price

std::vector<int> calculateSpan(std::vector<int>& prices) {
    std::stack<int> s;  // Stack of indices
    std::vector<int> span(prices.size());
    
    for(int i = 0; i < prices.size(); i++) {
        // Pop elements smaller than current
        while(!s.empty() && prices[s.top()] <= prices[i]) {
            s.pop();
        }
        
        // Calculate span
        span[i] = s.empty() ? (i + 1) : (i - s.top());
        
        s.push(i);
    }
    
    return span;
}

// Example: prices = [100, 80, 60, 70, 60, 75, 85]
// Output: [1, 1, 1, 2, 1, 4, 6]
```

### 9. **Next Greater Element**

```cpp
std::vector<int> nextGreaterElement(std::vector<int>& arr) {
    int n = arr.size();
    std::vector<int> result(n, -1);
    std::stack<int> s;
    
    // Traverse from right to left
    for(int i = n - 1; i >= 0; i--) {
        // Remove smaller elements
        while(!s.empty() && s.top() <= arr[i]) {
            s.pop();
        }
        
        // Top of stack is next greater
        if(!s.empty()) {
            result[i] = s.top();
        }
        
        s.push(arr[i]);
    }
    
    return result;
}

// Example: [4, 5, 2, 10, 8]
// Output: [5, 10, 10, -1, -1]
```

### 10. **Reversing Data**

```cpp
// Reverse a string
std::string reverseString(std::string str) {
    std::stack<char> s;
    
    for(char c : str) {
        s.push(c);
    }
    
    std::string reversed = "";
    while(!s.empty()) {
        reversed += s.top();
        s.pop();
    }
    
    return reversed;
}

// Reverse a linked list using stack
```

---

## More About Stack

### 1. Time Complexity Analysis

All stack operations are **O(1)** constant time:

```cpp
std::stack<int> s;

s.push(10);      // O(1)
s.pop();         // O(1)
s.top();         // O(1)
s.empty();       // O(1)
s.size();        // O(1)
s.swap(other);   // O(1) - just swaps internal containers
```

**Why O(1)?**
- All operations work on one end (top) only
- No traversal needed
- Underlying container (deque/vector/list) provides O(1) operations at end

### 2. Space Complexity

```cpp
// Stack space: O(n) where n = number of elements
std::stack<int> s;
// Space = n * sizeof(element) + container overhead
```

### 3. Underlying Container Performance

```cpp
// Option 1: deque (default) - balanced performance
std::stack<int> s1;

// Option 2: vector - best cache performance
std::stack<int, std::vector<int>> s2;
// Pros: Contiguous memory, cache-friendly
// Cons: Reallocation when capacity exceeded

// Option 3: list - stable iterators
std::stack<int, std::list<int>> s3;
// Pros: No reallocation, stable pointers
// Cons: Poor cache performance, memory overhead
```

**Benchmark Results** (typical):
```
Operation         | Deque  | Vector | List
------------------+--------+--------+------
push (average)    | Fast   | Fast   | Medium
push (worst case) | Fast   | Slow*  | Fast
pop               | Fast   | Fast   | Fast
memory overhead   | Medium | Low    | High
cache performance | Good   | Best   | Worst

* Vector may need to reallocate and copy all elements
```

### 4. Memory Management

```cpp
std::stack<int> s;

// Stack doesn't have capacity/reserve
// It depends on underlying container

// For vector-based stack:
std::stack<int, std::vector<int>> s;
// Cannot call s.capacity() or s.reserve() directly

// Workaround if needed:
std::vector<int> vec;
vec.reserve(1000);  // Pre-allocate
std::stack<int, std::vector<int>> s(vec);
```

### 5. Exception Safety

```cpp
std::stack<int> s;

// push() - may throw
try {
    s.push(10);  // May throw bad_alloc
} catch(std::bad_alloc& e) {
    // Handle memory allocation failure
}

// top() - never throws, but UB if empty
if(!s.empty()) {
    int x = s.top();  // Safe
}

// pop() - never throws
s.pop();  // No exception, but UB if empty
```

### 6. Thread Safety

Stack is **NOT thread-safe** by default:

```cpp
// ❌ NOT SAFE: Multiple threads accessing same stack
std::stack<int> s;

// Thread 1
s.push(10);

// Thread 2
if(!s.empty()) s.pop();  // Race condition!
```

**Thread-safe wrapper:**
```cpp
template<typename T>
class ThreadSafeStack {
    std::stack<T> s;
    mutable std::mutex mtx;
    
public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        s.push(value);
    }
    
    bool tryPop(T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        if(s.empty()) return false;
        value = s.top();
        s.pop();
        return true;
    }
    
    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return s.empty();
    }
};
```

### 7. Custom Types in Stack

```cpp
class Task {
    int priority;
    std::string description;
    
public:
    Task(int p, std::string d) : priority(p), description(d) {}
    
    // No comparison operators needed for stack
    // (unlike priority_queue)
};

std::stack<Task> taskStack;
taskStack.emplace(1, "High priority task");
taskStack.emplace(2, "Low priority task");
```

### 8. Stack vs std::vector (When to Use What?)

```cpp
// Use std::stack when:
// ✅ Need to enforce LIFO behavior
// ✅ Want to prevent accidental middle access
// ✅ Implementing algorithms that use stack concept

std::stack<int> s;
s.push(10);

// Use std::vector when:
// ✅ Need random access
// ✅ Need iteration
// ✅ Need to access/modify middle elements
// ✅ Need more flexibility

std::vector<int> v;
v.push_back(10);  // Can still use as stack
v[0];             // But also has random access
```

### 9. Common Mistakes

```cpp
// ❌ MISTAKE 1: Trying to return value from pop()
int x = s.pop();  // Error: pop() returns void

// ✅ CORRECT:
int x = s.top();
s.pop();

// ❌ MISTAKE 2: Not checking if empty
int x = s.top();  // Undefined behavior if empty!

// ✅ CORRECT:
if(!s.empty()) {
    int x = s.top();
}

// ❌ MISTAKE 3: Trying to iterate
for(int x : s) { }  // Error: no iterators

// ✅ CORRECT: Use copy
std::stack<int> temp = s;
while(!temp.empty()) {
    std::cout << temp.top();
    temp.pop();
}

// ❌ MISTAKE 4: Comparing empty check in loop condition
while(s.size() > 0) { }  // Less idiomatic

// ✅ BETTER:
while(!s.empty()) { }
```

### 10. Advanced: Min Stack (O(1) getMin)

```cpp
class MinStack {
    std::stack<int> s;
    std::stack<int> minS;  // Maintains minimum
    
public:
    void push(int x) {
        s.push(x);
        if(minS.empty() || x <= minS.top()) {
            minS.push(x);
        }
    }
    
    void pop() {
        if(!s.empty()) {
            if(s.top() == minS.top()) {
                minS.pop();
            }
            s.pop();
        }
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return minS.top();  // O(1) minimum retrieval
    }
};
```

### 11. Stack Overflow

```cpp
// Stack memory is limited!
void recursiveFunction() {
    int array[10000];  // Large local variable
    recursiveFunction();  // Deep recursion
}
// Eventually causes stack overflow!

// Solution 1: Use iterative approach with std::stack
// Solution 2: Increase stack size (compiler/OS dependent)
// Solution 3: Use heap memory (new/vector)
```

### 12. Implementing Stack from Scratch

```cpp
template<typename T>
class MyStack {
    std::vector<T> data;
    
public:
    void push(const T& value) {
        data.push_back(value);
    }
    
    void pop() {
        if(!empty()) data.pop_back();
    }
    
    T& top() {
        return data.back();
    }
    
    bool empty() const {
        return data.empty();
    }
    
    size_t size() const {
        return data.size();
    }
};
```

### 13. Performance Tips

```cpp
// Tip 1: Use emplace for complex types
std::stack<std::pair<int, std::string>> s;
s.emplace(1, "One");  // Better than push(make_pair(...))

// Tip 2: Reserve underlying vector if size known
std::vector<int> vec;
vec.reserve(1000);
std::stack<int, std::vector<int>> s(std::move(vec));

// Tip 3: Use references to avoid copies
if(!s.empty()) {
    const auto& top = s.top();  // Reference, no copy
}

// Tip 4: Clear stack efficiently
while(!s.empty()) s.pop();
// Or: swap with empty stack
std::stack<int>().swap(s);
```

### 14. Interesting Facts

1. **Name Origin**: "Stack" comes from stacking physical objects
2. **Memory Types**: "Stack memory" (program stack) vs `std::stack` (data structure)
3. **CPU Stack**: Every program has an implicit call stack
4. **Reverse Polish Notation**: Stack-based expression evaluation
5. **JVM & .NET**: Use stack-based architecture

### 15. Related Data Structures

```cpp
// Stack variations:
std::stack<T>              // Standard LIFO stack
std::deque<T>              // Can be used as stack with back operations
std::vector<T>             // Can be used as stack with back operations

// Related adapters:
std::queue<T>              // FIFO queue
std::priority_queue<T>     // Priority-based queue

// If you need:
// - Min/Max in O(1): Use MinStack pattern
// - Sorting: Use priority_queue
// - FIFO: Use queue
// - Deque operations: Use deque directly
```

---

## Summary - Quick Reference

```cpp
#include <stack>

// Creation
std::stack<int> s;
std::stack<int, std::vector<int>> sv;  // With vector

// Operations
s.push(10);              // Add to top
s.emplace(20);           // Construct at top
s.pop();                 // Remove from top (returns void!)
int x = s.top();         // Access top
bool e = s.empty();      // Check if empty
size_t sz = s.size();    // Get size

// Safe operations
if(!s.empty()) {
    int top = s.top();
    s.pop();
}

// Print (destructive)
while(!s.empty()) {
    std::cout << s.top() << " ";
    s.pop();
}
```

**Remember**: Stack enforces LIFO and restricts access to only the top element. This makes it perfect for algorithms that need this specific behavior pattern!