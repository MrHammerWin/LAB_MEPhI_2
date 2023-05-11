
template <class T>
class Sequence
{
public:

	//конструкторы и деструктор
	virtual Sequence(T* items, int count) = 0;
	virtual Sequence() = 0;
	virtual Sequence(Sequence<T>& seq const) = 0;
	virtual ~Sequence() {};

	//декомпозиция
	virtual T GetFirst() = 0;
	virtual T GetLast() = 0;
	virtual T Get(int index) = 0;
	virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;
	virtual int GetLength() = 0;

	//операции
	virtual void Append(T item) = 0;
	virtual void Prepend(T item) = 0;
	virtual void InsertAt(T item, int index) = 0;
	virtual Sequence<T>* Concat(Sequence<T>* seq) = 0;

};
