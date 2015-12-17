#include "operators.h"

Field operator+(const Field &f1, const Field &f2)
{
    return Field(f1.getX()+f2.getX(), f1.getY()+f2.getY());
}

bool operator==(const Field &f1, const Field &f2)
{
    return f1.get()==f2.get();
}

bool operator<(const Field &f1, const Field &f2)
{
    return (f1.getX() + 8*f1.getY()) < (f2.getX() + 8*f2.getY());
}

bool operator>(const Field &f1, const Field &f2)
{
    return (f1.getX() + 8*f1.getY()) > (f2.getX() + 8*f2.getY());
}
