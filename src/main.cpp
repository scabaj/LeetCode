#include <iostream>
#include <limits>
#include <vector>
#include <tuple>
#include <stack>
#include <unordered_set>

using namespace std;

using Grid = vector<vector<int>>;

namespace v1
{
    class Solution
    {
    public:
        int minPathSum(Grid &grid)
        {
            const unsigned x = 0;
            const unsigned y = 0;
            minPathSum(x, y, grid.at(y).at(x), grid);
            return m_sum;
        }

        void minPathSum(unsigned x, unsigned y, int sum, const Grid &grid)
        {
            if ((y == grid.size() - 1) && (x == grid.front().size() - 1))
            {
                if (m_sum > sum)
                {
                    m_sum = sum;
                }

                std::cout << "x:" << x << " y:" << y << " sum:" << sum << " ($)" << std::endl;
            }
            else
            {
                std::cout << "x:" << x << " y:" << y << " sum:" << sum << std::endl;

                if ((x + 1) < grid.front().size())
                {
                    minPathSum(x + 1, y, sum + grid.at(y).at(x + 1), grid);
                }
                if (y + 1 < grid.size())
                {
                    minPathSum(x, y + 1, sum + grid.at(y + 1).at(x), grid);
                }
            }
        }

    protected:
        int m_sum = std::numeric_limits<int>::max();
    };
}

namespace v2
{
    class Solution
    {
    public:
        int minPathSum(Grid &grid)
        {
            const unsigned h = grid.size();
            const unsigned w = grid.front().size();

            for (unsigned y = 1; y < h; ++y)
            {
                grid.at(y).at(0) += grid.at(y - 1).at(0);
            }
            for (unsigned x = 1; x < w; ++x)
            {
                grid.at(0).at(x) += grid.at(0).at(x - 1);
            }
            for (unsigned y = 1; y < h; ++y)
            {
                for (unsigned x = 1; x < w; ++x)
                {
                    grid.at(y).at(x) += std::min(grid.at(y).at(x - 1), grid.at(y - 1).at(x));
                }
            }
            return grid.back().back();
        }
    };
}

int main(int argc, char **argv)
{
    using namespace v2;
    Grid a{{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    std::cout << "a) path min sum: " << Solution().minPathSum(a) << std::endl;
    Grid b{{1, 2, 3}, {4, 5, 6}};
    std::cout << "b) path min sum: " << Solution().minPathSum(b) << std::endl;
    Grid c{{1, 2}, {1, 1}};
    std::cout << "c) path min sum: " << Solution().minPathSum(c) << std::endl;
    Grid d{// 16 x 18
           {3, 8, 6, 0, 5, 9, 9, 6, 3, 4, 0, 5, 7, 3, 9, 3},
           {0, 9, 2, 5, 5, 4, 9, 1, 4, 6, 9, 5, 6, 7, 3, 2},
           {8, 2, 2, 3, 3, 3, 1, 6, 9, 1, 1, 6, 6, 2, 1, 9},
           {1, 3, 6, 9, 9, 5, 0, 3, 4, 9, 1, 0, 9, 6, 2, 7},
           {8, 6, 2, 2, 1, 3, 0, 0, 7, 2, 7, 5, 4, 8, 4, 8},
           {4, 1, 9, 5, 8, 9, 9, 2, 0, 2, 5, 1, 8, 7, 0, 9},
           {6, 2, 1, 7, 8, 1, 8, 5, 5, 7, 0, 2, 5, 7, 2, 1},
           {8, 1, 7, 6, 2, 8, 1, 2, 2, 6, 4, 0, 5, 4, 1, 3},
           {9, 2, 1, 7, 6, 1, 4, 3, 8, 6, 5, 5, 3, 9, 7, 3},
           {0, 6, 0, 2, 4, 3, 7, 6, 1, 3, 8, 6, 9, 0, 0, 8},
           {4, 3, 7, 2, 4, 3, 6, 4, 0, 3, 9, 5, 3, 6, 9, 3},
           {2, 1, 8, 8, 4, 5, 6, 5, 8, 7, 3, 7, 7, 5, 8, 3},
           {0, 7, 6, 6, 1, 2, 0, 3, 5, 0, 8, 0, 8, 7, 4, 3},
           {0, 4, 3, 4, 9, 0, 1, 9, 7, 7, 8, 6, 4, 6, 9, 5},
           {6, 5, 1, 9, 9, 2, 2, 7, 4, 2, 7, 2, 2, 3, 7, 2},
           {7, 1, 9, 6, 1, 2, 7, 0, 9, 6, 6, 4, 4, 5, 1, 0},
           {3, 4, 9, 2, 8, 3, 1, 2, 6, 9, 7, 0, 2, 4, 2, 0},
           {5, 1, 8, 8, 4, 6, 8, 5, 2, 4, 1, 6, 2, 2, 9, 7}};
    std::cout << "d) path min sum: " << Solution().minPathSum(d) << std::endl;
    return EXIT_SUCCESS;
}
