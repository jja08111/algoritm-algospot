#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MOD=20090711;

struct RNG {
    int seed,a,b;
    RNG(int _a, int _b) : a(_a), b(_b), seed(1983) {}
    int next() {
        int ret=seed;
        seed=((seed*(long long)a)+b)%MOD;
        return ret;
    }
};

int runningMedian(int n, RNG rng)
{
    priority_queue<int, vector<int>, less<int> > maxHeap;
    priority_queue<int, vector<int>, greater<int> > minHeap;
    int ret=0;
    
    for(int cnt=1;cnt<=n;++cnt)
    {
        if(maxHeap.size()==minHeap.size())
            maxHeap.push(rng.next());
        else
            minHeap.push(rng.next());
        
        if(!minHeap.empty() && !maxHeap.empty() && 
            minHeap.top()<maxHeap.top())
        {
            int a=maxHeap.top(), b=minHeap.top();
            maxHeap.pop(); minHeap.pop();
            maxHeap.push(b);
            minHeap.push(a);
        }
        ret=(ret+maxHeap.top())%MOD;
    }
    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int n,a,b;
        cin>>n>>a>>b;
        
        cout<<runningMedian(n,RNG(a,b))<<endl;
    }
    return 0;
}
