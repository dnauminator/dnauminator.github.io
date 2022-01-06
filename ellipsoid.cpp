#include <iostream>
#include <math.h>
#include <vector>

const float pi = 3.1415;
struct Point2D
{
    float x, y, yprime;
};
//to be used for XZ plane ellipses
float EllipsoidSolverX(float a, float b, float y)
{
    float aa = a * a; float bb = b * b;
    return sqrt(aa - (((y-b) * (y-b)) * aa) / (bb))+a;
}
//upper part of an XY plane ellipse
float EllipsoidSolverY(float a, float b, float x)
{
    float aa = a * a; float bb = b * b;
    return sqrt(bb - (((x-a) * (x-a)) * bb) / (aa))+b;
}
//lower part of an XY plane ellipse
float EllipsoidSolverYPrime (float a, float b, float x)
{
    float aa = a * a; float bb = b * b;
    return -sqrt(bb - (((x - a) * (x - a)) * bb) / (aa)) + b;
}
//sets up ellipse data values to be displayed in a neat way
void PrintPoints(std::vector<Point2D> Points)
{
    for (float i = 0; i < Points.size(); i++)
    {
        printf("%f, %f, %f\n", Points[i].x, Points[i].y, Points[i].yprime);
    }
}
//creates the array that allows ellipse value display
std::vector<Point2D> sampleEllipsoid(float a, float b, float minx, float maxx, float step)
{
    std::vector<Point2D> Array_Y;
    for (float x = minx; x <= maxx; x += step)
    {
        Point2D point = { x, EllipsoidSolverY(a, b, x), EllipsoidSolverYPrime(a, b, x) };
        Array_Y.push_back(point);
    }
    return Array_Y;
}
int main() {
    while (true)
    {
        float x, y, z;//points
        float minx = 0;
        char radordeg;
        float mult1;//either keeps radians as radians or turns them into degrees
        //inputs
        printf("input vectors\n");//vector inputs and scanner
        scanf("%f, %f, %f", &x, &y, &z);
        float a = x/2, b = y/2;
        float maxx = x;
        printf("radians or degrees (r/d)\n");//radians or degrees selection and scanner
        scanf(" %c", &radordeg);
        //makes sure that the radordeg value works properly when "d" is input
        if (radordeg == 'd')
            mult1 = 180 / pi;
        else
            mult1 = 1;
        //various numerical operations
        float mag = sqrt(x * x + y * y + z * z);//calculates magnitude
        float anglex = acos(x / mag);//tilt from x-axis
        float angley = acos(y / mag);//tilt from y-axis
        float anglez = acos(z / mag);//tilt from z-axis
        float rectangular_prism = (double)(x * y * z);//volume of resultant rect. prism
        float inscribed_ellipsoid = (double)(4 * pi * ((x * y * z) / 8) / 3);//volume of resultant inscribed ellipsoid
        float X_Ellipse = EllipsoidSolverX(a, b, y);
        float Y_Ellipse = EllipsoidSolverY(a, b, x);
        std::vector<Point2D> EllipsoidPoints = sampleEllipsoid(a, b, minx, maxx, a/50);
        //print results
        printf("magnitude: %f\n", mag);
        printf("angles: %f, %f, %f\n", (double)anglex * mult1, (double)angley * mult1, (double)anglez * mult1);
        printf("your volume (rectangular prism): %f\n", rectangular_prism);
        printf("your volume (enclosed ellipsoid): %f\n", inscribed_ellipsoid);
        PrintPoints(EllipsoidPoints);//displays the ellipse values from earlier func, val 1 is step while 2 and 3 are respective x, y coords
        printf("your numbers: %f, %f, %f\n", x, y, z);//numbers that were input in prompt

      
        
    }
}