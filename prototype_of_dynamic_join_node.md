# Prototype of Dynamic Join Node

## Purpose

A way of dynamically creating join nodes (TBB) with different numbers of input ports during runtime.

## Idea

Since TBB uses the template technique to design `join_node`, one major disadvantage is that there is no way to dynamically create `join_node`s with arbitrary numbers of `input_port` by only using interfaces of TBB. However, we can do a huge `switch` to explicitly cover every possible situation. Since we have decided to use the `DataBucket` idea to pass data in TBB graphs, it eliminates the variable that data types may vary. So what really changes here is the number of `input_port`s. Therefore, it is possible to achieve this idea.

Notice that this idea has its own limitation that if it is to support a large number of `input_port`s, the code we need write down will be a lot. So, from a practical perspective, we may put a limit number to the final solution. In fact, TBB supports at most 10 `input_port`s as well, which is the same idea with ours to some extent.

## Proof of Concept Implementation

```
using namespace std;
using namespace tbb::flow;

void generate_join_node(vector<function_node<float, float>> &v, graph &g)
{
    int size = v.size();

    switch (size)
    {
    case 1:
    {
        auto *jn = new join_node<std::array<float, 1>>(g);
        make_edge(v[0], input_port<0>(*jn));

        auto *fn = new function_node<std::array<float, 1>>(g, unlimited,
                                                           [](const std::array<float, 1> &t) {
                                                               for (int i = 0; i < 1; i++)
                                                               {
                                                                   cout << t[i] << " |";
                                                               }
                                                               cout << endl;
                                                           });

        make_edge(*jn, *fn);
        break;
    }
    case 2:
    {
        auto *jn = new join_node<std::array<float, 2>>(g);
        make_edge(v[0], input_port<0>(*jn));
        make_edge(v[1], input_port<1>(*jn));

        auto *fn = new function_node<std::array<float, 2>>(g, unlimited,
                                                           [](const std::array<float, 2> &t) {
                                                               for (int i = 0; i < 2; i++)
                                                               {
                                                                   cout << t[i] << " |";
                                                               }
                                                               cout << endl;
                                                           });

        make_edge(*jn, *fn);
        break;
    }
    case 3:
    {
        auto *jn = new join_node<std::array<float, 3>>(g);
        make_edge(v[0], input_port<0>(*jn));
        make_edge(v[1], input_port<1>(*jn));
        make_edge(v[2], input_port<2>(*jn));

        auto *fn = new function_node<std::array<float, 3>>(g, unlimited,
                                                           [](const std::array<float, 3> &t) {
                                                               for (int i = 0; i < 3; i++)
                                                               {
                                                                   cout << t[i] << " |";
                                                               }
                                                               cout << endl;
                                                           });

        make_edge(*jn, *fn);
        break;
    }

    case 4:
    {
        auto *jn = new join_node<std::array<float, 4>>(g);
        make_edge(v[0], input_port<0>(*jn));
        make_edge(v[1], input_port<1>(*jn));
        make_edge(v[2], input_port<2>(*jn));
        make_edge(v[3], input_port<3>(*jn));

        auto *fn = new function_node<std::array<float, 4>>(g, unlimited,
                                                           [](const std::array<float, 4> &t) {
                                                               for (int i = 0; i < 4; i++)
                                                               {
                                                                   cout << "start" << endl;
                                                                   cout << t[i] << " |";
                                                                   cout << "end" << endl;
                                                               }
                                                               cout << endl;
                                                           });

        make_edge(*jn, *fn);
        break;
    }
    case 5:
    {
        auto *jn = new join_node<std::array<float, 5>>(g);
        make_edge(v[0], input_port<0>(*jn));
        make_edge(v[1], input_port<1>(*jn));
        make_edge(v[2], input_port<2>(*jn));
        make_edge(v[3], input_port<3>(*jn));
        make_edge(v[4], input_port<4>(*jn));

        auto *fn = new function_node<std::array<float, 5>>(g, unlimited,
                                                           [](const std::array<float, 5> &t) {
                                                               for (int i = 0; i < 5; i++)
                                                               {
                                                                   cout << t[i] << " |";
                                                               }
                                                               cout << endl;
                                                           });

        make_edge(*jn, *fn);
        break;
    }
    }
}

int main(int argc, char **argv)
{

    graph g;

    function_node<float, float> f1(g, unlimited, [](const float &i) { return 2 * i; });
    function_node<float, float> f2(g, unlimited, [](const float &i) { return i * i; });
    function_node<float, float> f3(g, unlimited, [](const float &i) { return i * i * i; });
    function_node<float, float> f4(g, unlimited, [](const float &i) { return i / 2; });

    vector<function_node<float, float>> v;
    v.push_back(f1);
    v.push_back(f2);
    v.push_back(f3);
    v.push_back(f4);

    generate_join_node(v, g);

    for (int i = 0; i < 2; i++)
    {
        v[i].try_put(((float)i + 1));
        v[i].try_put(((float)i + 2));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(6000));

    for (int i = 2; i < 4; i++)
    {
        v[i].try_put(((float)i + 1));
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        v[i].try_put(((float)i + 2));
    }

    g.wait_for_all();
    return 0;
}
```
