#include "./Node.hpp"
#include <iostream>

class AVL{//repeted value is not allowed;
public:
    Node* root=nullptr;

    AVL(){};

    Node* rotate(Node*a ,Node*b, int l);//将b转到a的位置，l表明b的l,r节点如何处理
    int height(Node* p) {
        return p ? p->height : 0;
    }

    int balanceFactor(Node* p) {
        return height(p->l) - height(p->r);
    }
    
    Node* rebalance(Node* p);//平衡节点p

    Node* insert(Node* p,int v);
    bool find(int v);//是否存在
    int erase();
    void showTree(std::ostream& out = std::cout);//不传参输出到标准输出，传ofstream则输出到文件
};