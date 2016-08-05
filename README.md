# Statistical Testing Simulation
A small suite to simulate the statistical testing phase of a software module.

## Requirements

```
gcc >= 5.3.0
```

## Installation
After cloning, in the main directory run

```bash
$ make
```

It will compile all sources and produce
* test executables in the test folder;
* the main executable `STSimulation`.

## Running
In order to run the simulation, run the executable

```bash
$ ./STSimulation
```

In input, you will be requested to type:
* The seed for the linear congruential engine
* The number of initial faults
* The (constant) failure rate in the pre-run phase (expressed in failure/h)
* The number of failure to be observed in the pre-run phase
* The number of failure to be observed in the run phase
* The Musa factor A.

The program will produce a txt file in `Mathematica` format, to be passed as input to the Newton-Raphson implementation in that language.
