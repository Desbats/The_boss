#include "base.h"

Base::Base()
{
    add_soldier(1, 100);
    add_soldier(2, 25);
    add_soldier(3, 50);
    add_soldier(4, 25);
    add_soldier(5, 100);
}

int base_color(int id_base)
{
    return 1;
}

int base_nb_soldier(int id_base)
{
    return 1;
}

int add_soldier(int id_base, int nb_soldier)
{
    return 1;
}

bool attack_base(int id_base1, int id_base2)
{
    return true;
}
