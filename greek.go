package main

// #cgo LDFLAGS: -L'${SRCDIR}/lib'
// #cgo LDFLAGS: -lgreek
// #include "include/greek.hxx"
import "C"

import "fmt"

func main() {
	num := C.double(3.4)

	res := C.Test(num)
	fmt.Println(res)
}
