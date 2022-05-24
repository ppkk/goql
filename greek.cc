#include <iostream>
#include <cstdlib>
#include <ql/quantlib.hpp>

using namespace QuantLib;

int main() 
{
    Real strike = 110.0;
    Real timeToMaturity = .5; //years
    Real spot = 100.0;
    Rate riskFree = .03;
    Rate dividendYield = 0.0;
    Volatility sigma = .20;

    //QuantLib requires sigma * sqrt(T) rather than just sigma/volatility
    Real vol = sigma * std::sqrt(timeToMaturity);

    //calculate dividend discount factor assuming continuous compounding (e^-rt)
    DiscountFactor growth = std::exp(-dividendYield * timeToMaturity);

    //calculate payoff discount factor assuming continuous compounding 
    DiscountFactor discount = std::exp(-riskFree * timeToMaturity);

    //instantiate payoff function for a call 
    ext::shared_ptr<PlainVanillaPayoff> vanillaCallPayoff = 
        ext::shared_ptr<PlainVanillaPayoff>(new PlainVanillaPayoff(Option::Type::Call, strike));

    BlackScholesCalculator bsCalculator(vanillaCallPayoff, spot, growth, vol, discount);
    std::cout << "Value of 110.0 call is " << bsCalculator.value() << std::endl;
    std::cout << "Delta of 110.0 call is " << bsCalculator.delta() << std::endl;
    std::cout << "Gamma of 110.0 call is " << bsCalculator.gamma() << std::endl;
    std::cout << "Vega of 110.0 call is "  << bsCalculator.vega(timeToMaturity) / 100. << std::endl;
    std::cout << "Theta of 110.0 call is " << bsCalculator.thetaPerDay(timeToMaturity) << std::endl;

    Real changeInSpot = 1.0;
    BlackScholesCalculator bsCalculatorSpotUpOneDollar(Option::Type::Call, strike, spot + changeInSpot, growth, vol, discount);
    std::cout << "Value of 110.0 call (spot up $" << changeInSpot << ") is " <<  bsCalculatorSpotUpOneDollar.value() << std::endl;
    std::cout << "Value of 110.0 call (spot up $" << changeInSpot << ") estimated from delta is " <<  (bsCalculator.value() + bsCalculator.delta() * changeInSpot) << std::endl;

    //use a Taylor series expansion to estimate the new price of a call given delta and gamma
    std::cout << "Value of 110.0 call (spot up $" << changeInSpot << ") estimated from delta and gamma is " << (bsCalculator.value() + (bsCalculator.delta() * changeInSpot) + (.5 * bsCalculator.gamma() * changeInSpot)) << std::endl;

    //calculate new price of a call given a one point change in volatility
    Real changeInSigma = .01;
    BlackScholesCalculator bsCalculatorSigmaUpOnePoint(Option::Type::Call, strike, spot, growth, (sigma + changeInSigma) * std::sqrt(timeToMaturity) , discount);
    std::cout << "Value of 110.0 call (sigma up " << changeInSigma << ") is " << bsCalculatorSigmaUpOnePoint.value() << std::endl;

    //estimate new price of call given one point change in volatility using vega
    std::cout << "Value of 110.0 call (sigma up " << changeInSigma << ") estimated from vega) is " << (bsCalculator.value() + (bsCalculator.vega(timeToMaturity)/100)) << std::endl;

}

