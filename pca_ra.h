#ifndef PCA_RA_H
#define PCA_RA_H

#include <string>
#include <vector>

// Creates a class of vectors for the layers of differentiation

class PCA_RA {
public:
	PCA_RA()
		: raMainString() {};
	// Vector of string vectors to differentiate various PCA analyses
	std::vector<std::pair<std::string, std::string>> pcaVec;
	std::vector<std::string> otuRmVec;
	std::string raMainString;
	std::vector<std::string> raVec;
};

#endif