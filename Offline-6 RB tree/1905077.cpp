#include <iostream>
#include <fstream>
using namespace std;
static int count = 0;

struct Node
{
  int data;
  Node *parent;
  Node *left;
  Node *right;
  int color; // black==0, red==1
};

class RedBlackTree
{
private:
  Node *root;
  Node *NIL;

  int getCountHelper(Node *root, int key)
  {
    int cnt = 0;

    if (root == nullptr)
    {
      return 0;
    }
    else if (root->data < key)
    {
      cnt++;
      cnt += getCountHelper(root->left, key);
      cnt += getCountHelper(root->right, key);
    }
    else
    {
      cnt += getCountHelper(root->left, key);
    }

    return cnt;
  }

  void leftRotate(Node *x)
  {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NIL)
    {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
      this->root = y;
    }
    else if (x == x->parent->left)
    {
      x->parent->left = y;
    }
    else
    {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(Node *x)
  {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NIL)
    {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
      this->root = y;
    }
    else if (x == x->parent->right)
    {
      x->parent->right = y;
    }
    else
    {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  Node *searchTreeHelper(Node *node, int key)
  {
    if (node == nullptr || key == node->data)
    {
      return node;
    }

    if (key < node->data)
    {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }
  Node *minimum(Node *node)
  {
    while (node->left != NIL)
    {
      node = node->left;
    }
    return node;
  }

  void deleteFix(Node *x)
  {
    Node *w;
    while (x != root && x->color == 0)
    {
      if (x == x->parent->left)
      {
        w = x->parent->right;
        if (w->color == 1)
        {
          w->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          w = x->parent->right;
        }

        if (w->left->color == 0 && w->right->color == 0)
        {
          w->color = 1;
          x = x->parent;
        }
        else
        {
          if (w->right->color == 0)
          {
            w->left->color = 0;
            w->color = 1;
            rightRotate(w);
            w = x->parent->right;
          }

          w->color = x->parent->color;
          x->parent->color = 0;
          w->right->color = 0;
          leftRotate(x->parent);
          x = root;
        }
      }
      else
      {
        w = x->parent->left;
        if (w->color == 1)
        {
          w->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          w = x->parent->left;
        }

        if (w->left->color == 0 && w->right->color == 0)
        {
          w->color = 1;
          x = x->parent;
        }
        else
        {
          if (w->left->color == 0)
          {
            w->right->color = 0;
            w->color = 1;
            leftRotate(w);
            w = x->parent->left;
          }

          w->color = x->parent->color;
          x->parent->color = 0;
          w->left->color = 0;
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = 0;
  }

  void rbTransplant(Node *u, Node *v)
  {
    if (u->parent == nullptr)
    {
      root = v;
    }
    else if (u == u->parent->left)
    {
      u->parent->left = v;
    }
    else
    {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void deleteNodeHelper(Node *z, int key)
  {
    Node *x;
    Node *y;

    y = z;
    int y_original_color = y->color;
    if (z->left == NIL)
    {
      x = z->right;
      rbTransplant(z, z->right);
    }
    else if (z->right == NIL)
    {
      x = z->left;
      rbTransplant(z, z->left);
    }
    else
    {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z)
      {
        x->parent = y;
      }
      else
      {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      rbTransplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }

    if (y_original_color == 0)
    {
      deleteFix(x);
    }
  }

  void insertFixUp(Node *k)
  {
    Node *u;
    while (k->parent->color == 1)
    {
      if (k->parent == k->parent->parent->right)
      {
        u = k->parent->parent->left;
        if (u->color == 1)
        {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        }
        else
        {
          if (k == k->parent->left)
          {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      }
      else
      {
        u = k->parent->parent->right;

        if (u->color == 1)
        {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        }
        else
        {
          if (k == k->parent->right)
          {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root)
      {
        break;
      }
    }
    root->color = 0;
  }

public:
  RedBlackTree()
  {
    NIL = new Node;
    NIL->color = 0;
    NIL->left = nullptr;
    NIL->right = nullptr;
    root = NIL;
  }

  bool searchTree(int k)
  {
    Node *np;
    np = searchTreeHelper(this->root, k);
    if (np == nullptr)
    {
      return false;
    }
    else
    {
      return true;
    }
  }

  void insertNode(int key)
  {

    Node *node = new Node;
    node->parent = nullptr;
    node->data = key;
    node->left = NIL;
    node->right = NIL;
    node->color = 1;

    Node *y = nullptr;
    Node *x = this->root;

    while (x != NIL)
    {
      y = x;
      if (node->data < x->data)
      {
        x = x->left;
      }
      else
      {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == nullptr)
    {
      root = node;
    }
    else if (node->data < y->data)
    {
      y->left = node;
    }
    else
    {
      y->right = node;
    }

    if (node->parent == nullptr)
    {
      node->color = 0;
      return;
    }

    if (node->parent->parent == nullptr)
    {
      return;
    }

    insertFixUp(node);
  }

  void deleteNode(int data)
  {
    Node *z = NIL;
    Node *node = root;
    int key = data;
    while (node != NIL)
    {
      if (node->data == key)
      {
        z = node;
      }

      if (node->data <= key)
      {
        node = node->right;
      }
      else
      {
        node = node->left;
      }
    }

    if (z == NIL)
    {
      cout << "Key not found in the tree" << endl;
      return;
    }

    deleteNodeHelper(z, data);
  }

  int getCount(int key)
  {
    int res = getCountHelper(this->root, key);
    return res;
  }
};

int main()
{
  RedBlackTree rbt;

  freopen("mst.txt", "r", stdin);
  int k, e, x;
  bool check;
  ifstream fin("mst.txt");
  fin >> k;
  cout << k << endl;
  while (k--)
  {
    fin >> e >> x;
    if (e == 0)
    {
      check = rbt.searchTree(x);
      if (check)
      {
        rbt.deleteNode(x);
        cout << e << " " << x << " " << 1 << endl;
      }
      else
      {
        cout << e << " " << x << " " << 0 << endl;
      }
    }
    if (e == 1)
    {
      check = rbt.searchTree(x);
      if (!check)
      {
        rbt.insertNode(x);
        cout << e << " " << x << " " << 1 << endl;
      }
      else
      {
        cout << e << " " << x << " " << 0 << endl;
      }
    }
    if (e == 2)
    {
      check = rbt.searchTree(x);
      if (check)
      {
        cout << e << " " << x << " " << 1 << endl;
      }
      else
      {
        cout << e << " " << x << " " << 0 << endl;
      }
    }

    if (e == 3)
    {
      int res = rbt.getCount(x);
      cout << e << " " << x << " " << res << endl;
    }
  }

  fin.close();
}
