# Genetic Algorithm Research
## Controlling the Rate of Evolution for Evolutionary Video Games

## Contributors
- [Dr. Terry Soule](http://www2.cs.uidaho.edu/~tsoule/)
- [Trevor Morse](http://www.github.com/trevmo)

## Summary
Starting in the fall of 2017, I started working with Dr. Soule to conduct some research regarding genetic algorithms. At the time, I was taking his Evolutionary Computation class and looking for more experience in this subfield of Machine Learning.

Over the course of the next one and a half semesters, we worked on analyzing how to improve the playability of video games through evolutionary computation.

Given a population of individuals with a single genome, representing health, we sought to analyze how the fitness of those individuals evolved while undergoing different types of damage. In other words, if we used a:
- constant damage OR
- damage from a uniform distribution OR
- damage from a Gaussian distribution
would we see a higher rate of evolution in the fitness of the individuals? (Fitness was measured as the number of hits it took to decrease an individual's health <=0.)

After analyzing this initial hypothesis, we then incorporated a second genome to the individuals, representing armor. Now that the individuals had a second genome, we conducted the same analysis to see how armor affected the rate of evolution. (Armor was treated the same as the health genome, except that it was subtracted from the damage value before damage was applied to health. Additionally, it never decreased after absorbing damage.)

**[2018/05/02]** We are currently working on a conference paper discussing our findings. This page will be updated if/when that paper is complete and accepted.

## Contents

### hp_analysis
This directory contains the code used for collecting data in the research project. It follows a standard genetic algorithm structure with classes for the population and individuals. The algorithm is heavily parameterized and structured in a way to make it easy to test a number of different values for each parameter in one session.
### r_scripts
r_scripts contains a variety of scripts used for analyzing the collected data. These scripts handle tasks like averaging and plotting the data. They are primarily targeted for this project with varying levels of generalization.
