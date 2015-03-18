//
//  main.cpp
//  Kth Ancestor
//
//  Created by Yunfan Jin on 3/16/15.
//  Copyright (c) 2015 yunfan.jin. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <set>
#include <utility>
#include <cassert>
#include <fstream>
using namespace std;

class Tree{
    unordered_map<long, pair<long, set<long>>> tree;
    
public:
    Tree(){
        tree[0] = make_pair(-1, set<long>());
    }
    
    void addNode(long child, long parent){
        auto search = tree.find(parent);
        if (search != tree.end()) {
            search->second.second.insert(child);
        }else{
            tree[parent] = make_pair(-1, set<long>({child}));
        }
    }
    
    void complete(long node){
        for (long child: tree[node].second){
            auto search = tree.find(child);
            if (search != tree.end()) {
                search->second.first = node;
                complete(child);
            }else{
                tree[child] = make_pair(node, set<long>());
            }
        }
    }
    
    void addLeaf(long parent, long child){
        assert(tree.find(child) == tree.end());
        tree[child] = make_pair(parent, set<long>());
        tree[parent].second.insert(child);
    }
    void removeLeaf(long leaf){
        assert(tree[leaf].second.empty());
        long parent = tree[leaf].first;
        tree[parent].second.erase(leaf);
        tree.erase(leaf);
    }
    
    long query(long node, long order){
        if (tree.find(node) == tree.end()) {
            return 0;
        }
        for (int i=0; i<order; i++) {
            node = tree[node].first;
            if (node == 0) {
                return 0;
            }
        }
        return node;
    }
};


int main(int argc, const char * argv[]) {
    
    int T;
    ifstream input("testcase.txt");
    input >> T;
    for (int i=0; i<T; i++) {
        Tree tree;
        long P, X, Y;
        input >> P;
        for (long j=0; j<P; j++) {
            input >> X >> Y;
            tree.addNode(X, Y);
        }
        tree.complete(0);
        long Q, K;
        int command;
        input >> Q;
        for (long j=0; j<Q; j++) {
            input >> command;
            if (command == 0) {
                input >> Y >> X;
                tree.addLeaf(Y, X);
            }else if (command == 1){
                input >> X;
                tree.removeLeaf(X);
            }else if (command == 2){
                input >> X >> K;
                cout << tree.query(X, K) << endl;
            }
        }
    }
    
    return 0;
}
