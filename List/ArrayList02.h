class ArrayList 
{
private:
    int size;      // List 的大小.
    double *data;  // 存放数据的内存区域.
public:
    void init(int _maxSize); // 初始化 List, 最大容量为 maxSize.
    void insert(double _val, int _pos); // 在指定位置插入一个元素.
    void printList();  // 列出表内全部元素.
};  