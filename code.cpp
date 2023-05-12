void reverse(int arr[],int L,int H){
        while(L<H){
            swap(arr[L++],arr[H--]);
        }
    }
    
    bool checkRotatedAndSorted(int arr[], int n){
        bool isNonDec;
        if(arr[0]<arr[1])
            isNonDec=true;
        else
            isNonDec=false;
        int index=-1;
        for(int i=1;i<n;i++){
            if(isNonDec && arr[i]<arr[i-1]){
                index=i;
                break
            }else if(!isNonDec && arr[i]>arr[i-1])
        }
        // Your code here
        
    }