#include <iostream>
#include <math.h>
using namespace std;
#define Pi 3.142



/**
 * @brief class which contains the variables and functions needed to make the donut
 *
 */
class Donut
{
    /**
     * @brief
     * R1 is the radius and R2 is distance from y axis
     * K1 is the stretching factor and K2 is the scaling factor
     * X_3D,Y_3D,Z_3D are the coordinates after rotation
     * X_2D,Y_2D are the 3d coordinates converted to 2d
     * Output array stores the characters to be printed at particular coordinates
     * Theta,Phi,A,B are angles of donut with different axes and are used in rotation
     * Luminance is used to decide which character will be printed at a particular location
     */
    float A, B, Z[80][30];
    char Output[80][30];
    int R1, R2, K1, K2;
    float Theta, Phi;
    float X_3D, Y_3D, Z_3D;
    int X_2D, Y_2D;
    int Luminance;


public:

    //constructor which initializes all the variables
    Donut()
    {
        A = 0, B = 0, Z[80][30] = {};
        Output[80][30] = {};
        R1 = 1, R2 = 2, K1 = 50, K2 = 7;
        Theta = 0, Phi = 0;
        X_3D = 0, Y_3D = 0, Z_3D = 0;
        X_2D = 0, Y_2D = 0;
        Luminance = 0;
    }

    //Deconstructor
    ~Donut() {}

    /**
     * @brief funtion to initialize the character array and z buffer after each print
     */
    void Reset()
    {
        for (int i = 0; i < 80; i++)
        {
            for (int j = 0; j < 30; j++)
            {
                Output[i][j] = ' ';
                Z[i][j] = 0;
            }
        }

        return;
    }

    /**
     * @brief function to calculate the coordinates and determine what character will be printed at those coordinates
     *
     */
    void Calculate()
    {
        for (Theta = 0; Theta < (Pi * 2); Theta += 0.07)
        {
            for (Phi = 0; Phi < (Pi * 2); Phi += 0.02)
            {
                X_3D = ((R2 + (R1 * cos(Theta))) * ((cos(B) * cos(Phi)) + (sin(A) * sin(B) * sin(Phi)))) - (R1 * cos(A) * sin(B) * sin(Theta));
                Y_3D = ((R2 + (R1 * cos(Theta))) * ((cos(Phi) * sin(B)) - (cos(B) * sin(A) * sin(Phi)))) + (R1 * cos(A) * cos(B) * sin(Theta));
                Z_3D = K2 + (cos(A) * (R2 + (R1 * cos(Theta))) * sin(Phi)) + (R1 * sin(A) * sin(Theta));

                X_2D = (80 / 2) + (K1 * X_3D * (1 / (K2 + Z_3D)));
                Y_2D = (30 / 2) + (K1 * Y_3D * (1 / (K2 + Z_3D)));

                Luminance = 8 * ((cos(Phi) * cos(Theta) * sin(B)) - (cos(A) * cos(Theta) * sin(Phi)) - (sin(A) * sin(Theta)) + (cos(B) * ((cos(A) * sin(Theta)) - (cos(Theta) * sin(A) * sin(Phi)))));

                if ((Y_2D > 0 && Y_2D < 30) && (X_2D > 0 && X_2D < 80) && (1 / (K2 + Z_3D)) > Z[X_2D][Y_2D])
                {
                    Z[X_2D][Y_2D] = (1 / (K2 + Z_3D));
                    Output[X_2D][Y_2D] = ".,-~:;=!*#$@"[Luminance > 0 ? Luminance : 0];
                }
            }
        }
    }

    /**
     * @brief function to display the donut
     *
     */
    void Display()
    {
        cout << "\x1b[H";//clear screen command

        for (int y = 0; y < 30; y++)
        {
            for (int x = 0; x < 80; x++)
                cout << Output[x][y];

            cout << endl;
        }

        A += 0.2;
        B += 0.2;
    }
};

int main()
{
    Donut Run;//instance of class

    //loop for infinite rotation of donut
    while (true)
    {
        Run.Reset();
        Run.Calculate();
        Run.Display();
    }

    return 0;
}
