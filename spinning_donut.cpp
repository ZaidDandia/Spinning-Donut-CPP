
#include <iostream>
#include <math.h>
using namespace std;
#define PI 3.14159

class Donut
{
    /**
     * @brief the private variables include the output array, z-buffer
     * luminance array, R1 (radius), R2 (distance from the y-axis), K1 (stretching factor), K2 (scaling factor).
     */
private:
    char output[100][30];
    float zTemp[100][30];
    char luminance_character[12] = {'.', ',', '-', '~', ':', ';', '=', '!', '*', '#', '$', '@'};
    const float R1, R2;
    const float K1, K2;

    /**
     * @brief the public includes the constructor, destructor, and the set function of donut.
     */
public:
    Donut() : R1(2), R2(4), K1(25), K2(5)
    {
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 30; j++)
            {
                output[i][j] = ' ';
                zTemp[i][j] = 0;
            }
        }
    };
    ~Donut() {}
    void set(float A, float B)
    {
        for (int row = 0; row < 100; row++)
        {
            for (int column = 0; column < 30; column++)
            {
                output[row][column] = ' ';
                zTemp[row][column] = 0;
            }
        }

        for (float theta = 0; theta < 2 * PI; theta += 0.05)
        {
            for (float phi = 0; phi < 2 * PI; phi += 0.01)
            {
                // the x value after rotation
                float x_final = (R2 + R1 * cos(theta)) * (cos(B) * cos(phi) + sin(A) * sin(B) * sin(phi)) - (R1 * sin(theta)) * cos(A) * cos(B);
                // the y value after rotation
                float y_final = (R2 + R1 * cos(theta)) * (sin(B) * cos(phi) - sin(A) * cos(B) * sin(phi)) + (R1 * sin(theta)) * cos(A) * cos(B);
                // the z value after rotation
                float z_final = K2 + cos(A) * (R2 + R1 * cos(theta)) * sin(phi) + (R1 * sin(theta)) * sin(A);
                // z inverse for z-buffer
                float z_inverse = 1 / (z_final);
                // the z and y value after conversion into 2D plane
                int x_prime = 50 + ((K1 * x_final) / (K2 + z_final));
                int y_prime = 15 + ((K1 * 0.6 * y_final) / (K2 + z_final));
                // the luminance is calculated here
                float Luminance = cos(B) * (sin(theta) * sin(A) - sin(phi) * cos(theta) * cos(A)) - sin(phi) * cos(theta) * sin(A) - sin(theta) * cos(A) - cos(phi) * cos(theta) * sin(B);
                // the condition for putting characters into the array
                if (x_prime > 0 && x_prime < 100 && y_prime > 0 && y_prime < 30)
                {
                    // this condition is here so that the z values once plotted are not plotted again
                    if (z_inverse > zTemp[x_prime][y_prime])
                    {
                        zTemp[x_prime][y_prime] = z_inverse;
                        int Luminance_Index = Luminance * 8;
                        output[x_prime][y_prime] = luminance_character[Luminance_Index > 0 ? Luminance_Index : 0];
                    }
                }
            }
        }
        // printing of the array
        for (int column = 0; column < 30; column++)
        {
            for (int row = 0; row < 100; row++)
            {
                cout << output[row][column];
            }
            cout << endl;
        }
    }
};

int main()
{
    // instance (object) of the class Donut is made here
    Donut d;
    float A = 0, B = 0;
    // for infinite rotation
    while (1)
    {
        // function is called here
        d.set(A, B);
        system("CLS");
        A += 0.1;
        B += 0.1;
    }
    return 0;
}
