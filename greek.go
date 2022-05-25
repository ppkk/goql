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
	num := C.double(3.4)

	res := C.Test(num)
	fmt.Println(res)
}
