
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

int maxLen=INT_MIN;
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        if(root==nullptr)return 0;
        int rootSum=subPath(root);
        int leftSum=maxPathSum(root->left);
        int rightSum=maxPathSum(root->right);
        maxLen=max(max(leftSum,rightSum),rootSum);
        
        return maxLen;
    }
    int subPath(TreeNode* root){//Ã»¿¼ÂÇ¸ºÊı
        if(root==nullptr)return 0;
        int cnt=root->val;
        cnt+=subPath(root->left)+subPath(root->right);
        return cnt;
    }
    
};