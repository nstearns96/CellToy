#ifndef ALLELE_H
#define ALLELE_H

class Allele
{
public:
	Allele();
	~Allele();

private:
	float childAngles[2];
	int childIndices[2];

	float splitFood;
	float splitFoodRatio;
	float splitAngle;

	int color;

	bool connectedSplit;
};

#endif