/** This program
 *create stack class
 *and can do many interesting things with it
 */

#include"declaration.h"

int main()
{
    /// Creating stack:
    /// Enter capacity
    size_t cap;
    printf("Enter maximal number of elements in stack\n");
    bool check = scanf("%d", &cap);
    if(check == FALSE)
    {
        printf("Wrong entry\n");
        return 1;
    }

    /// Number of elements you want to put on stack
    size_t size;
    printf("Enter number of elements\n");
    check = scanf("%d", &size);
    if(check == FALSE)
    {
        printf("Wrong entry\n");
        return 1;
    }
    if(size > cap)
    {
        printf("Wrong entry");
        return 1;
    }

    /// Test functions
    /// Test CREATE
    Stack<int> Stack;
    check = Stack.Create(cap);
    if(check == FALSE)
        return 1;

    /// Fill the stack with random numbers
    /// Test PUSH
    printf("Stack will be filled with random numbers\n");
    for(int i = 0; i < size; ++i)
        check = Stack.Push(rand() % 10);
    if(check == FALSE)
        return 1;
    /// Printing all stack characteristics and elements
    check = Stack.Dump();
    if(check == FALSE)
        return 1;

    /// Test POP
    int num = 0;
    Stack.Pop(&num);
    if(check == FALSE)
        return 1;
    printf("Here is the last element of the stack: %d\n", num);
    check = Stack.Dump();
    if(check == FALSE)
        return 1;
    printf("Pay attention that last element isn't in stack\n");

    /// Test SIZE
    check = Stack.Size(&num);
    if(check == FALSE)
        return 1;
    printf("Now there is only %d elements in stack\n", num);

    /// Test GET
    check = Stack.Get(&num);
    if(check == FALSE)
        return 1;
    printf("Here is the last element of the stack: %d\n", num);
    check = Stack.Dump();
    if(check == FALSE)
        return 1;
    printf("Pay attention that last element is still in stack\n");

    /// Test.2 PUSH
    printf("Write a number for stack\n");
    check = scanf("%d", &num);
    if(check == FALSE)
    {
        printf("Wrong entry");
        return 1;
    }
    check = Stack.Push(num);
    if(check == FALSE)
        return 1;
    check = Stack.Dump();
    if(check == FALSE)
        return 1;


    /// Test CLEAR
    check = Stack.Clear();
    if(check == FALSE)
        return 1;
    printf("Now stack is empty\n");
    check = Stack.Dump();
    if(check == FALSE)
        return 1;

    /// Test-2 SIZE
    check = Stack.Size(&num);
    if(check == FALSE)
        return 1;
    printf("Now stack is empty (size = %d)\n", num);
    check = Stack.Dump();
    if(check == FALSE)
        return 1;

    /// Test PLUSMEMORY
    for(int i = 0; i < size; ++i)
        check = Stack.Push(rand() % 10);
    if(check == FALSE)
        return 1;
    /// Now stack is overflow, but function will get memory
    for(int i = 0; i < size; ++i)
        check = Stack.Push(rand() % 10);
    if(check == FALSE)
        return 1;
    check = Stack.Dump();
    if(check == FALSE)
        return 1;

    /// Test DESTROY
    check = Stack.Destroy();
    if(check == FALSE)
        return 1;
    printf("Stack isn't exist now\n");
    check = Stack.Dump();
    if(check == FALSE)
        return 1;
    return 0;
}
