# Genetic Algorithm Research
## Controlling the Rate of Evolution for Evolutionary Video Games

## Contributors
- [Dr. Terry Soule](http://www2.cs.uidaho.edu/~tsoule/)
- [Trevor Morse](http://www.github.com/trevmo)

## Summary

### Background
Starting in the fall of 2017, I worked with Dr. Soule to conduct some research regarding genetic algorithms. At the time, I was taking his Evolutionary Computation class and looking for more experience in this subfield of Machine Learning.

Over the course of the next one and a half semesters, we worked on analyzing how to improve the playability of video games through evolutionary computation.

### Project Overview
Given a population of individuals with a single gene, representing health, how does the fitness evolve while undergoing different types of damage. In other words, if applying:
- a constant damage OR
- a damage from a uniform distribution OR
- a damage from a Gaussian distribution

is there a higher rate of evolution in fitness for a particular damage type? (Fitness is measured as the number of hits it takes to decrease an individual's health <=0.)

Additionally, how does incorporating a second gene, representing armor, affect the evolution of fitness? (Armor is treated the same as the health gene, except that it is subtracted from the damage value before damage is applied to health. Additionally, armor's value never decreases after absorbing damage.)

**[2018/05/02]** We are currently working on a conference paper discussing our findings. This page will be updated if/when that paper is complete and accepted.

## Contents

### hp_analysis
```hp_analysis/``` contains the code used for collecting data in the research project. It follows a standard genetic algorithm structure with classes for the population and individuals. The algorithm is heavily parameterized and structured in a way to make it easy to test a number of different values for each parameter in one session.

### r_scripts
```r_scripts/``` contains a variety of scripts used for analyzing the collected data. These scripts handle tasks like averaging and plotting the data. They are primarily targeted for this project with varying levels of generalization.
