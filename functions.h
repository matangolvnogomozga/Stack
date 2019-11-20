#include<errors.h>
#include<colours.h>
//-----------------------------------------------------
//! Function "SetColor" can change printing colour
//!
//!@param [in] text Colour of text you want
//!@param [in] background Colour of background you want
//!
//-----------------------------------------------------
void SetColor(ConsoleColor text, ConsoleColor background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
    return;
}

//-----------------------------------------------------
//! Function "RandomBig" count random LEN-signed number
//!
//!@return Random LEN-signed number
//-----------------------------------------------------
long long RandomBig()
{
    static bool first_start = false;
    if (first_start == false)
    {
        srand(time(0));
        first_start = true;
    }

    long long num = rand() % 9 + 1;
    for(int i = 0; i < LEN; ++i)
    {
        num *= 10;
        num += rand() % 10;
    }
    return num;
}

//-----------------------------------------------------
//! Function "Create" creates stack
//!
//!@param [in] cap Capacity of the stack
//!
//-----------------------------------------------------
template <typename T>
bool Stack<T>::Create(size_t cap)
{
    size = 0;
    capacity = cap;
    stack = (T *)calloc(cap, sizeof(T));

    #ifndef UNSAFE
    CANARY_1 = CANARYBEGIN1;
    CANARY_2 = CANARYBEGIN2;
    hash = Hash();
    #endif // UNSAFE

    if(OKCreate())
        return FAIL;
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "Hash" counts hash-sum
//!
//!@note Count hash every time when you change stack elements or size
//-----------------------------------------------------
#ifndef UNSAFE
template <typename T>
long Stack<T>::Hash()
{
    return (stack[0] * 64 + size * 2 + CANARY_1 % 67 - CANARY_2 % 23 - capacity - stack[size-1] % 48);
}
#endif // UNSAFE

//-----------------------------------------------------
//! Function "Push" pushes elements to stack
//!
//!@param [in] data Element pushing to stack
//!
//-----------------------------------------------------
template <typename T>
bool Stack<T>::Push(T data)
{
    if(OKPush())
        return FAIL;
    stack[size++] = data;

    #ifndef UNSAFE
    hash = Hash();
    #endif // UNSAFE

    if(OKPush())
        return FAIL;
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "Pop" pulls elements from stack
//!
//!@param [in] data Variable for the element
//!
//!@note After using element isn't exist in stack
//-----------------------------------------------------
template <typename T>
bool Stack<T>::Pop(T *data)
{
    assert(data != NULL);
    if(OKPop())
        return FAIL;
    *data = stack[--size];

    #ifndef UNSAFE
    hash = Hash();
    #endif // UNSAFE

    if(OKPop())
        return FAIL;
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "Get" get value element from the stack
//!
//!@param [in] data Variable for the element
//!
//!@note After using function element still exist in stack
//-----------------------------------------------------
template <typename T>
bool Stack<T>::Get(T *data)
{
    assert(data != NULL);
    if(OKPop())
        return FAIL;
    *data = stack[size-1];
    if(OKPop())
        return FAIL;
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "Destroy" destroys stack
//-----------------------------------------------------
template <typename T>
bool Stack<T>::Destroy()
{
    if(OKDestroy())
        return FAIL;
    free(stack);
    size = 0;
    capacity = 0;

    #ifndef UNSAFE
    hash = Hash();
    #endif // UNSAFE

    return SUCCESS;
}

//-----------------------------------------------------
//! Function "Clear" deletes all elements of stack
//-----------------------------------------------------
template <typename T>
bool Stack<T>::Clear()
{
    if(OKCreate())
        return FAIL;
    for(int i = size - 1; i >= 0; --i)
        stack[i] = 0;
    size = 0;

    #ifndef UNSAFE
    hash = Hash();
    #endif // UNSAFE

    if(OKCreate())
        return FAIL;
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "Size" learns number of elements in stack
//!
//!@param [in] number Variable for the size
//!
//-----------------------------------------------------
template <typename T>
bool Stack<T>::Size(T *number)
{
    assert(number != NULL);
    if(OKSize())
        return FAIL;
    *number = size;
    if(OKSize())
        return FAIL;
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "Print" prints element
//!
//!@param [in] data Variable to print
//!
//-----------------------------------------------------
template <typename T>
void Stack<T>::Print(T data)
{
    std::cout << data << std::endl;
}

//-----------------------------------------------------
//! Function "Dump" print all characteristic of stack and it's elements
//-----------------------------------------------------
template <typename T>
bool Stack<T>::Dump()
{
    if(OKCreate())
    {
        printf("\nFAIL");
        return FAIL;
    }
    SetColor(Cyan, Black);
    printf("\n\t\tDUMP\n");
    SetColor(Green, Black);
    printf("%s", "Pointer of the stack:");
    SetColor(Red, Black);
    printf("\t\t%p\n", stack);
    SetColor(Green, Black);
    printf("%s", "Capacity of the stack:");
    SetColor(Red, Black);
    printf("\t\t%d\n", capacity);
    SetColor(Green, Black);
    printf("%s", "Number of elements in stack:");
    SetColor(Red, Black);
    printf("\t%d\n", size);

    #ifndef UNSAFE
    SetColor(Green, Black);
    printf("%s\t", "Hash:");
    SetColor(Red, Black);
    printf("\t\t\t%d\n", hash);
    SetColor(Green, Black);
    printf("%s", "First canary:");
    SetColor(Red, Black);
    printf("\t\t\t%d\n", CANARY_1);
    SetColor(Green, Black);
    printf("%s", "Second canary:");
    SetColor(Red, Black);
    printf("\t\t\t%d\n\n", CANARY_2);
    #endif // UNSAFE

    SetColor(Blue, Black);
    printf("%s\n", "Stack elements");
    for(int i = 0; i < size; ++i)
    {
        SetColor(Green, Black);
        printf("Element number %d is ", i+1);
        SetColor(Yellow, Black);
        Print(stack[i]);
    }
    SetColor(Cyan, Black);
    printf("\n\t\tEND OF DUMP\n");
    if(OKCreate())
    {
        printf("FAIL");
        return FAIL;
    }
    return SUCCESS;
}

//-----------------------------------------------------
//! Function "PlusMemory" adds memory if it was over
//!
//!@note You can change number of added memory
//-----------------------------------------------------
template <typename T>
int Stack<T>::PlusMemory(T* ptr)
{
    assert(ptr != NULL);
    realloc(ptr, 10*sizeof(int));
    if(ptr == NULL)
    {
        printf("NO_MEM_MORE");
        return NO_MEM_MORE;
    }
    else
    {
        capacity += 10;
        return ALL_GOOD;
    }
}

//-----------------------------------------------------
//! All functions "OK" check correctness of functions
//!
//!@note You can change number of added memory
//-----------------------------------------------------
template <typename T>
int Stack<T>::OKCreate()
{
    if(capacity <= 0)
    {
        printf("ERR_CAP");
        return ERR_CAP;
    }
    else if(size < 0)
    {
        printf("ERR_SIZE");
        return ERR_SIZE;
    }
    else if(size > capacity)
    {
        printf("OVER_FLOW");
        return OVER_FLOW;
    }
    #ifndef UNSAFE
    else if(CANARY_1 != CANARYBEGIN1 || CANARY_2 != CANARYBEGIN2)
    {
        printf("ERR_CANARY");
        return ERR_CANARY;
    }
    else if(hash != Hash())
    {
        printf("ERR_HASH");
        return ERR_HASH;
    }
    #endif // UNSAFE
    else if(stack == NULL)
    {
        printf("ERR_PTR");
        return ERR_PTR;
    }
    else
        return ALL_GOOD;
}

template <typename T>
int Stack<T>::OKPush()
{
    if(capacity <= 0)
    {
        printf("ERR_CAP");
        return ERR_CAP;
    }
    else if(size < 0)
    {
        printf("ERR_SIZE");
        return ERR_SIZE;
    }
    else if(size > capacity)
    {
        printf("OVER_FLOW");
        return OVER_FLOW;
    }
    #ifndef UNSAFE
    else if(CANARY_1 != CANARYBEGIN1 || CANARY_2 != CANARYBEGIN2)
    {
        printf("ERR_CANARY");
        return ERR_CANARY;
    }
    else if(hash != Hash())
    {
        printf("ERR_HASH");
        return ERR_HASH;
    }
    #endif // UNSAFE
    else if(stack == NULL)
    {
        printf("ERR_PTR");
        return ERR_PTR;
    }
    else if(size == capacity)
        return PlusMemory(stack);
    else
        return ALL_GOOD;
}

template <typename T>
int Stack<T>::OKPop()
{
    if(capacity <= 0)
    {
        printf("ERR_CAP");
        return ERR_CAP;
    }
    else if(size < 0)
    {
        printf("ERR_SIZE");
        return ERR_SIZE;
    }
    else if(size > capacity)
    {
        printf("OVER_FLOW");
        return OVER_FLOW;
    }
    #ifndef UNSAFE
    else if(CANARY_1 != CANARYBEGIN1 || CANARY_2 != CANARYBEGIN2)
    {
        printf("ERR_CANARY");
        return ERR_CANARY;
    }
    else if(hash != Hash())
    {
        printf("ERR_HASH");
        return ERR_HASH;
    }
    #endif // UNSAFE
    else if(stack == NULL)
    {
        printf("ERR_PTR");
        return ERR_PTR;
    }
    else if(size == 0)
    {
        printf("EMPTY");
        return EMPTY;
    }
    else
        return ALL_GOOD;
}

template <typename T>
int Stack<T>::OKDestroy()
{
    if(stack == NULL)
    {
        printf("ERR_PTR");
        return ERR_PTR;
    }
    else
        return ALL_GOOD;
}

template <typename T>
int Stack<T>::OKSize()
{
    if(size < 0)
    {
        printf("ERR_SIZE");
        return ERR_SIZE;
    }
    else
        return ALL_GOOD;
}
