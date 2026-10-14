#pragma once
class Node{//树节点，递归删除
public:
    int value=0;
    Node* l=nullptr;
    Node* r=nullptr;
    int height=0;//提供给需要记录高的类使用
    Node(int value,Node* l=nullptr,Node* r=nullptr):value(value),l(l),r(r){
    }
};