#!/usr/bin/env Rscript
require(ggplot2)

FindLinearApprox <- function (xvals, yvals, slopeLabel, r2Label) {
  # Calculates the linear approximation and retrieves the corresponding
  # slope and R^2 values.
  #
  # Args:
  #   xvals: vector of data comprising the x axis
  #   yvals: vector of data comprising the y axis
  #   slopeLabel: label for slope col of the table of results
  #   r2Label: label for r^2 col of the table of results
  # Returns:
  #   table containing the slope and R^2 values
  model <- lm (yvals ~ xvals)
  r2 <- summary(model)$r.squared
  slope <- model$coefficients['xvals']
  #form a table with those values and labels
  final <- matrix(c(slope, r2), ncol = 2, byrow = TRUE)
  colnames(final) <- c(slopeLabel, r2Label)
  final <- as.table(final)
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
  output <- paste("out", filename, sep="_")
  header <- read.csv(args[1], nrows=9)
  write.csv(header, file = output, row.names = FALSE)
  dat <- read.csv(args[1], skip = 10)
  gen <- dat$Generation
  avg <- dat$AvgFit
  best <- dat$BestFit
  #plot(x,y)
  avgFinal <- FindLinearApprox(gen, avg, 'avgSlope', 'r^2')
  bestFinal <- FindLinearApprox(gen, best, 'bestSlope', 'r^2')
  #write the table out to the file created earlier
  write.table(avgFinal, output, sep = ",", col.names = T, row.names = F, append = T)
  write.table(bestFinal, output, sep = ",", col.names = T, row.names = F, append = T)
}

args = commandArgs(trailingOnly=TRUE)
if (length(args) != 1) {
  stop("You must specify a csv file on the command line.n")
}
FindResults(args[1])