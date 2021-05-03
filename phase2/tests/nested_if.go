
package main

import "fmt"


// Nested if statement
var f int = "FFFFFFFFFF"
if (f % 3) {
	if (f % 4) {
		if (f % 5) {
			f = f % f
		}
		f = f * f
	} else {
		f = f / f
	}
}
