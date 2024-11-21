#include <iostream>
#include <cstdlib>
#include <chrono> // For time measurement
using namespace std;

// Function to perform modular exponentiation: (base^exp) % mod
long long modularExponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod; // Handle base greater than mod

    while (exp > 0) {
        if (exp % 2 == 1) // If exp is odd, multiply base with result
            result = (result * base) % mod;

        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod; // Square the base
    }

    return result;
}

// Miller test for a given base 'a' and odd integer 'n'
bool millerTest(long long d, long long n) {
    long long a = 2 + rand() % (n - 4); // Random a in range [2, n-2]

    long long x = modularExponentiation(a, d, n); // Compute a^d % n

    if (x == 1 || x == n - 1)
        return true;

    // Keep squaring x while d does not reach n-1
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1) return false;
        if (x == n - 1) return true;
    }

    return false;
}

// Miller-Rabin primality test
bool isPrime(long long n, int k) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    // Find d such that n-1 = d * 2^r
    long long d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    // Perform k tests
    for (int i = 0; i < k; i++) {
        if (!millerTest(d, n))
            return false;
    }

    return true;
}

int main() {
    long long n;
    int k = 5; // Number of iterations, higher value increases accuracy

    cout << "Enter a number to check if it's prime: ";
    cin >> n;

    // Start time measurement
    auto start = chrono::high_resolution_clock::now();

    if (isPrime(n, k))
        cout << n << " is a prime number.\n";
    else
        cout << n << " is not a prime number.\n";

    // End time measurement
    auto end = chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Time taken: " << duration << " microseconds.\n";

    return 0;
}