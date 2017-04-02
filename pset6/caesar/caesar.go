package main

import (
	"fmt"
	"unicode"
)

var(
	key byte
	letters string
	upLetterForBias byte= 65
	lowLetterForBias byte = 97
	formulaNum byte = 26
	counter int = 0
	stringLength int
	CounterForBias byte
	convertLetter byte
	newLetters string
)

func main() {
	fmt.Print("Key = ")
	fmt.Scanf("%d", &key)
	letters = getLetters()
	caesarCipher()
	printing()
}

func getLetters()string {
	fmt.Print("plaintext: ")
	fmt.Scanf("%s", &letters)
	return letters
}

func caesarCipher(){
	stringLength = len(letters)

	for counter=0; counter<stringLength; counter++{
		if (unicode.IsLower(rune(letters[counter]))){
			calculateCipher(lowLetterForBias, counter)
		} else if (unicode.IsUpper(rune(letters[counter]))){
			calculateCipher(upLetterForBias, counter)
		} else {
			continue
		}
	}
}

func calculateCipher(CounterForBias byte, counter int){
	convertLetter = letters[counter]
	convertLetter = convertLetter - CounterForBias
	convertLetter = (convertLetter + key) % formulaNum
	convertLetter = convertLetter + CounterForBias
	newLetters += string(convertLetter)

}

func printing(){
	fmt.Print("ciphertext: ")
	fmt.Print(newLetters)
}