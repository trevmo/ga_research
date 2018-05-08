#!/usr/bin/env Rscript

# Form a heatmap from a given data set. Intended for use on the average results
# from multiple trial runs, collecting the average gene and fitness values over
# the course of multiple generations. This script parses out the gene or fitness value
# from the last generation in the data set and forms a heatmap across each damage type
# and range.
#
# @author trevmo

require(ggplot2)
require(reshape2)

DATA.MAP <- list(gaussian=1, uniform=2)

FormHeatmap <- function(dat, filename) {
  # Form a heatmap plot from the specified data frame.
  #
  # Args:
  #   dat: data frame
  #   filename: representative file name/path to parse directory from
  
  path <- dirname(filename)
  dirName <- paste(path, "/heatmap/", sep="")
  dir.create(dirName, showWarnings = F)
  
  plot <- ggplot(dat, aes(Damage.Type, Damage.Range)) + 
    geom_tile(aes(fill = Fitness.Value), colour = "white") + 
    geom_text(aes(label = round(Fitness.Value, 2)), colour = "white") +
    scale_fill_gradient(low = "lightgrey", high = "black") +
    scale_y_continuous(breaks = seq(0, max(dat$Damage.Range), by = 1), expand = c(0, 0)) +
    scale_x_discrete(expand = c(0, 0))
  ggsave(paste(paste(dirName, "heatmap", sep = ""), "png", sep = "."), plot = plot, width = 10)
}

FormatData <- function(files, skip.lines, column.name) {
  # Read in data from a vector of files and form a data frame
  # to be used in creating a heatmap.
  #
  # Args:
  #   files: vector of files
  #   skip.lines: number of header lines in each file
  #   column.name: name of the column to parse the last value from
  #
  # Return:
  #   formatted data frame
  
  num.cols <- length(files) / 2
  mat <- matrix(, nrow = 2, ncol = num.cols)
  rownames(mat) <- c("Gaussian Distribution", "Uniform Distribution")
  colnames(mat) <- 0:(num.cols-1)
  for (file in files) {
    dat <- read.csv(file, skip=skip.lines)
    # parse metadata from file name for use in forming table
    parsed.file.name <- strsplit(basename(file), "[_.]")
    type <- parsed.file.name[[1]][2]
    range <- strtoi(parsed.file.name[[1]][3], 10)
    # parse the last value from the specified column
    value <- tail(dat[[column.name]], n=1)
    mat[DATA.MAP[[type]], range+1] <- value
  }
  df <- melt(mat)
  colnames(df) <- c("Damage.Type", "Damage.Range", "Fitness.Value")
  return (df)
}
args = commandArgs(trailingOnly=TRUE)
if (length(args) < 3) {
  stop("Args:\n\tskip.lines: number of (header) lines to skip in each file\n\tcolumn.name: name of the column to pull data from\n\tfiles: vector of filenames")
}
skip.lines <- strtoi(args[1])
column.name <- args[2]

data <- FormatData(tail(args, length(args)-2), skip.lines, column.name)
FormHeatmap(data, tail(args, n = 1))