template <typename T>
class Stack
{
    private:
        #ifndef UNSAFE
        long long CANARY_1;
        #endif // UNSAFE

        size_t size;
        size_t capacity;
        T *stack;

        #ifndef UNSAFE
        long long hash;
        long long CANARYBEGIN1 = RandomBig();
        long long CANARYBEGIN2 = RandomBig();
        long long Hash();
        #endif // UNSAFE

        int PlusMemory(T* ptr);

        #ifndef UNSAFE
        long long CANARY_2;
        #endif // UNSAFE
    public:
        bool Create(size_t cap);
        bool Push(T data);
        bool Pop(T *data);
        bool Destroy();
        bool Get(T *data);
        bool Clear();
        bool Size(T *number);
        void Print(T data);
        bool Dump();

        int OKCreate();
        int OKPush();
        int OKPop();
        int OKDestroy();
        int OKSize();
};
