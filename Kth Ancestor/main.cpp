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
#include <queue>
#include <cassert>
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
    
    void complete(){
        queue<long> cache;
        cache.push(0);
        while (!cache.empty()) {
            long current = cache.front();
            cache.pop();
            for (long child: tree[current].second){
                auto search = tree.find(child);
                if (search != tree.end()) {
                    search->second.first = current;
                    cache.push(child);
                }else{
                    tree[child] = make_pair(current, set<long>());
                }
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
    cin >> T;
    for (int i=0; i<T; i++) {
        Tree tree;
        long P, X, Y;
        cin >> P;
        for (long j=0; j<P; j++) {
            cin >> X >> Y;
            tree.addNode(X, Y);
        }
        tree.complete();
        long Q, K;
        int command;
        cin >> Q;
        for (long j=0; j<Q; j++) {
            cin >> command;
            if (command == 0) {
                cin >> Y >> X;
                tree.addLeaf(Y, X);
            }else if (command == 1){
                cin >> X;
                tree.removeLeaf(X);
            }else if (command == 2){
                cin >> X >> K;
                cout << tree.query(X, K) << endl;
            }
        }
    }
    
    return 0;
}
