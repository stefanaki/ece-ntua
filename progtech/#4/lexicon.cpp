#include <iostream>
#include <string>

using namespace std;

class lexicon {
protected:
  struct node {
    string word;
    int freq;
    node *left, *right;

    node(const string &s) {
      word = s;
      freq = 1;
      left = right = nullptr;
    }
  };

  node *root;

  static void purge(node *r) {
    if (r != nullptr) {
      purge(r->left);
      purge(r->right);
      delete r;
    }
  }

  static node *insert(node *r, const string &s) {
    if (r == nullptr)
      return new node(s);
    if (r->word == s)
      r->freq++;
    else if (s < r->word)
      r->left = insert(r->left, s);
    else
      r->right = insert(r->right, s);
    return r;
  }

  static node *search(node *r, const string &s) {
    if (r == nullptr)
      return nullptr;
    if (r->word == s)
      return r;
    if (s < r->word)
      return search(r->left, s);
    else
      return search(r->right, s);
  }

  static int depth(node *r, const string &s) {
    if (search(r, s) == nullptr)
      return 0;
    if (s == r->word)
      return 1;
    else if (s < r->word)
      return 1 + depth(r->left, s);
    else
      return 1 + depth(r->right, s);
  }

  static node *remove(node *r, const string &s) {
    if (r == nullptr)
      return nullptr;
    else if (s < r->word)
      r->left = remove(r->left, s);
    else if (s > r->word)
      r->right = remove(r->right, s);
    else {                                             // word found
      if (r->left == nullptr && r->right == nullptr) { // node has no children
        delete r;
        r = nullptr;
      } else if (r->left == nullptr) { // node has only right child
        node *temp = r;
        r = r->right;
        delete temp;
      } else if (r->right == nullptr) { // node has only left child
        node *temp = r;
        r = r->left;
        delete temp;
      } else { // node has two children
        node *temp = findMax(r->left);
        r->word = temp->word;
        r->freq = temp->freq;
        r->left = remove(r->left, temp->word);
      }
    }
    return r;
  }

  static node *findMax(node *r) {
    node *p = r;
    while (p->right != nullptr)
      p = p->right;
    return p;
  }

  static ostream &inorder(ostream &out, node *r) {
    if (r == nullptr)
      return out;
    inorder(out, r->left);
    out << r->word << " " << r->freq << endl;
    inorder(out, r->right);
    return out;
  }

public:
  lexicon() { root = nullptr; }
  ~lexicon() { purge(root); }

  void insert(const string &s) { root = insert(root, s); }

  int lookup(const string &s) {
    node *p = search(root, s);
    if (p == nullptr)
      return 0;
    return p->freq;
  }

  int depth(const string &s) { return depth(root, s); }

  void replace(const string &s1, const string &s2) {
    node *p = search(root, s1);
    if (p == nullptr)
      return;
    int k = p->freq;
    root = remove(root, s1);
    node *s = search(root, s2);
    if (s == nullptr) {
      root = insert(root, s2);
      (search(root, s2))->freq = k;
    } else
      s->freq += k;
  }

  friend ostream &operator<<(ostream &out, const lexicon &l) {
    return l.inorder(out, l.root);
  }
};
