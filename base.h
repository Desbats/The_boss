#ifndef BASE_H
#define BASE_H

#include "qstd.h"
using namespace qstd;

class Base
{
private:
    int max_soldier = 100;
    QString color;

public:
    Base();
    int base_color(int);
    static int base_nb_soldier(int);
    static int add_soldier(int, int);
    static bool attack_base(int, int);
};

#endif // BASE_H
