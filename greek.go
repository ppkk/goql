package main

// #cgo LDFLAGS: -L'${SRCDIR}/lib'
// #cgo LDFLAGS: -Wl,--rpath-link='${SRCDIR}/lib'
// #cgo LDFLAGS: -lgreek
// #cgo LDFLAGS: -lstdc++ -lm -ldl
// #cgo LDFLAGS: -lQuantLib
// #include "include/greek.hxx"
// #include <stdlib.h>
import "C"

import "fmt"

func CalcGreeks(strike, timeToMaturity, spot, riskFree, dividendYield, sigma float64,
	value, delta, gamma, vega, theta *float64) {

	var c_value, c_delta, c_gamma, c_vega, c_theta C.double

	c_strike := C.double(strike)
	c_timeToMaturity := C.double(timeToMaturity) //years
	c_spot := C.double(spot)
	c_riskFree := C.double(riskFree)
	c_dividendYield := C.double(dividendYield)
	c_sigma := C.double(sigma)

	C.CalcGreeks(c_strike, c_timeToMaturity, c_spot, c_riskFree, c_dividendYield, c_sigma,
		&c_value, &c_delta, &c_gamma, &c_vega, &c_theta)

	*value = float64(c_value)
	*delta = float64(c_delta)
	*gamma = float64(c_gamma)
	*vega = float64(c_vega)
	*theta = float64(c_theta)
}

func main() {
	strike := 110.0
	timeToMaturity := 0.5 //years
	spot := 100.0
	riskFree := .03
	dividendYield := 0.0
	sigma := .20

	var value, delta, gamma, vega, theta float64

	CalcGreeks(strike, timeToMaturity, spot, riskFree, dividendYield, sigma,
		&value, &delta, &gamma, &vega, &theta)

	fmt.Println("Value of ", strike, " call is ", value)
	fmt.Println("Delta of ", strike, " call is ", delta)
	fmt.Println("Gamma of ", strike, " call is ", gamma)
	fmt.Println("Vega of ", strike, " call is ", vega)
	fmt.Println("Theta of ", strike, " call is ", theta)
}
