import java.util.*;

/* A class that implements a solver that explores the search space
 * using breadth-first search (BFS).  This leads to a solution that
 * is optimal in the number of moves from the initial to the final
 * state.
 */
public class Solver {
  public State solve (State initial) {
    Set<String> seen = new HashSet<>();
    Queue<State> remaining = new ArrayDeque<>();
    String moves = initial.getMoves();

    if (initial.isFinal()) return null;

    remaining.add(initial);

    while (!remaining.isEmpty()) {
      State s = remaining.remove();
      String pair = new String(s.getQueue().toString() + s.getStack().toString());

      if (!seen.contains(pair)) {
        if (!s.getQueue().isEmpty()) {
          State next_q = s.nextQ();
          remaining.add(next_q);
        }

        if (!s.getStack().isEmpty()) {
          State next_s = s.nextS();
          if (next_s.isFinal()) return next_s;
          remaining.add(next_s);
        }

        seen.add(pair);
      }

      if (s.isFinal()) return s;

      if (!s.getQueue().isEmpty()) {
        State next_q = s.nextQ();
        if (!seen.contains(next_q.getQueue().toString() + next_q.getStack().toString())) {
          remaining.add(next_q);
          seen.add(next_q.getQueue().toString() + next_q.getStack().toString());
        }

      }
      if (!s.getStack().isEmpty()) {
        State next_s = s.nextS();
        if (next_s.isFinal()) return next_s;
        if (!seen.contains(next_s.getQueue().toString() + next_s.getStack().toString())) {
          remaining.add(next_s);
          seen.add(next_s.getQueue().toString() + next_s.getStack().toString());
        }
      }

    }
    return null;
  }
}