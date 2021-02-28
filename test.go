// Single line comment
/*
	Multi line comment
*/

package main

import "fmt"

var x int = 10

if (x < 10) {
    x = x + 1
} else if(x == 10){
    x = x - 1
} else if(x == 9) {
    x = 20
} else {
	x = 0
}
func main(abc int) int {
	// fmt.Println("Hello, World!");

	var var_id int

	var int1 int = 2
	var int2 int = 1 + 2

	var float2 float32 = 1.1
	if (int1 < int2) {
		int1 = int2
	} else if(int2 < int1){
		int2 = int1
	}

	for var int3 int = 0; int3 < 4; int3 + 1{ 
      print(int3)
    } 
	var str1 string = 'hello world'
	var str2 string = "hello world"

	return 0
}

main(10)