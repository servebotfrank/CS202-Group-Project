#ifndef GAME_OBJECTS_H_P_P
#define GAME_OBJECTS_H_P_P

struct Vec2 {
	float x, y;
};

class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	virtual void draw() const = 0;
	virtual void updatePhysics() = 0;

	static int howMany();
private:
	int weight_;
	Vec2 velocity_;

	static int objectCount;
};



class Robot : public GameObject {
public:
	Robot();

	virtual void draw() const override;
	virtual void updatePhysics() override;
private:

};



class Platform : public GameObject {
public:
	Platform();

	virtual void draw() const override;
	virtual void updatePhysics() override;
private:

};

#endif
