
<!-- README.md is generated from README.Rmd. Please edit that file -->

# vcfppR: rapid manipulation of the VCF/BCF file

<!-- badges: start -->

![R-CMD-check](https://github.com/Zilong-Li/vcfppR/actions/workflows/check-release.yaml/badge.svg)
<a href="https://github.com/Zilong-Li/random/blob/main/vcfppR.png"><img src="https://raw.githubusercontent.com/Zilong-Li/random/main/vcfppR.png" height="200" align="right" /></a>
<!-- badges: end -->

The vcfppR package implements various useful functions for manipulating
the VCF/BCF file in R using the C++ API of
[vcfpp.h](https://github.com/Zilong-Li/vcfpp).

## Installation

You can install the development version of vcfppR with the system
dependencies of `libcurl`.

``` r
## install.package("vcfppR") ## from CRAN
devtools::install_github("Zilong-Li/vcfppR")
```

## API

There are two classes i.e. ***vcfreader*** and ***vcfwriter*** offering
the full R-bindings of vcfpp.h. Check out the examples in the
[tests](tests/testthat) folder or refer to the manual.

``` r
?vcfppR::vcfreader
```

In addtion to two classes for R-bindings of vcfpp.h, there are some
useful functions in the package, e.g. ***vcftable***, ***vcfsummary***
and ***vcfpopgen***. In the following examples, we use the URL link as
filename, which can be directly fed to vcfppR, and the performance will
depend on your connection to the servers.

## Read VCF as tabular data in R

This example shows how to read only SNP variants with genotypes in the
VCF/BCF into R tables:

``` r
library(vcfppR)
vcffile <- "https://ftp.1000genomes.ebi.ac.uk/vol1/ftp/data_collections/1000G_2504_high_coverage/working/20220422_3202_phased_SNV_INDEL_SV/1kGP_high_coverage_Illumina.chr21.filtered.SNV_INDEL_SV_phased_panel.vcf.gz"
res <- vcftable(vcffile, "chr21:1-5100000", vartype = "snps")
str(res)
```

This example shows how to read only SNP variants with PL format and drop
the INFO column in the VCF/BCF into R tables:

``` r
vcffile <- "https://ftp.1000genomes.ebi.ac.uk/vol1/ftp/data_collections/1000G_2504_high_coverage/working/20201028_3202_raw_GT_with_annot/20201028_CCDG_14151_B01_GRM_WGS_2020-08-05_chr21.recalibrated_variants.vcf.gz"
res <- vcftable(vcffile, "chr21:1-5100000", vartype = "snps", format = "PL", info = FALSE)
str(res)
```

This example shows how to read only indels variants with DP format in
the VCF/BCF into R tables:

``` r
vcffile <- "https://ftp.1000genomes.ebi.ac.uk/vol1/ftp/data_collections/1000G_2504_high_coverage/working/20201028_3202_raw_GT_with_annot/20201028_CCDG_14151_B01_GRM_WGS_2020-08-05_chr21.recalibrated_variants.vcf.gz"
res <- vcftable(vcffile, "chr21:1-5100000", vartype = "indels", format = "DP")
str(res)
```

## Variants summarization

This example shows how to summarize small variants discovered by GATK.
The data is from the 1000 Genome Project.

``` r
vcffile <- "https://ftp.1000genomes.ebi.ac.uk/vol1/ftp/data_collections/1000G_2504_high_coverage/working/20201028_3202_raw_GT_with_annot/20201028_CCDG_14151_B01_GRM_WGS_2020-08-05_chr21.recalibrated_variants.vcf.gz"
region <- "chr21:10000000-10500000"
res <- vcfsummary(vcffile, region)
str(res)
# get labels and do plottiing
ped <- read.table("https://ftp.1000genomes.ebi.ac.uk/vol1/ftp/data_collections/1000G_2504_high_coverage/20130606_g1k_3202_samples_ped_population.txt", h=T)
ped <- ped[order(ped$Superpopulation),]
out <- sapply(unique(ped$Superpopulation), function(pop) {
  id <- subset(ped, Superpopulation == pop)[,"SampleID"]
  ord <- match(id, res$samples)
  res$SNP[ord] + res$INDEL[ord]
})

boxplot(out, main = paste0("Average number of SNP & INDEL variants\nin region ", region))
```

This example shows how to summarize complex structure variants
discovered by GATK-SV.

``` r
svfile <- "https://ftp.1000genomes.ebi.ac.uk/vol1/ftp/data_collections/1000G_2504_high_coverage/working/20210124.SV_Illumina_Integration/1KGP_3202.gatksv_svtools_novelins.freeze_V3.wAF.vcf.gz"
sv <- vcfsummary(svfile, svtype = TRUE)
str(sv)
allsvs <- sv$summary[-1]
bar <- barplot(allsvs, ylim = c(0, 1.1*max(allsvs)),
               main = "Variant Count (all SVs)")
text(bar, allsvs+4500, paste("n: ", allsvs, sep=""))
```
