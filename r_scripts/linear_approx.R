#!/usr/bin/env Rscript

# This script is used to find the linear approximation, and associated
# values, from a batch of csv files. Each file is expected to have a
# header of 9 lines listing info about the trial run, followed by
# 100 rows of 3 columns of data.
#
# @author trevmo

require(ggplot2)

FindLinearApprox <- function (xvals, yvals) {
  # Calculates the linear approximation and retrieves the corresponding
  # slope and R^2 values.
  #
  # Args:
  #   xvals: vector of data comprising the x axis
  #   yvals: vector of data comprising the y axis
  # Returns:
  #   vector containing the slope and R^2 values
  
  model <- lm (yvals ~ xvals)
  r2 <- summary(model)$r.squared
  slope <- model$coefficients['xvals']
  final <- c(slope, r2)
  return(final)
}
FindResults <- function(filename) {
  # Find the results from the data in the specified csv file.
  #
  # Arg:
  #   filename: name of the csv file
  #
  # Returns:
  #   void (outputs results to a new file)
  dirName <- "stats"
  dir.create(dirName, showWarnings = F)
  output <- paste("stats", basename(filename), sep="_")
  outputPath <- file.path(dirName, output)
  
  header <- read.csv(filename, nrows=12)
  write.csv(header, outputPath, row.names = FALSE)
  dat <- read.csv(filename, skip = 13)
  gen <- dat$Generation
  avg <- dat$AvgFit
  best <- dat$BestFit
  #plot(x,y)
  avgFinal <- FindLinearApprox(gen, avg)
  bestFinal <- FindLinearApprox(gen, best)
  
  table <- matrix(c(avgFinal, bestFinal), ncol = 2, byrow = T)
  colnames(table) <- c("slope", "r2")
  rownames(table) <- c("avg", "best")
  table <- as.table(table)
  #write the table out to the file created earlier
  write.table(table, outputPath, sep = ",", col.names = T, row.names = T, append = T)
}

args = commandArgs(trailingOnly=TRUE)
if (length(args) < 1) {
  stop("You must specify csv file(s) on the command line.n")
}
#loop over the csv files, creating output files
for (arg in args) {
  FindResults(arg)
}