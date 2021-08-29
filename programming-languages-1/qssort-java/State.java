import java.util.*;

public class State {
  private ArrayDeque<Integer> queue, stack;
  private String moves;

  public State(ArrayDeque<Integer> q, ArrayDeque<Integer> s, String m) {
    queue = new ArrayDeque<Integer>(q);
    stack = new ArrayDeque<Integer>(s);
    moves = new String(m);
  }

  public ArrayDeque<Integer> getQueue() { return queue; }

  public ArrayDeque<Integer> getStack() { return stack; }

  public String getMoves() { return moves; }

  private boolean isQueueSorted() {
    int prev = queue.peek();
    for (int x : queue) {
      if (prev > x) return false;
      prev = x;
    }
    return true;
  }

  public boolean isFinal() {
    return stack.isEmpty() && isQueueSorted();
  }

  public State nextQ() {
    ArrayDeque<Integer> newQueue = queue.clone();
    ArrayDeque<Integer> newStack = stack.clone();
    String newMoves = new String(moves);
    int head = newQueue.remove();
    newStack.add(head);
    newMoves += "Q";
    return new State(newQueue, newStack, newMoves);
  }

  public State nextS() {
    ArrayDeque<Integer> newQueue = queue.clone();
    ArrayDeque<Integer> newStack = stack.clone();
    String newMoves = new String(moves);
    int last = newStack.removeLast();
    newQueue.add(last);
    newMoves += "S";
    return new State(newQueue, newStack, newMoves);
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    State other = (State) o;
    return (queue.toString() + stack.toString()).equals(other.queue.toString() + other.stack.toString());
  }

  @Override
  public int hashCode() {
    retu