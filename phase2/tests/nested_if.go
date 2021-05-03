package main

import "fmt"


var f int = 60
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
