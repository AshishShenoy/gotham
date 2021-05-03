package main

import "fmt"

// Nested loops
var e int = 5
for var l int = 10 ; l > 1 ; l = l - 1
{
	for var m int = 5 ; m > 2 ; m = m % 2
	{
		e = e * 3
	}
}