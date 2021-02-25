#include<iostream>
#include<map>
#include<unordered_map>
#include<list>
#include<cstring>
#include<list>


class LinkedList
{
    private:
        typedef struct node{
            int val = 0;
            node* next = nullptr;
        }*nodePtr;

        node* head;
        node* currentAddr;
        node* tempNode;


    public:
        int linkSize;
    /*
        LinkedList();
        void addNodeItem(int value);
        void removeNodeItem(int nodeIndex);
        void getItemData(int index);
    */


    LinkedList()
    {
        head = nullptr;
        currentAddr = nullptr;
        tempNode = nullptr;
        linkSize = 0;
    }

    void addNodeItem(int value)
    {   

       nodePtr newNode = new node;
       newNode->next = nullptr;
       newNode->val = value;
       if(head != nullptr)
       {
           currentAddr = head;
           while(currentAddr->next != nullptr)
           {
               currentAddr = currentAddr->next;
           }
           currentAddr->next = newNode;
       }
       else
       {
           head = newNode;
       }
       linkSize += 1;
    }



    void deleteNode(int value)
    {
        nodePtr deltPtr = nullptr; //this will point to address which we want to remove from the linked list
        currentAddr = head;
        tempNode = head;
        while(currentAddr != nullptr)
        {
            if(currentAddr->val == value)
            {
                break; // aqaa
            }
            tempNode = currentAddr;
            currentAddr = currentAddr->next;
        }

        if(currentAddr == nullptr)
        {
            std::cout << "data not in list" << std::endl;
        }
        else
        {
            deltPtr = currentAddr;
            currentAddr = currentAddr->next;
            tempNode->next = currentAddr;
            delete deltPtr;
            linkSize--;
        }
        
    }


    void printList()
    {
        currentAddr = head;
        while(currentAddr != nullptr)
        {
            std::cout<< currentAddr->val << std::endl;
            currentAddr = currentAddr->next;
        }
    }



    int size()
    {
        return linkSize;
    }


    int getByIndex(int index)
    {
        currentAddr = head;
        for(int i = 0; i < index; i++)
        {
            currentAddr = currentAddr->next;
        }
        return currentAddr->val;
    }


};







int main(){




   LinkedList gela;
   gela.addNodeItem(1);
   gela.addNodeItem(32);
   gela.addNodeItem(5);
   gela.printList();
   gela.deleteNode(32);
   gela.printList();

   std::cout << gela.getByIndex(1) << std::endl;

 

   return 1;


}