// Stats.cpp
// By: Sophia Moore
// Created on: 09/15/20

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double FindMean(double array[], int size);
// Pre-condition: takes an array and its size
// Post-condition: returns the mean of the array's values
double FindMedian(double array[], int size);
// Pre-condition: takes an array and its size
// Post-condition: sorts array by number size and returns the median
double FindStddev(double array[], int size, double mean);
// Pre-condition: takes an array, its size, and the mean of the array's values
// Post-condition: returns the standard deviation of the array's values

int main()
{
    // opening up the stream and file here
    ifstream in_stream;
    string file_name;

    cout << "Enter filename: ";
    cin >> file_name; // no whitespace in a filename so cin is fine

    in_stream.open(file_name);

    // putting contents of file into an array here
    double array[1000], number;
    int size(0), i(0);

    while (in_stream >> number)
    {
        array[i] = number;
        i++;
        size++;
    }

    // making stats have 3 decimal places
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(3);

    // finding and printing out stats
    double mean, median, stddev;
    mean = FindMean(array, size);
    cout << "Mean = " << mean << endl;
    median = FindMedian(array, size);
    cout << "Median = " << median << endl;
    stddev = FindStddev(array, size, mean);
    cout << "Stddev = " << stddev << endl;

    // closing stream
    in_stream.close();
    return 0;
}

double FindMean(double array[], int size)
{
    double sum (0), mean;

    for (int i = 0; i < size; i++)
    {
        sum += array[i];
    }

    mean = sum / size;
    return mean;
}

double FindMedian(double array[], int size)
{
    // bubble sort time!
    double temp;
    for (int i = size-1; i >= 0; i--)
    {
        for (int j = 1; j <= i; j++)
        {
            if (array[j-1] > array[j])
            {
                temp = array[j-1];
                array[j-1] = array[j];
                array[j] = temp;
            }
        }
    }

    // finding median from sorted list
    int lower_middle, upper_middle;
    double median;
    if (size % 2 == 0) // count is even
    {
        lower_middle = (size/2) - 1;
        upper_middle = lower_middle + 1;
        median = (array[lower_middle] + array[upper_middle])/2;
    }
    else // count is odd
    {
        lower_middle = (size-1)/2;
        median = array[lower_middle];
    }

    return median;
}

double FindStddev(double array[], int size, double mean)
{
    double sum(0), quotient, stddev;
    // first adding terms
    for (int i = 0; i < size; i++)
    {
        sum += pow(array[i]-mean,2);
    }
    // dividing sum by n-1
    quotient = sum/(size-1);
    // finally: the quotient to the power of 1/2 to find stddev
    stddev = pow(quotient,0.5);

    return stddev;
}

