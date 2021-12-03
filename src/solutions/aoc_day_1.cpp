#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <numeric>

#include "aoc_day_1.h"
#include "file_utils.h"

using namespace std;

AocDay1::AocDay1():AocDay(1)
{
}

AocDay1::~AocDay1()
{
}

vector<long> AocDay1::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<long> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        long l;
        string to_convert = *iter;
        l = strtol(to_convert.c_str(), NULL, 10);
        data.push_back(l);
    }
    return data;
}

string AocDay1::part1(string filename, vector<string> extra_args)
{
    vector<long> data = read_input(filename);
    long pos_diff_sum = 0;
    long last = data[0];
    for (vector<long>::iterator iter = std::next(data.begin()); iter != data.end(); ++iter)
    {
        if (last < *iter) {
            pos_diff_sum += 1;
        }
        last = *iter;
    }
    ostringstream out;
    out << pos_diff_sum;
    return out.str();
}

string AocDay1::part2(string filename, vector<string> extra_args)
{
    vector<long> data = read_input(filename);
    int window_size = 3;
    long pos_diff_sum = 0;
    long last = data[0];
    int vect_length = data.size(); 

    // Calculate the initial window sum
    long last_window_sum = accumulate(data.begin(), data.begin()+window_size, 0);

    // Calcuate the window sum, compare, and add up pos_diff window sums
    for (int iter = 1; iter<vect_length; iter++)
    {
        long window_sum = accumulate(data.begin()+ int(iter), data.begin() + int(iter + window_size), 0);
        if (last_window_sum < window_sum) {
            pos_diff_sum += 1;
        }
        last_window_sum = window_sum;
    }
    ostringstream out;
    out << pos_diff_sum;
    return out.str();
}
