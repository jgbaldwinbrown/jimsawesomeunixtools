#!/usr/bin/Rscript

data=as.numeric(readLines("stdin"))
cat("Number: ")
cat(length(data))
cat("\n")
summary(data)
