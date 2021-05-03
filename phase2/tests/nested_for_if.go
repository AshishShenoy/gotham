package main

import "fmt"


var d bool = 4
for var k int = 2 ; k < 10; k = k + 1
{
	if (k == 9) {
		d = d || d
	} else {
		d = d && d
	}
}
