#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>


void readDataset(const std::string& filename, std::vector<int>& left, std::vector<int>& right) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    int num1, num2;
    while (file >> num1 >> num2) {
        left.push_back(num1);
        right.push_back(num2);
    }

    file.close();
}
//part1
void sortVectors(std::vector<int>& left_vect, std::vector<int>& right_vect)
{
    std::sort(left_vect.begin(), left_vect.end());
    std::sort(right_vect.begin(), right_vect.end());
}

int calculateTotalDistance(const std::vector<int>& left_vect, const std::vector<int>& right_vect)
{
    if (left_vect.size() != right_vect.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }

    int total_distance = 0;
    for (size_t i=0; i<left_vect.size(); i++)
    {
        total_distance += std::abs(left_vect[i] - right_vect[i]);
    }

    return total_distance;
}

//part2
int calculateSimilarityScore(const std::vector<int>& left, const std::vector<int>& right)
{
    std::unordered_map<int, int> right_count;
    for (int num: right)
    {
        right_count[num]++;
    }

    int similarity_score = 0;
    for (int num : left) {
        similarity_score += num * right_count[num];
    }
    return similarity_score;
}

int main()
{
    std::vector<int> left, right;
    std::string filename = "data.csv";

    try
    {
        readDataset(filename, left, right);
        int similarityScore = calculateSimilarityScore(left, right);
        std::cout << "Similarity Score: " << similarityScore << "\n";
        sortVectors(left, right);
        int totalDistance = calculateTotalDistance(left, right);
        std::cout << "Total Distance: " << totalDistance << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
    }
    return 0;
}
