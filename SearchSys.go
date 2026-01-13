/*
  You are given an array of strings products and a string searchWord.
  Design a system that suggests at most three product names from products after each character of searchWord is typed. Suggested products should have common prefix with searchWord. If there are more than three products with a common prefix return the three lexicographically minimums products.
  Return a list of lists of the suggested products after each character of searchWord is typed.
*/
import "sort"

func suggestedProducts(products []string, searchWord string) [][]string {
    sort.Strings(products)

    res := make([][]string, 0, len(searchWord))
    prefix := ""

    for _, ch := range searchWord {
        prefix += string(ch)

        // Binary search for first product >= prefix
        idx := sort.SearchStrings(products, prefix)

        suggestions := []string{}
        for i := idx; i < len(products) && len(suggestions) < 3; i++ {
            if len(products[i]) < len(prefix) ||
               products[i][:len(prefix)] != prefix {
                break
            }
            suggestions = append(suggestions, products[i])
        }

        res = append(res, suggestions)
    }

    return res
}
