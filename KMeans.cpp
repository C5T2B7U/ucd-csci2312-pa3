// BRIAN SUMNER


#include "KMeans.h"
#include "Exceptions.h"
using namespace Clustering;

#include <fstream>



namespace Clustering
{


	KMeans::KMeans(unsigned int dim, unsigned int k, std::string filename, unsigned int maxIter) :
			__dimensionality(dim), __k(k), __iFileName(filename), __maxIter(maxIter)
	{
		if (k == 0)
			throw ZeroClustersEx();

		std::ifstream iFile(filename.c_str());
		if (iFile.fail())
			throw DataFileOpenEx(filename);
		iFile.close();

	}


	KMeans::~KMeans()
	{

	}

	// accessors
	unsigned int KMeans::getMaxIter()
	{
		return __maxIter;
	}

	unsigned int KMeans::getNumIters()
	{
		return __numIter;
	}

	unsigned int KMeans::getNumNonemptyClusters()
	{
		return __numNonempty;
	}

	unsigned int KMeans::getNumMovesLastIter()
	{
		return __numMovesLastIter;
	}


	// element access (for testing, no bounds checking)
	Cluster &KMeans::operator[](unsigned int u)
	{
		Cluster * newCluster;
		return *newCluster;
	}


	const Cluster &KMeans::operator[](unsigned int u) const
	{
		const Cluster * newCluster;
		return *newCluster;
	}

	// write out the results to a file
	std::ostream &operator<<(std::ostream &os, const KMeans &kmeans)
	{
		return os;
	}

	// clustering functions
	void KMeans::run()
	{

	//Implement the Cluster::Move::perform method and use it in the implementation of KMeans::run.
	//
	//		Note: This method should invalidate the centroids of both clusters.

	}










}
