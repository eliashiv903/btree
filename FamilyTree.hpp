#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;


namespace family {

    struct node {
        string type;
        string name;
        node *left;
        node *right;
        node *parent;
    };

    class Tree {
        node *root;
        string me;
    public:
        Tree(string name) {
            me = name;
            root = new node;
            root->name = name;
            root->left = NULL;
            root->right = NULL;
        }


        void remove(string name);

        string find(string relation);

        string relation(string name);

        Tree &addFather(string sun, string father);

        Tree &addMother(string sun, string mother);

        node *search(string key, node *leaf);

        node *search2(string key, node *leaf);

        void display();

        void postorder_print();

        void preorder_print();

    private:
        void inorder_print(node *leaf);

        void postorder_print(node *leaf);

        void preorder_print(node *leaf);

    };
}