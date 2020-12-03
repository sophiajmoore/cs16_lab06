void FindMedian(string file_name, ifstream& in_stream)
{
    in_stream.open(file_name);
    int number, i(0),count(0);
    int array[100];

    // putting the numbers into my array
    while (in_stream >> number)
    {
        array[i] = number;
        i++;
        count++;
    }

        // bubble sort time!
    int temp;
    for (int i = count-1; i >= 0; i--)
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
    if (count % 2 == 0) // count is even
    {
        lower_middle = (count/2) - 1;
        upper_middle = lower_middle + 1;
        median = static_cast<double>(array[lower_middle] + array[upper_middle])/2;
    }
    else // count is odd
    {
        lower_middle = (count-1)/2;
        median = array[lower_middle];
    }

    // putting median data into a file
    ofstream out_stream;
    out_stream.open("median_output.dat", ios::app);
    out_stream << median << endl;
    out_stream.close();


    in_stream.close();
    return;
}


