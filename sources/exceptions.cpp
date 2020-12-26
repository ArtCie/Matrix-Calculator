#include<iostream>
using namespace std;

class ErrorWrongSize : public exception
{
    virtual const char *what() const throw()
    {
        return "[Error]: Wymiary macierzy nie są równe";
    }
};

class ErrorNotNumber : public exception
{
    virtual const char *what() const throw()
    {
        return "[Error]: Oczekiwano wartości liczbowej";
    }
};

class ErrorNotSquared : public exception
{
    virtual const char *what() const throw()
    {
        return "[Error]: Macierz nie jest kwadratowa";
    }
};

class ErrorNotPositiveDefined : public exception
{
    virtual const char *what() const throw()
    {
        return "[Error]: Macierz nie jest dodatnio określona";
    }
};

class ErrorWrongMultiplication : public exception
{
    virtual const char *what() const throw()
    {
        return "[Error]: Bledne wymiary macierzy do wymnozenia";
    }
};

class ErrorLU : public exception
{
    virtual const char *what() const throw()
    {
        return "[Error]: Podczas wykonywania algorytmu\nwystąpiło dzielenie przez zero";
    }
};

class ErrorNotSymmetric : public exception
{
    virtual const char *what() const throw()
    {
        return "[Error]: Macierz nie jest symetryczna";
    }
};

class detEqualZero : public exception
{
    virtual const char *what() const throw()
    {
        return "[Error]: Macierz jest osobliwa(det(Matrix)==0)";
    }
};

class detTooBig : public exception
{
    virtual const char *what() const throw()
    {
        return "[Error]: Podana macierz jest zbyt duza.";
    }
};