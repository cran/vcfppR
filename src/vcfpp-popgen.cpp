#include <Rcpp.h>
#include "vcfpp.h"

using namespace Rcpp;
using namespace std;

//' calculate the number of heterozygous SNPs for each sample
//' @param vcffile path to the VCF file with index
//' @param region  region to extract, default "" for all
//' @param pass restrict to variants with FILTER==PASS
//' @param qual restrict to variants with QUAL > qual.
//' @param samples samples to extract, default "-" for all
//' @return A list of heterozygosity couts for each sample along with its id in the vcf header
//' @export
// [[Rcpp::export]]
List heterozygosity(std::string vcffile, std::string region = "", std::string samples = "-",
                    bool pass = false, double qual = 0) {
    vcfpp::BcfReader vcf(vcffile, region, samples);
    vcfpp::BcfRecord var(vcf.header);
    vector<int> gt;
    vector<int> hetsum(vcf.nsamples, 0);  // store the het counts
    while (vcf.getNextVariant(var)) {
        if (pass && (var.FILTER() != "PASS")) continue;
        if ((qual > 0) && (var.QUAL() < qual)) continue;
        var.getGenotypes(gt);
        // analyze SNP variant
        if (!var.isSNP()) continue;
        assert(var.ploidy() == 2);  // make sure it is diploidy
        for (size_t i = 0; i < gt.size() / 2; i++)
            hetsum[i] += abs(gt[2 * i + 0] - gt[2 * i + 1]) == 1;
    }

    return List::create(Named("samples") = vcf.header.getSamples(), Named("hets") = hetsum);
}
