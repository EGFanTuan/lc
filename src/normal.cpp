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


