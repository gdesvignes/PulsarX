/**
 * @author Gregory Desvignes
 * @email gdesvignes@mpifr-bonn.mpg.de
 * @create date 2023-02-02 11:38:39
 * @modify date 2023-02-02 11:38:39
 * @desc [description]
 */

#include "faraday.h"

using namespace std;


void Faraday::prepare(Pulsar::GridSearch &gs)
{
    nbin = gs.nbin;
    nchan = gs.nchan;
    nsubint = gs.nsubint;

    L.resize(nchan);
    lambda2.resize(nchan);
    frequencies.resize(nchan);

    // Copy frequencies
    for (int i=0; i<nchan; i++) {
        frequencies[i] = gs.frequencies[i];
        lambda2[i] = powf(299792458. / (frequencies[i]*1e6), 2);
    }

    
    // Make range of RM trials
    nRMs = 50000;
    float dRM = 6.0;
    float minRM = -150000.0;
    RM_trials.resize(nRMs);
    for (int i=0; i<nRMs; i++)
        RM_trials[i] = minRM + dRM*nRMs;

    Lavg.resize(nRMs);

}

void Faraday::run(Pulsar::GridSearch &gs)
{

    if (gs.pulsespan.back()>nbin || gs.pulsespan.back()<0 || gs.pulsespan.front() > nbin 
|| gs.pulsespan.front() < 0 || gs.pulsespan.back()<=gs.pulsespan.front())
     return;

    const complex<float> i(0.0, 1.0);
    
    for (int j=0; j<nchan; j++) {
      L[j] = 0.0;
      for (int i=0; i<nsubint; i++) {
	for (int k=0; k<nbin; k++) {
	  if (gs.pulsespan[0] <= k && k <= gs.pulsespan[1]) {
	    L[j] +=  gs.profiles[i*nchan*nbin+j*nbin+k + 1*nsubint*nchan*nbin] + i * gs.profiles[i*nchan*nbin+j*nbin+k+ 2*nsubint*nchan*nbin];
	  }
	}
      }
    }

    for (int i=0; i<nRMs; i++) {
        Lavg[i] = 0.0;
        for (int j=0; j<nchan; j++) {

            Lavg[i] += (L[j] * exp(-2*i * lambda2[j] * RM_trials[i]));
        }
	Lavg[i] = absf(Lavg[i]);
    }


}
