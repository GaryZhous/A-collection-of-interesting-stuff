#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//the upgraded version of 2Sum
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end()); // Sort the array

    for (int i = 0; i < nums.size(); ++i) {
        // Skip duplicate elements
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int target = -nums[i];
        int start = i + 1, end = nums.size() - 1;

        while (start < end) {
            int sum = nums[start] + nums[end];
            if (sum < target)
                ++start;
            else if (sum > target)
                --end;
            else {
                result.push_back({nums[i], nums[start], nums[end]});
                // Skip duplicate elements
                while (start < end && nums[start] == nums[start + 1])
                    ++start;
                while (start < end && nums[end] == nums[end - 1])
                    --end;
                ++start;
                --end;
            }
        }
    }
    return result;
}

int main(){
  vector<int> nums = {-1,0,1,2,-1,-4}; //test
  vector<vector<int>> result = threeSum(nums);
  return (0);
}
