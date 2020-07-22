

class ButtonAbstract
{
public:
	virtual void move(int x, int y) = 0;
	virtual void press(int x, int y) = 0;
	virtual void release(int x, int y) = 0;
	virtual void draw() = 0;
};