#include "walls.h"

void Walls::addWall(GsPnt2 c1, GsPnt2 c2, GsPnt2 c3, GsPnt c4)
{
	struct line *l;
	l = new line;
	l->p1 = c1;l->p2 = c2;
	wall.push_back(l);
	l = new line;
	l->p1 = c2;l->p2 = c3;
	wall.push_back(l);
	l = new line;
        l->p1 = c3;l->p2 = c4;
        wall.push_back(l);
	l = new line;
        l->p1 = c4;l->p2 = c1;
        wall.push_back(l);
}

void Walls::printWalls()
{
	for( int i=0; i<wall.size(); i++ )
	{
		gsout << "Walls::printWall: "<<wall[i]->p1<<","<<wall[i]->p2<<gsnl;
	}
}

bool Walls::queryIntersection(GsPnt2 p1, GsPnt2 p2)
{
	float x, y;
	bool ret;
	for( int i=0; i<wall.size(); i++ )
	{
		float detL1 = Det(wall[i]->p1.x, wall[i]->p1.y, wall[i]->p2.x, wall[i]->p2.y);
		float detL2 = Det(p1.x, p1.y, p2.x, p2.y);
		float x1mx2 = wall[i]->p1.x - wall[i]->p2.x;
		float x3mx4 = p1.x - p2.x;
		float y1my2 = wall[i]->p1.y - wall[i]->p2.y;
		float y3my4 = p1.y - p2.y;

		float xnom = Det(detL1, x1mx2, detL2, x3mx4);
		float ynom = Det(detL1, y1my2, detL2, y3my4);
		float denom = Det(x1mx2, y1my2, x3mx4, y3my4);

		if(denom == 0.0f)
		{
			return false;
		}


		x = xnom / denom;	
		y = ynom / denom;

		float min_wall_x = std::min(wall[i]->p1.x, wall[i]->p2.x);
		float min_wall_y = std::min(wall[i]->p1.y, wall[i]->p2.y);
		float max_wall_x = std::max(wall[i]->p1.x, wall[i]->p2.x);
		float max_wall_y = std::max(wall[i]->p1.y, wall[i]->p2.y);
		float min_p_x = std::min(p1.x, p2.x);
		float min_p_y = std::min(p1.y, p2.y);
		float max_p_x = std::max(p1.x, p2.x);
		float max_p_y = std::max(p1.y, p2.y);
		gsout << "Min-max x of wall: " << min_wall_x << "," << max_wall_x << gsnl;
		gsout << "Min-max y of wall: " << min_wall_y << "," << max_wall_y << gsnl;
		gsout << "Min-max x of p: " << min_p_x << "," << max_p_x << gsnl;
		gsout << "Min-max y of p: " << min_p_y << "," << max_p_y << gsnl;

		bool xgwx = (x > min_wall_x || x == min_wall_x);
		bool xlwx = (x < max_wall_x || x == max_wall_x);
		bool ygwy = (y > min_wall_y || y == min_wall_y);
		bool ylwy = (y < max_wall_y || y == max_wall_y);
		gsout << "y less than wall y" << (y == max_wall_y) << gsnl;
		bool xgpx = (x > min_p_x || x == min_p_x);
                bool xlpx = (x < max_p_x || x == max_p_x);
                bool ygpy = (y > min_p_y || y == min_p_y);
                bool ylpy = (y < max_p_y || y == max_p_y);

		float trialx1 = x-min_wall_x;
		float trialx2 = x-max_wall_x;
		//if(trialx1 == trialx2) xlwx = true;
		gsout << "trailing a new x xor op: " << trialx1<<","<<trialx2<<","<<xlwx<< gsnl;

		float trialy1 = y-min_wall_y;
		float trialy2 = y-max_wall_y;
		//if(trialy1 == trialy2) ylwy = true;
		gsout << "trailing a new y xor op: " << trialy1<<","<<trialy2<<","<<ylwy<< gsnl;

		float px1 = x-min_p_x;
		float px2 = x-max_p_x;
		//xlpx = (px1 == px2);

		float py1 = y-min_p_y;
		float py2 = y-max_p_y;
		//ylpy = (py1 == py2);
		
		gsout << x << " x grea than wall_x " << min_wall_x << xgwx << gsnl;
		gsout << x << " x less than wall_x " << max_wall_x << xlwx << gsnl;
		gsout << y << " y grea than wall_y " << min_wall_y << ygwy << gsnl;
		gsout << y << " y less than wall_y " << max_wall_y << ylwy << gsnl;
		gsout << x << " x grea than poin x " << min_p_x << xgpx << gsnl;
		gsout << x << " x less than poin_x " << max_p_x << xlpx << gsnl;
		gsout << y << " y grea than poin_y " << min_p_y << ygpy << gsnl;
		gsout << y << " y less than poin_y " << max_p_y << ylpy << gsnl;
		if(xgwx && xlwx &&
		   ygwy && ylwy &&
		   xgpx && xlpx &&
		   ygpy && ylpy)
		{
		    	gsout << "col Wall : (" << wall[i]->p1 << "," << wall[i]->p2 << ")" <<
				"and line: (" << p1 << "," << p2 << "): at" << 
				x << "," << y << gsnl;
		    	ret = false;
			break;
		}
		else
		{
			gsout << "no col Wall : (" << wall[i]->p1 << "," << wall[i]->p2 << ")" <<
				"and line: (" << p1 << "," << p2 << "): at" << 
				x << "," << y << gsnl;
			ret = true;
		}
	}
	return ret;
}
