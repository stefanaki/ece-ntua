#include <cstdio>

class queue{
public:
  queue();
  bool empty();
  void enqueue(int x);
  int dequeue();
  int peek();

private:
  struct node{
    int data;
    node *next;
  };

  typedef struct node *nodePtr;

  nodePtr front;
  nodePtr rear;
};

queue::queue(){
  front = nullptr;
  rear = nullptr;
}

bool queue::empty(){
  return front == nullptr;
}

void queue::enqueue(int x){
  nodePtr n = new node;

  n->data = x;
  n->next = nullptr;

  if(front == nullptr){
    front = n;
  }else{
    rear->next = n;
  }

  rear = n;

  return;
}

int queue::dequeue(){
  int k = front->data;
  nodePtr n = new node;

  if(front == rear){
    rear = nullptr;
  }

  front = front->next;

  delete n;

  return k;
}

int queue::peek(){
  return front->data;
}

int main(){
  int x, i, j;
  int diff = 0;
  queue posQueue, negQueue;

  while(scanf("%d",&x) == 1){
    if(x > 0){
      posQueue.enqueue(x);
      diff++;
    }else if(x < 0){
      negQueue.enqueue(x);
      diff--;
    }
  }

  if(diff == 0){
    i = j = 0;

    while(!posQueue.empty() && i == j){
      i = posQueue.dequeue();
      j = negQueue.dequeue() * (-1);
    }

    if(i == j){
      printf("yes\n");
    }else{
      printf("no\n");
    }
  }else{
    printf("no\n");
  }

  return 0;
}
