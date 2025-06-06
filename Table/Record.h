#pragma once

//структура табличной записи
template<typename TKey, typename TVal>

struct Record
{
	TKey key;
	TVal val;

	bool operator<=(const Record& r)
	{
		return (key <= r.key);
	}
	bool operator>=(const Record& r)
	{
		return (key >= r.key);
	}
	bool operator<(const Record& r)
	{
		return (key < r.key);
	}
	bool operator>(const Record& r)
	{
		return (key > r.key);
	}
	bool operator==(const Record& r)
	{
		return (key == r.key);
	}
	bool operator!=(const Record& r)
	{
		return (key != r.key);
	}
	friend std::ostream& operator<<(std::ostream& os, const Record<TKey, TVal>& r)
	{
		os << "Key: " << r.key << ", Value: " << r.val;
		return os;
	}
};