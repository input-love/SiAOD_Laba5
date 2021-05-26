#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <algorithm>

struct Detail
{
	int ta;
	int tb;
	int tc;
};

std::vector<Detail> vec;
int64_t cnt = 0;

int detail_procesing(std::vector<int>& order)
{
	cnt++;

	int res = 0;

	std::queue<Detail> a;
	std::queue<Detail> b;
	std::queue<Detail> c;

	for (int i : order)
	{
		a.push(vec[i]);
	}

	while (!(a.empty() && b.empty() && c.empty()))
	{
		int tmp = INT32_MAX;

		tmp = (a.empty() ? tmp : std::min(tmp, a.front().ta));
		tmp = (b.empty() ? tmp : std::min(tmp, b.front().tb));
		tmp = (c.empty() ? tmp : std::min(tmp, c.front().tc));

		if (!a.empty())
			a.front().ta -= tmp;
		if (!b.empty())
			b.front().tb -= tmp;
		if (!c.empty())
			c.front().tc -= tmp;

		if (!a.empty() && a.front().ta == 0)
		{
			b.push(a.front());
			a.pop();
		}

		if (!b.empty() && b.front().tb == 0)
		{
			c.push(b.front());
			b.pop();
		}

		if (!c.empty() && c.front().tc == 0)
		{
			c.pop();
		}

		res += tmp;
	}
	return res;
}

std::vector<Detail> randomize(int n, int d)
{
	std::vector<Detail> res(n);
	for (int i = 0; i < res.size(); ++i)
	{
		res[i].ta = 1 + (rand() % d);
		res[i].tb = 1 + (rand() % d);
		res[i].tc = 1 + (rand() % d);
	}
	return res;
}

void print(int result_time, int ans, std::vector<int> arr)
{
	std::cout << "Время работы: " << result_time << "мс" << std::endl;
	std::cout << "Колличество вызовов: " << cnt << std::endl;
	std::cout << ans << std::endl;
	for (int i = 0; i < arr.size(); ++i)
	{
		std::cout << arr[i] + 1 << " | ";
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int n;
	std::cin >> n;
	vec = std::vector<Detail>(10);
	std::vector<int> res(n);

	int d;
	std::cin >> d;
	vec = randomize(n, d);
	for (int i = 0; i < n; ++i)
	{
		res[i] = i;
	}

	std::vector<int> tmp = res;

	unsigned int start = clock();

	int ans = INT32_MAX;
	do
	{
		int count = detail_procesing(tmp);
		if (count < ans)
		{
			res = tmp;
			ans = count;
		}

	} while (std::next_permutation(tmp.begin(), tmp.end()));

	unsigned int stop = clock();

	print(stop - start, ans, res);

	return 0;
}