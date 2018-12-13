#include <stdlib.h>
#include <thread>
#include <chrono>
#include <math.h>
#include <deque>
#include <sig/gs_vec.h>
#include <sig/gs_input.h>
#include <sig/sn_lines.h>
#include <sig/gs_output.h>
#include <sig/gs_mat.h>

#include "walls.h"

struct Node
{
	std::vector <Node*> children;
	Node *parent;
	pnt p;
};

struct Robot
{
	float m;
	GsVec pos;
	GsVec vel;
	GsVec steer_dir;
	float max_force;
	float max_speed;
};

class RRTGraph
{
    protected:
    	Walls *walls_;
	int alpha_, maxi_;
	pnt goal_;
	float reach_thresh_;
	float win_height_, win_width_;
	Node *root_, *last_node_;
	Robot *robo_;
	std::vector <Node*> nodes_;
	std::vector <Node*> path_;
	float slowing_distance = 2.0f;
	GsMat *position_;
	bool path_computed_;
	bool new_goal_;
	void deleteNodes(Node* root_);
    public:
     	enum obj_type{ ROBOT, WALL, GOAL };
	RRTGraph();
	void init(GsPnt2 start, float rt, float win_w, float win_h, GsMat* pos);
	void setGoal(GsVec a);
	GsVec getPosition(){ return robo_->pos; }
	Node* getRandomNode();
	Node* nearestPoint(pnt p);
	pnt findConfig(Node *c, Node *c_near);
	void addConfig(Node *cN, Node *c_new);
	bool reached();
	void printWalls() { walls_->printWalls(); }
	void run(SnLines *pl, SnLines *gl);
	void performRRT(SnLines* pl, SnLines* gl);
	void addWall(pnt c1, pnt c2, pnt c3, pnt c4)
	{
		walls_->addWall(c1, c2, c3, c4);
	}
	std::vector<pnt> getNodePoints();
	std::vector<pnt> getPathPoints();
	void eulerIntegration();
	GsVec truncate(GsVec v, float t);
	void steering(GsVec g);
	float magnitude(GsVec v)
	{
		return(sqrtf(v.x*v.x + v.y*v.y + v.z*v.z));
	}
};
