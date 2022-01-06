class List {
private:
	int* numsPtr;
	int length;

public:
	List(int size);

	void addNum(int num);

	int getNumAt(int loc);

	int getLastNum();

	void deleteNums();

	int getLength();
};