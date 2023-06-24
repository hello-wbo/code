class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int res=nums[0],cnt=1,size=nums.size();
        for(int i=1;i<size;i++){
            if(cnt==0){
                res=nums[i];
                cnt++;
                continue;
            }
            
            if(nums[i]==res)cnt++;
            else{
                cnt--;
            }

        }
        return res;
    }
};