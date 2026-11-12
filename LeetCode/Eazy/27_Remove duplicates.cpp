#include <vector>
using namespace std;

int removeElement(vector<int> nums, int val)
{
    int k = 0;
    auto it = nums.begin();

    while (it != nums.end())
    {
        if (*it == val)
            nums.erase(it);
        else
        {
            k++;
            it++;
        }
    }
    return k;
}
