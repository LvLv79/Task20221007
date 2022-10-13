#include "sort.hpp"

void Sort::sort_points(vector<RotatedRect> exchange_contours)
{
    for (int i = 0; i < 4; i++)
    {
        points_x[i] = exchange_contours[i].center.x;
    }

    for (int i = 0; i < 4; i++)
    {
        points_y[i] = exchange_contours[i].center.y;
    }

    for (int i = 0; i < 4; i++)
    {
        points_sum[i] = points_x[i] + points_y[i];
        
    }
    points = bubbleSort(points_sum);
}

vector<float> Sort::bubbleSort(vector<float> &nums)
{
    int i = nums.size() - 1, j = 0;
    bool flag = true;
    for (; i > 0 && flag; i--)
    { // 如果没有发生过交换，说明剩余部分已经有序，排序完成
        flag = false;
        for (j = 0; j < i; j++)
        { //保持最右边元素已经排序
            if (nums[j] > nums[j + 1])
            { // 如果左边的数大于右边的数，则交换，保证右边的数字最大
                swap(nums[j], nums[j + 1]);
                flag = true; // 表示发生了交换
            }
        }
    }
    return nums;
}

/*int main()
{
    Solution s;
    vector<int> nums = {8,9,1,7,2,3,5,4,6,0};
    vector<int> result = s.bubbleSort(nums);
    return 0;
}*/
