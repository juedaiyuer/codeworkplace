#include<stddef.h>

using namespace std;

struct ListNode{
	int val;
	ListNode *next;
	ListNode(int x):val(x), next(NULL){}
};

class Solution{
public:
      ListNode *addTwoNumbers(ListNode  *l1 , ListNode  *l2){
      	int carry = 0;
      	ListNode* tail = new ListNode(0);  // kai shi lian biao shi shu zi wei 0 de lian biao 
      	ListNode* ptr = tail;

      	while(l1 != NULL || l2 != NULL){
      		int val1=0;
      		if(l1 != NULL){
      			val1 = l1->val;
      			l1 = l1 ->next;
      		}

      		int val2 = 0;
      		if(l2 != NULL){
      			val2 = l2->val;
      			l2 = l2 ->next;
      		}

      		int tmp = val1 + val2 +carry;
      		ptr->next = new ListNode(tmp % 10) ;  // zhi liu xia ge wei shu zi 
      		carry = tmp /10 ;
      		ptr = ptr ->next;
      	}

      	if (carry == 1){
      		ptr->next = new ListNode(1);
      	}
	
	return tail->next;
	
       }
};

int main(){
	
	return 0;
}
