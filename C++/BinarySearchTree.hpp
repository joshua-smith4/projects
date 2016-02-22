//  BinarySearchTree.hpp
//  Binary Search Tree
//
//  Created by Joshua Smith on 2/5/16.
//  Copyright © 2016 Joshua Smith. All rights reserved.
//

#ifndef BinarySearchTree_h
#define BinarySearchTree_h

template <typename T>
struct Node
{
    Node(T value)
    {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }
    T value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};

template <typename T>
class BSTree
{
public:
    BSTree()
    {
        root = nullptr;
    }
    std::shared_ptr<Node<T> > root;
    void remove(T value){remove(root,value);}
    void insert(T value){insert(root,value);}
    
    void inOrder(std::function<void(std::shared_ptr<Node<T> >)> f){inOrder(root,f);}
    void preOrder(std::function<void(std::shared_ptr<Node<T> >)> f){preOrder(root,f);}
    void postOrder(std::function<void(std::shared_ptr<Node<T> >)> f){postOrder(root,f);}
    std::shared_ptr<Node<T> > search(T value){return search(root,value);}
    bool find(T value){return find(root,value);}
private:
    
    void remove(std::shared_ptr<Node<T> > & current, T value)
    {
        if(!current) return;
        if(value==current->value){
            if(!current->left && !current->right){
                current = nullptr;
                return;
            }else{
                if(current->right){
                    std::shared_ptr<Node<T> > replacement = current->right;
                    while(replacement->left) replacement = replacement->left;
                    current->value = replacement->value;
                    //std::shared_ptr<Node<T> >& newLoc = replacement;
                    remove(current->right,replacement->value);
                    return;
                }else{
                    std::shared_ptr<Node<T> > replacement = current->left;
                    while(replacement->right){
                        replacement = replacement->right;
                    }
                    current->value = replacement->value;
                    //std::shared_ptr<Node<T> >& newLoc = replacement;
                    remove(current->left,replacement->value);
                    return;
                }
            }
        }else if(value>current->value){
            remove(current->right,value);
        }else{
            remove(current->left,value);
        }
        
    }
    // think about making a tree printout
    
    void insert(std::shared_ptr<Node<T> > & current, T value)
    {
        if(!current){
            current = std::make_shared<Node<T> >(value);
            return;
        }
        if(value==current->value) return;
        if(value<current->value) insert(current->left,value);
        else insert(current->right,value);
    }
    
    void inOrder(std::shared_ptr<Node<T> > current, std::function<void(std::shared_ptr<Node<T> >)> f)
    {
        if(!current) return;
        inOrder(current->left,f);
        f(current);
        inOrder(current->right,f);
    }
    
    void preOrder(std::shared_ptr<Node<T> > current, std::function<void(std::shared_ptr<Node<T> >)> f)
    {
        if(!current) return;
        f(current);
        preOrder(current->left,f);
        preOrder(current->right,f);
    }

    void postOrder(std::shared_ptr<Node<T> > current, std::function<void(std::shared_ptr<Node<T> >)> f)
    {
        if(!current) return;
        postOrder(current->left,f);
        postOrder(current->right,f);
        f(current);
    }
    
    std::shared_ptr<Node<T> > search(std::shared_ptr<Node<T> > current,T value){
        if(!current) return nullptr;
        if(value==current->value) return current;
        if(value>current->value) return search(current->right,value);
        else return search(current->left,value);
    }
    
    bool find(std::shared_ptr<Node<T> > current, T value){
        if(!current) return false;
        if(value==current->value) return true;
        if(value<current->value) return find(current->left,value);
        else return find(current->right,value);
    }

};

void print(std::shared_ptr<Node<char> > location){
    std::cout << location->value << " ";
}


#endif /* BinarySearchTree_h */
