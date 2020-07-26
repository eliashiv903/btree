#include "FamilyTree.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

namespace family {
    node *Tree::search(string key, node *leaf) {
        if (leaf != NULL) {
            if (key.compare(leaf->name) == 0) {
                return leaf;
            }
            node *b = search(key, leaf->left);
            if (b != NULL)
                return b;
            else
                return search(key, leaf->right);
        } else {
            return NULL;
        }
    }

    node *Tree::search2(string key, node *leaf) {
        if (leaf != NULL) {
            if (relation(leaf->name).compare(key) == 0) {
                return leaf;
            }
            node *b = search2(key, leaf->left);
            if (b != NULL)
                return b;
            else
                return search2(key, leaf->right);
        } else {
            return NULL;
        }
    }


    void Tree::display() {
        inorder_print(root);
        cout << "\n";
    }

    void Tree::inorder_print(node *leaf) {
        if (leaf != NULL) {
            inorder_print(leaf->left);
            cout << leaf->name << ",";
            inorder_print(leaf->right);
        }
    }

    void Tree::postorder_print() {
        postorder_print(root);
        cout << "\n";
    }

    void Tree::postorder_print(node *leaf) {
        if (leaf != NULL) {
            inorder_print(leaf->left);
            inorder_print(leaf->right);
            cout << leaf->name << ",";
        }
    }

    void Tree::preorder_print() {
        preorder_print(root);
        cout << "\n";
    }

    void Tree::preorder_print(node *leaf) {
        if (leaf != NULL) {
            cout << leaf->name << ",";
            inorder_print(leaf->left);
            inorder_print(leaf->right);
        }
    }

    Tree &Tree::addFather(string sun, string father) {
        node *x = new node;
        x->type = "right";
        x->name = father;
        node *y = search(sun, root);
        if (y->right != NULL)
            throw std::out_of_range{"The tree cannot handle the '" + sun + "' relation"};
        y->right = x;
        x->parent = y;
        return *this;
    }

    Tree &Tree::addMother(string sun, string mother) {
        node *x = new node;
        x->type = "left";
        x->name = mother;
        node *y = search(sun, root);
        if (y->left != NULL)
            throw std::out_of_range{"The tree cannot handle the '" + sun + "' relation"};
        y->left = x;
        x->parent = y;
        return *this;
    }

    string Tree::relation(string name) {
        node *b = search(name, root);
        if (b == NULL)
            return "unrelated";
        if (b->name.compare(me) == 0)
            return "me";
        bool type;
        if (b->type.compare("left") == 0)
            type = true;
        else
            type = false;
        int count = 0;
        while (b->name.compare(me) != 0) {
            count++;
            b = b->parent;
        }
        if (type && count == 1)
            return "mother";
        if (type && count == 2)
            return "grandmother";
        if (type && count > 2) {
            string ans = "grandmother";
            while (count > 2) {
                ans = "great-" + ans;
                count--;
            }
            return ans;
        }
        if (!type && count == 1)
            return "father";
        if (!type && count == 2)
            return "grandfather";
        if (!type && count > 2) {
            string ans1 = "grandfather";
            while (count > 2) {
                ans1 = "great-" + ans1;
                count--;
            }
            return ans1;
        }
        return NULL;
    }

    string Tree::find(string relation) {
        node *ans = search2(relation, root);
        if (ans == NULL)
            throw std::out_of_range{"The tree cannot handle the '" + relation + "' relation"};
        return ans->name;
    }

    void Tree::remove(string name) {
        if (name.compare(me) == 0) {
            root = NULL;
            return;
        }
        node *s = search(name, root);
        bool type;
        if (s->type.compare("left") == 0)
            type = true;
        else
            type = false;
        s = s->parent;
        if (type)
            s->left = NULL;
        else
            s->right = NULL;
    }

}