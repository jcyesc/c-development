# Chapter 3 - Pointers and Functions

Pointers allow data to be passed and modified by a function. Complex data
can also be passed and returned from a function in the form of a pointer to
a structure. When pointers hold the addres of a function, they provide a means to
dynamically control a program's execution flow.


## Activation Records (Stack frame)
The segment of the stack that contains the variables for a function is the
"activation record" or "stack frame" of that function. In addition to storing local
variables, the activation record for a function also stores some save registers values.

### Frame Pointer
A special register, called the "frame pointer" (FP) points to the beginning of the
current frame. Another register, the "stack pointer" (SP, contains the address of the first
unused location on the stack.

### Organization of a Stack Frame
A stack frame consists of several elements, including:

-`Returning address`: The address in the program where the function is to return upon completion.
-`Storage for local data`: Memory allocated for local variables.
-`Storage for parameters`: Memory allocated for the function's parameters.
- `Stack and frame pointers (base pointers)`: Pointers used by the runtime system to manage the stack.

## Returning a Pointer
If we need to return an object from a function, two techniques are frequently used:

- Allocate memory within the function using `malloc` and return its address. The caller is
responsible for deallocating the memory returned.

- Pass an object o the functin where it is modified. This makes the allocation and deallocation of the 
object's memory the caller's responsibility.

Several potential problems can occur when returning a pointer from a function, including:

- Returning an unitialized pointer
- Returning a pointer to an invalid address
- Returning a pointer to a local variable
- Returning a pointer but failing to free it

## Passing a pointer to a pointer
When a pointer is passed to a function, it is passed by value. If we want to modify the original
pointer and not the copy of the pointer, we need to pass it as a pointer to a pointer.

