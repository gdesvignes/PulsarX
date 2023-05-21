/**
 * @author Gregory Desvignes
 * @email gdesvignes@mpifr-bonn.mpg.de
 * @create date 2023-02-02 11:38:39
 * @modify date 2023-02-02 11:38:39
 * @desc [description]
 */


#ifndef FARADAY_H_
#define FARADAY_H_

#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>

#include "gridsearch.h"

using namespace std;

class Faraday
{
public:
  Faraday();
  ~Faraday(){}
  void prepare(Pulsar::GridSearch &gs);
  void run(Pulsar::GridSearch &gs);
  
public:
  
  int nbin;
  int nchan;
  int nsubint;
  long int nRMs;
  vector<complex<float>> L;
  vector<float> Lavg;
  vector<float> RM_trials;
  vector<double> frequencies;
  vector<float> lambda2;

};

#endif /* FARADAY_H_ */
