package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strings"
)

func checkLine(integerLine []int) bool {

	// rules:
	// must be either all increasing or all decreasing
	// any two adjacent levels differ by at least one or at most three

	// note: we should do an edge case where the first delta is 0
	// thus we need to calculate with two other value, but
	// the case will be caught later on as the delta of two values is at minimum 1
	firstDelta := integerLine[1] - integerLine[0]

	allIncreasing := true
	if firstDelta < 0 {
		allIncreasing = false
	}

	for i := 0; i < len(integerLine)-1; i++ {
		delta := integerLine[i+1] - integerLine[i]

		distance := math.Abs(float64(delta))
		if allIncreasing {
			if delta < 0 {
				return false
			}
		}
		if !allIncreasing {
			if delta > 0 {
				return false
			}
		}

		if distance > 3 {
			return false
		}
		if distance < 1 {
			return false
		}
	}

	return true
}

func checkLineDampened(integerLine []int) bool {

	if checkLine(integerLine) {
		return true
	}

	// this is a dumb solution, but at least it is still fast, and it works
	for i := 0; i < len(integerLine); i++ {
		// copy all values except i
		subArray := make([]int, len(integerLine))
		copy(subArray, integerLine)

		// remove ith element
		subArray = append(subArray[:i], subArray[i+1:]...)

		if checkLine(subArray) {
			return true
		}
	}

	return false
}

func main() {
	dat, err := os.Open("input.txt")
	if err != nil {
		fmt.Println("File reading error", err)
		return
	}
	defer dat.Close()

	scanner := bufio.NewScanner(dat)

	good_lines := 0
	bad_lines := 0

	good_lines_damped := 0
	bad_lines_damped := 0
	for scanner.Scan() {
		line_scanner := strings.Split(scanner.Text(), " ")
		integerLine := make([]int, len(line_scanner))

		for i, v := range line_scanner {
			fmt.Sscanf(v, "%d", &integerLine[i])
		}

		if checkLine(integerLine) {
			good_lines++
		} else {
			bad_lines++
		}

		if checkLineDampened(integerLine) {
			good_lines_damped++
		} else {
			bad_lines_damped++
		}
	}

	println("Good lines: ", good_lines)
	println("Bad lines: ", bad_lines)

	println("Good lines (with dampener): ", good_lines_damped)
	println("Bad lines (with dampener): ", bad_lines_damped)
}
