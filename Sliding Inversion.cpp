#include <bits/stdc++.h>
#include <utility>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


using namespace std;

typedef long long LL;
typedef pair<LL, LL> pii;

const LL MaxN = 500 * 1000;
LL a[MaxN + 10];


class FenwTree
{
    private:
    vector<LL> t;
    LL maxNum;

    public:
    void init (LL n)
    {
        maxNum = n;
        t.assign(maxNum, 0);
    }

    LL sum(LL r)
    {
        LL result = 0;
        for (; r >= 0; r = (r & (r+1)) - 1)
            result += t[r];
        return result;
    }

    void inc(LL i, LL delta)
    {
        for (; i < maxNum; i = (i | (i+1)))
            t[i] += delta;
    }

    LL sum(LL l, LL r)
    {
        return sum (r) - sum (l-1);
    }
};

class FenwTreeRange
{
    private:
    vector<LL> dataMul, dataAdd;
    LL maxNum;
	void update(LL at, LL mul, LL add)
	{
		while (at < maxNum)
		{
			dataMul[at] += mul;
			dataAdd[at] += add;
			at |= (at + 1);
		}
	}

    public:
    void init (LL n)
    {
        maxNum = n;
        dataMul.assign(maxNum, 0);
        dataAdd.assign(maxNum, 0);
    }


	void inc(LL left, LL right, LL delta)
	{
		update(left, delta, -delta * (left - 1));
		update(right, -delta, delta * right);
	}


	LL sum(LL at)
	{
		LL mul = 0;
		LL add = 0;
		LL start = at;
		while (at >= 0) {
			mul += dataMul[at];
			add += dataAdd[at];
			at = (at & (at + 1)) - 1;
		}
		return mul * start + add;
	}

	LL val(LL at)
	{
	    return sum(at) - sum(at-1);
	}
};



void compress(LL n)
{
    set<LL> s;
    map<LL, LL> cnt;
    map<LL, LL> mp;
    for (LL i = 0; i < n; i++)
    {
        s.insert(a[i]);
        cnt[a[i]]++;
    }

    {
        LL i = 1;
        while (s.size())
        {
            mp[*s.begin()] = i;
            i += cnt[*s.begin()];
            s.erase(s.begin());
        }
    }

    for (LL i = 0; i < n; i++)
        a[i] = mp[a[i]]++;

/*
    cout << endl << endl;
    for (LL i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl << endl;
*/
}

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    LL n, m;
    cin >> n >> m;

    for (LL i = 0; i < n; i++)
        cin >> a[i];

    compress(n);

    LL ans = 0;

    FenwTree cnt;
    FenwTreeRange sumCount;
    sumCount.init(n+5);
    cnt.init(n+5);
    LL negSum = 0;
    for (LL i = n-1; i >= 0; i--)
    {
        if (i+m < n)
        {
            cnt.inc(a[i+m], -1);
            LL val = sumCount.val(a[i+m]);
            sumCount.inc(a[i+m], a[i+m], -negSum - val);
        }
        cnt.inc(a[i], 1);

        LL exist = a[i] - cnt.sum(a[i]-1);
        LL sum = sumCount.sum(a[i] - 1);
        LL add = sum + exist * negSum;
        ans += add;

        {
            LL val = sumCount.val(a[i]);
            sumCount.inc(a[i], a[i], -val);
        }

        //if (i+m < n) sumCount.inc(a[i], a[i], min(m, i+1));
        //else
        {
            LL start = max(i-m+1, 0LL);
            LL finish = min(n-m, i);
            sumCount.inc(a[i], a[i], finish - start + 1);
        }

        if (i + m <= n)
        {
            sumCount.inc(0, n, -1);
            negSum++;
        }
/*
        cout << i << endl;
        cout << add << " " << sum << endl;
        for (LL i = 0; i <= n; i++)
            cout << i << " ";
        cout << endl;
        for (LL i = 0; i <= n; i++)
            cout << sumCount.val(i) << " ";
        cout << endl;
        cout << "**********" << endl << endl;
*/
    }

    cout << ans << endl;
	return 0;
}
