/**
 * @file BinarySearchTree.h
 * @brief 二叉搜索树（BST）接口与结点定义。
 *
 * @tparam Comparable 存储的键（或值）类型。要求支持严格弱序（通常通过 operator< 实现）。
 */

/// 存储 Comparable 类型元素的二叉搜索树。
template <typename Comparable>
class BinarySearchTree
{
public:
    /**
     * @name 构造/析构
     * @{
     */

    /**
     * @brief 构造一棵空树。
     */
    BinarySearchTree( );

    /**
     * @brief 拷贝构造函数。
     * @param rhs 要拷贝的源树。
     * @note 进行深拷贝：为每个结点分配新内存并复制元素。
     */
    BinarySearchTree( const BinarySearchTree & rhs );

    /**
     * @brief 移动构造函数。
     * @param rhs 资源被接管的源树。
     * @post rhs 被置为空树（root == nullptr）。
     */
    BinarySearchTree( BinarySearchTree && rhs );

    /**
     * @brief 析构函数，释放整棵树的所有结点。
     */
    ~BinarySearchTree( );

    /** @} */

    /**
     * @name 只读查询接口
     * @{
     */

    /**
     * @brief 返回最小元素（中序遍历第一个）。
     * @return 指向最小元素的常量引用。
     * @pre 树非空；若树为空，行为未定义（具体取决于实现）。
     */
    const Comparable & findMin( ) const;

    /**
     * @brief 返回最大元素（中序遍历最后一个）。
     * @return 指向最大元素的常量引用。
     * @pre 树非空；若树为空，行为未定义（具体取决于实现）。
     */
    const Comparable & findMax( ) const;

    /**
     * @brief 判断是否包含给定元素。
     * @param x 待查找的元素。
     * @return 若存在等价元素（!(x<y) && !(y<x)）则返回 true，否则返回 false。
     */
    bool contains( const Comparable & x ) const;

    /**
     * @brief 判断树是否为空。
     * @return 为空返回 true。
     */
    bool isEmpty( ) const;

    /**
     * @brief 按中序遍历打印整棵树。
     * @param out 输出流，默认 std::cout。
     */
    void printTree( ostream & out = cout ) const;

    /** @} */

    /**
     * @name 修改接口
     * @{
     */

    /**
     * @brief 清空整棵树并释放内存。
     * @post 调用后变为空树。
     */
    void makeEmpty( );

    /**
     * @brief 插入一个元素（左值版本）。
     * @param x 要插入的元素。
     * @note 若已存在等价元素，典型实现会忽略或覆盖，取决于具体实现细节。
     */
    void insert( const Comparable & x );

    /**
     * @brief 插入一个元素（右值版本）。
     * @param x 要插入的元素，将被移动。
     */
    void insert( Comparable && x );

    /**
     * @brief 删除等价于给定值的元素。
     * @param x 待删除的元素。
     * @return 无；若不存在则无操作。
     */
    void remove( const Comparable & x );

    /**
     * @brief 拷贝赋值。
     * @param rhs 源树。
     * @return 引用自身。
     * @note 进行深拷贝；自赋值需被安全处理。
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs );

    /**
     * @brief 移动赋值。
     * @param rhs 源树，其资源将被接管。
     * @return 引用自身。
     * @post rhs 被置为空树。
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs );

    /** @} */

private:
    /**
     * @brief 内部结点结构。
     *
     * 保存元素与左右孩子指针；不保存父指针。
     */
    struct BinaryNode
    {
        Comparable element;   ///< 结点中存储的元素
        BinaryNode *left;     ///< 左孩子
        BinaryNode *right;    ///< 右孩子

        /**
         * @brief 结点构造函数（拷贝元素）。
         * @param theElement 元素值（左值）。
         * @param lt 左孩子指针。
         * @param rt 右孩子指针。
         */
        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }

        /**
         * @brief 结点构造函数（移动元素）。
         * @param theElement 元素值（右值，将被移动）。
         * @param lt 左孩子指针。
         * @param rt 右孩子指针。
         */
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root; ///< 根结点指针；空树时为 nullptr

    // —— 私有递归实现（被公有接口调用）——

    /**
     * @brief 递归插入（左值）。
     * @param x 待插入元素。
     * @param t 子树根结点的引用（可能被修改）。
     */
    void insert( const Comparable & x, BinaryNode * & t );

    /**
     * @brief 递归插入（右值）。
     * @param x 待插入元素，将被移动。
     * @param t 子树根结点的引用（可能被修改）。
     */
    void insert( Comparable && x, BinaryNode * & t );

    /**
     * @brief 递归删除。
     * @param x 待删除元素。
     * @param t 子树根结点的引用（可能被修改）。
     */
    void remove( const Comparable & x, BinaryNode * & t );

    /**
     * @brief 在给定子树中查找最小结点。
     * @param t 子树根结点。
     * @return 指向最小结点的指针；若 t 为 nullptr，则返回 nullptr。
     */
    BinaryNode * findMin( BinaryNode *t ) const;

    /**
     * @brief 在给定子树中查找最大结点。
     * @param t 子树根结点。
     * @return 指向最大结点的指针；若 t 为 nullptr，则返回 nullptr。
     */
    BinaryNode * findMax( BinaryNode *t ) const;

    /**
     * @brief 递归查找是否包含元素。
     * @param x 目标值。
     * @param t 子树根结点。
     * @return 找到返回 true，否则 false。
     */
    bool contains( const Comparable & x, BinaryNode *t ) const;

    /**
     * @brief 递归清空子树并释放内存。
     * @param t 子树根结点的引用；完成后置为 nullptr。
     */
    void makeEmpty( BinaryNode * & t );

    /**
     * @brief 递归打印（中序）。
     * @param t 子树根结点。
     * @param out 输出流。
     */
    void printTree( BinaryNode *t, ostream & out ) const;

    /**
     * @brief 递归克隆子树（深拷贝）。
     * @param t 子树根结点。
     * @return 新子树的根结点指针。
     */
    BinaryNode * clone( BinaryNode *t ) const;
};