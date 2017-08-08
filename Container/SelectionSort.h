#ifndef SELECTIONSORT_H_
#define SELECTIONSORT_H_

#include <vector>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <numeric>

static unsigned int MAX = 50;

template<typename T>
class VectorWrapper
{
private:
	std::vector<T> bag;
	VectorWrapper(const VectorWrapper&);
	int recursion;
	//VectorWrapper& operator=(const VectorWrapper&);
protected:
	void Compare(const int& pos);
	void Insert(const int& pos, const int& gap);
	void ShellSortHelper(const int& gap);
	void MergeSortHelper(int begin, int end);
	void Merge(int begin, int mid, int end);
	void MergeCreate(int begin, int mid, int end);
	void RecursiveInsert(std::vector<T>& ouput,
		int index1, int index1_end, int index2, int index2_end);
public:
	int Partition(std::vector<T>& input, int begin, int end);
public:
	explicit VectorWrapper() {}
	explicit VectorWrapper(const unsigned int& capacity);
	~VectorWrapper()
	{
		bag.resize(0);
	}
	std::vector<T>& GetVector()
	{
		return bag;
	}

	void Init(const unsigned int& capacity);

	void SelectionSort();
	void InsertionSort();
	void ShellSort();
	void MergeSort();
};

template<typename T>
VectorWrapper<T>::VectorWrapper(const unsigned int& capacity)
{
	Init(capacity);
	recursion = 0;
}

template<typename T>
void VectorWrapper<T>::Init(const unsigned int& capacity)
{
	bag.resize(capacity);
	srand(time(NULL));
	//srand(12345);
	//	Generate integers for test
	for (auto i = 0; i < capacity; i++)
	{
		bag[i] = rand() % MAX + 1;
	}
	//	Display
	/*for (auto i : bag)
	{
	std::cout << i << ", ";
	}*/
}

template<typename T>
void VectorWrapper<T>::SelectionSort()
{
	if (bag.size() <= 1)
		return;

	int capacity = bag.size();

	for (auto i = 0; i < capacity; i++)
	{
		Compare(i);
	}
}

template<typename T>
void VectorWrapper<T>::InsertionSort()
{
	if (bag.size() <= 1)
		return;

	int capacity = bag.size();

	for (auto i = 1; i < capacity; i++)
	{
		Insert(i, 1);
	}

	/*for (auto i : bag)
	{
		std::cout << i << ", ";
	}*/
}

template<typename T>
void VectorWrapper<T>::ShellSort()
{
	int gaps[] = { 701, 301, 132, 57, 23, 10, 4, 1 };
	if (bag.size() <= 1)
		return;

	for (auto gap : gaps)
	{
		ShellSortHelper(gap);
	}
	/*for (auto i : bag)
	{
		std::cout << i << ", ";
	}*/
}

template<typename T>
void VectorWrapper<T>::MergeSort()
{
	if (bag.size() <= 1)
		return;
	MergeSortHelper(0, bag.size() - 1);
	for (auto i = 0; i <= 50; i++)
	{
	std::cout << bag[i] << ", ";
	}
}

template<typename T>
void VectorWrapper<T>::MergeSortHelper(int begin, int end)
{
	/*std::cout << std::endl;
	std::cout << "Begin: " << begin << " End: " << end;
	std::cout << std::endl;*/
	if (begin >= end)
		return;

	int mid = (begin + end) / 2;
	MergeSortHelper(begin, mid);
	/*std::cout << std::endl;
	for (auto i : bag)
	{
		std::cout << i << ", ";
	}
	std::cout << std::endl;*/
	MergeSortHelper(mid + 1, end);
	/*std::cout << std::endl;
	for (auto i : bag)
	{
		std::cout << i << ", ";
	}
	std::cout << std::endl;*/
	
	//Merge(begin, mid, end);
	if (end - begin <= 31)
	{
		//	Insertion Sort for small arrays
		Merge(begin, mid, end);
	}
	else
	{
		MergeCreate(begin, mid, end);
	}
}

template<typename T>
void VectorWrapper<T>::Merge(int begin, int mid, int end)
{
	//std::cout << "Merge " << begin << ", " << mid << ", " << end << std::endl;
	if (bag[mid] <= bag[mid + 1])
		return;
	for (auto i = begin + 1; i <= end; i++)
	{
		for (auto j = begin; j < i; j++)
		{
			if (bag[i] < bag[j])
			{
				if (j == i - 1)
				{
					//	Exchange
					T holder = bag[i];
					bag[i] = bag[j];
					bag[j] = holder;
				}
				else
				{
					//	Push and insert
					T holder = bag[i];
					for (auto k = i; k > j; k--)
					{
						bag[k] = bag[k - 1];
					}
					bag[j] = holder;
				}
				break;
			}
		}
	}
}

template<typename T>
void VectorWrapper<T>::MergeCreate(int begin, int mid, int end)
{
	//	If it's alreadt in order, do not need to merge
	if (bag[mid] <= bag[mid + 1])
	{
		return;
	}

	//	If each half is only 1 element
	if (begin == end - 1)
	{
		if (bag[begin] > bag[end])
		{
			T holder = bag[begin];
			bag[begin] = bag[end];
			bag[end] = holder;
		}
		return;
	}

	////	If it's small, use Insertion Sort
	//if (end - begin <= 32)
	//{
	//	if (bag[mid] <= bag[mid + 1])
	//	return;
	//	for (auto i = begin + 1; i <= end; i++)
	//	{
	//		for (auto j = begin; j < i; j++)
	//		{
	//			if (bag[i] < bag[j])
	//			{
	//				if (j == i - 1)
	//				{
	//					//	Exchange
	//					T holder = bag[i];
	//					bag[i] = bag[j];
	//					bag[j] = holder;
	//				}
	//				else
	//				{
	//					//	Push and insert
	//					T holder = bag[i];
	//					for (auto k = i; k > j; k--)
	//					{
	//						bag[k] = bag[k - 1];
	//					}
	//					bag[j] = holder;
	//				}
	//				break;
	//			}
	//		}
	//	}
	//}

	//	Merge by creating new std::vector
	std::vector<T> new_vector;
	//new_vector.reserve(end - begin + 1);
	RecursiveInsert(new_vector, begin, mid, mid + 1, end);
	for (auto i = begin; i <= end; i++)
	{
		bag[i] = new_vector[i - begin];
	}
}

template<typename T>
void VectorWrapper<T>::RecursiveInsert(std::vector<T>& output,
	int index1, int index1_end, int index2, int index2_end)
{
	while (1)
	{
		//	Stop when either half is exhausted
		if (index1 > index1_end)
		{
			//	First half is exhausted
			//	Simply put everything from index2 to end into output
			for (auto i = index2; i <= index2_end; i++)
			{
				output.push_back(bag[i]);
			}
			break;
		}

		if (index2 > index2_end)
		{
			//	Second half is exhausted
			//	Simply put everything from index1 to mid into o
			for (auto i = index1; i <= index1_end; i++)
			{
				output.push_back(bag[i]);
			}
			break;
		}

		//	Neither half is exhausted
		if (bag[index1] >= bag[index2])
		{
			output.push_back(bag[index2]);
			index2 += 1;
		}
		else
		{
			output.push_back(bag[index1]);
			index1 += 1;
		}
	}

	//if (index1 > index1_end)
	//{
	//	//	First half is exhausted
	//	//	Simply put everything from index2 to end into output
	//	for (auto i = index2; i <= index2_end; i++)
	//	{
	//		output.push_back(bag[i]);
	//	}
	//	return;
	//}
	//
	//if (index2 > index2_end)
	//{
	//	//	Second half is exhausted
	//	//	Simply put everything from index1 to mid into o
	//	for (auto i = index1; i <= index1_end; i++)
	//	{
	//		output.push_back(bag[i]);
	//	}
	//	return;
	//}

	////	Neither half is exhausted
	//if (bag[index1] >= bag[index2])
	//{
	//	output.push_back(bag[index2]);
	//	index2 += 1;
	//}
	//else
	//{
	//	output.push_back(bag[index1]);
	//	index1 += 1;
	//}
	//RecursiveInsert(output, index1, index1_end, index2, index2_end);
}

template<typename T>
void VectorWrapper<T>::ShellSortHelper(const int& gap)
{
	int capacity = bag.size();

	for (auto i = gap; i < capacity; i += gap)
	{
		Insert(i, gap);
	}
}

template<typename T>
void VectorWrapper<T>::Compare(const int& pos)
{
	//	Compare bag[pos] with smallest element in bag[pos]~bag[capacity-1]
	int walker = pos;
	int capacity = bag.size();
	for (auto i = pos + 1; i < capacity; i++)
	{
		if (bag[i] < bag[walker])
			walker = i;
	}
	//	Exchange bag[pos] and bag[walker]
	T holder = bag[pos];
	bag[pos] = bag[walker];
	bag[walker] = holder;
}

template<typename T>
void VectorWrapper<T>::Insert(const int& pos, const int& gap)
{
	//	Insert bag[pos] into bag[0], bag[gap], ... bag[pos - gap]
	int walker = pos;
	for (auto i = 0; i <= pos - 1; i+=gap)
	{
		if (bag[i] > bag[walker])
		{
			walker = i;
			break;
		}
	}
	//	insert bag[pos] into bag[walker]
	if (walker == 0 && pos == gap)
	{
		//	Exchange bag[pos] and bag[walker]
		T holder = bag[pos];
		bag[pos] = bag[walker];
		bag[walker] = holder;
	}
	else
	{
		//	Move bag[pos] to bag[walker]
		//	Move bag[walker] to bag[walker+1] for elements from walker to pos-1
		T holder = bag[pos];
		for (auto i = pos; i > walker; i -= gap)
		{
			bag[i] = bag[i - 1];
		}
		bag[walker] = holder;
	}
}

template<typename T>
int VectorWrapper<T>::Partition(std::vector<T>& input, int begin, int end)
{
	//	Debug
	for (auto i : input)
	{
		std::cout << i << ", ";
	}
	
	//	Small arrays are sorted by insertion sort, no need to worry
	//	You need to implement insertion sort in QuickSort()

	float average = std::accumulate(input.begin(), input.end(), 0) / input.size();
	int walker1 = begin;
	int walker2 = end;

	while (1)
	{
		//	STOPPING criteria
		if (walker1 >= walker2)
		{
			//	Debug
			std::cout << "Average is: " << average << std::endl;
			for (auto i : input)
			{
				std::cout << i << ", ";
			}
			return walker1 - 1;	//	return what?
		}

		//	Walking
		if (bag[walker1] > average)
		{
			if (bag[walker2] < average)
			{
				//	Make exchange only when both are satisfied
				T temp = bag[walker1];
				bag[walker1] = bag[walker2];
				bag[walker2] = temp;
				walker2 -= 1;
				walker1 += 1;
			}
		}
		else
		{
			if (bag[walker2] < average)
			{
				walker1 += 1;
			}
			walker2 -= 1;
		}
	}

	
}

#endif