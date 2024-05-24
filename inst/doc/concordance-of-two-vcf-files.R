## ----include = FALSE----------------------------------------------------------
knitr::opts_chunk$set(
  collapse = TRUE,
  comment = "#>"
)

## ----setup--------------------------------------------------------------------
library(vcfppR)

## ----eval = FALSE-------------------------------------------------------------
#  vcfcomp(testvcf, truthvcf, formats = c("DS", "GT"), stats = "r2")

## ----eval = FALSE-------------------------------------------------------------
#  vcfcomp(testvcf, truthvcf, formats = c("MDS", "GT"), stats = "r2")
#  vcfcomp(testvcf, truthvcf, formats = c("FDS", "GT"), stats = "r2")

## ----eval = FALSE-------------------------------------------------------------
#  vcfcomp(testvcf, truthvcf, formats = c("GT","GT"), stats="nrc", by.sample=TRUE)
#  vcfcomp(testvcf, truthvcf, formats = c("GT","GT"), stats="f1", by.sample=TRUE)

## ----eval = FALSE-------------------------------------------------------------
#  vcfcomp(testvcf, truthvcf, stats="pse", return_pse_sites=TRUE)

## ----eval = FALSE-------------------------------------------------------------
#  saveRDS(vcftable(truthvcf), "truth.rds")
#  vcfcomp(test=testvcf1, truth="truth.rds")
#  vcfcomp(test=testvcf2, truth="truth.rds")
#  vcfcomp(test=testvcf3, truth="truth.rds")

