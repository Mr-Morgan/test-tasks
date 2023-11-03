#include <iostream>
#include <queue>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v = 0, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(v), left(l), right(r) {}
};// TreeNode

TreeNode* createTreeNode(int N) {
    std::queue<TreeNode*> tree;
    TreeNode* root;
    for (int i = 0; i < N; i++) {
        TreeNode* node = new TreeNode(i+1);
        if (!tree.empty()) {
            if (!tree.front()->left) tree.front()->left = node;
            else {
                tree.front()->right = node;
                tree.pop();
            }// if()
            } else root = node;
        tree.push(node);
    }// for()
    return root;
}// TreeNode* createTreeNode()

std::ostream & printTreeNodeLVR(std::ostream &ost, TreeNode* root) {
    if (root->left) printTreeNodeLVR(ost, root->left);
    ost << root->val << " ";
    if (root->right) printTreeNodeLVR(ost, root->right);
    return ost;
}// void printTreeNode()

void findParent(TreeNode* root, TreeNode* &parent, bool &is_left, int val_child, bool &is_find) {
    if (root->val == val_child) {
        parent = nullptr;
        is_find = true;
    }// if()

    if (!is_find) {
        if(root->left) {
            if (root->left->val == val_child) {
                is_left = true;
                is_find = true;
                parent = root;
                return;
            } else findParent(root->left, parent, is_left, val_child, is_find);
        }// if()
        if(root->right) {
            if (root->right->val == val_child) {
                is_left = false;
                is_find = true;
                parent = root;
                return;
            } else findParent(root->right, parent, is_left, val_child, is_find);
        }// if()
        }// if()
    return;
}// TreeNode* findParent()

void swapNode(TreeNode* parent, bool child_is_left) {
    TreeNode* v = (child_is_left)? parent->left : parent->right;
    TreeNode* tmp = (child_is_left)? parent->right : parent->left;
    if (child_is_left) {
        parent->right = v->right;
        v->right = tmp;
    } else {
        parent->left = v->left;
        v->left = tmp;
    }// if()
    std::swap(parent->val,v->val);
}// void swapNode()

void swapNode(TreeNode* root, int val_swap_node) {
    // найти узел со значением val_swap_node и сохранить его родителя возвращает родителя и устанавлевает флаг
    // если родителя нет, значит возвращаем nullptr
    // определить ребенок левый или правый (bool flag)
    bool is_left {false}, find{false};
    TreeNode* parent = nullptr;
    findParent(root, parent, is_left, val_swap_node, find);
    // выбрать механизм свопа левый/правый (возможно сделать обобщенный метод в зависимости от флага)
    if (parent) swapNode(parent, is_left);
}// void swapNode()

int main()
{
    int N, swap_count;
    std::cin >> N >> swap_count;
    TreeNode* root = createTreeNode(N);

    int swap_node;

    for (int i = 0; i < swap_count; i++) {
        std::cin >> swap_node;
        swapNode(root, swap_node);
    }// for ()

    printTreeNodeLVR(std::cout, root);

    return 0;
}// int main()
