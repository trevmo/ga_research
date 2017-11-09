#!/usr/bin/env Rscript
require(ggplot2)

findLinearApprox <- function (xvals, yvals, slopeLabel, r2Label) {
  model <- lm (yvals ~ xvals)
  r2 <- summary(model)$r.squared
  slope <- model$coefficients['xvals']
  #form a table with those values and labels
  final <- matrix(c(slope, r2), ncol = 2, byrow = TRUE)
  colnames(final) <- c(slopeLabel, r2Label)
  final <- as.table(final)
  return(final)
}
findResults <- function(filename) {
  output <- paste("out", filename, sep="_")
  header <- read.csv(args[1], nrows=9)
  write.csv(header, file = output, row.names = FALSE)
  dat <- read.csv(args[1], skip = 10)
  gen <- dat$Generation
  avg <- dat$AvgFit
  best <- dat$BestFit
  #plot(x,y)
  avgFinal <- findLinearApprox(gen, avg, 'avgSlope', 'r^2')
  bestFinal <-findLinearApprox(gen, best, 'bestSlope', 'r^2')
  #write the table out to the file created earlier
  write.table(avgFinal, output, sep = ",", col.names = T, row.names = F, append = T)
  write.table(bestFinal, output, sep = ",", col.names = T, row.names = F, append = T)
}

args = commandArgs(trailingOnly=TRUE)
if (length(args) != 1) {
  stop("You must specify a csv file on the command line.n")
}
findResults(args[1])