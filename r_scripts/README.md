# R Scripts

## Overview
These scripts were created to simplify data analysis for the research project. Each script was designed with a specific purpose in mind:

| Name        | Description           | Usage  |
| ------------- |:-------------:| -----|
| avg_data.R     | Averages the data collected in csv files. | ```./avg_data.R``` *numGenerations* *batchSize* *files*|
| avg_stats.R     | Averages the statistical data collected in csv files. | ```./avg_stats.R``` *files* |
| collate_results.sh | Bash script for running sequence of R scripts. | ```./collate_results``` */path/to/R/scripts* */path/to/data* |
| form_heatmap.R | Form a heatmap of data from average results. | ```./form_heatmap.R``` *numberOfHeaderLinesInCsvFiles* *columnNameToGetDataFrom* *files* |
| form_table.R     | Form a table of average stats from collected data (when varying mutation and damage range). | ```./form_table.R``` */path/to/data* *filePrefix* *rangeIncrement* |
| format_plot.R | Source file to assist with ggplot formatting. | ```source("format_plot.R")``` |
| linear_approx.R | Calculate the linear approximation and R^2 values from the collected data. | ```./linear_approx.R``` *csvFiles* |
| plot_avgs.R | Form a plot from the output of ```avg_stats.R```. | ```./plot_avgs.R``` *csvFiles* |
| plot_data.R | Form a plot from a single csv file with generation, average fitness, and best fitness columns of data. | ```./plot_data.R``` *csvFile* |
| plot_direct_avg_data.R | Plot average gene and/or fitness values over the number of generations in the test. | ```./plot_direct_avg_data.R``` *numberOfHeaderLinesInCsvFiles* *includeFitness* *csvFiles* |

These scripts "get the job done" for this project, and I would recommend generalizing/optimizing them before trying to use them in another project.

### Side Note
I was learning R as I went in this project. As a result, you may notice varying levels of generalization and utilization of R-specific techniques. Utimately, the goal was simply to automate the data analysis, and the scripts could be further optimized with some more R experience.
