#ifndef _GREEK_H_
#define _GREEK_H_

void greeks(double strike, double timeToMaturityYears, double spot, double riskFree, double dividendYield, double sigma,
            double *value, double *delta, double *gamma, double *vega, double *theta);


#endif //_GREEK_H_