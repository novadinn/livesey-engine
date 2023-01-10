#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include <glm/glm.hpp>

namespace Livesey {

    struct OrthographicCamera {
	OrthographicCamera();
	OrthographicCamera(float w, float h);
	OrthographicCamera(float w, float h, float size, float near, float far);
	
	void onResize(float w, float h);
	
	inline const glm::mat4& getViewMatrix() const { return view_; }
	inline const glm::mat4& getProjectionMatrix() const { return proj_; }

	void setPosition(glm::vec2 v) { pos_ = v; recalcView(); }
	inline const glm::vec2& getPosition() const { return pos_; }
	void setRotation(float v) { rot_ = v; recalcView(); }
	inline float getRotation() const { return rot_; }

	void setSize(float v) { size_ = v; recalcProj(); }
	inline float getSize() const { return size_; }
	void setNear(float v) { near_ = v; recalcProj(); }
	inline float getNear() const { return near_; }
	void setFar(float v) { far_ = v; recalcProj(); }
	inline float getFar() const { return far_; }
	
    private:
	void recalcProj();
	void recalcView();
	
	glm::mat4 view_ = glm::mat4(1.0f);
	glm::mat4 proj_ = glm::mat4(1.0f);

	glm::vec2 pos_ = glm::vec2(0.0f);
	float rot_ = 0.0f;

	float size_ = 1.0f;
	float near_ = -1.0f;
	float far_ = 1.0f;
	float ar_ = 0.0f;
    };
}

#endif // ORTHOGRAPHIC_CAMERA_H
