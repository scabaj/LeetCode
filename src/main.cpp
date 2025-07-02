#include <iostream>
#include <variant>
#include <vector>

using namespace std;

using Matrix = vector<vector<int>>;

enum class Order
{
    Unmutable,
    LeftToRight,
    RightToLeft,
    TopToBottom,
    BottomToTop
};

template <Order order = Order::Unmutable>
struct Indexer
{
    Indexer(int x, int y) : x(x), y(y) {}

    Indexer &operator++()
    {
        if constexpr (order == Order::LeftToRight)
        {
            x += 1;
        }
        else if constexpr (order == Order::RightToLeft)
        {
            x -= 1;
        }
        else if constexpr (order == Order::TopToBottom)
        {
            y += 1;
        }
        else if constexpr (order == Order::BottomToTop)
        {
            y -= 1;
        }
        return *this;
    }

    // Indexer operator++(int)
    // {
    //     Indexer tmp(*this);
    //     operator++();
    //     return tmp;
    // }

    template <Order otherOrder>
    bool operator==(const Indexer<otherOrder> &that) const
    {
        return x == that.x && y == that.y;
    }

    template <Order someOrder>
    bool operator!=(const Indexer<someOrder> &other) const
    {
        return !operator==(other);
    }

    template <Order someOrder>
    friend ostream &operator<<(ostream &os, const Indexer<someOrder> &that);

    int x;
    int y;
};

template <Order order>
struct Range
{
    Indexer<order> begin;
    Indexer<order> end;
};

using RangeFromLeftToRight = Range<Order::LeftToRight>;
using RangeFromRightToLeft = Range<Order::RightToLeft>;
using RangeFromTopToBottom = Range<Order::TopToBottom>;
using RangeFromBottomToTop = Range<Order::BottomToTop>;

using AnyRange = std::variant<
    RangeFromLeftToRight,
    RangeFromRightToLeft,
    RangeFromTopToBottom,
    RangeFromBottomToTop>;

using AnyRangeVec = std::vector<AnyRange>;

AnyRangeVec makeRanges(int pos, int size)
{
    AnyRangeVec vec;
    if (size > 0)
    {
        vec.emplace_back(RangeFromTopToBottom{{pos + size, pos}, {pos + size, pos + size}});
        vec.emplace_back(RangeFromLeftToRight{{pos, pos}, {pos + size, pos}});
        vec.emplace_back(RangeFromBottomToTop{{pos, pos + size}, {pos, pos}});
        vec.emplace_back(RangeFromRightToLeft{{pos + size, pos + size}, {pos, pos + size}});
    }
    return vec;
}

template <Order someOrder>
ostream &operator<<(ostream &os, const Indexer<someOrder> &that)
{
    os << "{" << that.x << "," << that.y << "}";
    return os;
}

class Solution
{
public:
    template <typename RangeA, typename RangeB>
    void swap(Matrix &mx, RangeA &rangeA, RangeB &rangeB)
    {
        auto posA = rangeA.begin;
        auto posB = rangeB.begin;
        while (posA != rangeA.end)
        {
            std::swap(mx.at(posA.y).at(posA.x), mx.at(posB.y).at(posB.x));
            ++posA;
            ++posB;
        }
    }

    void rotate(Matrix &matrix)
    {
        const int size = static_cast<int>(matrix.size());
        for (int offset = 0; offset < (size + 1) / 2; ++offset)
        {
            const auto length = size - 2 * offset - 1;
            auto ranges = makeRanges(offset, length);
            //dbgPrint(offset, length, ranges);
            if (!ranges.empty())
            {
                auto someRangeA = ranges.begin();
                auto someRangeB = std::next(ranges.begin());
                while (someRangeB != ranges.end())
                {
                    std::visit([this, &matrix](auto &rangeA, auto &rangeB)
                    {
                        swap(matrix, rangeA, rangeB);
                    }, *someRangeA, *someRangeB);
                    ++someRangeA;
                    ++someRangeB;
                }
            }
        }
    }

    Matrix rotate(const Matrix &matrix)
    {
        Matrix mx(matrix);
        rotate(mx);
        return mx;
    }

    void dbgPrint(int offset, int length, const AnyRangeVec &ranges)
    {
        std::cout << "=================================" << std::endl;
        std::cout << "Ranges, offset:" << offset << " length:" << length << std::endl;
        if (!ranges.empty())
        {
            for (auto someRange : ranges)
            {
                std::visit([](const auto &range)
                {
                    std::cout << "------------" << std::endl;
                    for (auto it = range.begin; it != range.end; ++it)
                    {
                        std::cout << it << std::endl;
                    }
                }, someRange);
            }
        }
        else
        {
            std::cout << "------------" << std::endl;
            std::cout << "{empty}" << std::endl;
        }
    }
};

const Matrix test_case_1_input = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
const Matrix test_case_1_output = {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}};
const Matrix test_case_2_input = {{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
const Matrix test_case_2_output = {{15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11}};

int main(int argc, char **argv)
{
    // Matrix matrix = test_case_1_input;
    // Matrix matrix = test_case_2_input;
    std::cout << "test #1 " << ((Solution().rotate(test_case_1_input) == test_case_1_output) ? "succeeded" : "failed") << std::endl;
    std::cout << "test #2 " << ((Solution().rotate(test_case_2_input) == test_case_2_output) ? "succeeded" : "failed") << std::endl;

    //     Matrix matrix = test_case_1_input;
    //     // 1,2,3
    //     // 4,5,6
    //     // 7 8 9
    //
    //     Indexer<Order::LeftToRight> begin(0,0);
    //     Indexer<> end(10, 0);
    //     for (auto it = begin; it != end; )
    //     {
    //         std::cout << it << " -> " << (++it) << std::endl;
    //     }
    //
    //
    //     // Iterator a(matrix, 0, 0, 1, 0, 2, );
    //
    return EXIT_SUCCESS;
}
