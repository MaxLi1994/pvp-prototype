#include "type.hpp"

using namespace pvp;

DataBucket add(DataBucket data, Params params)
{
    int a = data.get_int("a");
    int b = data.get_int("b");
    data.set_int("result", a+b);
    return data;
}

DataBucket sub(DataBucket data, Params params)
{
    int a = data.get_int("a");
    int b = data.get_int("b");
    data.set_int("result", a-b);
    return data;
}

DataBucket mul(DataBucket data, Params params)
{
    int a = data.get_int("a");
    int b = data.get_int("b");
    data.set_int("result", a*b);
    return data;
}