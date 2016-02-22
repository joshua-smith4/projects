//
//  LinkedList.hpp
//  Sorted Linked List
//
//  Created by Joshua Smith on 1/29/16.
//  Copyright © 2016 Joshua Smith. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h

#include <memory>

template <typename T>
class Node{
public:
    Node(T value){
        this->value = value;
        next = nullptr;
        prev = nullptr;
        numEntries = 1;
    }
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;
    void inc_entry() {++numEntries;}
    void acc_entry(int n) {numEntries+=n;}
    void dec_entry() {--numEntries;}
    int getNumEnt(){return numEntries;}
    T value;
private:
    int numEntries;
};

template <typename T>
class LinkedList{
    
public:
    LinkedList(){head = nullptr;tail = nullptr;}
    
    LinkedList(T array[],int size){
        insert(array,size);
    }
    
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    
    std::shared_ptr<Node<T>> search(T value){
        std::shared_ptr<Node<T>> cur = head;
        while(cur){
            if(cur->value==value)return cur;
            cur = cur->next;
        }
        return nullptr;
    }
    
    void insert(T value){
        std::shared_ptr<Node<T>> found = search(value);
        std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>(value);
        if(found){found->inc_entry();return;}
        else{
            if(!head){
                head = temp;
                tail = temp;
            }else{
                tail->next = temp;
                temp->prev = tail;
                tail = temp;
            }
        }
    }
    
    void insert(T array[],int size){
        for(int i=0;i<size;++i){
            insert(array[i]);
        }
    }
        
    void del_single(T value){
        std::shared_ptr<Node<T>> found = search(value);
        if(found){
            if(found->getNumEnt()==1){
                if(found==head && !head->next){
                    head = nullptr;
                    tail = nullptr;
                }else if(found==head){
                    head = head->next;
                    head->prev = nullptr;
                }else if(found==tail){
                    tail = tail->prev;
                    tail->next = nullptr;
                }else{
                    found->prev->next = found->next;
                    found->next->prev = found->prev;
                }
            }else{
                found->dec_entry();
            }
        }
    }
    
    void del_all(T value){
        std::shared_ptr<Node<T>> found = search(value);
        if (found){
            if(found==head && !head->next){
                head = nullptr;
                tail = nullptr;
            }else if(found==head){
                head = head->next;
                head->prev = nullptr;
            }else if(found==tail){
                tail = tail->prev;
                tail->next = nullptr;
            }else{
                found->prev->next = found->next;
                found->next->prev = found->prev;
            }
        }
    }
    
    void clear(){
        head = nullptr;
        tail = nullptr;
    }
    
    std::string to_string(){
        std::shared_ptr<Node<T>> cur = head;
        std::string list;
        while(cur){
            list=list+std::to_string(cur->value)+' ';
            //"["+std::to_string(cur->getNumEnt())+"]"+
            cur = cur->next;
        }
        return list;
    }
    
    void reverse(){
        std::shared_ptr<Node<T>> cur = head;
        if(!head)return;
        if(!head->next)return;
        head = tail;
        tail = cur;
        cur->prev = cur->next;
        cur->next = nullptr;
        while (cur->prev){
            cur->prev->prev = cur->prev->next;
            cur->prev->next = cur;
            cur = cur->prev;
        }
    }


    
};

template <typename T>
std::ostream & operator<<(std::ostream & os, LinkedList<T> list){
    std::shared_ptr<Node<T>> cur = list.head;
    os << list.to_string();
    return os;
}


#endif /* LinkedList_h */
