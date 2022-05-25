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

func main() {
	strike := C.double(110.0)
	timeToMaturity := C.double(0.5) //years
	spot := C.double(100.0)
	riskFree := C.double(.03)
	dividendYield := C.double(0.0)
	sigma := C.double(.20)

	value := C.double(0.0)
	delta := C.double(0.0)
	gamma := C.double(0.0)
	vega := C.double(0.0)
	theta := C.double(0.0)

	C.CalcGreeks(strike, timeToMaturity, spot, riskFree, dividendYield, sigma,
		&value, &delta, &gamma, &vega, &theta)

	fmt.Println("Value of ", strike, " call is ", value)
	fmt.Println("Delta of ", strike, " call is ", delta)
	fmt.Println("Gamma of ", strike, " call is ", gamma)
	fmt.Println("Vega of ", strike, " call is ", vega)
	fmt.Println("Theta of ", strike, " call is ", theta)
}
