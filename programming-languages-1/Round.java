import java.io.*;
import java.util.*;

/* Round.java */

/* Giorgos Stefanakis */
/* Fragiskos Kondilis */

public class Round {
    public static void main(String args[]) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader(args[0]));
            String line = reader.readLine();
            String[] config = line.split(" ");
            int N = Integer.parseInt(config[0]); // Cities
            int K = Integer.parseInt(config[1]); // Cars
            line = reader.readLine();
            String[] initStateString = line.split(" ");
            int[] initCarState = new int[K];
            for (int i = 0; i < K; i++)
                // Holds the index of the city in which every car is initially
                initCarState[i] = Integer.parseInt(initStateString[i]);
            reader.close();

            Arrays.sort(initCarState);
            int[] moddedInitCarState = new int[K]; // Initial car state sorted and without duplicate values
            int[] carsPerCity = new int[N]; // Holds the number of cars in every city initially

            int j = 0;
            int length;
            for (int i = 0; i < K - 1; ++i) {
                ++carsPerCity[initCarState[i]];
                if (initCarState[i] != initCarState[i + 1])
                    moddedInitCarState[j++] = initCarState[i];
            }

            ++carsPerCity[initCarState[K - 1]];
            moddedInitCarState[j++] = initCarState[K - 1];
            length = j;

            // Algorithm suggested by colleague:
            // For every possible final state - city:
            // Calculate the sum of moves required (sum) and the distance
            // the most remote car has to travel to get to goal city (max).
            // The result should be the city with the least number of moves required.
            // Also, in order for the cars to move alternatively;
            // max <= sum - max + 1

            // moddedInitCarState[maxIndex] contains the first city on the right of the
            // one that has at least one car

            int sum = 0;
            int max = 0;
            int maxIndex = 0;
            int minSum = 0;
            int minCity = 0;

            for (int i = 0; i < K; ++i) {
                if (initCarState[i] != 0) {
                    sum += N - initCarState[i];
                    max = Math.max(max, N - initCarState[i]);
                }
            }

            // Check if zeroth city is valid
            if (max <= sum - max + 1) minSum = sum;

            // Check for the rest cities
            if (moddedInitCarState[0] == 0) maxIndex = 1;

            for (int finalState = 1; finalState < N; ++finalState) {
                sum += K - N * carsPerCity[finalState];
                if (carsPerCity[finalState] == 0) {
                    // In case current city doesn't have any cars, increment max
                    ++max;
                } else {
                    // Repeat algorithm from start when maxIndex reaches the end of moddedInitCarState
                    if (maxIndex == length - 1) maxIndex = 0;
                    // Else, go to the city immediately on the right that has at least one car
                    else ++maxIndex;

                    // If the first city with cars on the left of current city
                    // max is calculated by simply moving cars from the furthest city
                    // to current city
                    if (moddedInitCarState[maxIndex] <= finalState)
                        max = finalState - moddedInitCarState[maxIndex];
                    // Else, we have to account for a whole circle of moves
                    // since the first city on the right of current city
                    // is on the "left" of current city
                    else
                        max = N - moddedInitCarState[maxIndex] + finalState;
                }

                // Check if current state is valid and if it has smaller sum than previous smallest sum
                // (or if the sums are equal and index of current city is smaller than previous best city)
                if (max <= sum - max + 1 && ((sum < minSum) || (sum == minSum && finalState < minCity))) {
                    minSum = sum;
                    minCity = finalState;
                }

            }

            System.out.println(minSum + " " + minCity);
        } catch (IOException e) {
            System.out.println("Exception raised.");
        }
    }
}