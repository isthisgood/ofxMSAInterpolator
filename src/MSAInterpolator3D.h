
/**************************** 3D InterpolatorT (of Vec3) ****************************/

#pragma once

#include "MSAInterpolatorT.h"

namespace msa {
	
	typedef InterpolatorT<Vec3f> Interpolator3D;
	
	
    //--------------------------------------------------------------
	inline float lengthOf(const Vec3f& v) {
		return v.length();
	}
	
	
    //--------------------------------------------------------------
	// OpenGL ES compatibility added by Rob Seward
	// http://www.openframeworks.cc/forum/viewtopic.php?f=25&t=3767&p=19865
	inline void drawInterpolatorRaw(Interpolator3D spline, int dotSize = 20, int lineWidth = 4){
		int numItems = spline.size();
        if(numItems == 0) return;
		
		if(lineWidth) {
			glLineWidth(lineWidth);
			GLfloat* vertex = new GLfloat[numItems * 3];
			for(int i=0; i<numItems; i++) {
				vertex[i*3]		= spline.at(i).x;
				vertex[(i*3)+1] = spline.at(i).y;
				vertex[(i*3)+2] = spline.at(i).z;
			}
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, vertex);
			glDrawArrays(GL_LINE_STRIP, 0, numItems);
			delete[] vertex;
		}
		
		if(dotSize) {
			glPointSize(dotSize);
			GLfloat* vertex = new GLfloat[numItems * 3];
			for(int i=0; i<numItems; i++) {
				vertex[i*3]		= spline.at(i).x;
				vertex[(i*3)+1] = spline.at(i).y;
				vertex[(i*3)+2] = spline.at(i).z;
			}
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, vertex);
			glDrawArrays(GL_POINTS, 0, numItems);
			delete[] vertex;
		}		
	}
	
	
    //--------------------------------------------------------------
	inline void drawInterpolatorSmooth(Interpolator3D spline, int numSteps, int dotSize = 8, int lineWidth = 2) {
		float spacing = 1.0/numSteps;
        if(spline.size() == 0) return;
        
		if(lineWidth) {
			glLineWidth(lineWidth);
			
			GLfloat* vertex = new GLfloat[numSteps * 3];
			int i=0;
			for(float f=0; f<1; f+= spacing) {
				Vec3f v			= spline.sampleAt(f);
				vertex[i*3]		= v.x;
				vertex[(i*3)+1] = v.y;
				vertex[(i*3)+2] = v.z;
				i++;
			}
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, vertex);
			glDrawArrays(GL_LINE_STRIP, 0, numSteps);
			delete[] vertex;
		}
		
		if(dotSize) {
			glPointSize(dotSize);
			GLfloat* vertex = new GLfloat[numSteps * 3];
			int i=0;
			for(float f=0; f<1; f+= spacing) {
				Vec3f v			= spline.sampleAt(f);
				vertex[i*3]		= v.x;
				vertex[(i*3)+1] = v.y;
				vertex[(i*3)+2] = v.z;
				i++;
			}
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, vertex);
			glDrawArrays(GL_POINTS, 0, numSteps);
			delete[] vertex;
		}
	}
	
}