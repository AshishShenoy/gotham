package main

import "fmt"


// if-else statement
var a int = 5
if ( a > 10 ) {
	var aa int = true || false && -40
	var ab int = 40 + 50
	var ac int = 5
}  else {
	var ba string = "Hello"
}

// if-else-if statement
var b float32 = 3.5
if ( b < 4.2 ) {
	var ca bool = false
} else if ( b > 6.9 ) {
	var ba int = 69 * 420 / 666
}

// for loop
var c float32 = 1.1
for var j float32 = 4.2 ; j < 6.9; j = j + 0.1
{
	c = c + 0.7
}

// Nested conditionals and loops
var d bool = 4
for var k int = 2 ; k < 10; k = k + 1
{
	if (k == 9) {
		d = d || d
	} else {
		d = d && d
	}
}

// Nested loops
var e int = 5
for var l int = 10 ; l > 1 ; l = l - 1
{
	for var m int = 5 ; m > 2 ; m = m % 2
	{
		e = e * 3
	}
}

// Nested if statement
var f int = 12
if (f % 3) {
	if (f % 4) {
		f = f * f
	} else {
		f = f / f
	}
}

func main() int {
	var toobee bool = true
	toobee = toobee || ! toobee
}
