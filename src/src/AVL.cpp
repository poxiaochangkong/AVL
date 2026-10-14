#include "../include/AVL.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

Node* AVL::rotate(Node*a ,Node* b,int l){
    Node* sub = (l == 1 ? b->l : b->r);

    if (l == 1) {
        a->r = sub;
        b->l = a;
    } else {
        a->l = sub;
        b->r = a;
    }
    //height自动处理空节点
    a->height = std::max(height(a->l),
                         height(a->r)) + 1;

    b->height = std::max(height(b->l),
                         height(b->r)) + 1;

    return b;
}

Node* AVL::rebalance(Node* p){//计算平衡因子并调用rotate


    if (!p) return nullptr;

    int lh = height(p->l);
    int rh = height(p->r);

    p->height = std::max(lh, rh) + 1;

    int bf = lh - rh;

    if (bf > 1) { // 左侧过高
        if (height(p->l->l) < height(p->l->r)) {
            // LR：先对左子节点左旋
            p->l = rotate(p->l, p->l->r, 1);
        }
        // LL 或 LR：对当前节点右旋
        return rotate(p, p->l, 0);
    }

    if (bf < -1) { // 右侧过高
        if (height(p->r->r) < height(p->r->l)) {
            // RL：先对右子节点右旋
            p->r = rotate(p->r, p->r->l, 0);
        }
        // RR 或 RL：对当前节点左旋
        return rotate(p, p->r, 1);
    }

    return p;
}

Node* AVL::insert(Node* p,int v){//recursive
    if(!p){
        p=new Node(v);
        if(!root)
            root=p;
        p->height=1;
        return p;
    }
    if(p->value==v){
        std::cout<<v<<" is exsited, do not insert again"<<std::endl;
    }else if(v<p->value){
        p->l=insert(p->l,v);
    }else{
        p->r=insert(p->r,v);    
    }
    //旋转
    return rebalance(p);
}
bool AVL::find(int v){
    Node* p=root;
    while(p){
        if(v<p->value)
            p=p->l;
        else if(v>p->value)
            p=p->r;
        else
            return true;
    }
    return false;
}
int AVL::erase(){
    Node* AVL::erase(Node* p, int v) {
    if (!p)
        return nullptr;

    if (v < p->value) {
        p->l = erase(p->l, v);
    }
    else if (v > p->value) {
        p->r = erase(p->r, v);
    }
    else {
        // 找到待删除节点

        // 0 个或 1 个子节点
        if (!p->l || !p->r) {
            Node* child = p->l ? p->l : p->r;
            delete p;
            return child;
        }

        // 2 个子节点：寻找中序后继
        Node* succ = p->r;

        while (succ->l)
            succ = succ->l;

        // 用后继节点的值替换当前节点
        p->value = succ->value;

        // 删除后继节点
        p->r = erase(p->r, succ->value);
    }

    // 递归返回时逐层恢复平衡
    return rebalance(p);
}
}

void AVL::showTree(std::ostream& out){
    if(!root){
        out<<"(empty tree)"<<std::endl;
        return;
    }

    //中序遍历分配列号：col = 2 * 序号，使 左子树列 < 父列 < 右子树列
    //levels[d]：第d层的 (列号, 数值字符串)，中序顺序保证层内按列升序
    std::vector<std::vector<std::pair<int, std::string>>> levels;
    std::unordered_map<Node*, int> colOf;
    int nextCol = 0;

    //links[d]：第d层与第d+1层之间的连接行，斜线画在父子列的中点
    std::vector<std::string> links;

    //把字符c写到line的第col列，等价于 line[col] = c：
    //string不能给超过末尾的位置赋值，长度不够时先补空格垫到位，再写入或追加
    auto put = [](std::string& line, int col, char c){
        if((int)line.size() < col)
            line.append(col - line.size(), ' ');//先补空格到第col列
        if((int)line.size() == col)
            line.push_back(c);//line正好长到col，追加
        else
            line[col] = c;//col处已有字符（空格），覆盖
    };
    //在第d层与第d+1层之间的连接行的第col列写一个字符
    //斜线是递归乱序写入的，目标行可能还不存在，用到哪行就先扩到哪行
    auto putLink = [&](int d, int col, char c){
        if((int)links.size() <= d)
            links.resize(d + 1);
        put(links[d], col, c);
    };

    std::function<void(Node*, int)> assign = [&](Node* p, int d){
        if(!p) return;
        assign(p->l, d + 1);
        colOf[p] = nextCol;
        if((int)levels.size() <= d)//中序先走左子树，d可能比当前层数深好几层
            levels.resize(d + 1);
        levels[d].push_back({nextCol, std::to_string(p->value)});
        if(p->l)//左子树已分配完，父子列已知
            putLink(d, (nextCol + colOf[p->l]) / 2, '/');
        nextCol += 2;
        assign(p->r, d + 1);
        if(p->r)
            putLink(d, (colOf[p] + colOf[p->r]) / 2, '\\');
    };
    assign(root, 0);

    for(size_t d = 0; d < levels.size(); d++){
        //节点行：数值以自己的列为中心
        std::string line;
        for(size_t i = 0; i < levels[d].size(); i++){
            int col = levels[d][i].first;
            std::string& s = levels[d][i].second;
            int pad = col - (int)s.size() / 2 - (int)line.size();
            if(pad > 0)
                line.append(pad, ' ');
            line += s;
        }
        out<<line<<"\n";
        if(d + 1 < levels.size())
            out<<links[d]<<"\n";
    }
}