#!/usr/bin/env Rscript

# This script is used to collate the average results after collecting test data
# while varying the mutate range as well as the damage range.
#
# @author trevmo

require(tidyr)

GetFiles <- function(homedir, prefix, increment) {
  #
  #
  
  storageDirs <- list.files(homedir)
  df <- data.frame(seq(0, 15))
  names(df) <- c("Damage.Range")
  currRange = as.numeric(increment)
  initInc = currRange
  for (dir in storageDirs) {
    if (grepl(prefix, dir)) {
      avgs <- list.files(paste(homedir, "/" , dir, "/avgs/", sep = ""), full.names = T)
      df <- data.frame(df, GetResults(avgs, "gaussian", "uniform", currRange))
      currRange = currRange + initInc
    }
  }
  write.csv(df, file = "varying_mutate_results.csv", row.names = F)
}

GetResults <- function(batch, setLabel1, setLabel2, rng) {
  # tbd
  # 
  
  set1Avg <- c()
  set1Best <- c()
  set2Avg <- c()
  set2Best <- c()
  for (file in batch) {
    dat <- read.csv(file)
    #TODO: generalize function
    if (grepl(setLabel1, file)) {
      #insert into that set
      set1Avg <- append(set1Avg, dat$avgSlope)
      set1Best <- append(set1Best, dat$bestSlope)
    } else {
      #insert into the other set
      set2Avg <- append(set2Avg, dat$avgSlope)
      set2Best <- append(set2Best, dat$bestSlope)
    }
  }
  #range <- seq(0, length(set1Avg)-1)
  all <- data.frame(set1Best, set2Best)
  names(all) <- c(paste(setLabel1, rng, sep = "."), paste(setLabel2, rng, sep = "."))
  return(all)
}

args = commandArgs(trailingOnly=TRUE)
if (length(args) < 1) {
  stop("You must specify csv file(s) on the command line.n")
}
GetFiles(args[1], args[2], args[3])