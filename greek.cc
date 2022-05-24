#include <iostream>
#include <cstdlib>
#include <ql/quantlib.hpp>

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

int main() 
{
    Real strike = 110.0;
    Real timeToMaturity = .5; //years
    Real spot = 100.0;
    Rate riskFree = .03;
    Rate dividendYield = 0.0;
    Volatility sigma = .20;


    // TODO introduce structs
    double value, delta, gamma, vega, theta;
    greeks(strike, timeToMaturity, spot, riskFree, dividendYield, sigma, &value, &delta, &gamma, &vega, &theta);

    std::cout << "Value of 110.0 call is " << value << std::endl;
    std::cout << "Delta of 110.0 call is " << delta << std::endl;
    std::cout << "Gamma of 110.0 call is " << gamma << std::endl;
    std::cout << "Vega of 110.0 call is "  << vega << std::endl;
    std::cout << "Theta of 110.0 call is " << theta << std::endl;

    // TODO use function to up as well

    //QuantLib requires sigma * sqrt(T) rather than just sigma/volatility
    Real vol = sigma * std::sqrt(timeToMaturity);

    //calculate dividend discount factor assuming continuous compounding (e^-rt)
    DiscountFactor growth = std::exp(-dividendYield * timeToMaturity);

    //calculate payoff discount factor assuming continuous compounding 
    DiscountFactor discount = std::exp(-riskFree * timeToMaturity);

    Real changeInSpot = 1.0;
    BlackScholesCalculator bsCalculatorSpotUpOneDollar(Option::Type::Call, strike, spot + changeInSpot, growth, vol, discount);
    std::cout << "Value of 110.0 call (spot up $" << changeInSpot << ") is " <<  bsCalculatorSpotUpOneDollar.value() << std::endl;
    std::cout << "Value of 110.0 call (spot up $" << changeInSpot << ") estimated from delta is " <<  (value + delta * changeInSpot) << std::endl;

    //use a Taylor series expansion to estimate the new price of a call given delta and gamma
    std::cout << "Value of 110.0 call (spot up $" << changeInSpot << ") estimated from delta and gamma is " << (value + (delta * changeInSpot) + (.5 * gamma * changeInSpot)) << std::endl;

    //calculate new price of a call given a one point change in volatility
    Real changeInSigma = .01;
    BlackScholesCalculator bsCalculatorSigmaUpOnePoint(Option::Type::Call, strike, spot, growth, (sigma + changeInSigma) * std::sqrt(timeToMaturity) , discount);
    std::cout << "Value of 110.0 call (sigma up " << changeInSigma << ") is " << bsCalculatorSigmaUpOnePoint.value() << std::endl;

    //estimate new price of call given one point change in volatility using vega
    std::cout << "Value of 110.0 call (sigma up " << changeInSigma << ") estimated from vega is " << value + vega << std::endl;
}

