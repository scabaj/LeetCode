#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
using namespace std::string_literals;


class Solution {
public:
    int longestValidParentheses(string s) {

        for (size_t n = 1; n < s.size(); ++ n)
        {
            if (s.at(n) == ')')
            {
                size_t k = n;
                while (k > 0 && s.at(k - 1) == '.')
                {
                    k -= 1;
                }
                if (k > 0 && s.at(k - 1) == '(')
                {
                    s.at(n) = s.at(k - 1) = '.';
                }
            }
        }
        // return std::count(s.begin(), s.end(), '.');

        size_t length = 0;
        size_t first = 0;
        size_t last = 0;
        while ((first = s.find_first_of('.', last)) != string::npos)
        {
            if ((last = s.find_first_not_of('.', first)) == string::npos)
            {
                if (length < s.size() - first)
                {
                    length = s.size() - first;
                }
                break;
            }

            if (length < last - first)
            {
                length = last - first;
            }
        }
        return static_cast<int>(length);//std::count(s.begin(), s.end(), '.');
    }
};

int main(int argc, char** argv)
{
    auto a = "(()";    // -> 2
    auto b = ")()())"; // -> 4
    auto c = "()(()";  // -> 2
    std::cout << a << " " << Solution().longestValidParentheses(a) << std::endl;
    std::cout << b << " " << Solution().longestValidParentheses(b) << std::endl;
    std::cout << c << " " << Solution().longestValidParentheses(c) << std::endl;
    return EXIT_SUCCESS;

}
