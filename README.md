# MTU-CS4411-OSHW1
Finding the Maximum Fast!
Well, it may not be that fast. But, this problem is a very interesting exercise.
Everyone knows how to find the maximum of a set of integers. You might do the following:

     max = x[0];
     for (i = 1; i < n; i++)
          if (x[i] > max)
               max = x[i];

This is based on the fact that you have only one CPU and use n - 1 comparisons to find the maximum. Can we do better if more CPUs are available? The answer is certainly a "yes". Here is how.
Let us use a thread to simulate a CPU. Suppose we have n distinct integers x0, x1, ..., xn-1. We first initialize a working array of n entries, say w, to all 1s. This can be done with n threads, each of which writes a 1 into its corresponding entry. More precisely, thread Ti writes 1 into wi. Since each thread (or CPU if you prefer) takes one step to complete its task and since all threads run concurrently, the initialization step only needs one step. After this initialization step, two more steps are required.

Step 2 For each pair of integers xi and xj, we create a thread (or a CPU if you prefer) Tij. This thread compares xi and xj, and writes a 0 into wi if xi < xj. Otherwise, it writes a 0 into wj. Therefore, in this step, we need n(n-1)/2 threads, each of which executes one compare and one write. Why n(n-1)/2 threads rather than n2?

Step 3 This step requires n threads. The i-th thread checks the value of wi. If it is a 0, this thread does nothing. If it is a 1, this threads displays the value of xi because it is the maximum! Here is why. The maximum value is larger than any other numbers. As a result, when it is compared with other values in Step 2, its corresponding entry in array w never receives a zero. Step 3 also requires one step to output the maximum. Thus, if we have n(n-1)/2 threads, it only takes three comparison steps to find the maximum!

Example
Consider the following example. Suppose we have 4 numbers, x0 = 3, x1 = 1, x2 = 7, x3 = 4. Array w is initialized to 1, 1, 1, 1 (i.e., w0 = w1 = w2 = w3 = 1). In Step 2, we need 4×(4-1)/2= 6 threads:
![image](https://user-images.githubusercontent.com/30169115/172193918-bfe13c91-0e68-4a18-b735-555652dbf5ac.png)


After this step, w0, w1 and w3 are set to zero, and w2 is still 1. Therefore, in Step 3, the thread associated with w2 sees a 1 and outputs the value of x2, which is 7. Thus, the maximum is 7.
Input and Output
The input to your program should be taken from command line arguments. Your executable must be named as prog1. The command line looks like the following:

prog1  n  x0 x1 ... xn-1

It starts with the name of your executable prog1, followed by an integer n, followed by that number of distinct integers. You can assume the value of n is in the range of 3 and 10 and all input values are correct so that you do not have to do error checking.
Here is what should be shown by your program:

The values of array w after the initialization step.
The activity performed by thread Tij in Step 2.
The values of array w after Step 2.
The maximum and its location.
Suppose the command line is

     prog1  4  3 1 7 4
         
Then, you program's output should look like the following:

     Number of input values = 4
     Input values         x = 3 1 7 4
     After initialization w = 1 1 1 1
          ..........
     Thread T(1,3) compares x[1] = 1 and x[3] = 4, and writes 0 into w[1]
          ..........
     After Step 2         w = 0 0 1 0
     Maximum                = 7
     Location               = 2

[OriginURL](https://pages.mtu.edu/~shene/FORUM/Taiwan-Forum/ComputerScience/003-OS/PROG/PG1/prog1.html)
