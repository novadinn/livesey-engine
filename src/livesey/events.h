#ifndef EVENTS_H
#define EVENTS_H

namespace Livesey {
    enum EventType {
	I_KEY,
	I_CHAR,
	I_CURSOR_POS,
	I_CURSOR_ENTER,
	I_MOUSE_BUTTON,
	I_SCROLL,
	// TODO: I_JOYSTICK, glfwSetJoystickUserPointer

	W_CLOSE,
	W_SIZE,
	W_FRAMEBUFFER_SIZE,
	W_CONTENT_SCALE,
	W_POS,
	W_ICONIFY,
	W_MAXIMIZE,
	W_FOCUS,
	W_REFRESH
    };

    struct Event {
	virtual ~Event() = default;
	
	inline virtual EventType getType() const = 0;
    };

    struct KeyEvent : public Event {
	KeyEvent(int k, int sc, int acts, int mods) :
	    k_(k), sc_(sc), acts_(acts), mods_(mods) {}

	inline int getKey() const { return k_; }
	inline int getScanCode() const { return sc_; }
	inline int getActions() const { return acts_; }
	inline int getMods() const { return mods_; }	
	inline virtual EventType getType() const override { return EventType::I_KEY; }
	
    private:
	int k_, sc_, acts_, mods_;
    };
    
    struct CharEvent : public Event {
	CharEvent(unsigned int cp) : cp_(cp) {}

	inline unsigned int getCodePoint() const { return cp_; }	
	inline virtual EventType getType() const override { return EventType::I_CHAR; }

    private:
	unsigned int cp_;
    };
    
    struct CursorPosEvent : public Event {
	CursorPosEvent(double x, double y) : x_(x), y_(y) {}

	inline double getX() const { return x_; }
	inline double getY() const { return y_; }
	inline virtual EventType getType() const override { return EventType::I_CURSOR_POS; }

    private:
	double x_, y_;
    };
    
    struct CursorEnterEvent : public Event {
	CursorEnterEvent(int e) : e_(e) {}

	inline int getEntered() const { return e_; }
	inline virtual EventType getType() const override { return EventType::I_CURSOR_ENTER; }

    private:
	int e_;
    };
    
    struct MouseButtonEvent : public Event {
	MouseButtonEvent(int b, int acts, int mods) : b_(b), acts_(acts), mods_(mods) {}

	inline int getButton() const { return b_; }
	inline int getActions() const { return acts_; }
	inline int getMods() const { return mods_; }
	inline virtual EventType getType() const override { return EventType::I_MOUSE_BUTTON; }

    private:
	int b_, acts_, mods_;
    };
    
    struct ScrollEvent : public Event {
	ScrollEvent(double x, double y) : x_(x), y_(y) {}

	inline double getXOffset() const { return x_; }
	inline double getYOffset() const { return y_; }
	inline virtual EventType getType() const override { return EventType::I_SCROLL; }

    private:
	double x_, y_;
    };    

    struct CloseEvent : public Event {
	CloseEvent() = default;
	
	inline virtual EventType getType() const override { return EventType::W_CLOSE; }
    };
    
    struct SizeEvent : public Event {
	SizeEvent(int w, int h) : w_(w), h_(h) {}

	inline int getWidth() const { return w_; }
	inline int getHeight() const { return h_; }
	inline virtual EventType getType() const override { return EventType::W_SIZE; }

    private:
	int w_, h_;
    };
    
    struct FramebufferSizeEvent : public Event {
	FramebufferSizeEvent(int w, int h) : w_(w), h_(h) {}

	inline int getWidth() const { return w_; }
	inline int getHeight() const { return h_; }
	inline virtual EventType getType() const override { return EventType::W_FRAMEBUFFER_SIZE; }

    private:
	int w_, h_;
    };
    
    struct ContentScaleEvent : public Event {
	ContentScaleEvent(float x, float y) : x_(x), y_(y) {}

	inline float getXScale() const { return x_; }
	inline float getYScale() const { return y_; }
	inline virtual EventType getType() const override { return EventType::W_CONTENT_SCALE; }

    private:
	float x_, y_;
    };
    
    struct PosEvent : public Event {
	PosEvent(int x, int y) : x_(x), y_(y) {}

	inline int getX() const { return x_; }
	inline int getY() const { return y_; }
	inline virtual EventType getType() const override { return EventType::W_POS; }

    private:
	int x_, y_;
    };
    
    struct IconifyEvent : public Event {
	IconifyEvent(int ic) : ic_(ic) {}

	inline int getIconified() const { return ic_; }
	inline virtual EventType getType() const override { return EventType::W_ICONIFY; }

    private:
	int ic_;
    };
    
    struct MaximizeEvent : public Event {
	MaximizeEvent(int m) : m_(m) {}

	inline int getMaximized() const { return m_; }
	inline virtual EventType getType() const override { return EventType::W_MAXIMIZE; }

    private:
	int m_;
    };
    
    struct FocusEvent : public Event {
	FocusEvent(int f) : f_(f) {}

	inline int getFocused() const { return f_; }
	inline virtual EventType getType() const override { return EventType::W_FOCUS; }

    private:
	int f_;
    };
    
    struct RefreshEvent : public Event {
	RefreshEvent() = default;
	
	inline virtual EventType getType() const override { return EventType::W_REFRESH; }
    };
}

#endif // EVENTS_H
