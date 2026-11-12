#include <vector>
using namespace std;

int removeDuplicates(vector<int> &nums)
{
    int numActual = nums[0];
    int k = 1;
    vector<int>::iterator it = nums.begin() + 1;
    while (it != nums.end())
    {
        if (*it != numActual)
        {
            numActual = *it;
            k++;
            it++;
        }
        else
        {
            nums.erase(it);
        }
    }

    return k;
}
