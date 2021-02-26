#include<iostream>



class HashedTable
{
    private:
        static const  int hashSize = 20;
        int *hashTable; //it is now a pointer
    public:
        int length;

    HashedTable()
    {
        hashTable = new int[hashSize]; 
    }

    int hashKey(int key)
    {
        return key % hashSize; // it will always be less than or equal to hashSize - 1
    }

     void addItem(int key, int value)
    {
        int hashedKey = hashKey(key);
        hashTable[hashedKey] = value;
    }   

    
    void removeItem(int key)
    {
        int hashedKey = hashKey(key);
        hashTable[hashedKey] = 0;
    }    

    int findItem(int key)
    {
        return hashTable[hashKey(key)];
    }

    void destroyTable()
    {
        delete[] hashTable;
    }
};


int main()
{


    HashedTable table;
    table.addItem(200,1);
    table.addItem(211,9);
    table.addItem(452,5);

   
    return 0;
}