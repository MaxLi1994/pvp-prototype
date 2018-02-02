# PVP Prototype
## Purpose
+ Validating the initial version of API design
+ Eliciting more details in requirements
+ Exploring technical feasibility of certain features

## Main Features
1. The pipeline framework can integrate a CV algorithm into a pipeline network as a dynamic library. The interaction between the algorithm and the framework will be solely defined by a configuration file. Any changes in CV algorithm parameters or topological structure will only have to modify the configuration file without recompiling any dynamic libraries.
2. The pipeline framework supports algorithms with different kinds of input data or parameters.

## Prototype Design
### Notice
**This is not a working prototype. All the designs and implementations below are for prototype use only. Code samples in this article can be found in this repository. This prototype will be discarded in the architecture design phase, so things like  error handling, extensibility, and decoupling are not considered.**

### Algorithm API

Any algorithm to be integrated into the pipeline framework needs to do only one thing: expose the entry of the algorithm following certain rules.
We’ve designed two classes for transmitting data and passing parameters: `DataBucket` and `Params`. With these two classes, we are able to design a universal shape of interface for algorithms to expose:
```
extern "C" DataBucket& func(DataBucket &, Params &)
```

Here are two sample algorithms:
```
// alogorithms/int_cal.cpp
// simple algorithm which adds two integers
#include "type.hpp"

using namespace pvp;

extern "C" DataBucket& add(DataBucket &data, Params &params)
{
    int a = data.get_int("a");
    int b = data.get_int("b");
    data.set_int("result", a+b);
    return data;
}
```

```
// alogorithms/cvMat_cal.cpp
// algorithm using openCV
#include "type.hpp"

using namespace pvp;

extern "C" DataBucket& blur(DataBucket &data, Params &params)
{
    cv::Mat src = data.get_opencv_mat("origin");
    cv::Mat dst;
    cv::Size ksize = params.get_opencv_size("ksize");
    cv::blur(src, dst, ksize);
    data.set_opencv_mat("blurred", dst);
    return data;
}

extern "C" DataBucket& canny(DataBucket &data, Params &params)
{
    cv::Mat src = data.get_opencv_mat("origin");
    cv::Mat edges;
    float threshold1 = params.get_float("threshold1");
    float threshold2 = params.get_float("threshold2");
    cv::Canny(src, edges, threshold1, threshold2);
    data.set_opencv_mat("edges", edges);
    return data;
}
```

The `DataBucket` and `Params` are basically wrappers for data or parameters. 
They provide APIs for getting data or parameters with the right type that authors of algorithms want. 
Also, they allow all kinds of data or parameters to be passed while keep a universal interface.

### Configuration File

Although the two wrappers seem to have infinite flexibility, the data and parameters need to be defined somewhere so this framework knows what to pass.
Those are defined in configuration files.

A typical configuration file may look like this:
```
// configuration/config2.json
{
    "nodes":[
        { 
            "name":"src",
            "type":"source",
            "data": { // data could be multiple
                "type": "open_Mat", // there will be a set of pre-defined types in this framework
                "source": "~/test.jpg"
            }
        },{ 
            "name":"step1",
            "type":"function",
            "func": {
                "library": "/Users/xx/libCV.so", // location of the dynamic lib
                "name": "blur" // name of the exposed function
            },
            "data": [ // input data type definition
                {
                    "type": "opencv_Mat",
                    "name": "origin"
                }
            ],
            "params": [ // parameters to be passed into the Params object
                {
                    "type": "opencv_Size",
                    "name": "ksize", 
                    "value": 10
                }
            ],
            "output": [ // output data type definition
                {
                    "type": "opencv_Mat",
                    "name": "blurred"
                }
            ]
        },{ 
            "name":"step2",
            "type":"funcntion",
            "func": "canny",
            "data":[
                {
                    "type": "opencv_Mat",
                    "name": "origin"
                }
            ],
            "params": [
                {
                    "type": "float",
                    "name": "threshold1", 
                    "value": 1.0
                }, {
                    "type": "float",
                    "name": "threshold2", 
                    "value": 2.0
                }
            ],
            "output": [
                {
                    "name": "edges",
                    "type": "opencv_Mat"
                }
            ]
        }],
    "edges":[
        {
            "source":["src"],
            "receiver":["step1"]
        },{ 
            "source":["step1"],
            "receiver":["step2"] 
        }]
}
```
Notice that in this prototype we choose to use TBB as the task scheduler and to construct a data graph.
Therefore, the concept `node` and `edge` are coming from TBB.

### Framework Implementation

As mentioned above, the pipeline framework will be using TBB as the task scheduler.
The construction of the dependency graph is very similar to the sample project you gave us except we extract the algorithm part into configuration files.
Configuration files point out the location of certain dynamic algorithm library and the framework will be using `dlopen` to load the dynamic library.

During the process of creating the graph, the framework will instantiate `Params`s for each node so that every time a node gets executed the corresponding `Params` will be passed to the algorithm.


