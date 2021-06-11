// Homework 3 - Tanner Koza

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <math.h>

using namespace std;

void propagate(string, string); // function prototypes
void normalize(double *);
int file_size(string);

int main()
{
    string input_file = "hw3_data.txt"; // declare file names
    string output_file = "output.txt";
    propagate(input_file, output_file); // call instance of propagate
}

void propagate(string input_file, string output_file)
{
    int in_size = file_size(input_file); // number of lines in input file
    double gyro_data[in_size][3];        // gyroscope array definition - 3 columns x, y, z

    double x_acc, y_acc, z_acc; // imu data definition
    double x_gyro, y_gyro, z_gyro;
    double x_mag, y_mag, z_mag;

    ifstream infile(input_file); // make class instance of read and write while opening respective files
    ofstream outfile(output_file);

    int q_size = in_size + 1;             // number of lines in output file
    double tstep = 1.0 / 128.0;           // timestep
    double q[q_size][4] = {{1, 0, 0, 0}}; // quanternion array definition and first row

    int i = 0; // while loop index

    if (infile.is_open() && outfile.is_open())
    {
        while (infile >> x_acc >> y_acc >> z_acc >> x_gyro >> y_gyro >> z_gyro >> x_mag >> y_mag >> z_mag) // passes input file values to corresponding variables
        {
            gyro_data[i][0] = x_gyro; // gyro_data population
            gyro_data[i][1] = y_gyro;
            gyro_data[i][2] = z_gyro;

            // quarternion calcultaions using Euler integration
            q[i + 1][0] = (q[i][0] + (q[i][1] * -0.5 * gyro_data[i][0] * tstep) + (q[i][2] * -0.5 * gyro_data[i][1] * tstep) + (q[i][3] * -0.5 * gyro_data[i][2] * tstep));
            q[i + 1][1] = ((q[i][0] * 0.5 * gyro_data[i][0] * tstep) + q[i][1] + (q[i][2] * 0.5 * gyro_data[i][2] * tstep) + (q[i][3] * -0.5 * gyro_data[i][1] * tstep));
            q[i + 1][2] = ((q[i][0] * 0.5 * gyro_data[i][1] * tstep) + (q[i][1] * -0.5 * gyro_data[i][2] * tstep) + q[i][2] + (q[i][3] * 0.5 * gyro_data[i][0] * tstep));
            q[i + 1][3] = ((q[i][0] * 0.5 * gyro_data[i][2] * tstep) + (q[i][1] * 0.5 * gyro_data[i][1] * tstep) + (q[i][2] * -0.5 * gyro_data[i][0] * tstep) + q[i][3]);

            double *row_ptr = q[i + 1]; // create pointer for current array row

            normalize(row_ptr); // pass pointer to normalize function

            outfile << q[i][0] << "\t"; // write table delimited data to output
            outfile << q[i][1] << "\t";
            outfile << q[i][2] << "\t";
            outfile << q[i][3] << endl;

            i++;
        }
        infile.close();
        outfile.close();
    }
}

void normalize(double *ptr)
{
    double temp;
    double mag;

    for (int i = 0; i < 4; i++)
    {
        temp += pow(*(ptr + i), 2); // add squares of 4 column elements together
    }

    mag = sqrt(temp); // find magnitude

    for (int i = 0; i < 4; i++)
    {
        *(ptr + i) = *(ptr + i) / mag; // divide the current contents by the mag and resave
    }
}

int file_size(string file)
{
    ifstream input_file(file);

    char c;
    int numchars = 0, numsize = 0;

    input_file.get(c); // gets first character from file

    while (input_file)
    {
        while (input_file && c != '\n')
        {
            numchars = numchars + 1;
            input_file.get(c);
        }
        numsize = numsize + 1;
        input_file.get(c);
    }
    return numsize;
}