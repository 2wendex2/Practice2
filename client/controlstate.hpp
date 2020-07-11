class ControlState
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void mousePress(int x, int y) = 0;
	virtual void charGet(char c) = 0;
};