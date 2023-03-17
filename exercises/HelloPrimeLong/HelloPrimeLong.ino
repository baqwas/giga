/**
 * @file HelloPrimeLong.ino
 * @brief To perform CPU intensive calculations using data type long for a specific number of iterations
 * @author armw
 *
 * millis - returns elapsed time, in milliseconds as unsigned long, since the start of the current program
 */


/**
 * this section runs once at startup
 */
void setup() {                          // basic initialization
  Serial.begin(115200);                 // faster speeds may be supported
  Serial.println("GIGA R1 WiFi");       // for documentation purposes
}

/**
 * basic calculation of prime numbers using the sieve of Eratosthenes method
 * @param n the number of primes to be calculated
 *
 * memset - set memory to specified value
 * sizeof - number of bytes used by the parameter; data type: size_t
 *
 * References:
 * https://www.geeksforgeeks.org/c-program-for-sieve-of-eratosthenes/
 * https://www.arduino.cc/reference/en/language/variables/utilities/sizeof/
 */

void SieveOfEratosthenes(long n)
{
    // Create a boolean array "prime[0..n]" and initialize
    // all entries it as true. A value in prime[i] will
    // finally be false if i is Not a prime, else true.
    bool prime[n+1];                    // allocate storage for the flags
    memset(prime, true, sizeof(prime)); // initialize all storage

    for (long p = 2; p*p <= n; p++)    // iterate through range 
    {

      if (prime[p] == true)           // If flag is unchanged, then the index is a prime number
      {
          for (long i = p*2; i <= n; i += p) // all multiples of a prime number cannot be prime numbers
              prime[i] = false;
      }
    }

}

/**
 * this section runs indefinitely
 */
void loop() {                           // repeat the calculations
  unsigned long primes = 256L;
  unsigned long MAX_q = 1000000;        //2147483647;
  unsigned long started = millis();

  for (unsigned long q = 0; q < MAX_q; q++)
  {
    SieveOfEratosthenes(primes);
  }
  
  unsigned long elapsed = millis() - started;
  Serial.print("Elapsed time = ");
  Serial.println(elapsed, DEC);
}
