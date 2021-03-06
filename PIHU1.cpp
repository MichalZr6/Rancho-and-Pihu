#include <vector>
#include <iostream>
#include <algorithm>

std::vector<unsigned int> nums;

typedef std::vector<unsigned int>::const_iterator Iter;

bool read_numbers(int limit)
{
	int number;
	nums.reserve(limit);
	for (int j = 0; j < limit; j++)
	{
		std::cin >> number;
		if (number < 1 || number > 1000000000)
			return false;
		else
			nums.push_back(number);
	}

	return true;
}

bool num_search(Iter first, Iter last, unsigned int val)
{
	if (val == 0)
		return false;

	last = std::upper_bound(first, last, val);
	
	if (first == last)
		return false;

	last--;

	while (first != last)
	{
		if (*first + *last == val)
			return true;
		else if (val - *last > *first)
			first++;
		else
			last--;
	}

	return false;
}

int main()
{
	int n, tests;
	unsigned int p;
	std::cin >> tests;

	if (tests > 15 || tests < 1)
		return 0;

	std::vector<bool> ret_vector(tests, false);

	for (int i = 0; i < tests; i++)
	{
		nums.clear();

		std::cin >> n;
		if (n < 3 || n > 1000)
			continue;

		if (!read_numbers(n))
			continue;

		std::cin >> p;
		if (p < 1 || p > 3000000000)
			continue;

		std::sort(nums.begin(), nums.end());

		auto first = nums.cbegin();
		auto last = std::upper_bound(first, nums.cend(), p);
		last--;

		while (last > first + 1 && !num_search(first, last, p - static_cast<int>(*last)))
			last--;

		if (last > first + 1)
			ret_vector[i] = true;
	}

	for (auto it : ret_vector)
	{
		if (it) std::cout << "YES\n";
		else std::cout << "NO\n";
	}

	return 0;
}