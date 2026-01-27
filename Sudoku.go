package main

import "fmt"

func solveSudoku(board [][]byte) {
	solve(board)
}

func solve(board [][]byte) bool {
	for row := 0; row < 9; row++ {
		for col := 0; col < 9; col++ {
			if board[row][col] == '.' {
				for num := byte('1'); num <= '9'; num++ {
					if isValid(board, row, col, num) {
						board[row][col] = num
						if solve(board) {
							return true
						}
						board[row][col] = '.' // backtrack
					}
				}
				return false // no valid number can be placed
			}
		}
	}
	return true // all cells are filled correctly
}

func isValid(board [][]byte, row, col int, num byte) bool {
	// Check row
	for i := 0; i < 9; i++ {
		if board[row][i] == num {
			return false
		}
	}

	// Check column
	for i := 0; i < 9; i++ {
		if board[i][col] == num {
			return false
		}
	}

	// Check 3x3 sub-box
	boxRowStart := (row / 3) * 3
	boxColStart := (col / 3) * 3
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			if board[boxRowStart+i][boxColStart+j] == num {
				return false
			}
		}
	}

	return true
}

func printBoard(board [][]byte) {
	for _, row := range board {
		for _, cell := range row {
			fmt.Printf("%c ", cell)
		}
		fmt.Println()
	}
}

func main() {
	board := [][]byte{
		{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
		{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
		{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
		{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
		{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
		{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
		{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
		{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
		{'.', '.', '.', '.', '8', '.', '.', '7', '9'},
	}

	fmt.Println("Initial board:")
	printBoard(board)

	solveSudoku(board)

	fmt.Println("\nSolved board:")
	printBoard(board)
}
