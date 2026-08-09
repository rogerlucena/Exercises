#include <cctype>  // for isdigit() below.
#include <iostream>
#include <numeric>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "tools.cpp"

using namespace std;

// Process string with operations like the one below (Apple, 2026).
// Example:
// ( + 2 5 8 ( * 2 3 ) 7 ) -> 28

// Remember: always tokenize if you can/needed (especially if having spaces - to not babysit an index and write error-prone code) and
// then process the "vector<string> tokens" consuming a deque from front by reference or using a separate stack on the fly.
// See idea of creating a "spaced" auxiliar before tokenizing (when the input is not already rightly spaced for '(' or ')') below.
// If you cannot tokenize or that is not needed (as in Basic Calculator below with all chars contiguous) - use a while and "ch = input[i++]" and
// pass the index by reference in the case of recursion for parentheses.
// Note: remember that stoi also handles well strings starting with '-' (that should convert to negative numbers).
// Note: my tokenize function is below too, and attention with "long long" to avoid overflow for multiplication acc also below.

// Obs: additional similar tricky problems with string processing and stack (like Reverse Polish Notation and Basic Calculator) also below.

// Nice solution from Claude using deque (nice idea) and .pop_front() after tokenizing:
class Solution {
public:
    int resolve(const string& expression) {
        deque<string> tokens = tokenize(expression);
        return eval(tokens);
    }

private:
    int eval(deque<string>& tokens) {
        string token = tokens.front(); tokens.pop_front();
        if (token != "(") return stoi(token); // plain number leaf

        string op = tokens.front(); tokens.pop_front(); // '+' or '*' (assuming that after an '(' necessarily an operation will follow, and not a ')')
        int result = (op == "+") ? 0 : 1;
        while (tokens.front() != ")") {
            int operand = eval(tokens);
            result = (op == "+") ? result + operand : result * operand;
        }
        tokens.pop_front(); // pop ')'
        return result;
    }

    deque<string> tokenize(const string& s) {
        string spaced;
        for (char c : s) {
            if (c == '(' || c == ')') { spaced += ' '; spaced += c; spaced += ' '; }
            else spaced += c;
        }
        istringstream iss(spaced);
        deque<string> tokens;
        string tok;
        while (iss >> tok) tokens.push_back(tok);
        return tokens;
    }
};

class SolutionMine {  // Call recursion when finding an open parentheses.
public:
    int resolve(const string& input) {
        vector<string> tokens = tokenize(input, " ");
        int i = 0;
        return helper(tokens, i);
    }

private:
    int helper(const vector<string>& tokens, int& i) {
        if(string token = tokens[i++]; token != "(") {
            return stoi(token);
        }

        int acc = 0;
        if (string token = tokens[i]; token == "+" || token == "*") {
            string op = token;
            acc = op == "+" ? 0 : 1;
            ++i;
            while (tokens[i] != ")") {
                int num = helper(tokens, i);  // The helper function itself will increment i to the next relevant position (handles both a val and a nested expression).
                acc = op == "+" ? acc + num : acc * num;
            }
        }

        ++i;  // Skip ")".
        return acc;
    }

    vector<string> tokenize(const string& input, const string& sep) {
        vector<string> ans;
        if (sep.empty()) {  // if sep is empty, input.find("", start) returns start. Adding sep.size() (0) below results in start = start, causing an infinite loop.
            ans.push_back(input);
            return ans;
        }

        size_t start = 0;  // if the input string is larger than ~2 GB (INT_MAX characters), using int for start or end would overflow, use size_t instead (a type of unsigned int).
        size_t end = input.find(sep);
        while (end != string::npos) {
            ans.push_back(input.substr(start, end - start));
            start = end + sep.size();
            end = input.find(sep, start);
        }

        ans.push_back(input.substr(start));
        return ans;
    }
};

class SolutionMineFirstVersion {  
public:
    int resolve(const string& input) {
        vector<string> tokens = tokenize(input, " ");
        stack<string> st;
        for (const string& token : tokens) {  // using tokens itself as the stack with .back() and .pop_back() would not work because it is already complete and not being built as we read with the algorithm on the fly -> thus use a separate stack. 
            st.push(token);
            if (token == ")") {
                int processed = processOneParenthesis(st);
                st.push(to_string(processed));
            }
        }

        return st.empty() ? 0 : stoi(st.top());
    }

private:
    int processOneParenthesis(stack<string>& st) {
        st.pop();  // removes ")" from the stack.
        vector<int> values = {};
        while (st.top() != "(") {
            string top = st.top();
            if (isOp(top)) {
                int acc = 0;
                if (top == "+") {
                    acc = accumulate(values.begin(), values.end(), 0);
                } else {  // case for "*" here.
                    acc = values.empty() ? 0 : accumulate(values.begin(), values.end(), 1, multiplies<int>());
                    // multiply acc grows rapidly, consider also long long to avoid overflow: `long long product = accumulate(nums.begin(), nums.end(), 1LL, multiplies<long long>());`
                }
                values = {acc};
            } else {
                values.push_back(stoi(top));
            }
            st.pop();
        }

        st.pop();  // removes "(" from the stack.
        return values.empty() ? 0 : values[0];
    }

    vector<string> tokenize(const string& input, const string& sep) {
        vector<string> ans;
        if (sep.empty()) {  // if sep is empty, input.find("", start) returns start. Adding sep.size() (0) below results in start = start, causing an infinite loop.
            ans.push_back(input);
            return ans;
        }

        size_t start = 0;  // if the input string is larger than ~2 GB (INT_MAX characters), using int for start or end would overflow, use size_t instead (a type of unsigned int).
        size_t end = input.find(sep);
        while (end != string::npos) {
            ans.push_back(input.substr(start, end - start));
            start = end + sep.size();
            end = input.find(sep, start);
        }

        ans.push_back(input.substr(start));
        return ans;
    }

    inline bool isOp(const string& token) {
        return token == "+" || token == "*";
    }
};

int main() {
	string input = "( + 2 5 8 ( * 2 ( + 1 2 1 ) ) ( + 1 6 ) 7 )";  // -> 37
	// string input = "( + 2 5 8 ( * 2 3 ) 7 )";  // -> 28

    Solution sol;
	cout << "Answer: " << sol.resolve(input) << endl;
	// printVector(tokenize(input, " "));  // testing tokenize function.

	return 0;
}


// Basic Calculator II
// https://neetcode.io/problems/basic-calculator-ii
// https://leetcode.com/problems/basic-calculator-ii (Medium)
// Remember: use stack, for + and - add to the top of the stack, for * and / immediately pop the stack
// and process to push the result back to the stack. Finally return the sum of the stack as ans. Note that
// recursion and passing a reference of the index i is only useful for the case with parentheses below (III).

// You are given a string s which represents an expression, evaluate this expression and return its value.
// The integer division should truncate toward zero.
// You may assume that the given expression is always valid. All intermediate results will be in the range of [-(2^31), (2^31)-1].

// Example 1:
// Input: s = "3+2*2"
// Output: 7

// Example 2:
// Input: s = " 3+5 / 2 "
// Output: 5

// Constraints:
// 1 <= s.length <= 300,000
// s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
// s represents a valid expression.

int calculate(string s) {
	stack<int> st;
	int i = 0;
	int num = 0;
	char op = '+';
	while (i < s.size()) {
		char c = s[i++];
		if (isdigit(c)) {
			num = num * 10 + (c - '0');
		}
		if ((!isdigit(c) && c != ' ') || i == s.size()) {  // Here, c is a new op or we reached the end of the input (note that it also needs to enter here when c is digit but i is end of input now).
			if (op == '+') {
				st.push(num);
			} else if (op == '-') {
				st.push(-num);
			} else if (op == '*') {  // Immediately process * and / with the top of the stack.
				int top = st.top();
				st.pop();
				st.push(top * num);
			} else if (op == '/') {
				int top = st.top();
				st.pop();
				st.push(top / num);
			}

			// Updates current op and resets num (no problem in the case c was digit but end of input).
			op = c;
			num = 0;	
		}
	}

	// Returns the sum of all final elements in the stack.
	int ans = 0;
	while (!st.empty()) {
		ans += st.top();
		st.pop();
	}

	return ans;
}


// Basic Calculator III (LeetCode 772 - Premium Hard)
// https://www.lintcode.com/problem/849
// https://leetcode.com/problems/basic-calculator-iii (Hard)
// https://neetcode.io/problems/basic-calculator-iii
// Implement a basic calculator to evaluate a simple expression string containing nonnegative integers,
// operators +, -, *, /, open ( and closing ) parentheses.  

// Input: A valid math expression string s (e.g., s = "2*(5+5*2)/3+(6/2+8)").  
// Rules:
// Standard operator precedence applies (* and / before + and -).
// Parentheses nested at any depth override normal priority.
// Integer division truncates toward zero (e.g., 5 / 2 = 2).
// You cannot use built-in functions like Python's eval().

// Solution Approach:
// Stack + Recursion (DFS)
// The key to handling arithmetic precedence without complex Dijkstra Shunting-Yard logic is using a Stack combined with Recursion:
// Deferring Low Priority Operations (+, -): Push values into a stack. Subtractions are pushed as negative numbers.
// Immediate Evaluation (*, /): When encountering multiplication or division, pop the top element from the stack, compute
// the result immediately with the current number, and push the result back.
// Nested Expressions ( and ): When an opening parenthesis ( is encountered, make a recursive call to process the nested
// expression. When reaching a closing parenthesis ), evaluate the sub-expression's stack and return the total sum.

// Note:
// 1) long long prevention: intermediate multiplications can exceed standard 32-bit int limits prior to division, so long long is used inside the stack.
// 2) truncation toward zero: unlike python, C++'s native division operator / truncates toward zero for negative integers by default (since C++11), matching the problem constraints out of the box.
// 3) pass index by reference (int& i): passing the string index i as a reference ensures that recursive sub-calls advance the position across the original string smoothly without needing a queue.
class SolutionBasicCalculatorIII {
public:
    int calculate(string& s) {
        int i = 0;
        return helper(s, i);
    }

private:
    int helper(const string& s, int& i) {
        vector<long long> stack;
        char op = '+';
        long long num = 0;

        while (i < s.size()) {
            char ch = s[i++];

            if (isdigit(ch)) {
                num = num * 10 + (ch - '0');
            }

            if (ch == '(') {
                // Recursively compute the value inside parentheses.
                num = helper(s, i);
            }

            // Apply operator if character is a new non-digit operator or at the end of string/expression.
            if ((!isdigit(ch) && ch != ' ') || i == s.length()) {
                if (op == '+') {
                    stack.push_back(num);
                } else if (op == '-') {
                    stack.push_back(-num);
                } else if (op == '*') {  // last seen op before current num.
                    long long top = stack.back();
                    stack.pop_back();
                    stack.push_back(top * num);
                } else if (op == '/') {
                    long long top = stack.back();
                    stack.pop_back();
                    // C++ integer division automatically truncates toward zero.
                    stack.push_back(top / num);
                }

				// Update the next op and resets num.
                op = ch;
                num = 0;
            }

            if (ch == ')') {
				// Exits the while to already process and return the sum of the values in the current stack (precessed final value/result inside that parenthesis).
                // Obs: note that the index "i" was already updated above to the first char after ')' (as wanted out of this recursive call).
				break;
            }
        }

        // Sum up all evaluated components.
        long long total = 0;
        for (long long val : stack) {
            total += val;
        }

        return static_cast<int>(total);
    }
};


// https://neetcode.io/problems/evaluate-reverse-polish-notation
// https://leetcode.com/problems/evaluate-reverse-polish-notation (Medium)
// Remember: attention to the constraints of the problem! Here, negative numbers with a leading char '-' are allowed inside tokens.

// You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.
// Evaluate the expression. Return an integer that represents the value of the expression.

// Note that:
// The valid operators are '+', '-', '*', and '/'.
// Each operand may be an integer or another expression.
// The division between two integers always truncates toward zero.
// There will not be any division by zero.
// The input represents a valid arithmetic expression in a reverse polish notation.
// The answer and all the intermediate calculations can be represented in a 32-bit integer.

// Example 1:
// Input: tokens = ["2","1","+","3","*"]
// Output: 9

// Example 2:
// Input: tokens = ["4","13","5","/","+"]
// Output: 6

// Example 3:
// Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
// Output: 22

// Constraints:
// 1 <= tokens.length <= 10^4
// tokens[i] is either an operator: "+", "-", "*", or "/", or an integer in the range [-200, 200].

int evalRPN(vector<string>& tokens) {
	stack<int> st;
	for (const string& token : tokens) {
		if (isdigit(token.back())) {  // attention with negative numbers that have a leading char '-' (verify last char then and not first).
			st.push(stoi(token));  // stoi also already properly handles negative numbers.
			continue;
		}
		
		// If here, we have an op in token -> thus pop last two fom st, do the operation and then push the result.
		int prev = st.top(); st.pop();
		int prev_prev = st.top(); st.pop();
		if (token == "+") {
			st.push(prev_prev + prev);
		} else if (token == "-") {
			st.push(prev_prev - prev);
		} else if (token == "*") {
			st.push(prev_prev * prev);
		} else if (token == "/") {
			st.push(prev_prev / prev);
		}
	}

	return st.empty() ? 0 : st.top();
}


// https://leetcode.com/problems/parsing-a-boolean-expression (Hard)
// Remember: use stack in this kind of problem.

// It is guaranteed that the given expression is valid and follows the given rules.
// expression[i] is one following characters: '(', ')', '&', '|', '!', 't', 'f', and ','.

// Example 1:
// Input: expression = "&(|(f))"
// Output: false

// Example 2:
// Input: expression = "|(f,f,f,t)"
// Output: true

// Example 3:
// Input: expression = "!(&(f,t))"
// Output: true

class SolutionBooleanExpression {
public:
    bool parseBoolExpr(string expression) {
        stack<char> st;

        for (char ch : expression) {
            if (ch == ',') continue;

            if (ch == ')') {
                bool has_true = false, has_false = false;
                while (st.top() != '(') {  // Check the elements inside to see if true or false was seen.
					char val = st.top(); st.pop();
                    if (val == 't') has_true = true;
                    if (val == 'f') has_false = true;
                }
                st.pop();  // Pop '('.

                char op = st.top();  // The operator right before '('.
                st.pop();

                if (op == '!') st.push(has_true ? 'f' : 't');
                else if (op == '&') st.push(has_false ? 'f' : 't');
                else if (op == '|') st.push(has_true ? 't' : 'f');
            } else {
                st.push(ch);
            }
        }

        return st.top() == 't';
    }
};


// ______________________________________________________________________
// (Additional below)

// https://leetcode.com/problems/parse-lisp-expression (Hard)
// Remember: tokenize and use deque to consume it by reference with .pop_front() too.

// Example 1:
// Input: expression = "(let x 2 (mult x (let x 3 y 4 (add x y))))"
// Output: 14

// Example 2:
// Input: expression = "(let x 3 x 2 x)"
// Output: 2

// Example 3:
// Input: expression = "(let x 1 y 2 x (add x y) (add x y))"
// Output: 5

// Note: A let expression takes the form "(let v1 e1 v2 e2 ... v_n e_n expr)" with a final expr to be evaluated by the end.

// Simpler solution (less babysitting the index and skipping spaces - less error-prone) from Claude:
// (Tokenizing first, using a deque which is a nice idea, and then using a hash map of stacks for the scope - accessing the last by reference using .back() below)
class SolutionLispExpression {
public:
    int evaluate(string expression) {
        deque<string> tokens = tokenize(expression);
        return eval(tokens);
    }

private:
    unordered_map<string, vector<int>> vars; // variable name -> stack of live values (nice way too)

    int eval(deque<string>& tokens) {
        string token = tokens.front(); tokens.pop_front();
        if (token != "(") return value(token);

        string op = tokens.front(); tokens.pop_front();
        int result = 0;
        vector<string> bound; // vars this "let" introduced, to unbind after

        if (op == "add") {
            result = eval(tokens) + eval(tokens);
        } else if (op == "mult") {
            result = eval(tokens) * eval(tokens);
        } else { // let
            while (true) {
                if (tokens.front() == "(") {          // final expr is itself a parenthesized expression
                    result = eval(tokens);
                    break;
                }
                string var = tokens.front(); tokens.pop_front();
                if (tokens.front() == ")") {          // var was actually the final expr (name or number)
                    result = value(var);
                    break;
                }
                vars[var].push_back(eval(tokens));    // var = val
                bound.push_back(var);
            }
            for (auto& v : bound) vars[v].pop_back();
        }
        tokens.pop_front(); // pop ")"
        return result;
    }

    int value(const string& token) {
        if (isdigit(token[0]) || token[0] == '-') return stoi(token);
        return vars[token].back();
    }

    deque<string> tokenize(const string& s) {
        string spaced;
        for (char c : s) {
            if (c == '(' || c == ')') { spaced += ' '; spaced += c; spaced += ' '; }  // Nice idea even when parentheses are not spaced.
            else spaced += c;
        }
        istringstream iss(spaced);
        deque<string> tokens;
        string tok;
        while (iss >> tok) tokens.push_back(tok);
        return tokens;
    }
};

// Older solution.
// Remember: pass index by reference in the recursion, and use a vector<hash_map> as the dynamic scope (to iterate in reverse order, and pop_back later).
class SolutionLispExpressionFirstVersion {
public:
    int evaluate(string expression) {
        vector<unordered_map<string, int>> scope;
        int i = 0;
        return parse(expression, i, scope);
    }

private:
    int parse(const string& s, int& i, vector<unordered_map<string, int>>& scope) {
        if (s[i] == '(') {
            ++i; // Skip '('
            scope.push_back({}); // New variable scope.
            
            string op = parseToken(s, i);
            int result = 0;

            if (op == "add" || op == "mult") {  // We have two operands ahead.
                int a = parse(s, i, scope);
                int b = parse(s, i, scope);
                result = op == "add" ? a + b : a * b;
            } else if (op == "let") {  // Process all pairs of var and val (and add to curr scope) until final expr.
                while (true) {
					if (s[i] == '(') {  // Case on which the last expr of let starts with '(' -> parse it recursively and return. Note that var names never start with '('.
						result = parse(s, i, scope);
						break;
					}
                    string var = parseToken(s, i);
                    if (s[i] == ')') { 
                        // If no second value follow-up and the index was updated to ')', 'var' is actually the final expression expr (either a variable or a value to parse, then return).
                        result = getValue(var, scope);
                        break;
                    }
                    int val = parse(s, i, scope);
                    scope.back()[var] = val;  // Note that .back() return a reference to the last element in scope (as wanted).
                }
            }

            ++i;  // Skip ')'.
			skipSpace(s, i);  // Also essential here.
            scope.pop_back();  // Exit last scope.
			
            return result;
        } else {
            string token = parseToken(s, i);
            return getValue(token, scope);
        }
    }

    string parseToken(const string& s, int& i) {
        int start = i;
        while (i < s.size() && s[i] != ' ' && s[i] != ')') {
            ++i;
        }
        string token = s.substr(start, i - start);
        skipSpace(s, i);
        return token;
    }

    int getValue(const string& token, const vector<unordered_map<string, int>>& scope) {
        if (isdigit(token[0]) || token[0] == '-') {  // Or just use isdigit(token.back()).
            return stoi(token);
        }
        // Search scopes backward for variable assignment.
        for (auto it = scope.rbegin(); it != scope.rend(); ++it) {
            if (it->count(token)) {
				return it->at(token);
			}
        }
        return 0;
    }

	inline void skipSpace(const string& s, int& i) {
		if (i < s.size() && s[i] == ' ') ++i;
	}
};