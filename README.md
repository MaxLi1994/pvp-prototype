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
**All the designs and implementations below are for prototype use only. This prototype will be discarded in the architecture design phase, so things like  error handling, extensibility, and decoupling are not considered.**

### Algorithm API

Any algorithm to be integrated into the pipeline framework needs to do only one thing: expose the entry of the algorithm following certain rules.
We’ve designed two classes for transmitting data and passing parameters: `data_bucket` and `para_bucket`. With these two classes, we are able to design a universal shape of interface for algorithms to expose:
```
data_bucket& func(data_bucket &, para_bucket &)
```

Here are two sample algorithms:
```
```

```
```

The `data_bucket` and `para_bucket` are basically wrappers for data or parameters. 
They provide APIs for getting data or parameters with the right type that authors of algorithms want. 
Also, they allow all kinds of data or parameters to be passed while keep a universal interface.

### Configuration File

Although the two buckets seem to have infinite flexibility, the data and parameters need to be defined somewhere so this framework knows what to pass.
Those are defined in configuration files.

A typical configuration file may look like this:
```
```
Notice that in this prototype we choose to use TBB as the task scheduler and to construct a data graph.
Therefore, the concept `node` and `edge` are coming from TBB.

### Framework Implementation

As mentioned above, the pipeline framework will be using TBB as the task scheduler.
The construction of the dependency graph is very similar to the sample project you gave us except we extract the algorithm part into configuration files.
Configuration files point out the location of certain dynamic algorithm library and the framework will be using `dlopen` to load the dynamic library.

During the process of creating the graph, the framework will instantiate `para_bucket`s for each node so that every time a node gets executed the corresponding `para_bucket` will be passed to the algorithm.


