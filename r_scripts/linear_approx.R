#!/usr/bin/env Rscript
require(ggplot2)
args = commandArgs(trailingOnly=TRUE)
if (length(args) != 1) {
  stop("You must specify a csv file on the command line.n")
}
filename <- args[1]
output <- paste("out", filename, sep="_")
header <- read.csv(args[1], nrows=9)
write.csv(header, file = output, row.names = FALSE)
dat <- read.csv(args[1], skip = 10)
gen <- dat$Generation
avg <- dat$AvgFit
best <- dat$BestFit
#plot(x,y)
#calculate the linear model/approx
res <- lm(avg ~ gen)
#parse out the r^2 and slope values
r2 <- summary(res)$r.squared
slope <- res$coefficients['gen']
#form a table with those values and labels
final <- matrix(c(slope, r2), ncol = 2, byrow = TRUE)
colnames(final) <- c('Slope', 'R^2')
final <- as.table(final)
#write the table out to the file created earlier
write.table(final, output, sep = ",", col.names = T, row.names = F, append = T)