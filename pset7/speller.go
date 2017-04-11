package main

import (
	"io/ioutil"
	"fmt"
	"strings"
	"unicode"
	"time"
	"log"
)

func main() {
	dictionary := string(getFile("dictionaries/large"))
	dictionaryMap := DictionaryMap(dictionary)
	text := strings.ToLower(string(getFile("texts/alice.txt")))
	textArr:= getWordsFromText(text)
	fmt.Println("Words misspelled: ",getMisspellings(dictionaryMap,textArr))

}

func getFile(filename string) []byte{
	defer timeCalc(time.Now(), "load from "+filename)
	file, err := ioutil.ReadFile(filename)
	if err != nil {
		fmt.Print(err)
	}
	return file
}

func DictionaryMap(text string) map[string]string {
	defer timeCalc(time.Now(), "make dictionary")
	wordsInDictionary:=0
	wordsMap := make(map[string]string)
	str := strings.Split(text, "\n")
	for counter:= range str{
		wordsMap[str[counter]] = str[counter]
		wordsInDictionary++
	}
	printing("Words in Dictionary", wordsInDictionary)
	return wordsMap
}

func getWordsFromText(text string) []string {
	defer timeCalc(time.Now(), "load words")
	wordsInText:=0
	var words []string
	word := ""
	for _, value := range text {
		if unicode.IsLetter(value) || (value == '\'' && len(word) > 0) {
			word += string(value)
		} else if unicode.IsDigit(value) {
			word = ""
		} else if len(word) > 0 {
			words = append(words,word)
			word = ""
			wordsInText++
		}

	}
	printing("Words in text", wordsInText)
	return words
}

func getMisspellings(dictionary map[string]string, text []string) int {
	defer timeCalc(time.Now(), "misspellings counting")
	misspellings := 0
	chanelForMisspellings := make (chan bool)
	for _,v := range text{
		go checkWord(chanelForMisspellings, v, dictionary)
	}
	for range text{
		if <-chanelForMisspellings{
			misspellings++
		}
	}
	close(chanelForMisspellings)
	return misspellings
}

func checkWord(chanelForMisspellings chan bool, word string, dictionary map[string]string) {
	if dictionary[word] != word {
		chanelForMisspellings <- true
	} else {
		chanelForMisspellings <- false
	}
}
func timeCalc(start time.Time, name string) {
	log.Printf("%s = %s", name, time.Since(start))
}

func printing(name string, value int){
	fmt.Printf("%s = %d\n", name, value)
}