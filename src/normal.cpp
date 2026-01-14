#include <normal.hpp>

#define s26 a26s1

auto s26::countNegatives(vector<vector<int>>& grid) -> int {
  int m=grid.size(), n=grid[0].size();
  int ans = 0;
  int l=m-1, r=0;
  while(l>=0 && r<n){
    while(l>=0 && r<n && grid[l][r] >= 0)
      r++;
    if(l<m && r<n)
      ans+=n-r;
    l--;  
  }
  return ans;
}

auto s26::minimumBoxes(vector<int>& apple, vector<int>& capacity) -> int{
  sort(capacity.begin(), capacity.end());
  int total = 0;
  for(int a:apple)
    total += a;
  int i=capacity.size() - 1;
  while(i>=0 && total>0)
    total -= capacity[i--];
  return capacity.size() - i - 1;
}

auto s26::minDeletionSize(vector<string>& strs) -> int{
  int ssize = strs[0].length(), n = strs.size();
  int ans = 0;
  for(int i=0;i<ssize;i++){
    char lst = strs[0][i];
    for(int j=0;j<n;j++){
      if(strs[j][i] < lst){
        ans++;
        break;
      }
      lst = strs[j][i];
    }
  }
  return ans;
}

auto s26::latestDayToCross(int row, int col, vector<vector<int>>& cells) -> int{
  int r = cells.size()+1, l = 1, lst = 0;
  vector<vector<int>> dir = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
  vector<vector<bool>> road(row+1, vector<bool>(col+1, true));
  auto check = [&cells, &road, &dir, &lst, row, col](int mid) -> bool {
    queue<pair<int, int>>q;
    vector<vector<bool>> vis(row + 1, vector<bool>(col + 1, false));
    // for(int i=0;i<mid;i++)
    //   mp[cells[i][0]].emplace(cells[i][1]);
    if(mid > lst){
      for(int i=lst;i<mid;i++)
        road[cells[i][0]][cells[i][1]] = false;
    }
    else{
      for(int i=lst-1;i>=mid;i--)
        road[cells[i][0]][cells[i][1]] = true;
    }
    lst = mid;
    for(int i=1;i<=col;i++){
      if(road[1][i]){
        q.emplace(make_pair(1, i));
        vis[1][i] = true;
      }
    }
    while(!q.empty()){
      auto [rw, cl] = q.front();
      q.pop();
      if(rw == row) return true;
      for(auto& d:dir){
        int rwc=rw+d[0], clc=cl+d[1];
        if(rwc>0&&rwc<=row && clc>0&&clc<=col && road[rwc][clc]){
          if(!vis[rwc][clc]){
            vis[rwc][clc] = true;
            q.emplace(make_pair(rwc, clc));
          }
        }
      }
    }
    return false;
  };
  while(l<r){
    int mid = l+(r-l)/2;
    if(check(mid))
      l = mid + 1;
    else
      r = mid;
  }
  return l - 1;
}

auto s26::sumFourDivisors(vector<int>& nums) -> int{
  const int r = 1e5;
  if(sumFourDivisorsVec.empty()){
    sumFourDivisorsVec.reserve(r+1);
    sumFourDivisorsVec.emplace_back(0);
    for(int cur=1;cur<=r;cur++){
      auto total = 0, count = 0;
      auto maxi = (int)sqrt((double)cur);
      for(int i=1;i<=maxi;i++){
        if(cur%i==0){
          if(i==cur/i){
            total++;
            count+=i;
          }
          else{
            total+=2;
            count+=i+cur/i;
          }
        }
        if(total>4) break;
      }
      if(total==4) sumFourDivisorsVec.emplace_back(count);
      else sumFourDivisorsVec.emplace_back(0);
    }
  }
  int ans=0;
  for(auto n:nums) ans+=sumFourDivisorsVec[n];
  return ans;
}

auto s26::maxMatrixSum(vector<vector<int>>& matrix) -> long long{
  long long ans=0, neg_sum=0;
  int mini=INT_MAX, maxi=INT_MIN, count=0;
  for(auto& row:matrix){
    for(int num:row){
      if(num>0){
        mini = min(mini, num);
        ans+=num;
      }
      else{
        neg_sum+=num;
        count++;
        maxi=max(maxi, num);
      }
    }
  }
  if(count%2==0) return ans-neg_sum;
  ans -= neg_sum;
  ans += maxi;
  int last=maxi;
  if(abs(last) > mini) return ans-mini*2+abs(last);
  else return ans+last;
}

auto s26::maxLevelSum(TreeNode* root) -> int{
  int maxi = INT_MIN, level = 1, ans = 1;
  queue<TreeNode*>q;
  q.emplace(root);
  while(!q.empty()){
    int node_count=q.size(), sum=0;
    while(node_count>0){
      auto node = q.front();
      q.pop();
      sum+=node->val;
      if(node->left!=nullptr) q.emplace(node->left);
      if(node->right!=nullptr) q.emplace(node->right);
      node_count--;
    }
    if(sum>maxi){
      maxi=sum;
      ans=level;
    }
    level++;
  }
  return ans;
}

auto s26::maxProduct(TreeNode* root) -> int{
  long long mod=1e9+7, ans = INT_MIN;
  int l=0, r=0, diff=INT_MAX;
  long long sum=0;
  queue<TreeNode*>q;
  q.emplace(root);
  while(!q.empty()){
    auto node=q.front();
    q.pop();
    sum+=node->val;
    if(node->left!=nullptr) q.emplace(node->left);
    if(node->right!=nullptr) q.emplace(node->right);
  }
  auto func=[&](auto&& func, TreeNode* node) -> int {
    if(node==nullptr) return 0;
    int l_val=func(func, node->left);
    int r_val=func(func, node->right);
    ans = max(ans, (sum-l_val)*l_val);
    ans = max(ans, (sum-r_val)*r_val);
    return node->val+l_val+r_val;
  };
  func(func, root);
  return ans%mod;
}

auto s26::maxDotProduct(vector<int>& nums1, vector<int>& nums2) -> int{
  int m=nums1.size(), n=nums2.size();
  int ans=INT_MIN;

  vector<vector<int>>row_maxi(2, vector<int>(n+1, 0));

  for(int i=1;i<=m;i++){
    int maxi_row=0;
    for(int j=1;j<=n;j++){
      int cur=nums1[i-1]*nums2[j-1];
      int tmp=cur+maxi_row;
      ans=max(ans, tmp);
      row_maxi[(1+i)%2][j] = max(tmp, row_maxi[i%2][j]);
      maxi_row=max(maxi_row, row_maxi[i%2][j]);
    }
  }

  return ans;
}

auto s26::subtreeWithAllDeepest(TreeNode* root) -> TreeNode*{
  int max_depth=0;
  vector<int>mp(501, -1);
  auto find_maxi = [&](auto&& rec, TreeNode* node, int cur_depth=0) -> int {
    if(node==nullptr) return cur_depth;
    int l=rec(rec, node->left, cur_depth+1), r=rec(rec, node->right, cur_depth+1);
    int m=max(l, r);
    mp[node->val]=m;
    // max_depth=max(max_depth, node->val);
    return m;
  };
  max_depth=find_maxi(find_maxi, root);
  queue<TreeNode*>q;
  q.emplace(root);
  while(!q.empty()){
    int sz=q.size();
    while(sz>0){
      sz--;
      auto node=q.front();
      q.pop();
      if(node==nullptr) continue;
      if(mp[node->val]==max_depth){
        if(node->left==nullptr && node->left==node->right) return node;
        else if(node->left!=nullptr && node->right!=nullptr && mp[node->right->val] == mp[node->left->val]) return node;
      }
      q.emplace(node->left);
      q.emplace(node->right);
    }
  }
  return root;
}

auto s26::minTimeToVisitAllPoints(vector<vector<int>>& points) -> int {
  int ans=0;
  for(int i=1;i<points.size();i++){
    auto& cur=points[i], &prev=points[i-1];
    int ver=abs(cur[1]-prev[1]), hor=abs(cur[0]-prev[0]);
    ans+=max(ver, hor);
  }
  return ans;
}

auto s26::separateSquares(vector<vector<int>>& squares) -> double {
  double l=0, r=1e9+1;
  auto check = [&](double mid) -> bool {
    double lower=0, upper=0;
    for(auto& sq:squares){
      double u=max(0.0, sq[1]+sq[2]-mid), v=max(0.0, mid-sq[1]);
      u=min(u, (double)sq[2]);
      v=min(v, (double)sq[2]);
      lower += v*sq[2];
      upper += u*sq[2];
    }
    return upper <= lower;
  };
  while(r-l>1e-5){
    double mid=l+(r-l)/2;
    if(check(mid)) r=mid;
    else l=mid+1e-5;
  }
  return l;
}

auto s26::minimumDeleteSum(string s1, string s2) -> int {
  int m=s1.length(), n=s2.length();
  vector<vector<int>>dp(m+1, vector<int>(n+1, 0));
  for(int i=1;i<=m;i++){
    dp[i][0]=dp[i-1][0]+(int)s1[i-1];
  }
  for(int j=1;j<=n;j++){
    dp[0][j]=dp[0][j-1]+(int)s2[j-1];
  }
  for(int i=1;i<=m;i++){
    for(int j=1;j<=n;j++){
      dp[i][j]=min(
        {dp[i-1][j-1]+(s1[i-1]==s2[j-1]?0:(int)s1[i-1]+(int)s2[j-1]),
         dp[i-1][j]+(int)s1[i-1],
         dp[i][j-1]+(int)s2[j-1]}
      );
    }
  }
  return dp[m][n];
}

auto s26::maximalRectangle(vector<vector<char>>& matrix) -> int {
  int m=matrix.size(), n=matrix[0].size(), ans=0;
  vector<vector<int>>toright(m+1, vector<int>(n+1, 0));
  for(int i=m-1;i>=0;i--){
    for(int j=n-1;j>=0;j--){
      if(matrix[i][j]=='0') continue;
      toright[i][j]=toright[i][j+1]+1;
      ans=max(ans, toright[i][j]);
      int k=i+1, min_width=toright[i][j];
      while(k<m && toright[k][j]>0){
        min_width=min(min_width, toright[k][j]);
        ans=max(ans, min_width*(k-i+1));
        k++;
      }
    }
  }
  return ans;
}


