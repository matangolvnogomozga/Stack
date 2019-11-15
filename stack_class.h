template <typename T>
class Stack
{
    private:
        long long CANARY_1;
        size_t size;
        size_t capacity;
        T *stack;
        long hash;
        long long CANARY_2;

        long Hash();
        int PlusMemory(T* ptr);
    public:
        bool Create(size_t cap);
        bool Push(T data);
        bool Pop(T *data);
        bool Destroy();
        bool Get(T *data);
        bool Clear();
        size_t Size(T *number);
        void Print(T data);
        bool Dump();

        int OKCreate();
        int OKPush();
        int OKPop();
        int OKDestroy();
        int OKSize();
        int OKDump();
};
