
template <class T>
class Sequence
{
public:
	
	// деструктор
	virtual ~Sequence() {};

	// декомпозиция
	virtual T GetFirst() = 0;
	virtual T GetLast() = 0;
	virtual T Get(int index) = 0;
	virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;
	virtual size_t GetLength() = 0;

	// операции
	virtual void Append(T item) = 0;
	virtual void Prepend(T item) = 0;
	virtual void InsertAt(T item, int index) = 0;
	virtual Sequence<T>* Concat(Sequence<T>* seq) = 0;

};
