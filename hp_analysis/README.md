# HP Analysis

## Overview
This project was developed in C++ in Visual Studio 2017. It compiles into an automated app for collecting data based off of the parameterization in the project. All results get stored into csv files for further analysis.

## Classes
### Genetic Algorithm
The Genetic Algorithm class serves to setup and control the overall run of each session. It has a simple structure that primarily relies on the Population and Individual classes for the bulk of the work.

### Population
The Population class initializes a population of individuals for use in the genetic algorithm. It handles the higher level parameters, adapts each successive generation, and selects parents from the population. It also has some methods for calculating average values from the population's members as well as outputting those values to stdout or a csv file.

### Individual
The Individual class defines the structure of a given member of the population. The core properties are the genome and fitness value. Aside from helper methods, the class also has methods for performing uniform mutation and calculating the fitness. This fitness calculation relies on utility functions for acquiring value from uniform and Gaussian distributions.

### Other Components
#### Utility
The util files contain a few helper methods, primarily for use when calculating the fitness. ```uniformDistDamage``` and ```gaussianDistDamage``` are used for generating values from a uniform random distribution and a Gaussian distribution, respectively. These functions are used for testing the affects of different damage types on the evolution of fitness.

#### Parameters
The params header file defines two structures for controlling the damage and mutation in a given test session.
##### Damage struct
- type: constant, uniform, or Gaussian
- mean: mean damage value for a distribution
- range: range or standard deviation of the distribution
- isVariable: boolean indicating whether the test is varying the mean damage or not

##### Mutate struct
- type: currently only uniform is supported
- range: range of the mutation
- skipGene: allows for skipping an index in the genome when performing mutation
- isVariable: boolean indicating whether the test is varying the mutation range or not