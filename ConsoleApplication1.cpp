﻿#include <iostream> 
#include <algorithm> //std::max()를 사용하기 위함
/*AVLtree의 node 클래스*/
class Node {
public:
    int key; //node의 키값
    Node* left; //왼쪽 자식node 포인터
    Node* right; //오른쪽 자식node 포인터
    int height; //node 높이

    Node(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};
/*AVLtree의 클래스 정의*/
class AvlTree {
private:


    Node* root; //AVLtree의 루트node 포인터
    /*노드의 height반환*/
    int getHeight(Node* n) {
        if (n == nullptr) return 0;// node가 없으면 0 반환, 존재하면 높이 반환
        return n->height;
    }
    /*노드의 왼쪽과 오른쪽 서브트리의 높이 차이 반환*/
    int getBalanceFactor(Node* n) {
        if (n == nullptr) return 0;//node가 없으면 0 반환, 존재하면 왼쪽과 오른쪽 서브트리의 높이차이 반환
        return getHeight(n->left) - getHeight(n->right);
    }
    /*노드 오른쪽으로 회전*/
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;//회전
        y->left = T2;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;//높이 갱신
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;//회전 후 새로운 루트 반환
    }
    /*노드 왼쪽으로 회전*/
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;//회전
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;//높이 갱신
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;//회전 후 새로운 루트 반환
    }
    /*노드 삽입 함수*/
    Node* insertNode(Node* n, int key) {
        if (n == nullptr) return new Node(key);

        if (key < n->key) {
            n->left = insertNode(n->left, key);//재귀함수
        }
        else if (key > n->key) {
            n->right = insertNode(n->right, key);
        }
        else {
            return n;
        }

        n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));//높이 갱신
        int balance = getBalanceFactor(n);

        if (balance > 1 && key < n->left->key)//한 node의 왼쪽 서브트리의 왼쪽 자식node쪽에 node가 삽입되는 경우
            return rightRotate(n);

        if (balance < -1 && key > n->right->key)//한 node의 오른쪽 서브트리의 오른쪽 자식node쪽에 node가 삽입되는 경우
            return leftRotate(n);

        if (balance > 1 && key > n->left->key) {//한 node의 왼쪽 서브트리의 오른쪽 자식node쪽에 node가 삽입되는 경우
            n->left = leftRotate(n->left);
            return rightRotate(n);
        }

        if (balance < -1 && key < n->right->key) {//한 node의 오른쪽 서브트리의 왼쪽 자식node쪽에 node가 삽입되는 경우
            n->right = rightRotate(n->right);
            return leftRotate(n);
        }

        return n;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

public:
    AvlTree() : root(nullptr) {}

    /*key를 삽입하는 함수*/
    void insert(int key) {
        root = insertNode(root, key);
    }
    /*트리가 비었는지 확인하는 함수*/
    bool empty() const {
        return isEmpty();
    }
};

// 
int main() {
    AvlTree t;
    t.insert(10);
    //t.insert(20);
    //t.insert(5);

    std::cout << "Tree empty? " << (t.empty() ? "Yes" : "No") << std::endl;
    return 0;
}
