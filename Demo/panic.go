package main

import "fmt"

func main() {

	defer func() {
		err := recover()
		if err != nil {
			fmt.Printf("recover: %v", err)
		} else {
			fmt.Printf("defer: no error")
		}
	}()

	fmt.Println("after me, a panic will occur")
	panic(nil)
	fmt.Println("you wont see this, since a panic is occured")
}
