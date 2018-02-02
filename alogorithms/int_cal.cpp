#include "type.hpp"

using namespace pvp;

ReturnType add(Data data, Params params)
{
    int a = data.get_int("a");
    int b = data.get_int("b");
    ReturnType res;
    res.set_int("result", a+b);
    return res;
}

ReturnType sub(Data data, Params params)
{
    int a = data.get_int("a");
    int b = data.get_int("b");
    ReturnType res;
    res.set_int("result", a-b);
    return res;
}

ReturnType mul(Data data, Params params)
{
    int a = data.get_int("a");
    int b = data.get_int("b");
    ReturnType res;
    res.set_int("result", a*b);
    return res;
}