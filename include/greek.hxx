#ifndef _GREEK_H_
#define _GREEK_H_


#ifdef __cplusplus
extern "C" {
#endif

double Test(double a);

void CalcGreeks(double strike, double timeToMaturityYears, double spot, double riskFree, double dividendYield, double sigma,
             double *value, double *delta, double *gamma, double *vega, double *theta);

#ifdef __cplusplus
}
#endif

#endif //_GREEK_H_