#include "orthographic_camera.h"

namespace Livesey {

    OrthographicCamera::OrthographicCamera() {
	recalcView();
	recalcProj();
    }

    OrthographicCamera::OrthographicCamera(float w, float h) {
	ar_ = w/h;

	recalcView();
	recalcProj();
    }
    
    OrthographicCamera::OrthographicCamera(float w, float h, float size, float near, float far) :
	size_(size), near_(near), far_(far) {

	ar_ = w/h;
	recalcView();
	recalcProj();
    }
	
    void OrthographicCamera::onResize(float w, float h) {
	ar_ = w/h;
	recalcProj();
    }

    void OrthographicCamera::recalcProj() {
	float left = -size_ * ar_;
	float right = size_ * ar_;
	float bottom = -size_;
	float top = size_;
	
	proj_ = glm::ortho(left, right, bottom, top, near_, far_);
    }
    
    void OrthographicCamera::recalcView() {
	view_ = glm::mat4(1.0f);
	view_ = glm::translate(view_, glm::vec3(pos_, 0.0f));
	view_ = glm::rotate(view_, glm::radians(rot_),
			    glm::vec3(0.0f, 0.0f, 1.0f));
    }
}
