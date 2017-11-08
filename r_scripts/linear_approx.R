#!/usr/bin/env Rscript
require(ggplot2)
args = commandArgs(trailingOnly=TRUE)
if (length(args) != 1) {
  stop("You must specify a csv file on the command line.n")
}
dat <- read.csv(args[1], skip = 10)
gen <- dat$Generation
avg <- dat$AvgFit
best <- dat$BestFit
#plot(x,y)
res <- lm(avg ~ gen)
r2 <- summary(res)$r.squared
slope <- res$coefficients['gen']
print(paste("slope:", slope))
print(paste("r^2:", r2))