#include "type.hpp"

using namespace pvp;

extern "C" DataBucket& add(DataBucket &data, Params &params)
{
    int a = data.get_int("a");
    int b = data.get_int("b");
    data.set_int("result", a+b);
    return data;
}
