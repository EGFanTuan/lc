#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <math.h>

using namespace std;

class a26s1{
  static vector<int> sumFourDivisorsVec;
public:
  static int countNegatives(vector<vector<int>>& grid);

  static int minimumBoxes(vector<int>& apple, vector<int>& capacity);

  static int minDeletionSize(vector<string>& strs);

  static int latestDayToCross(int row, int col, vector<vector<int>>& cells);

  int sumFourDivisors(vector<int>& nums);

  long long maxMatrixSum(vector<vector<int>>& matrix);
};