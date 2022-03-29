#include <iostream>
#include "hashtable.h"

using namespace std;

int main()
{
    HashTable myHashTable(1);
    myHashTable.insert("wow","A half-Turkish delicacy");
    myHashTable.insert("hello","A common greeting");
    myHashTable.insert("colton","A good friend");
    myHashTable.insert("logan","See Mike");
    myHashTable.display();
    myHashTable.remove("ello");
    myHashTable.remove("hello");
    myHashTable.remove("funny hats");
    myHashTable.display();
    myHashTable.insert("logan","Chocolate");
    myHashTable.display();
    return 0;
}
