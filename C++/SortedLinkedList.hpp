//
//  LinkedList.hpp
//  Sorted Linked List
//
//  Created by Joshua Smith on 1/29/16.
//  Copyright © 2016 Joshua Smith. All rights reserved.
//

#ifndef SortedLinkedList_h
#define SortedLinkedList_h

#include <memory>

template <typename T>
struct Node{
    Node(T value){
        this->value = value;
        this->next = nullptr;
        this->prev = nullptr;
    }
    T value;
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;
};

template <typename T>
class SortedLinkedList{
    
public:
    SortedLinkedList(){
        head = nullptr;
        tail = nullptr;
        ltog = false;
    }
    
    SortedLinkedList(T array[],int size){
        insert(array,size);
    }
    
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    
    void insert(T value){
        auto temp = std::make_shared<Node<T>>(value);
        std::shared_ptr<Node<T>> cur = head;
        
        if(!head){
            head = temp;
            tail = temp;
        }else{
            if(ltog){
                while(cur){
                    if(cur->value==value){
                        break;
                    }else if(head->value>value){
                        temp->next = head;
                        head->prev = temp;
                        head = temp;
                        break;
                    }else if(!head->next){
                        head->next = temp;
                        temp->prev = head;
                        tail = head->next;
                        break;
                    }else if(!cur->next){
                        cur->next = temp;
                        temp->prev = cur;
                        tail = cur->next;
                        break;
                    }else if(cur->next->value>value){
                        temp->next = cur->next;
                        temp->next->prev = temp;
                        cur->next = temp;
                        temp->prev = cur;
                        break;
                    }
                    cur = cur->next;
                }
            }else{
                while(cur){
                    if(cur->value==value){
                        break;
                    }else if(head->value<value){
                        temp->next = head;
                        head->prev = temp;
                        head = temp;
                        break;
                    }else if(!head->next){
                        head->next = temp;
                        temp->prev = head;
                        tail = head->next;
                        break;
                    }else if(!cur->next){
                        cur->next = temp;
                        temp->prev = cur;
                        tail = cur->next;
                        break;
                    }else if(cur->next->value<value){
                        temp->next = cur->next;
                        temp->next->prev = temp;
                        cur->next = temp;
                        temp->prev = cur;
                        break;
                    }
                    cur = cur->next;
                }
            }
        }
    }
    
    void insert(T array[],int size){
        for(int i=0;i<size;++i){
            insert(array[i]);
        }
    }
    
    void del(T value){
        std::shared_ptr<Node<T>> cur = head;
        if(!head) return;
        if(head->value==value){
            head = head->next;
            head->prev = nullptr;
            return;
        }
        while (cur){
            if(!cur->next)break;
            else if(cur->next->value==value && !cur->next->next){
                cur->next->prev = nullptr;
                cur->next = nullptr;
                tail = cur;
            }else if(cur->next->value==value){
                cur->next = cur->next->next;
                cur->next->prev = cur;
            }
            cur = cur->next;
        }
        
    }
    
    void clear(){
        head = nullptr;
        tail = nullptr;
    }
    
    void reverse(){
        ltog = !ltog;
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
    
    std::string to_string(){
        std::shared_ptr<Node<T>> cur = head;
        std::string list;
        while(cur){
            list=list+std::to_string(cur->value)+' ';
            cur = cur->next;
        }
        return list;
    }
    
private:
    bool ltog;
    
};
template <typename T>
std::ostream & operator<<(std::ostream & os,SortedLinkedList<T> list){
    std::shared_ptr<Node<T>> cur = list.head;
    os << list.to_string();
    return os;
}

#endif /* SortedLinkedList_h */
