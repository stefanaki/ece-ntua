import java.io.*;
import java.util.*;

public class QSSort {
  // The main function.
  public static void main(String[] args) {
    try {
      ArrayDeque<Integer> initQueue = new ArrayDeque<>();
      ArrayDeque<Integer> initStack = new ArrayDeque<>();
      BufferedReader reader = new BufferedReader(new FileReader(args[0]));
      String line = reader.readLine();
      String [] a = line.split(" ");
      int N = Integer.parseInt(a[0]);
      line = reader.readLine();
      String[] initQueueOfStrings = line.split(" ");
      for (int i = 0; i < N; i++)
        initQueue.add(Integer.parseInt(initQueueOfStrings[i]));
      reader.close();
      Solver solver = new Solver();
      State initial = new State(initQueue, initStack, "");
      State result = solver.solve(initial);
      if (result == null) {
        System.out.println("empty");
      } else {
        System.out.println(result.getMoves());
      }
    } catch (IOException e) {
      System.out.println(e);
    }
  }
}