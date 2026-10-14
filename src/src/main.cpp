#include "../include/AVL.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
int main(){
    AVL avl;
    int n;
    int num;
    //最终形态写入文件：相对运行程序时所在的目录，即 根目录/tree/tree.txt
    std::filesystem::create_directories("tree");//目录不存在则创建
    std::ofstream file("tree/tree.txt");
    if(!file){
        std::cerr<<"cannot open tree/tree.txt"<<std::endl;
        return 1;
    }

    cin>>n;
    for(;n>0;n--){
        cin>>num;
        avl.root=avl.insert(avl.root,num);//旋转可能更换根节点，必须接住返回值
        avl.showTree(file);
    }
    
    return 0;
}
