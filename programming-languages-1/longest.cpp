#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

/*
 * longest.cpp
 */

/*
 * Giorgos Stefanakis
 * Fragiskos Kondilis
 */

 // debug by magi coco

/*
 * Το ζητούμενο της άσκησης είναι να βρεθεί ο μέγιστος
 * υποπίνακας του days, έστω a_ij για τον οποίο ισχύει η σχέση:
 * Σ(a_ij) < 0 && abs(Σ(a_ij)) / (N * l) >= 1 =>
 * -Σ(a_ij) / (N * l) >= 1 =>
 * (-Σ(a_ij) - N * l) / l >= 0 =>
 * -Σ(a_ij) - Σ(Ν)) / l >= 0 =>
 * Σ(-a_ij - N) >= 0. όπου Ν το πλήθος των νοσοκομείων
 * και l το μήκος του ζητούμενου υποπίνακα.
 * Ονομάζοντας τον παραπάνω πίνακα -a_ij - N = b_ij, το πρόβλημα
 * ανάγεται στην εύρεση μέγιστου υποπίνακα με άθροισμα στοιχείων
 * μεγαλύτερο ή ίσο του μηδενός. Ο αλγόριθμος που υλοποιήσαμε
 * χρησιμοποιεί prefix sum και binary search για την αποδοτική
 * πολυπλοκότητα O(nlogn).
 * Πηγή: https://www.geeksforgeeks.org/largest-subarray-having-sum-greater-than-k/
 */

using namespace std;

struct node { // Structure that contains the prefix sum
    int sum;  // of the subarray b_[0, index]
    int index;

    node(int s, int i) : sum(s), index(i) {}
};

bool compare(const node &a, const node &b) { // Compare function to sort prefix sum vector
    if (a.sum == b.sum)                      // by ascending sum, or by ascending index in
        return a.index < b.index;            // case of equal sums
    return a.sum < b.sum;
}

int binary_search(const vector<node> &pre_sum, int n, int x) {
    int left = 0, right = n - 1;
    int result = -1;
    int mid;

    while (left <= right) {
        mid = (left + right) / 2;

        if (pre_sum[mid].sum == x) {
            result = mid;
            return result;
        } else if (pre_sum[mid].sum < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int main(int argc, char **argv) {
    int K, N, x, sum, result = 0;
    int i;
    vector<int> days, minInd;
    vector<node> prefix_sums;
    ifstream file;

    file.open(argv[1]);
    if (!file.is_open())
        return 1;

    file >> K >> N;
    if (K == 0 || N == 0) { return 1; }

    for (i = 0; i < K; ++i) {
        file >> x;
        days.push_back(-1 * x);
        days[i] -= N;
    }

    sum = 0;
    for (i = 0; i < K; ++i) {
        sum += days[i];
        prefix_sums.push_back(node(sum, i));
    }

    sort(prefix_sums.begin(), prefix_sums.end(), compare);

    /* minInd[i] is an index in the prefix_sums vector
     * which gives the smallest index with sum less than prefix_sums[i].sum */
    minInd.push_back(prefix_sums[0].index);
    for (i = 1; i < K; ++i)
        minInd.push_back(min(minInd[i - 1], prefix_sums[i].index));

    sum = 0;
    for (i = 0; i < K; ++i) {
        sum += days[i];

        if (sum >= 0)
            result = i + 1;
        else { // If sum < 0  then a value of at most -sum has to be subtracted from it
               // so that it becomes greater or equal to zero. That means we have to
               // find the smallest possible index j that has prefix_sums[j].sum at most -sum.
               // We consider our new candidate subarray to be [j+1, i].
               // j has to be the smallest possible so that our new candidate subarray is the
               // longest possible.
            int temp = binary_search(prefix_sums, K, sum);
            if (temp != -1 && minInd[temp] < i)
                result = max(result, i - minInd[temp]);
        }
    }

    cout << result << endl;
    file.close();
    return 0;
}
