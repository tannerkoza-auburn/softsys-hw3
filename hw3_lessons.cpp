// // Homework 3 "Spinning Round and Round" - Tanner Koza

// // Include Statemeants for Header Files
// #include <iostream>
// #include <string>
// #include <fstream>

// using namespace std; // allow for easier standard namespace usage

// // Prototypes - References Supporting Functions for int main() use
// double *saveGyro(string);
// int lines(string);

// // Main Function
// int main()
// {
//     string file = "hw3_data.txt";
//     const int size = lines(file);

//     double *x, *y, *z;
//     x, y, z = saveGyro(file, size);

//     double *imu_data[size][3];

//     for (int i = 0; i <= size; i++)
//     {
//         imu_data[i][0] = &x[i];
//         imu_data[i][1] = &y[i];
//         imu_data[i][2] = &z[i];
//     }

//     for (int i = 0; i < 7; i++)
//     {
//         cout << imu_data[i][1] << endl;
//     }
// }

// // Supporting Functions
// double *saveGyro(string file, int size)
// {
//     int i = 0; // creates index for array
//     const int size = lines(file);
//     // Array Definition
//     static double x[size];
//     static double y[size];
//     static double z[size];

//     // IMU Value Definition
//     double x_acc, y_acc, z_acc;
//     double x_gyro, y_gyro, z_gyro;
//     double x_mag, y_mag, z_mag;

//     ifstream input_file(file); // use if stream and assign filename to be read

//     if (input_file.is_open())
//     {
//         while (input_file)
//         {
//             input_file >> x_acc >> y_acc >> z_acc >> x_gyro >> y_gyro >> z_gyro >> x_mag >> y_mag >> z_mag; // passes column values to corresponding variables
//             x[i] = x_gyro;
//             y[i] = y_gyro;
//             z[i] = z_gyro;

//             i++;
//         }
//         input_file.close();
//     }
//     return x, y;
// }

// int lines(string file)
// {
//     ifstream input_file(file);
//     char c;
//     int numchars, numlines;

//     numchars = 0;
//     numlines = 0;
//     input_file.get(c);
//     while (input_file)
//     {
//         while (input_file && c != '\n')
//         {
//             numchars = numchars + 1;
//             input_file.get(c);
//         }
//         numlines = numlines + 1;
//         input_file.get(c);
//     }
//     return numlines;
// }

// // Homework 3 "Spinning Round and Round" - Tanner Koza

// // Include Statemeants for Header Files
// #include <iostream>
// #include <string>
// #include <fstream>

// using namespace std; // allow for easier standard namespace usage

// // Prototypes - References Supporting Functions for int main() use
// double quat_vec(int, double (*)[3]);
// int file_size(string);

// // Main Function
// int main()
// {
//     string in_file = "hw3_data.txt";  // saves filename
//     int numsize = file_size(in_file); // reads line numbers
//     int i = 0;                        // creates index value

//     double gyro_data[numsize][3]; // gyroscope array definition

//     double x_acc, y_acc, z_acc; // IMU data definition
//     double x_gyro, y_gyro, z_gyro;
//     double x_mag, y_mag, z_mag;

//     ifstream input_file(in_file); // use ifstream and assign filename to be read

//     if (input_file.is_open())
//     {
//         while (input_file)
//         {
//             input_file >> x_acc >> y_acc >> z_acc >> x_gyro >> y_gyro >> z_gyro >> x_mag >> y_mag >> z_mag; // passes column values to corresponding variables
//             gyro_data[i][0] = x_gyro;
//             gyro_data[i][1] = y_gyro;
//             gyro_data[i][2] = z_gyro;

//             i++;
//         }
//         input_file.close();
//     }

//     double quat = quat_vec(numsize, gyro_data);
// }

// // Supporting Functions
// double quat_vec(int numsize, double data[][3])
// {
//     int size = numsize + 1;             // number of rows in q array
//     double delta_t = 0.0078;            // time step
//     double q[size][4] = {{1, 0, 0, 0}}; // q array declaration and first row

//     ofstream output_file("output.txt");

//     for (int i = 0; i < size; i++)
//     {
//         q[i + 1][0] = (q[i][0] + (q[i][1] * -0.5 * data[i][0] * delta_t) + (q[i][2] * -0.5 * data[i][1] * delta_t) + (q[i][3] * -0.5 * data[i][2] * delta_t));
//         q[i + 1][1] = ((q[i][0] * 0.5 * data[i][0] * delta_t) + q[i][1] + (q[i][2] * 0.5 * data[i][2] * delta_t) + (q[i][3] * -0.5 * data[i][1] * delta_t));
//         q[i + 1][2] = ((q[i][0] * 0.5 * data[i][1] * delta_t) + (q[i][1] * -0.5 * data[i][2] * delta_t) + q[i][2] + (q[i][3] * 0.5 * data[i][0] * delta_t));
//         q[i + 1][3] = ((q[i][0] * 0.5 * data[i][2] * delta_t) + (q[i][1] * 0.5 * data[i][1] * delta_t) + (q[i][2] * -0.5 * data[i][0] * delta_t) + q[i][3]);
//     }
//     for (int i = 0; i <= size; i++)
//     {
//         output_file << q[i][0] << "\t";
//         output_file << q[i][1] << "\t";
//         output_file << q[i][2] << "\t";
//         output_file << q[i][3] << "\n";
//     }

//     // cout << q[i][3] << "\t" << i << endl;

//     output_file.close();
// }

// // double norm_quat_vec() cout << data[i][0] << "\t" << data[i][1] << "\t" << data[i][2] << endl;

// int file_size(string file)
// {
//     ifstream input_file(file);
//     char c;
//     int numchars, numsize;

//     numchars = 0;
//     numsize = 0;
//     input_file.get(c);
//     while (input_file)
//     {
//         while (input_file && c != '\n')
//         {
//             numchars = numchars + 1;
//             input_file.get(c);
//         }
//         numsize = numsize + 1;
//         input_file.get(c);
//     }
//     return numsize;
// }