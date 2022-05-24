#include <iostream>
#include <ql/quantlib.hpp>

#include "greek.h"

using namespace QuantLib;


void greeks(double strike, double timeToMaturityYears, double spot, double riskFree, double dividendYield, double sigma,
            double *value, double *delta, double *gamma, double *vega, double *theta)
{

    //QuantLib requires sigma * sqrt(T) rather than just sigma/volatility
    Real vol = sigma * std::sqrt(timeToMaturityYears);

    //calculate dividend discount factor assuming continuous compounding (e^-rt)
    DiscountFactor growth = std::exp(-dividendYield * timeToMaturityYears);

    //calculate payoff discount factor assuming continuous compounding 
    DiscountFactor discount = std::exp(-riskFree * timeToMaturityYears);

    //instantiate payoff function for a call 
    ext::shared_ptr<PlainVanillaPayoff> vanillaCallPayoff = 
        ext::shared_ptr<PlainVanillaPayoff>(new PlainVanillaPayoff(Option::Type::Call, strike));

    BlackScholesCalculator bsCalculator(vanillaCallPayoff, spot, growth, vol, discount);

    *value = bsCalculator.value();
    *delta = bsCalculator.delta();
    *gamma = bsCalculator.gamma();
    *vega = bsCalculator.vega(timeToMaturityYears) / 100.;
    *theta = bsCalculator.thetaPerDay(timeToMaturityYears);
}

