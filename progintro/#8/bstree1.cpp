#include <cstdio>
#include <cstdlib>
#include <iostream>

class bstree {
private:
  struct node {
    int data;
    node *left, *right;
  };

  typedef struct node *tree;

  tree rootPtr;

  int heightaux(tree t);
  int searchaux(tree t, int x);
  void inorderaux(tree t);
  void preorderaux(tree t);
  void postorderaux(tree t);

  tree insertaux(tree t, int x) {
    tree n = new node;

    if (t == nullptr) {
      n->data = x;
      n->left = n->right = nullptr;
      return n;
    }

    if (t->data > x) {
      t->left = insertaux(t->left, x);
    } else if (t->data < x) {
      t->right = insertaux(t->right, x);
    }

    return t;
  }

public:
  bstree();
  int height();
  void insert(int x);
  int search(int x);
  int min();
  int max();
  void inorder();
  void preorder();
  void postorder();
};

bstree::bstree() { rootPtr = nullptr; }

int bstree::height() { return heightaux(rootPtr); }

int bstree::heightaux(tree t) {
  int hLeft = 1, hRight = 1;

  if (t == nullptr) {
    return 0;
  } else {
    hLeft += heightaux(t->left);
    hRight += heightaux(t->right);
  }

  if (hLeft >= hRight) {
    return hLeft;
  } else {
    return hRight;
  }
}

void bstree::insert(int x) {
  rootPtr = insertaux(rootPtr, x);
  return;
}

int bstree::search(int x) { return searchaux(rootPtr, x); }

int bstree::searchaux(tree t, int x) {
  int i = 1;

  if (t == nullptr) {
    return 0;
  } else if (t->data == x) {
    return 1;
  } else {
    if (x < t->data) {
      i += searchaux(t->left, x);
    } else {
      i += searchaux(t->right, x);
    }
  }

  if (i == 1) {
    return 0;
  }

  return i;
}

int bstree::min() {
  tree n = rootPtr;

  while (n->left != nullptr) {
    n = n->left;
  }

  return n->data;
}

int bstree::max() {
  tree n = rootPtr;

  while (n->right != nullptr) {
    n = n->right;
  }

  return n->data;
}

void bstree::inorder() {
  inorderaux(rootPtr);
  return;
}

void bstree::inorderaux(tree t) {
  if (t == nullptr) {
    return;
  } else {
    inorderaux(t->left);
    printf("%d ", t->data);
    inorderaux(t->right);
  }
  return;
}

void bstree::preorder() {
  preorderaux(rootPtr);
  return;
}

void bstree::preorderaux(tree t) {
  if (t == nullptr) {
    return;
  } else {
    printf("%d ", t->data);
    preorderaux(t->left);
    preorderaux(t->right);
  }
  return;
}

void bstree::postorder() {
  postorderaux(rootPtr);
  return;
}

void bstree::postorderaux(tree t) {
  if (t == nullptr) {
    return;
  } else {
    postorderaux(t->left);
    postorderaux(t->right);
    printf("%d ", t->data);
  }
  return;
}

int main() {
  int N, M, i, x;
  int *searches;
  bstree myTree;

  scanf("%d", &N);
  for (i = 0; i < N; i++) {
    scanf("%d", &x);
    myTree.insert(x);
  }

  scanf("%d", &M);
  searches = (int *)malloc(sizeof(int) * M);
  for (i = 0; i < M; i++) {
    scanf("%d", &x);
    searches[i] = x;
  }

  printf("%d\n", myTree.height());

  printf("%d %d\n", myTree.min(), myTree.max());

  for (i = 0; i < M; i++) {
    printf("%d", myTree.search(searches[i]));
    if (i != M - 1) {
      printf(" ");
    }
  }
  printf("\n");

  myTree.inorder();
  printf("end\n");

  myTree.preorder();
  printf("end\n");

  myTree.postorder();
  printf("end\n");

  free(searches);

  return 0;
}
