// File auto-generated by StartNewDay

#include <ACSolver.ipp>
#include <Utilities.ipp>

#include <algorithm>
#include <unordered_map>
#include <vector>

#include <gtest/gtest.h>

namespace
{
    struct Solver : public ACSolver
    {
        Answer solvePartOne() override
        {
            std::vector<std::int64_t> leftList;
            std::vector<std::int64_t> rightList;

            for(const auto& line : mInput)
            {
                if(line.empty())
                {
                    break;
                }

                const auto [left, right] = [&]() -> std::pair<std::int64_t, std::int64_t>
                {
                    const auto whiteSpace = line.find_first_of(' ');
                    return {util::StringTo<std::int64_t>(line.substr(0, line.size() - whiteSpace)),
                            util::StringTo<std::int64_t>(line.substr(whiteSpace))};
                }();

                leftList.push_back(left);
                rightList.push_back(right);
            }

            std::ranges::sort(leftList);
            std::ranges::sort(rightList);

            std::int64_t totalDistance = 0;
            for(std::size_t i = 0; i < leftList.size() && i < rightList.size(); ++i)
            {
                totalDistance += std::abs(leftList[i] - rightList[i]);
            }

            return totalDistance;
        }

        Answer solvePartTwo() override
        {
            std::vector<int64_t> ids;
            std::unordered_map<std::int64_t, std::int64_t> occurrences;

            for(const auto& line : mInput)
            {
                if(line.empty())
                {
                    break;
                }

                const auto [left, right] = [&]() -> std::pair<std::int64_t, std::int64_t>
                {
                    const auto whiteSpace = line.find_first_of(' ');
                    return {util::StringTo<std::int64_t>(line.substr(0, line.size() - whiteSpace)),
                            util::StringTo<std::int64_t>(line.substr(whiteSpace))};
                }();

                ids.push_back(left);

                if(occurrences.contains(right))
                {
                    occurrences[right]++;
                }
                else
                {
                    occurrences[right] = 1;
                }
            }

            std::int64_t similarityScore = 0;
            for(const auto id : ids)
            {
                similarityScore += id * occurrences[id];
            }

            return similarityScore;
        }
    };

    Solver CreateSolver(bool useSample)
    {
        const auto inputFile = useSample ? "1_sample.txt" : "1.txt";
        Solver solver;
        solver.mInput = util::Parse(util::GetInputFile(inputFile));
        return solver;
    }
}

TEST(day_1, part_1)
{
    const auto answer = CreateSolver(false).solvePartOne();
    ASSERT_NE(answer, std::nullopt);
    EXPECT_EQ(*answer, 1223326);
    std::cout << "part one: " << *answer << std::endl;
}

TEST(day_1, part_2)
{
    const auto answer = CreateSolver(false).solvePartTwo();
    ASSERT_NE(answer, std::nullopt);
    EXPECT_EQ(*answer, 21070419);
    std::cout << "part two: " << *answer << std::endl;
}

TEST(day_1, sample_part_1)
{
    const auto answer = CreateSolver(true).solvePartOne();
    ASSERT_NE(answer, std::nullopt);
    EXPECT_EQ(*answer, 11);
}

TEST(day_1, sample_part_2)
{
    const auto answer = CreateSolver(true).solvePartTwo();
    ASSERT_NE(answer, std::nullopt);
    EXPECT_EQ(*answer, 31);
}
