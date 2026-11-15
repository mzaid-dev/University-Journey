# Dynamic Memory Allocation in C: `malloc()`, `calloc()`, `realloc()` and `free()`

> **OS Lab 3 --- C Programming \| Exam-focused notes**

## 1. Why do we need dynamic memory allocation?

A normal array has a fixed size decided when we write the program:

``` c
int arr[5];
```

This array can store five integers. But suppose the user runs the
program and enters `n = 20`. We may want an array with exactly 20
elements.

**Dynamic memory allocation** allows a program to request memory while
it is running (at runtime). In C, the main functions are:

-   `malloc()` --- allocates a block of memory.
-   `calloc()` --- allocates memory for multiple elements and
    initializes all bytes to zero.
-   `realloc()` --- changes the size of an already allocated block.
-   `free()` --- releases dynamically allocated memory.

These functions are declared in:

``` c
#include <stdlib.h>
```

## 2. Understand the memory picture

Think of memory as a row of numbered storage slots. A pointer stores the
address of the first slot in the allocated block.

For example:

``` c
int *ptr = malloc(5 * sizeof(int));
```

Conceptually, this requests enough space for five integers.

``` mermaid
flowchart TB
    P["Pointer variable: ptr"] --> A["Address of first allocated slot"]
    subgraph H["Dynamically allocated memory (heap)"]
      A --> S1["Integer 1"]
      S1 --> S2["Integer 2"]
      S2 --> S3["Integer 3"]
      S3 --> S4["Integer 4"]
      S4 --> S5["Integer 5"]
    end
```

The diagram is conceptual: the five elements occupy one contiguous block
of memory. The pointer `ptr` points to the first element.

### Stack and heap --- basic distinction

-   **Stack:** commonly stores local variables, such as `int n;`.
-   **Heap:** the area from which dynamic memory is allocated.
    `malloc()` and `calloc()` request memory from this area.

``` mermaid
flowchart LR
    subgraph S["Stack (local variables)"]
      N["n"]
      P["ptr"]
    end
    subgraph H["Heap (dynamic allocation)"]
      B["Allocated block: 5 integers"]
    end
    P --> B
```

`ptr` itself is a local pointer variable in this example; the block it
points to is dynamically allocated.

## 3. `malloc()` --- Memory Allocation

`malloc` means **memory allocation**. It requests one block of the
specified number of bytes and returns a pointer to the beginning of that
block.

### Syntax

``` c
pointer = malloc(number_of_bytes);
```

A common textbook-style form is:

``` c
ptr = (int*) malloc(5 * sizeof(int));
```

In C, the cast `(int*)` is not required. A clear modern C form is:

``` c
int *ptr = malloc(5 * sizeof *ptr);
```

### Understand every part

  Part                Meaning
  ------------------- -------------------------------------------------
  `int *ptr`          Declares a pointer that can point to an integer
  `malloc(...)`       Requests a block of memory
  `5`                 Number of integer elements requested
  `sizeof(int)`       Number of bytes occupied by one `int`
  `5 * sizeof(int)`   Total number of bytes requested
  `ptr`               Receives the address returned by `malloc()`

**Important:** `sizeof(int)` is used instead of assuming an integer
always occupies a particular number of bytes. The actual size is
implementation-dependent.

### What does `malloc()` contain initially?

The allocated memory is **uninitialized**. It contains indeterminate
values; do not assume it starts at zero. Assign values before reading
from it.

## 4. Complete `malloc()` program

``` c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, i;
    int *arr;

    printf("Enter array size: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Please enter a positive array size.\n");
        return 1;
    }

    arr = malloc(n * sizeof *arr);

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; i++)
    {
        printf("Enter number %d: ", i + 1);
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Invalid input.\n");
            free(arr);
            return 1;
        }
    }

    printf("Array elements: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    arr = NULL;

    return 0;
}
```

### Dry run

Suppose the user enters:

``` text
Enter array size: 3
Enter number 1: 10
Enter number 2: 20
Enter number 3: 30
```

  Step   What happens
  ------ -------------------------------------------------------------
  1      `n` receives `3`
  2      `malloc(3 * sizeof *arr)` requests space for three integers
  3      If successful, the returned address is stored in `arr`
  4      `arr[0]` receives `10`
  5      `arr[1]` receives `20`
  6      `arr[2]` receives `30`
  7      The loop prints `10 20 30`
  8      `free(arr)` releases the allocated block

Output:

``` text
Array elements: 10 20 30
```

### How does `arr[i]` work?

For an array-like block, indexing starts at zero:

  Expression     Element
  -------------- ----------------
  `arr[0]`       First integer
  `arr[1]`       Second integer
  `arr[2]`       Third integer
  `arr[n - 1]`   Last integer

`arr[i]` is equivalent to `*(arr + i)`.

## 5. `calloc()` --- Contiguous Allocation

`calloc` means **contiguous allocation**. It allocates space for a
number of elements and sets all bytes in the allocated block to zero.

### Syntax

``` c
pointer = calloc(number_of_elements, size_of_each_element);
```

Example:

``` c
int *arr = calloc(5, sizeof(int));
```

This requests space for five integers and initializes the allocated
bytes to zero. For an ordinary integer array, the elements will
therefore have the value `0`.

### `calloc()` memory picture

``` mermaid
flowchart TB
    P["arr points to first element"] --> A
    subgraph H["Allocated block: 5 integers"]
      A["arr[0] = 0"] --> B["arr[1] = 0"]
      B --> C["arr[2] = 0"]
      C --> D["arr[3] = 0"]
      D --> E["arr[4] = 0"]
    end
```

### Complete `calloc()` example

``` c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;
    int *arr;

    arr = calloc(5, sizeof *arr);

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Initial values: ");
    for (i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }

    free(arr);
    arr = NULL;

    return 0;
}
```

Output:

``` text
Initial values: 0 0 0 0 0
```

You can then assign new values to `arr[0]`, `arr[1]`, and so on.

## 6. Difference between `malloc()` and `calloc()`

  -----------------------------------------------------------------------
  `malloc()`                          `calloc()`
  ----------------------------------- -----------------------------------
  Takes one size argument             Takes two arguments

  `malloc(total_bytes)`               `calloc(count, element_size)`

  Allocates a block of memory         Allocates space for an array of
                                      elements

  Memory is uninitialized             All allocated bytes are initialized
                                      to zero

  Example: `malloc(5 * sizeof(int))`  Example: `calloc(5, sizeof(int))`
  -----------------------------------------------------------------------

**Exam point:** Both return a pointer to the allocated memory, or `NULL`
if the allocation fails. Both must eventually be paired with `free()`
when the memory is no longer needed.

## 7. `realloc()` --- Resize allocated memory

`realloc()` changes the size of a block that was previously allocated
using `malloc()`, `calloc()`, or `realloc()`.

### Syntax

``` c
new_ptr = realloc(old_ptr, new_size_in_bytes);
```

Example:

``` c
int *temp = realloc(arr, 10 * sizeof *arr);
if (temp != NULL)
{
    arr = temp;
}
```

This attempts to resize the block to hold ten integers. The block may
move to a new location, so use the pointer returned by `realloc()`.

**Safe rule:** Store the result in a temporary pointer. If `realloc()`
fails for a non-zero requested size, it returns `NULL` and the original
block remains allocated.

``` mermaid
flowchart TD
    A["Existing block: 5 integers"] --> B["Call realloc() for 10 integers"]
    B --> C{"Did realloc succeed?"}
    C -->|Yes| D["Use returned pointer; block now has new size"]
    C -->|No| E["Keep original pointer and original block"]
```

## 8. `free()` --- Release allocated memory

When the program no longer needs dynamically allocated memory, release
it:

``` c
free(arr);
arr = NULL;
```

-   `free(arr)` returns the allocated block to the memory allocator.
-   Setting `arr = NULL` is a helpful habit: it prevents this pointer
    variable from retaining a stale address.
-   Do not use the block after freeing it.
-   Do not free the same allocation twice.
-   Only pass a valid allocated pointer (or `NULL`) to `free()`.

### What happens if we forget `free()`?

Memory that is no longer needed remains allocated for as long as the
program continues. This is called a **memory leak**. In a long-running
program, repeated leaks can waste memory.

## 9. Full comparison

  -----------------------------------------------------------------------
  Function                Main purpose            Initialization
  ----------------------- ----------------------- -----------------------
  `malloc()`              Allocate a block of     Uninitialized
                          bytes                   

  `calloc()`              Allocate space for      All bytes set to zero
                          multiple elements       

  `realloc()`             Resize an existing      Preserves existing
                          allocated block         contents up to the
                                                  smaller of old and new
                                                  sizes; any added
                                                  portion is
                                                  uninitialized

  `free()`                Release allocated       Not applicable
                          memory                  
  -----------------------------------------------------------------------

## 10. Common mistakes to avoid

1.  **Forgetting `<stdlib.h>`** --- the allocation functions are
    declared there.
2.  **Forgetting to check `NULL`** --- allocation can fail.
3.  **Reading `malloc()` memory before assigning values** --- its
    contents are uninitialized.
4.  **Using the wrong size** --- use `n * sizeof *ptr` for `n` elements.
5.  **Forgetting `free()`** --- can cause a memory leak.
6.  **Using memory after `free()`** --- this is invalid.
7.  **Overwriting the only pointer with `realloc()` directly** --- if it
    fails, you may lose access to the original block.
8.  **Using a non-positive or unreasonable user-provided size** ---
    validate input before allocating.

## 11. Important viva and exam questions

**Q1. What is dynamic memory allocation?**\
It is the process of allocating memory during program execution
(runtime), according to the program's needs.

**Q2. What is `malloc()`?**\
`malloc()` allocates a specified number of bytes and returns a pointer
to the allocated memory. The memory is uninitialized.

**Q3. What is `calloc()`?**\
`calloc()` allocates memory for a specified number of elements and
initializes all allocated bytes to zero.

**Q4. What is the main difference between `malloc()` and `calloc()`?**\
`malloc()` takes one argument and leaves memory uninitialized.
`calloc()` takes two arguments and zero-initializes the allocated bytes.

**Q5. What does `sizeof()` do?**\
It returns the size in bytes of a type or object.

**Q6. What does `NULL` indicate after an allocation call?**\
It indicates that the allocation failed and no usable block was
returned.

**Q7. Why do we use `free()`?**\
To release dynamically allocated memory when it is no longer required.

**Q8. What is a memory leak?**\
A memory leak occurs when allocated memory is no longer needed but is
not released.

**Q9. What is `realloc()` used for?**\
It changes the size of a previously allocated memory block.

**Q10. Where are `malloc()`, `calloc()`, `realloc()`, and `free()`
declared?**\
In the standard header file `<stdlib.h>`.

## 12. Quick revision sheet

``` c
#include <stdlib.h>

int *a;

/* Allocate memory for 5 integers (uninitialized) */
a = malloc(5 * sizeof *a);

/* Allocate memory for 5 integers (zero-initialized bytes) */
a = calloc(5, sizeof *a);

/* Resize an existing allocation */
int *temp = realloc(a, 10 * sizeof *a);
if (temp != NULL)
    a = temp;

/* Release the allocation */
free(a);
a = NULL;
```

> **Remember this for the exam:** `malloc` = allocate; `calloc` =
> allocate and zero-initialize; `realloc` = resize; `free` = release.

The short code above demonstrates the function calls separately. In a
real program, do not overwrite a pointer that already owns an allocation
with a new `malloc()` or `calloc()` result unless you have safely
handled the old allocation.
