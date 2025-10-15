# StringCalculator Test Specification

| **Test ID** | **Test Description** | **Input String** | **Expected Output / Behavior** | **Notes** |
|--------------|----------------------|------------------|--------------------------------|------------|
| **TC01** | Return 0 for empty input | `""` | `0` | Base case |
| **TC02** | Return single number as sum | `"5"` | `5` | Single number only |
| **TC03** | Sum of two comma-separated numbers | `"1,2"` | `3` | Default delimiter `,` |
| **TC04** | Handle multiple comma-separated numbers | `"1,2,3,4,5"` | `15` | Any number of inputs |
| **TC05** | Support new line `\n` as delimiter | `"1\n2,3"` | `6` | Mix of `,` and `\n` |
| **TC06** | Ignore invalid format `"1,\n"` | `"1,\n"` | *Invalid (not tested)* | Mentioned as “not OK”, but no validation needed |
| **TC07** | Support custom single-character delimiter | `"//;\n1;2"` | `3` | Custom delimiter is `;` |
| **TC08** | Support custom multi-character delimiter | `"//[***]\n1***2***3"` | `6` | Custom delimiter is `***` |
| **TC09** | Support multiple numbers with custom delimiter | `"//;\n1;2;3;4"` | `10` | Same delimiter across all numbers |
| **TC10** | Throw exception for single negative number | `"1,-2,3"` | Exception → `"negatives not allowed: -2"` | Negative numbers not allowed |
| **TC11** | Throw exception for multiple negative numbers | `"1,-2,-3,4"` | Exception → `"negatives not allowed: -2, -3"` | List all negatives in message |
| **TC12** | Ignore numbers greater than 1000 | `"2,1001"` | `2` | 1001 ignored |
| **TC13** | Include number 1000 in sum | `"1000,2"` | `1002` | Only numbers >1000 ignored |
| **TC14** | Custom delimiter and newline combination | `"//;\n1;2\n3"` | `6` | Both `;` and `\n` work |
| **TC15** | Custom delimiter with long symbol mix | `"//[###]\n1###2###3###4"` | `10` | Multi-length custom delimiter |
| **TC16** | Custom delimiter with negative number | `"//[***]\n1***-2***3"` | Exception → `"negatives not allowed: -2"` | Exception check with custom delimiter |
| **TC17** | Multiple delimiters of any length (optional extension) | `"//[*][%]\n1*2%3"` | `6` | If extended support added later |
