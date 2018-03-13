#!/usr/bin/env Rscript


# This script is used for formatting ggplots. It can be sourced in other R scripts via:
# source("format_plot.R")
#
# @author trevmo

require(ggplot2)

CalculateAxisTicks <- function(range, interval) {
  # Calculate a distance between tick marks for a given axis from the axis' specified
  # range of data.
  #
  # Args:
  #   range: range of data for a given axis of the plot
  #   interval: specified interval to divide the range by
  #
  # Returns:
  #   distance between labels on the axis
  dist <- range[1] + range[2]
  if (dist > interval)
    return(round(dist / interval))
  else
    return(dist / interval)
}
FormatPlot <- function(plot) {
  # Add formatting to a ggplot.
  #
  # Arg:
  #   plot: ggplot
  #
  # Returns:
  #   formatted plot
  title.font <- 20
  title.margin <- margin(t = 10, r = 0, b = 14, l = 0, unit = "pt")
  increment <- 10
  
  yrange <- ggplot_build(plot)$layout$panel_ranges[[1]]$y.range
  xrange <- ggplot_build(plot)$layout$panel_ranges[[1]]$x.range
  
  return(plot +
    geom_point(size = 1.5) +
    scale_x_continuous(breaks = seq(0, round(xrange[2]), CalculateAxisTicks(xrange, increment))) +
    scale_y_continuous(breaks = seq(0, round(yrange[2]), CalculateAxisTicks(yrange, increment))) +
    theme(plot.title = element_text(size = title.font, hjust = 0.5, margin = title.margin)) +
    theme(axis.title = element_text(size = title.font-4)) +
    theme(legend.position = "bottom"))
}