#ifndef GENOME_H
#define GENOME_H

#include "Allele.h"
#include "Constants.h"

class Genome
{
public:
	Genome();
	~Genome();

private:
	Allele alleles[GENOME_ALLELE_NUM];

	int activeIndex;
	int initialIndex;
};

#endif