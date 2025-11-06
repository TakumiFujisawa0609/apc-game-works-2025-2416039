#pragma once
class Stage
{
public:




	// ïWèÄÇÃé©å»î≠åıêF
	static constexpr COLOR_F COLOR_EMI_DEFAULT = { 0.5f, 0.5f, 0.5f, 0.5f };

	Stage();
	~Stage();
	void Init();
	void Update();
	void Draw();



private:
	
	int model_;
	VECTOR pos_;
	VECTOR localRot_;
	VECTOR rot_;
	VECTOR scl_;

};

