#include <iostream>
#include "AvlTree.h"
using namespace std;

    // Test program
int main( )
{
    AvlTree<int> t;
    int x = 7;

    t.insert( 3 );
    t.insert( 2 );
    t.insert( 1 ); // 单旋转
    t.insert( 4 );
    t.insert( 5 ); // 双旋转
    t.insert( 6 );
    t.insert( x );
    t.printTree( );
    return 0;
}
