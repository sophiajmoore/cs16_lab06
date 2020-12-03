// Rhymes.cpp
// By: Sophia Moore
// Created on: 11/16/20

#include <iostream>
#include <fstream>
#include <string>
#include <array>

using namespace std;

string CleanUp(string the_string, int length);
// Pre-condition: takes a string and its length
// Post-condition: returns a new string with only letters and whitespace
string FindLastWord(string the_string);
// Pre-condition: takes in a string
// Post-condition: returns the last word in the string
string LastTwo(string the_string);
// Pre-condition: takes in a string (a word)
// Post-condition: returns the last two letters of the string
int RhymeCounter(string array[], int array_size);
// Pre-condition: takes in an array of strings and it's size
// Post-condition: returns the number of adjacent rhymes
double RhymeDensity(int rhyme_count, int line_count);
// Pre-condition: takes in the rhyme count and line count
// Post-condition: returns the rhyme density
void Printer(int rhyme_count, double density, int line_count);
// Pre-condition: takes in number of rhymes, rhyme density, and line count
// Post_condition: just prints out results

int main()
{
    // opening up the stream and file here
    ifstream in_stream;
    string file_name;

    cout << "Enter filename:\n";
    cin >> file_name;

    in_stream.open(file_name);
    if (in_stream.fail()) // checking if filename is valid
    {
        cerr << "Input file opening failed.\n";
        exit(1);
    }

    // add characters from file to one string and then cleaning the string
    string the_string;
    char chars;
    int length(0), line_count(0);

    while (in_stream.get(chars))
    {
        the_string += chars;
        if (chars == '\n')
        {
            line_count++;
        }
        length++;
    }

    the_string = CleanUp(the_string, length);

    // add last words into an array
    string last_word_array[1000]; // assuming there are less than 1000 lines
    string the_line = "", last_word = "";
    int start_position(0), newline_position(0), line_length(0), i(0);

    while (i < line_count)
    {
        newline_position = the_string.find('\n', start_position); // finding where line ends
        line_length = newline_position - start_position; // finding length of line
        the_line = the_string.substr(start_position, line_length); // extracting line
        last_word_array[i] = FindLastWord(the_line); // putting last two words into an array

        i++; // moving to next spot in array
        start_position = newline_position+1; // moving to the next line
    } 

    // figuring out stats of rhymes, then printing out
    int rhyme_count = RhymeCounter(last_word_array,i);
    double rhyme_density = RhymeDensity(rhyme_count, line_count);
    Printer(rhyme_count, rhyme_density, line_count);

    // closing stream
    in_stream.close();

    return 0;
}

string CleanUp(string the_string, int length)
{
    // adding only letters and whitespace to a new string
    string new_string;

    for (int i = 0; i < length; i++)
    {
        if ( (isalpha(the_string[i]) != 0) || (the_string[i] == ' ') || (the_string[i] == '\n') )
        {
            new_string += the_string[i];
        }
    }

    return new_string;
}

string FindLastWord(string the_string)
{
    int newline_position, last_space_position, word_length;
    string last_word;

    newline_position = the_string.find('\n');
    last_space_position = the_string.rfind(' ', newline_position);
    word_length = newline_position - last_space_position;

    last_word = the_string.substr(last_space_position+1, word_length); // +1 to not include the space

    return last_word;
}

string LastTwo(string the_string)
{
    string new_string = "";

    for (int i = the_string.length()-2; i <= the_string.length(); i++)
    {
        new_string += the_string[i]; // adding letters to a new string
    }

    return new_string;
}

int RhymeCounter(string array[], int array_size)
{
    int rhyme_count(0);

    for (int i = 0; i < array_size-1; i++) 
    {
        if ( LastTwo(array[i]) == LastTwo(array[i+1]) )
        {
            cout << array[i] << " and " << array[i+1] << endl;
            rhyme_count++;
        }
    }

    return rhyme_count;
}

double RhymeDensity(int rhyme_count, int line_count)
{
    double density;

    density = static_cast<double>(rhyme_count)/static_cast<double>(line_count);
    
    return density;
}

void Printer(int rhyme_count, double density, int line_count)
{
    if (rhyme_count == 0)
    {
        cout << "No rhymes found.\n";
    }
    else if (rhyme_count == 1)
    {
        cout << "There is 1 pair of rhyming words.\n";
    }
    else // there are multiple rhyming words
    {
        cout << "There are " << rhyme_count << " pairs of rhyming words.\n";
    }

    // making stats have 2 decimal places
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    
    if (rhyme_count > 0)
    {
        if (line_count == 1)
        {
            cout << "There is 1 line in this poem, so the rhyme-line density is: " << density << endl;
        }
        else // zero or more than one
        {
            cout << "There are " << line_count << " lines in this poem, so the rhyme-line density is: "
                << density << endl;
        }   
    }

    else // no rhymes
    {
        if (line_count == 1)
        {
            cout << "There is 1 line in this poem.\n";
        }
        else // zero or more than one
        {
            cout << "There are " << line_count << " lines in this poem.\n";
        }
    }

    return;
}

