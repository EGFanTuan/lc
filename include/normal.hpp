#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <math.h>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class a26s1{
  static vector<int> sumFourDivisorsVec;
public:
  static int countNegatives(vector<vector<int>>& grid);

  static int minimumBoxes(vector<int>& apple, vector<int>& capacity);

  static int minDeletionSize(vector<string>& strs);

  static int latestDayToCross(int row, int col, vector<vector<int>>& cells);

  int sumFourDivisors(vector<int>& nums);

  long long maxMatrixSum(vector<vector<int>>& matrix);

  int maxLevelSum(TreeNode* root);

  int maxProduct(TreeNode* root);
  
  int maxDotProduct(vector<int>& nums1, vector<int>& nums2);

  TreeNode* subtreeWithAllDeepest(TreeNode* root);
};