package main

import (
	"fmt"
	"unicode"
	"bufio"
	"os"
)

var(
	letters string
	counter = 0;
	initials string
	space byte = 32
)

func main() {
	letters = getLetters()
	getInitials()
	printing()
}

func getLetters()string {
	fmt.Print("Name: ")
	letters := bufio.NewScanner(os.Stdin)
	letters.Scan()
	return letters.Text()
}

func getInitials(){
	for counter = 0; counter<len(letters); counter++ {
		if ((unicode.IsLower(rune(letters[counter]))) || (unicode.IsUpper(rune(letters[counter])))) {
			initials += string(letters[counter])
			for {
				if (byte(letters[counter])== space){
					break
				}
			counter++
			}
		}
	}
}

func printing(){
	fmt.Print("Initials: ")
	fmt.Print(initials)

}


