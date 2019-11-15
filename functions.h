#include<errors.h>
#include<colours.h>
void SetColour(ConsoleColor text, ConsoleColor background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
    return;
}

long long RandomBig()
{
    srand(time(0));
    long long num = rand() % 9 + 1;
    for(int i = 0; i < LEN; ++i)
    {
        num *= 10;
        num += rand() % 10;
    }
    return num;
}

template <typename T>
bool Stack<T>::Create(size_t cap)
{
    CANARY_1 = CANARYBEGIN1;
    CANARY_2 = CANARYBEGIN2;
    size = 0;
    capacity = cap;
    stack = (T *)calloc(cap, sizeof(T));
    hash = Hash();
    if(OKCreate())
        return FAIL;
    return SUCCESS;
}

template <typename T>
long Stack<T>::Hash()
{
    return (size * 2 + CANARY_1 % 67 - CANARY_2 % 23 - capacity);
}

template <typename T>
bool Stack<T>::Push(T data)
{
    assert(isfinite(data));
    if(OKPush())
        return FAIL;
    stack[size++] = data;
    hash = Hash();
    if(OKPush())
        return FAIL;
    return SUCCESS;
}

template <typename T>
bool Stack<T>::Pop(T *data)
{
    assert(data != NULL);
    if(OKPop())
        return FAIL;
    *data = stack[--size];
    hash = Hash();
    if(OKPop())
        return FAIL;
    return SUCCESS;
}

template <typename T>
bool Stack<T>::Get(T *data)
{
    if(OKPop())
        return FAIL;
    *data = stack[size];
    if(OKPop())
        return FAIL;
    return SUCCESS;
}

template <typename T>
bool Stack<T>::Destroy()
{
    if(OKDestroy())
        return FAIL;
    free(stack);
    size = 0;
    capacity = 0;
    hash = Hash();
    return SUCCESS;
}

template <typename T>
bool Stack<T>::Clear()
{
    if(OKCreate())
        return FAIL;
    for(int i = size - 1; i >= 0; --i)
        stack[i] = 0;
    size = 0;
    hash = Hash();
    if(OKCreate())
        return FAIL;
    return SUCCESS;
}

template <typename T>
size_t Stack<T>::Size(T *number)
{
    if(OKSize())
        return FAIL;
    *number = size;
    if(OKSize())
        return FAIL;
    return SUCCESS;
}

template <typename T>
void Stack<T>::Print(T data)
{
    std::cout << data << std::endl;
}

template <typename T>
bool Stack<T>::Dump()
{
    if(OKCreate())
    {
        printf("FAIL");
        return FAIL;
    }
    SetColour(Cyan, Black);
    printf("\n\t\tDUMP\n");
    SetColour(Green, Black);
    printf("%s", "Pointer of the stack:");
    SetColour(Red, Black);
    printf("\t\t%p\n", stack);
    SetColour(Green, Black);
    printf("%s", "Capacity of the stack:");
    SetColour(Red, Black);
    printf("\t\t%d\n", capacity);
    SetColour(Green, Black);
    printf("%s\t", "Number of elements in stack:");
    SetColour(Red, Black);
    printf("%d\n", size);
    SetColour(Green, Black);
    printf("%s\t", "Hash:");
    SetColour(Red, Black);
    printf("\t\t\t%d\n", hash);
    SetColour(Green, Black);
    printf("%s", "First canary:");
    SetColour(Red, Black);
    printf("\t\t\t%d\n", CANARY_1);
    SetColour(Green, Black);
    printf("%s", "Second canary:");
    SetColour(Red, Black);
    printf("\t\t\t%d\n\n", CANARY_2);

    SetColour(Blue, Black);
    printf("%s\n", "Stack elements");
    for(int i = 0; i < size; ++i)
    {
        SetColour(Green, Black);
        printf("Element number %d is ", i+1);
        SetColour(Yellow, Black);
        Print(stack[i]);
    }
    SetColour(Cyan, Black);
    printf("\n\t\tEND OF DUMP\n");
    if(OKCreate())
    {
        printf("FAIL");
        return FAIL;
    }
    return SUCCESS;
}

template <typename T>
int Stack<T>::PlusMemory(T* ptr)
{
    assert(ptr != NULL);
    realloc(ptr, size*sizeof(T));
    if(ptr == NULL)
    {
        printf("NO_MEM_MORE");
        return NO_MEM_MORE;
    }
    else
        return ALL_GOOD;
}

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
