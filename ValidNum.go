import (
	"strings"
	"unicode"
)

/*Given a string s, return whether s is a valid number:
* For example, all the following are valid numbers: "2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789", while the following are not valid numbers: "abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53".
*
* Formally, a valid number is defined using one of the following definitions:
* An integer number followed by an optional exponent.
* A decimal number followed by an optional exponent.
* An integer number is defined with an optional sign '-' or '+' followed by digits.
*
* A decimal number is defined with an optional sign '-' or '+' followed by one of the following definitions:
* Digits followed by a dot '.'.
* Digits followed by a dot '.' followed by digits.
* A dot '.' followed by digits.
* An exponent is defined with an exponent notation 'e' or 'E' followed by an integer number.
* 
* The digits are defined as one or more digits.
*/

func isNumber(s string) bool {
	s = strings.TrimSpace(s) // Remove leading and trailing spaces
	if len(s) == 0 {
		return false
	}

	numSeen, dotSeen, expSeen := false, false, false
	for i, ch := range s {
		if unicode.IsDigit(ch) {
			numSeen = true
		} else if ch == '.' {
			if dotSeen || expSeen {
				return false // A decimal point cannot appear after an exponent or more than once
			}
			dotSeen = true
		} else if ch == 'e' || ch == 'E' {
			if expSeen || !numSeen {
				return false // An exponent must come after a number and appear only once
			}
			expSeen = true
			numSeen = false // Reset numSeen for exponent part
		} else if ch == '+' || ch == '-' {
			if i != 0 && (s[i-1] != 'e' && s[i-1] != 'E') {
				return false // Sign is only valid at the start or after an exponent
			}
		} else {
			return false // Invalid character found
		}
	}

	return numSeen // Ensure at least one digit exists
}
